/*
 * case_mode.c — Real‑time case-transformation engine for QMK
 *
 * This module implements a deterministic, low-overhead “case mode” system
 * that transforms text *as it is typed*. Unlike post-processing filters,
 * case modes operate on each keystroke in real time and never require
 * look-ahead, buffering, or semantic analysis.
 *
 * Supported modes:
 *   • camelCase
 *   • PascalCase
 *   • snake_case
 *   • SCREAMING_SNAKE_CASE
 *   • kebab-case
 *   • dot.case
 *   • path/to/case
 *   • PUNC (auto-capitalize the next character after punctuation)
 *
 * Core behavior:
 *   1. Intercept separator keys (space, dash, underscore, slash)
 *   2. Replace them with the mode-appropriate separator, or swallow them
 *      entirely (camelCase / PascalCase)
 *   3. Apply one-shot shift when capitalization is required
 *   4. Maintain minimal state: active mode, idle timer, first-character flag,
 *      and whether the next character should be capitalized
 *
 * Design notes:
 *   • This module never rewrites keycodes. It only adjusts modifiers and
 *     optionally suppresses separators. This keeps it compatible with
 *     tap-dance, mod-tap, layer-tap, Unicode macros, and other QMK features.
 *
 *   • case_mode_alpha_transform() must be called *before* sending alphabetic
 *     keycodes so that one-shot shift can be applied correctly.
 *
 *   • case_mode_separator() should be called during keycode translation
 *     (before the key is emitted) to normalize separators for the active mode.
 *
 *   • Modes are fully deterministic and require no buffering, making them
 *     safe for real-time firmware use.
 *
 * Integration points:
 *   • process_record_user():
 *         - Call case_mode_separator() before emitting separators
 *         - Call case_mode_alpha_transform() before emitting A–Z
 *         - Call case_mode_update() after emitting any “meaningful” key
 *
 *   • matrix_scan_user():
 *         - Call case_mode_scan() to enforce idle timeout behavior
 *
 * This file contains only the state machine and transformation logic.
 * The keymap is responsible for invoking these functions at the correct
 * points in the QMK event pipeline.
 */

#include "case_mode.h"
#include "utils.h"
#include "src/core/keymap.h"

// Global case-mode state
static case_state_t case_state = {
    .active = false,
    .mode = CASE_OFF,
    .timer = 0,
    .capitalize_next = false,
    .first_char = true,
};

// Returns true if a given keycode is a valid character, editing, or arrow key.
static bool is_valid_char(const uint16_t keycode) {
    switch (keycode) {
        // Standard and numpad separators
        case KC_UNDS:
            return case_state.mode == CASE_SNAKE || case_state.mode == CASE_CONST ? true : false;
        case KC_MINUS:
        case KC_KP_MINUS:
            return case_state.mode == CASE_KEBAB ? true : false;
        case KC_SLSH:
        case KC_KP_SLASH:
        case SLSH_HYPR: // NOTE: Mod-tap key defined in keymap.h
            return case_state.mode == CASE_PATH ? true : false;
        case KC_DOT:
        case KC_KP_DOT:
            return case_state.mode == CASE_DOT ? true : false;

        // Exceptions
        case KC_NO: // Handle camelCase and PascalCase char swallowing
            return case_state.capitalize_next
                && (case_state.mode == CASE_CAMEL || case_state.mode == CASE_PASCAL) ? true : false;
        case KC_TAB: // Allow for shell tab completion
            return case_state.mode == CASE_PATH ? true : false;

        // Alphabetic
        case KC_A ... KC_Z:

        // Number row digits
        case KC_1 ... KC_0:

        // Numpad digits
        case KC_KP_0:
        case KC_KP_1:
        case KC_KP_2:
        case KC_KP_3:
        case KC_KP_4:
        case KC_KP_5:
        case KC_KP_6:
        case KC_KP_7:
        case KC_KP_8:
        case KC_KP_9:

        // Editing and movement
        case KC_BSPC:
        case KC_DEL:
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RGHT:
            return true;

        default:
            return false;
    }
}

// ─────────────────────────────────────────────────────────────
// Public API
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// Getter Functions
// ──────────────────────────────

// Returns true if any case mode is currently active.
bool is_case_mode_on(void) {
    return case_state.active;
}

// Returns the current case mode of the global state.
case_mode_t case_mode(void) {
    return case_state.mode;
}

/*
 * Intercepts separator keys (dash, dot, underscore, slash) and
 * returns the transformed separator appropriate for the active case mode.
 *
 * For camelCase and PascalCase:
 *   - The separator is swallowed (KC_NO)
 *   - capitalize_next is set so the next alpha character is capitalized
 *
 * For snake_case, kebab-case, dot.case, and path/to/case:
 *   - The separator is replaced with the mode's canonical separator
 *
 * For CASE_OFF:
 *   - The separator is returned unchanged
 *
 * Returns:
 *   - A transformed keycode
 *   - KC_NO if the separator should be swallowed
 */
uint16_t case_mode_separator(const uint16_t keycode) {
    switch (keycode) {
            case KC_SPACE:
            case KC_MINUS:
            case KC_UNDS:
            case KC_SLSH:
                switch (case_state.mode) {
                    case CASE_SNAKE:
                    case CASE_CONST:
                        return KC_UNDS;

                    case CASE_KEBAB:
                        return KC_MINUS;

                    case CASE_PATH:
                        return KC_SLSH;

                    case CASE_DOT:
                        return KC_DOT;

                    case CASE_CAMEL:
                    case CASE_PASCAL:
                        case_state.capitalize_next = true;
                        return KC_NO; // swallow separator
                    case CASE_OFF:
                    default:
                        return keycode;
                }
    }
    return keycode;
}

// ──────────────────────────────
// Setter Functions
// ──────────────────────────────

/*
 * Updates or terminates the active case mode based on the most recently
 * produced key.
 *
 * Behavior:
 *   • If case mode is active and the key is *not* considered a valid
 *     character (letters, digits, separators, editing/navigation keys),
 *     the mode is immediately turned off.
 *
 *   • If the key *is* valid, the idle timer is refreshed so that the mode
 *     remains active. This timer is used by case_mode_scan() to implement
 *     automatic timeout behavior.
 *
 * This function should be called after emitting any “meaningful” key so
 * that case mode can react to punctuation, symbols, or other terminating
 * characters.
 */
void case_mode_update(const uint16_t keycode) {
    if (is_case_mode_on() && !is_valid_char(keycode)) {
        case_mode_off();
    } else {
        case_state.timer = timer_read(); // Reset idle timer on each valid keystroke
    }
}

/*
 * Applies capitalization rules for the next alphabetic character.
 * This function should be called *before* sending A–Z keycodes.
 *
 * Behavior:
 *   - If capitalize_next is set, apply one-shot shift (camelCase, PascalCase)
 *   - For CONST_CASE, capitalization persists for all characters
 *   - For PUNC mode, capitalization applies to exactly one character,
 *     then the mode automatically turns off
 */
void case_mode_alpha_transform(void) {
    if (is_case_mode_on()) {
        if (case_state.capitalize_next) {
            add_oneshot_mods(MOD_LSFT);
        }
        case_state.capitalize_next = false;

        // case_punc is alive for exactly one char
        if (case_state.mode == CASE_PUNC) {
            case_mode_off();
        }
    }
}

// ──────────────────────────────
// On/Off Functions
// ──────────────────────────────

// Activates a case mode and initializes its state.
// PascalCase, SCREAMING_SNAKE_CASE and PUNC modes begin with `capitalize_next = true`.
void case_mode_on(case_mode_t mode) {
    case_state.active = true;
    case_state.mode = mode;
    case_state.timer = timer_read();
    case_state.capitalize_next =
        mode == CASE_PASCAL || mode == CASE_PUNC ? true : false;
    case_state.first_char = true;
    // Enable Caps Lock only for SCREAMING_SNAKE_CASE
    if (mode == CASE_CONST) {
        caps_lock_on();
    } else {
        caps_lock_off(); // Turn Caps Lock off, if it has been previously enabled
    }
}

// Deactivates case mode and resets mode to CASE_OFF.
void case_mode_off(void) {
    if (is_case_mode_on()) {
        // Disable caps lock for screaming_snake_case
        if (case_state.mode == CASE_CONST) {
            caps_lock_off();
        }
        case_state.active = false;
        case_state.mode = CASE_OFF;
    }
}

// Capitalize exactly one character, then turn off.
// Used for sentence-style auto-capitalization after punctuation.
void auto_cap_next_char_only(void) {
    // Guard: clear out any active modes
    if (case_state.active) {
        case_mode_off();
    }
    case_mode_on(CASE_PUNC);
}

// Called by matrix_scan_user to enforce the Case Mode timeout.
// If the mode is active and no valid key has been pressed within
// CASE_MODE_TIMEOUT, the mode is automatically turned off
void case_mode_scan(void) {
    if (case_state.active &&
        timer_elapsed(case_state.timer) > CASE_MODE_TIMEOUT) {
        case_mode_off();
    }
}

// ──────────────────────────────
// Toggle Functions
// ──────────────────────────────

// Toggles camelCase mode on/off.
void camel_case_toggle(void) {
    case_state.active && case_state.mode == CASE_CAMEL ? case_mode_off()
                                                       : case_mode_on(CASE_CAMEL);
}

// Toggles PascalCase mode on/off.
void pascal_case_toggle(void) {
    case_state.active && case_state.mode == CASE_PASCAL ? case_mode_off()
                                                        : case_mode_on(CASE_PASCAL);
}

// Toggles snake_case mode on/off.
void snake_case_toggle(void) {
    case_state.active && case_state.mode == CASE_SNAKE ? case_mode_off()
                                                       : case_mode_on(CASE_SNAKE);
}

// Toggles SCREAMING_SNAKE_CASE mode on/off.
void const_case_toggle(void) {
    case_state.active && case_state.mode == CASE_CONST ? case_mode_off()
                                                       : case_mode_on(CASE_CONST);
}

// Toggles path/to/case mode on/off.
void path_case_toggle(void) {
    case_state.active && case_state.mode == CASE_PATH ? case_mode_off()
                                                      : case_mode_on(CASE_PATH);
}

// Toggles kebab-case mode on/off.
void kebab_toggle(void) {
    case_state.active && case_state.mode == CASE_KEBAB ? case_mode_off()
                                                       : case_mode_on(CASE_KEBAB);
}
