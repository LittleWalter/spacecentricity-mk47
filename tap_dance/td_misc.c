#include "td_misc.h"
#include "tap_dance_actions.h"
#include "custom_keys.h"

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
    switch (undo_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            // Undo
            tap_code16(current_os == OS_MACOS ? LGUI(KC_Z) : C(KC_Z));
            break;
        case TD_DOUBLE_HOLD:
            // Redo
            if (current_os == OS_WIN) { // General redo Windows shortcut
                tap_code16(C(KC_Y));
            } else if (current_os == OS_LINUX) {
                tap_code16(C(S(KC_Y))); // Most common Linux redo shortcut
            } else {
                tap_code16(LGUI(S(KC_Z))); // macOS
            }
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(current_os == OS_MACOS ? LGUI(KC_Z) : C(KC_Z));
            tap_code16(current_os == OS_MACOS ? LGUI(KC_Z) : C(KC_Z));
            break;
        default: break;
    }
}

// Release any keys pressed by TD_UNDO and reset the state
void undo_reset(tap_dance_state_t *state, void *user_data) {
    undo_tap_state.state = TD_NONE;
}
