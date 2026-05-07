/*
 * case_mode.h — Real‑time case-transformation engine for QMK
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

#pragma once

#include QMK_KEYBOARD_H

#define CASE_MODE_TIMEOUT 5000  // ms before Case Mode timeout

// ─────────────────────────────────────────────────────────────
// Case Mode Data Types
// ─────────────────────────────────────────────────────────────

typedef enum {
    CASE_OFF = 0,
    CASE_CAMEL,   // camelCase
    CASE_CONST,   // SCREAMING_SNAKE_CASE
    CASE_DOT,     // dot.case
    CASE_KEBAB,   // kebab-case
    CASE_PASCAL,  // PascalCase
    CASE_PATH,    // path/to/case/
    CASE_PUNC,    // Prose: end of sentence auto capitalization
    CASE_SNAKE,   // snake_case
} case_mode_t;

typedef struct {
    bool active;          // Is case mode active?
    case_mode_t mode;     // The kind of case mode
    uint16_t timer;       // How long has case mode been running?
    bool capitalize_next; // camelCase / PascalCase humps
    bool first_char;      // Is it on the first char?
} case_state_t;

// ─────────────────────────────────────────────────────────────
// Public API
// ─────────────────────────────────────────────────────────────

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
void case_mode_update(const uint16_t keycode);

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
void case_mode_alpha_transform(void);

// ──────────────────────────────
// Getter Functions
// ──────────────────────────────

// Returns true if any case mode is currently active.
bool is_case_mode_on(void);

// Returns the current case mode of the global state.
case_mode_t case_mode(void);

/*
 * Intercepts separator keys (dash, dot, underscore, slash) and returns
 * the transformed separator appropriate for the active case mode.
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
uint16_t case_mode_separator(const uint16_t keycode);

// ──────────────────────────────
// On/Off Functions
// ──────────────────────────────

// Activates a case mode and initializes its state.
// PascalCase and PUNC modes begin with `capitalize_next = true`.
void case_mode_on(case_mode_t mode);

// Deactivates case mode and resets mode to CASE_OFF.
void case_mode_off(void);

// Capitalize exactly one character, then turn off.
// Used for sentence-style auto-capitalization after punctuation.
void auto_cap_next_char_only(void);

// Called by matrix_scan_user to enforce the Case Mode timeout.
// If the mode is active and no valid key has been pressed within
// CASE_MODE_TIMEOUT, the mode is automatically turned off
void case_mode_scan(void);

// ──────────────────────────────
// Toggle Functions
// ──────────────────────────────

// Toggles camelCase mode on/off.
void camel_case_toggle(void);

// Toggles PascalCase mode on/off.
void pascal_case_toggle(void);

// Toggles snake_case mode on/off.
void snake_case_toggle(void);

// Toggles SCREAMING_SNAKE_CASE mode on/off.
void const_case_toggle(void);

// Toggles path/to/case mode on/off.
void path_case_toggle(void);

// Toggles kebab-case mode on/off.
void kebab_toggle(void);
