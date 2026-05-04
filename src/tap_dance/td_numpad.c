/*
 * td_numpad.c — Tap Dance definitions for numpad digit and shifted-letter entry.
 *
 * This module implements tap-dance behaviors for numpad keys (1–6), allowing
 * each key to produce both its numeric keypad value and a corresponding
 * shifted alphabetic character. The design provides fast access to numbers
 * while enabling convenient entry of capital letters without using Shift.
 *
 * Behavior pattern for each numpad tap dance:
 *   - Single tap:       Send KC_KP_n (numpad digit)
 *   - Single hold:      Send Shifted letter (A–F)
 *   - Double tap:       Repeat the numpad digit (tap + register)
 *   - Double single tap: Same as double tap (repeat digit)
 *
 * This module centralizes all numpad-related tap-dance logic so that numeric
 * and shifted-letter behaviors remain consistent, predictable, and easy to
 * maintain across the keymap.
 */

#include "td_numpad.h"
#include "tap_dance_actions.h"
#include "src/features/case_mode.h"

// ─────────────────────────────────────────────────────────────
//  Number Pad Tap Dance Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_NUMPAD_1                1 A
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_1 quad dance.
static td_tap_t numpad_1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_1
void numpad_1_finished(tap_dance_state_t *state, void *user_data) {
    numpad_1_tap_state.state = cur_dance(state);
    switch (numpad_1_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_A)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_1);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_1);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_1); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_1 and reset the state
void numpad_1_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_1_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code(KC_KP_1);   break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_A)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_KP_1); break;
        default: break;
    }
    numpad_1_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NUMPAD_2                2 B
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_2 quad dance.
static td_tap_t numpad_2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_2
void numpad_2_finished(tap_dance_state_t *state, void *user_data) {
    numpad_2_tap_state.state = cur_dance(state);
    switch (numpad_2_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_B)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_2);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_2);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_2); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_2 and reset the state
void numpad_2_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_2_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_B)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code(KC_KP_2);   break;
        default: break;
    }
    numpad_2_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NUMPAD_3                3 C
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_3 quad dance.
static td_tap_t numpad_3_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_3
void numpad_3_finished(tap_dance_state_t *state, void *user_data) {
    numpad_3_tap_state.state = cur_dance(state);
    switch (numpad_3_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_C)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_3);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_3);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_3); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_3 and reset the state
void numpad_3_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_3_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_C)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code(KC_KP_3);   break;
        default: break;
    }
    numpad_3_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NUMPAD_4                4 D
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_4 quad dance.
static td_tap_t numpad_4_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_4
void numpad_4_finished(tap_dance_state_t *state, void *user_data) {
    numpad_4_tap_state.state = cur_dance(state);
    switch (numpad_4_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_D)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_4);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_4);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_4); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_4 and reset the state
void numpad_4_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_4_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_D)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code(KC_KP_4);   break;
        default: break;
    }
    numpad_4_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NUMPAD_5                5 E
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_5 quad dance.
static td_tap_t numpad_5_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_5
void numpad_5_finished(tap_dance_state_t *state, void *user_data) {
    numpad_5_tap_state.state = cur_dance(state);
    switch (numpad_5_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_E)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_5);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_5);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_5); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_5 and reset the state
void numpad_5_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_5_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_E)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code(KC_KP_5);   break;
        default: break;
    }
    numpad_5_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NUMPAD_5                6 F
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NUMPAD_6 quad dance.
static td_tap_t numpad_6_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate shortcut for TD_NUMPAD_6
void numpad_6_finished(tap_dance_state_t *state, void *user_data) {
    numpad_6_tap_state.state = cur_dance(state);
    switch (numpad_6_tap_state.state) {
        case TD_SINGLE_HOLD: register_and_update(S(KC_F)); break;
        case TD_TRIPLE_TAP:        tap_code(KC_KP_6);
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_KP_6);
        case TD_SINGLE_TAP:  register_and_update(KC_KP_6); break;
        default: break;
    }
}

// Release any keys pressed by TD_NUMPAD_6 and reset the state
void numpad_6_reset(tap_dance_state_t *state, void *user_data) {
    switch (numpad_6_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_F)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code(KC_KP_6);   break;
        default: break;
    }
    numpad_6_tap_state.state = TD_NONE;
}
