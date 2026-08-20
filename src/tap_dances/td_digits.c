/*
 * td_digits.c — Tap Dance definitions for digit keys and their alternate actions.
 *
 * This module implements tap‑dance behaviors for the number row (0–9), allowing
 * each digit key to produce both its normal numeric value and an alternate
 * shifted or symbolic action depending on tap, hold, or multi‑tap behavior.
 * These tap dances provide fast access to symbols, shortcuts, or macros that
 * would normally require modifier keys.
 *
 * Typical behavior pattern (varies per digit):
 *   - Single tap:       Send the numeric character (0–9)
 *   - Single hold:      Send the shifted symbol or alternate action
 *   - Double tap:       Repeat the digit or trigger a related macro
 *   - Double single tap: Same as double tap (repeat or macro)
 *
 * This module centralizes all digit‑related tap‑dance logic so that number‑row
 * behaviors remain consistent, ergonomic, and easy to maintain across the keymap.
 */

#include "td_digits.h"
#include "tap_dance_actions.h"
#include "src/core/keymap.h"
#include "src/features/leader.h"

// ─────────────────────────────────────────────────────────────
// Number Key Function Key Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_0       0  Leader History 0
// ──────────────────────────────

// Create static `zero_tap_dance` for TD_0
TD_DEF(zero);

// Send the appropriate symbol for TD_0
void zero_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(zero);
    switch (TD_STATE(zero)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(0);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(0); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_0); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_0); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_0);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_0 and reset the state
void zero_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(zero)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_0);
        default: break;
    }
    TD_RESET(zero);
}

// ──────────────────────────────
// TD_1       1  Leader History 1
// ──────────────────────────────

// Create static `one_tap_dance` for TD_1
TD_DEF(one);

// Send the appropriate symbol for TD_1
void one_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(one);
    switch (TD_STATE(one)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(1);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(1); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_1); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_1); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_1);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_1 and reset the state
void one_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(one)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_1);
        default: break;
    }
    TD_RESET(one);
}

// ──────────────────────────────
// TD_2       2  Leader History 2
// ──────────────────────────────

// Create static `two_tap_dance` for TD_2
TD_DEF(two);

// Send the appropriate symbol for TD_2
void two_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(two);
    switch (TD_STATE(two)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(2);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(2); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_2); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_2); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_2);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_2 and reset the state
void two_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(two)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_2);
        default: break;
    }
    TD_RESET(two);
}

// ──────────────────────────────
// TD_3       3  Leader History 3
// ──────────────────────────────

// Create static `three_tap_dance` for TD_3
TD_DEF(three);

// Send the appropriate symbol for TD_3
void three_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(three);
    switch (TD_STATE(three)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(3);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(3); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_3); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_3); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_3);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_3 and reset the state
void three_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(three)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_3);
        default: break;
    }
    TD_RESET(three);
}

// ──────────────────────────────
// TD_4       4  Leader History 4
// ──────────────────────────────

// Create static `four_tap_dance` for TD_4
TD_DEF(four);

// Send the appropriate symbol for TD_4
void four_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(four);
    switch (TD_STATE(four)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(4);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(4); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_4); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_4); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_4);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_4 and reset the state
void four_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(four)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_4);
        default: break;
    }
    TD_RESET(four);
}

// ──────────────────────────────
// TD_5       5  Leader History 5
// ──────────────────────────────

// Create static `five_tap_dance` for TD_5
TD_DEF(five);

// Send the appropriate symbol for TD_5
void five_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(five);
    switch (TD_STATE(five)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(5);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(5); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_5); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_5); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_5);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_5 and reset the state
void five_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(five)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_5);
        default: break;
    }
    TD_RESET(five);
}

// ──────────────────────────────
// TD_6       6  Leader History 6
// ──────────────────────────────

// Create static `six_tap_dance` for TD_6
TD_DEF(six);

// Send the appropriate symbol for TD_6
void six_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(six);
    switch (TD_STATE(six)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(6);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(6); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_6); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_6); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_6);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_6 and reset the state
void six_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(six)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_6);
        default: break;
    }
    TD_RESET(six);
}

// ──────────────────────────────
// TD_7       7  Leader History 7
// ──────────────────────────────

// Create static `six_tap_dance` for TD_7
TD_DEF(seven);

// Send the appropriate symbol for TD_7
void seven_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(seven);
    switch (TD_STATE(seven)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(7);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(7); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_7); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_7); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_7);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_7 and reset the state
void seven_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(seven)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_7);
        default: break;
    }
    TD_RESET(seven);
}

// ──────────────────────────────
// TD_8       8  Leader History 8
// ──────────────────────────────

// Create static `eight_tap_dance` for TD_8
TD_DEF(eight);

// Send the appropriate symbol for TD_8
void eight_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(eight);
    switch (TD_STATE(eight)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(8);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(8); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_8); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_8); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_8);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_8 and reset the state
void eight_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(eight)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_8);
        default: break;
    }
    TD_RESET(eight);
}

// ──────────────────────────────
// TD_9       9  Leader History 9
// ──────────────────────────────

// Create static `nine_tap_dance` for TD_9
TD_DEF(nine);

// Send the appropriate symbol for TD_9
void nine_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(nine);
    switch (TD_STATE(nine)) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(9);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(9); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_9); // fallthru
        case TD_DOUBLE_TAP:                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_9); // fallthru
        case TD_SINGLE_TAP:
            register_and_update(KC_9);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_9 and reset the state
void nine_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(nine)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_9);
        default: break;
    }
    TD_RESET(nine);
}
