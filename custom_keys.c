#include "custom_keys.h"
#include "macros/mac_programming.h"
#include "macros/mac_special_char.h"
#include "macros/mac_terminal.h"
#include "macros/mac_vim.h"
#include "rgb.h"
#include "tapping_term.h"

os_t current_os = OS_MACOS; // Default to Apple macOS

// Intercepts custom keycodes and runs their associated macros and miscellenous
// non-macros. This function handles all higher‑level behaviors that aren't
// simple keypresses, including programming bigrams (e.g., ", ", "; ", ": ",
// ". "), Vim navigation motions (gj/gk, buffer and tab movement, window
// resizing), viewport controls, and buffer‑level commands (write, quit,
// substitute). Returning false prevents QMK from sending the underlying
// keycode so the macro can fully replace it.
//
// Most logic functionally decomposed.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t mouse_key_timer; // Tracking key hold time, SEE:MOUSE_FN branch
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
                select_all();
            }
            return false;
        case COPY: // Copy Selected
            if (record->event.pressed) {
                copy();
            }
            return false;
        case PASTE: // Paste from clipboard
            if (record->event.pressed) {
                paste();
            }
            return false;
        case CUT: // Cut Selected
            if (record->event.pressed) {
                cut();
            }
            return false;

        case VDT_LEFT: // Change to left virtual desktop/workspace
            if (record->event.pressed) {
                vdt_left();
            }
            return false;
        case VDT_RIGHT:
            if (record->event.pressed) { // Change to right virtual desktop/workspace
                vdt_right();
            }
            return false;

        case ZOOM_IN: // Browser Zoom In
            if (record->event.pressed) {
                zoom_in();
            }
            return false;
        case ZOOM_OUT: // Browser Zoom Out
            if (record->event.pressed) {
                zoom_out();
            }
            return false;
        case ZOOM_RESET: // Broswer Zoom Reset (100%)
            if (record->event.pressed) {
                zoom_reset();
            }
            return false;

        // ─────────────────────────────────────────────────────────────
        // Miscellaneous (Non-Macros)
        // ─────────────────────────────────────────────────────────────
        case TG_MOUSE: // Toggle mouse/previous layer
            if (record->event.pressed) {
                toggle_mouse();
            }
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
                toggle_os();
            }
            return false;

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
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
// App Shortcuts
// ─────────────────────────────────────────────────────────────

// App shortcut: select all; defaults to CMD+A for macOS, otherwise
// uses LCTL+A for Microsoft Windows and Linux
void select_all(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_A) : C(KC_A));
}

// App shortcut: copy selected; defaults to CMD+C for macOS, otherwise
// uses LCTL+C for Microsoft Windows and Linux
void copy(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_C) : C(KC_C));
}

// App shortcut: cut selected; defaults to CMD+X for macOS, otherwise
// uses LCTL+X for Microsoft Windows and Linux
void cut(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_X) : C(KC_X));
}

// App shortcut: paste from clipboard; defaults to CMD+V for macOS, otherwise
// uses LCTL+V for Microsoft Windows and Linux
void paste(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_V) : C(KC_V));
}

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+LEFT for macOS, otherwise uses LCTL+ALT+LEFT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+LEFT for Microsoft Windows.
void vdt_left(void) {
    switch (current_os) {
        case OS_MACOS: tap_code16(C(KC_LEFT));       break; // macOS:   LCTL+LEFT
        case OS_LINUX: tap_code16(C(A(KC_LEFT)));    break; // Linux:   LCTL+ALT+LEFT
        case OS_WIN:   tap_code16(LGUI(C(KC_LEFT))); break; // Windows: WIN+LCTL+LEFT
        default: break;
    }
}

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+RIGHT for macOS, otherwise uses LCTL+ALT+RIGHT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+RIGHT for Microsoft Windows.
void vdt_right(void) {
    switch (current_os) {
        case OS_MACOS: tap_code16(C(KC_RGHT));       break; // macOS:   LCTL+RIGHT
        case OS_LINUX: tap_code16(C(A(KC_RGHT)));    break; // Linux:   LCTL+ALT+RIGHT
        case OS_WIN:   tap_code16(LGUI(C(KC_RGHT))); break; // Windows: WIN+LCTL+RIGHT
        default: break;
    }
}

// Browser shortcut: zoom in; defaults to CMD+SFT+= for macOS, otherwise
// uses LCTL+SFT+= for Microsoft Windows and Linux
void zoom_in(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(S(KC_EQL)) : C(S(KC_EQL)));
}

// Browser shortcut: zoom out; defaults to CMD+- for macOS, otherwise
// uses LCTL+- for Microsoft Windows and Linux
void zoom_out(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_MINS) : C(KC_MINS));
}

// Browser shortcut: zoom reset (100%); defaults to CMD+0 for macOS, otherwise
// uses LCTL+0 for Microsoft Windows and Linux
void zoom_reset(void) {
    tap_code16(current_os == OS_MACOS ? LGUI(KC_0) : C(KC_0));
}

// ─────────────────────────────────────────────────────────────
// Miscellaneous
// ─────────────────────────────────────────────────────────────

// Toggle mouse layer, go back to previous layer. Since DOOM is accessed via MOUSE, we handle the
// expected behavior logic here to avoid future issues.
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

// Switch to mouse layer on shorter key presses, otherwise go to function keys layer
void mouse_fn(uint16_t mouse_key_timer) {
    uint16_t elapsed = timer_elapsed(mouse_key_timer);
    // Tap behavior
    if (elapsed < TAPPING_TERM + MOUSE_FN_DELAY) {
        layer_on(_MOUSE);
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
