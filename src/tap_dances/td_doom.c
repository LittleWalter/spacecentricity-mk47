#include "td_doom.h"
#include "tap_dance_actions.h"

// ─────────────────────────────────────────────────────────────
// Doom Classic Tap Dance Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_DOOM_ESC          Esc   y n
// ──────────────────────────────

// Create static `b_tap_dance` for TD_DOOM_ESC
TD_DEF(doom_esc);

// Send the appropriate Vim command for TD_DOOM_ESC
void doom_esc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_esc);
    switch (TD_STATE(doom_esc)) {
        case TD_SINGLE_HOLD: // fallthru
            register_code16(KC_N); // N for “no”
            break;
        case TD_DOUBLE_HOLD: // `y` for “yes”
            register_and_update(KC_Y);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_ESC);          // fallthru
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_ESC);          // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_ESC);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_ESC and reset the state
void doom_esc_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_esc)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_N); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_Y); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_ESC); break;
        default: break;
    }
    TD_RESET(doom_esc);
}


