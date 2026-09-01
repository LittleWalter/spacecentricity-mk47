// ─────────────────────────────────────────────────────────────
// Spacecentricity — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// ─────────────────────────────────────────────────────────────

#include "custom_keys.h"
#include "keymap.h"
#include "src/features/case_mode.h"
#include "src/features/leader.h"
#include "src/features/rgb.h"
#include "src/features/utils.h"
#include "src/features/tapping_term.h"
#include "src/macros/mac_doom.h"
#include "src/macros/mac_programming.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_surround.h"
#include "src/macros/mac_system.h"
#include "src/macros/mac_terminal.h"
#include "src/macros/mac_vim.h"

os_t current_os = OS_MACOS; // Default to Apple macOS on boot

// ─────────────────────────────────────────────────────────────
// Custom Keycode Helpers
// ─────────────────────────────────────────────────────────────

#ifdef LEADER_ENABLE
// Track Leader sequence characters
static void leader_track(const uint16_t keycode) {
    if (leader_state.enabled && leader_state.active) {
        if (leader_state.size < LEADER_MAX_SEQUENCE_LENGTH) {
            leader_state.buffer[leader_state.size++] = keycode;
        }
    }
}
#endif

// ─────────────────────────────────────────────────────────────
// Custom Keycodes
// ─────────────────────────────────────────────────────────────
// Intercepts custom keycodes and runs their associated macros and miscellenous
// non-macros. This function handles all higher‑level behaviors that aren't
// simple keypresses, including programming n-grams (e.g., " += ", " == ",
// " := ", "++"), Vim navigation motions (gj/gk, buffer and tab movement, window
// resizing), viewport controls, and buffer‑level commands (write, quit,
// substitute). Returning false prevents QMK from sending the underlying
// keycode so the macro can fully replace it.
//
// Most logic functionally decomposed.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t mouse_key_timer; // Tracking key hold time, SEE:MOUSE_FN branch

    // Keycode preprocessing
    if (record->event.pressed) {
#ifdef LEADER_ENABLE
        leader_track(keycode);
#endif
        case_mode_alpha_transform();
    }

    switch (keycode) {
        // ─────────────────────────────────────────────────────────────
        // Terminal Macros
        // ─────────────────────────────────────────────────────────────
        case LS_TERM: // `ls -lah`: long list w/ human-readable values
            if (record->event.pressed) {
                ls_long_term_macro();
            }
            return false;
        case CD_HOME: // `cd ~`
            if (record->event.pressed) {
                cd_macro(COM_CD_HOME, true);
            }
            return false;
        case CD_PREV: // `cd -`
            if (record->event.pressed) {
                cd_macro(COM_CD_PREV, true);
            }
            return false;
        case CD_GITROOT:
            if (record->event.pressed) {
                cd_macro(COM_CD_GITROOT, true);
            }
            return false;
        case MKDIR: // `mkdir -p `
            if (record->event.pressed) {
                mkdir_macro();
            }
            return false;
        case TOUCH: // `touch `
            if (record->event.pressed) {
                touch_macro();
            }
            return false;
        case PING: // `ping `
            if (record->event.pressed)  {
                ping_macro();
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // Symbols
        // ─────────────────────────────────────────────────────────────
        case DEG: // Degree symbol (°)
            if (record->event.pressed) {
                special_char_macro(CHAR_DEGREE);
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // Vim
        // ─────────────────────────────────────────────────────────────
        case BUF_TOGGLE: // Switch to previously active buffer
            if (record->event.pressed){
                vim_buffer_toggle_macro();
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // Programming Macros
        // ─────────────────────────────────────────────────────────────
        case TERN: // ` ? :` w/ cursor placed at start
            if (record->event.pressed) {
                prog_operator_macro(OP_TERNARY, false);
            }
            return false;
        case VWS_CBR:
            if (record->event.pressed) {
                surround_macro(SUR_VWS_CBR);
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // App/Operating System Shortcuts (Non-Macros)
        // ─────────────────────────────────────────────────────────────
        case ALL: // Select All
            if (record->event.pressed) {
                select_all_macro();
            }
            return false;
        case COPY: // Copy Selected
            if (record->event.pressed) {
                copy_macro();
            }
            return false;
        case PASTE: // Paste from clipboard
            if (record->event.pressed) {
                paste_macro();
            }
            return false;
        case CUT: // Cut Selected
            if (record->event.pressed) {
                cut_macro();
            }
            return false;

        case VDT_LEFT: // Change to left virtual desktop/workspace
            if (record->event.pressed) {
                vdt_left_macro();
            }
            return false;
        case VDT_RIGHT:
            if (record->event.pressed) { // Change to right virtual desktop/workspace
                vdt_right_macro();
            }
            return false;

        case ZOOM_IN: // Browser Zoom In
            if (record->event.pressed) {
                zoom_in_macro();
            }
            return false;
        case ZOOM_OUT: // Browser Zoom Out
            if (record->event.pressed) {
                zoom_out_macro();
            }
            return false;
        case ZOOM_RESET: // Broswer Zoom Reset (100%)
            if (record->event.pressed) {
                zoom_reset_macro();
            }
            return false;
        case APP: // Trigger App Switching key when held
            case_mode_off();
            record->event.pressed ? app_switch_macro(true) : app_switch_macro(false);
            return false;

        // ─────────────────────────────────────────────────────────────
        // DOOM Macros
        // ─────────────────────────────────────────────────────────────
        case DOOM_PAUSE: // Pause Game
            if (record->event.pressed) {
                toggle_doom_pause();
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // Miscellaneous (Non-Macros)
        // ─────────────────────────────────────────────────────────────
        case TG_MOUSE: // Toggle mouse/previous layer
#ifdef MOUSEKEY_ENABLE
            if (record->event.pressed) {
                toggle_mouse();
            }
#endif
            return false;
        case MOUSE_FN: // Tap for mouse layer, hold for function keys layer
            if (record->event.pressed) {
                mouse_key_timer = timer_read();
            } else {
                mouse_fn(mouse_key_timer);
            }
            return false;
        case TG_OS: // Operating system toggle: macOS, Linux, Windows
            if (record->event.pressed) {
                case_mode_off();
                toggle_os();
            }
            return false;
        case TG_LEAD: // Toggle Leader Keys on/off
#ifdef LEADER_ENABLE
            if (record->event.pressed) {
                case_mode_off();
                toggle_leader();
            }
#endif
            return false;
        case TG_PATH_CASE:
            if (record->event.pressed) {
                path_case_toggle();
            }
            return false;
        case LIST_LEADER_ALL_SAVED:
            if (record->event.pressed) {
                leader_type_all();
            }
            return false;

#ifdef RGB_MATRIX_ENABLE
        // ─────────────────────────────────────────────────────────────
        // RGB Matrix Keys
        // ─────────────────────────────────────────────────────────────
        case RM_PREV:
        case RM_NEXT:
        case RM_VALD:
        case RM_VALU:
        case RM_HUED:
        case RM_HUEU:
        case RM_SPDD:
        case RM_SPDU:
        case RM_SATD:
        case RM_SATU:
            rgb_preview.triggered = true;
            rgb_preview.timer = timer_read();
            break;
#endif
        // ─────────────────────────────────────────────────────────────
        // Other keycodes
        // ─────────────────────────────────────────────────────────────
        default:
            // TODO: Maybe make SLSH_HYPR a tap-dance key
            if (keycode <= BASIC_KEYCODES || keycode == SLSH_HYPR) {
                case_mode_update(keycode);
            }
            break;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
// Mouse-related Function Definitions
// ─────────────────────────────────────────────────────────────

// Toggle the mouse layer and return to the previous layer. Because DOOM is entered through the
// MOUSE layer, its expected behavior is handled here to avoid conflicts with future layer logic.
#ifdef MOUSEKEY_ENABLE
void toggle_mouse(void) {
    const uint8_t current = get_highest_layer(layer_state);

    switch (current) {
        // If we're in MOUSE, turn it off and go back to the highest non-MOUSE, non-DOOM layer
        case _MOUSE:
            // Turn off mouse
            layer_off(_MOUSE);

            // Compute previous layer using bit masks, ignoring MOUSE and DOOM
            uint32_t state_without_mouse_doom =
                layer_state & ~(1UL << _MOUSE) & ~(1UL << _DOOM);

            uint8_t prev = get_highest_layer(state_without_mouse_doom);

            // Go back to that layer (BASE, LOWER, UPPER, etc.)
            layer_move(prev);
            break;
        // If we're in DOOM and hit the mouse toggle, treat it as "I'm done, go to BASE"
        case _DOOM:
            layer_off(_DOOM);
            layer_move(_BASE);
            break;
        // Otherwise, we're in BASE, LOWER, UPPER, etc. → turn MOUSE on
        default:
            layer_on(_MOUSE);
    }
}
#endif

// Switch to mouse layer on shorter key presses, otherwise go to function keys layer
void mouse_fn(uint16_t mouse_key_timer) {
    uint16_t elapsed = timer_elapsed(mouse_key_timer);
    // Tap behavior
    if (elapsed < TAPPING_TERM + MOUSE_FN_DELAY) {
#ifdef MOUSEKEY_ENABLE
        layer_on(_MOUSE);
#endif
    }
    // Hold behavior delayed
    else if (elapsed > TAPPING_TERM + MOUSE_FN_DELAY) {
        layer_on(_FN);
    }
}

// Toggle operating system mode between macOS, Linux, and Windows
void toggle_os(void) {
    current_os++;
    if (current_os > OS_WIN) {
        current_os = OS_MACOS;
    }
}
