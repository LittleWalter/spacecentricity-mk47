/*
 * td_control.c — Tap Dance definitions for control, action, and navigation keys.
 *
 * This file implements all tap‑dance behaviors related to:
 *   - Editing keys: Backspace, Delete, Enter, Tab
 *   - State keys: Caps Lock / Caps Word
 *   - App shortcuts: Undo / Redo
 *   - Navigation keys: Home, End, Page Up, Page Down
 *
 * The goal of this module is to centralize all non‑character tap‑dance
 * behaviors so they remain consistent and easy to maintain.
 */

#include "td_control.h"
#include "tap_dance_actions.h"
#include "src/core/keymap.h"
#include "src/core/custom_keys.h"
#include "src/features/caps_word.h"
#include "src/features/case_mode.h"
#include "src/features/utils.h"
#include "src/macros/mac_special_char.h"

// ─────────────────────────────────────────────────────────────
// Control/Action/State Key Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// Instance of 'td_tap_t' for the TD_BSPC quad tap dance
static td_tap_t bspc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate delete key for TD_BSPC
void bspc_finished(tap_dance_state_t *state, void *user_data) {
    bspc_tap_state.state = cur_dance(state);
    switch (bspc_tap_state.state) {
        case TD_SINGLE_HOLD: // ⌫ previous word
            register_and_update(current_os == OS_MACOS ? A(KC_BSPC) : C(KC_BSPC));
            break;
        case TD_DOUBLE_HOLD: // ⌫ to BOL
            tap_code16(C(S(KC_LEFT)));
            tap_and_update(KC_BSPC);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_BSPC);             // fallthru
        case TD_DOUBLE_TAP:                                         // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_BSPC);             // fallthru
        case TD_SINGLE_TAP: // ⌫ Backspace
            register_and_update(KC_BSPC);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_BSPC and reset the state
void bspc_reset(tap_dance_state_t *state, void *user_data) {
    switch (bspc_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code16(current_os == OS_MACOS ? A(KC_BSPC) : C(KC_BSPC));
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_BSPC); break;
        default: break;
    }
    bspc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CAPS
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CAPS quad tap dances
static td_tap_t caps_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_CAPS
void caps_finished(tap_dance_state_t *state, void *user_data) {
    caps_tap_state.state = cur_dance(state);
    switch (caps_tap_state.state) {
#ifdef CAPS_WORD_ENABLE
        case TD_SINGLE_TAP:
            case_mode_off();
            caps_word_toggle();
            break;
#endif
        case TD_DOUBLE_TAP:
            const_case_toggle(); // SCREAMING_SNAKE_CASE
            break;
        case TD_SINGLE_HOLD:
            case_mode_off();
            caps_lock_toggle();
            break;
        default: break;
    }
}

// Release any keys pressed by TD_CAPS and reset the state
void caps_reset(tap_dance_state_t *state, void *user_data) {
    caps_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DEL                ⌦  ⌦L ⌦w
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DEL quad tap dance
static td_tap_t del_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate delete key for TD_DEL
void del_finished(tap_dance_state_t *state, void *user_data) {
    del_tap_state.state = cur_dance(state);
    switch (del_tap_state.state) {
        case TD_SINGLE_HOLD: // ⌦ next word
            register_and_update(current_os == OS_MACOS ? A(KC_DEL) : C(KC_DEL));
            break;
        case TD_DOUBLE_HOLD: // ⌫ to EOL
            tap_code16(S(KC_END));
            tap_code(KC_DEL);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_DEL); // fallthru
        case TD_DOUBLE_TAP:                            // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DEL); // fallthru
        case TD_SINGLE_TAP: // ⌦ Delete
            register_and_update(KC_DEL);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_DEL and reset the state
void del_reset(tap_dance_state_t *state, void *user_data) {
    switch (del_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code16(current_os == OS_MACOS ? A(KC_DEL) : C(KC_DEL));
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_DEL); break;
        default: break;
    }
    del_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_ENT
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_ENT quad dance.
static td_tap_t enter_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_ENT
void enter_finished(tap_dance_state_t *state, void *user_data) {
    enter_tap_state.state = cur_dance(state);
    switch (enter_tap_state.state) {
        case TD_DOUBLE_HOLD:
            register_and_update(S(KC_ENT));
            break;
        case TD_TRIPLE_TAP:        tap_code(KC_ENT); // fallthru
        case TD_DOUBLE_TAP:                          // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ENT); // fallthru
        case TD_SINGLE_HOLD:                         // fallthru
        case TD_SINGLE_TAP: // `↵`
            register_and_update(KC_ENT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_ENT and reset the state
void enter_reset(tap_dance_state_t *state, void *user_data) {
    switch (enter_tap_state.state) {
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_ENT)); break;
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_ENT); break;
        default: break;
    }
    enter_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_ESC
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_ESC quad dance.
static td_tap_t esc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_ESC
void esc_finished(tap_dance_state_t *state, void *user_data) {
    esc_tap_state.state = cur_dance(state);
    switch (esc_tap_state.state) {
        case TD_SINGLE_HOLD: layer_on(_MACOS); break;
        case TD_DOUBLE_HOLD: // Close window
            tap_and_update(current_os == OS_MACOS ? LGUI(KC_W) : A(KC_F4));
            break;
        case TD_TRIPLE_TAP:        tap_code(KC_ESC); // fallthru
        case TD_DOUBLE_TAP:                          // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ESC); // fallthru
        case TD_SINGLE_TAP: // `Esc`
            register_and_update(KC_ESC);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_ESC and reset the state
void esc_reset(tap_dance_state_t *state, void *user_data) {
    switch (esc_tap_state.state) {
        case TD_SINGLE_HOLD: layer_off(_MACOS); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_ESC); break;
        default: break;
    }
    esc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_TAB                     ⇥ ⇤
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_TAB tap and hold dance.
static td_tap_t tab_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_TAB
void tab_finished(tap_dance_state_t *state, void *user_data) {
    tab_tap_state.state = cur_dance(state);
    switch (tab_tap_state.state) {
        case TD_SINGLE_HOLD: // ⇤ Shift+Tab (Reverse Tab)
            register_and_update(S(KC_TAB));
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_TAB); // fallthru
        case TD_DOUBLE_TAP:                            // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); // fallthru
        case TD_SINGLE_TAP: // ⇥ Tab
            register_and_update(KC_TAB);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_TAB and reset the state
void tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (tab_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_TAB)); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_TAB); break;
        default: break;
    }
    tab_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// App Shortcut Functions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_UNDO              Undo Redo
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_UNDO quad dance.
static td_tap_t undo_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_UNDO
void undo_finished(tap_dance_state_t *state, void *user_data) {
    undo_tap_state.state = cur_dance(state);
    const uint16_t undo_keycode = current_os == OS_MACOS ? LGUI(KC_Z) : C(KC_Z);
    switch (undo_tap_state.state) {
        case TD_DOUBLE_HOLD:
            // Redo
            if (current_os == OS_WIN) { // General redo Windows shortcut
                tap_and_update(C(KC_Y));
            } else if (current_os == OS_LINUX) {
                tap_and_update(C(S(KC_Y))); // Most common Linux redo shortcut
            } else {
                tap_and_update(LGUI(S(KC_Z))); // macOS
            }
            break;
        case TD_TRIPLE_TAP:        tap_code16(undo_keycode);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code16(undo_keycode);
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:       tap_and_update(undo_keycode); break;
        default: break;
    }
}

// Release any keys pressed by TD_UNDO and reset the state
void undo_reset(tap_dance_state_t *state, void *user_data) {
    undo_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Navigation Key Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_HOME            ⇱ ^ h ← `←`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_HOME quad tap dance.
static td_tap_t home_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_HOME
void home_finished(tap_dance_state_t *state, void *user_data) {
    home_tap_state.state = cur_dance(state);
    switch (home_tap_state.state) {
        case TD_DOUBLE_TAP:  register_and_update(KC_CIRC);       break; // `^` (Caret)
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_LEFT); break; // `→` (symbol)
        case TD_SINGLE_HOLD: register_and_update(KC_LEFT);       break; // Left Arrow
        case TD_DOUBLE_HOLD: register_and_update(KC_H);          break; // `h` (Vim left motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_HOME);                  // fallthru
        case TD_SINGLE_TAP:  register_and_update(KC_HOME);       break; // Home
        default: break;
    }
}

// Release any keys pressed by TD_HOME and reset the state
void home_reset(tap_dance_state_t *state, void *user_data) {
    switch (home_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_CIRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LEFT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_H);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_HOME); break;
        default: break;
    }
    home_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PGDN            ⇟ } j ↓ `↓`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PGDN quad tap dance.
static td_tap_t pgdn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_PGDN
void pgdn_finished(tap_dance_state_t *state, void *user_data) {
    pgdn_tap_state.state = cur_dance(state);
    switch (pgdn_tap_state.state) {
        case TD_DOUBLE_TAP:  register_and_update(KC_RCBR);       break; // `}`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_DOWN); break; // `↓` (symbol)
        case TD_SINGLE_HOLD: register_and_update(KC_DOWN);       break; // Down Arrow
        case TD_DOUBLE_HOLD: register_and_update(KC_J);          break; // `j` (Vim left motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PGDN);                  // fallthru
        case TD_SINGLE_TAP:  register_and_update(KC_PGDN);       break; // Page Down
        default: break;
    }
}

// Release any keys pressed by TD_PGDN and reset the state
void pgdn_reset(tap_dance_state_t *state, void *user_data) {
    switch (pgdn_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RCBR); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_DOWN); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_J);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PGDN); break;
        default: break;
    }
    pgdn_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PGUP            ⇞ { k ↑ `↑`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PGUP quad tap dance.
static td_tap_t pgup_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_PGUP
void pgup_finished(tap_dance_state_t *state, void *user_data) {
    pgup_tap_state.state = cur_dance(state);
    switch (pgup_tap_state.state) {
        case TD_DOUBLE_TAP:  register_and_update(KC_LCBR);     break; // `{`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_UP); break; // `↑` (symbol)
        case TD_SINGLE_HOLD: register_and_update(KC_UP);       break; // Up Arrow
        case TD_DOUBLE_HOLD: register_and_update(KC_K);        break; // `k` (Vim up motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PGUP);                // fallthru
        case TD_SINGLE_TAP:  register_and_update(KC_PGUP);     break; // Page Up
        default: break;
    }
}

// Release any keys pressed by TD_PGUP and reset the state
void pgup_reset(tap_dance_state_t *state, void *user_data) {
    switch (pgup_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_UP);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_K);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PGUP); break;
        default: break;
    }
    pgup_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_END                 ⇲ $ l →
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_END quad tap dance.
static td_tap_t end_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_END
void end_finished(tap_dance_state_t *state, void *user_data) {
    end_tap_state.state = cur_dance(state);
    switch (end_tap_state.state) {
        case TD_DOUBLE_TAP:  register_and_update(KC_DLR);         break; // `$`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_RIGHT); break; // `→` (symbol)
        case TD_SINGLE_HOLD: register_and_update(KC_RGHT);        break; // Right Arrow
        case TD_DOUBLE_HOLD: register_and_update(KC_L);           break; // `l` (Vim right motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_END);                    // fallthru
        case TD_SINGLE_TAP:  register_and_update(KC_END);         break; // End
        default: break;
    }
}

// Release any keys pressed by TD_END and reset the state
void end_reset(tap_dance_state_t *state, void *user_data) {
    switch (end_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_DLR);  break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RGHT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_L);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_END); break;
        default: break;
    }
    end_tap_state.state = TD_NONE;
}
