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

// Instance of 'td_tap_t' for the TD_0 tap dances
static td_tap_t zero_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_0
void zero_finished(tap_dance_state_t *state, void *user_data) {
    zero_tap_state.state = cur_dance(state);
    switch (zero_tap_state.state) {
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
    switch (zero_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_0);
        default: break;
    }
    zero_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_1       1  Leader History 1
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_1 tap dances
static td_tap_t one_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_1
void one_finished(tap_dance_state_t *state, void *user_data) {
    one_tap_state.state = cur_dance(state);
    switch (one_tap_state.state) {
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
    switch (one_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_1);
        default: break;
    }
    one_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_2       2  Leader History 2
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_2 tap dances
static td_tap_t two_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_2
void two_finished(tap_dance_state_t *state, void *user_data) {
    two_tap_state.state = cur_dance(state);
    switch (two_tap_state.state) {
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
    switch (two_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_2);
        default: break;
    }
    two_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_3       3  Leader History 3
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_3 tap dances
static td_tap_t three_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_3
void three_finished(tap_dance_state_t *state, void *user_data) {
    three_tap_state.state = cur_dance(state);
    switch (three_tap_state.state) {
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
    switch (three_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_3);
        default: break;
    }
    three_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_4       4  Leader History 4
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_4 tap dances
static td_tap_t four_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_4
void four_finished(tap_dance_state_t *state, void *user_data) {
    four_tap_state.state = cur_dance(state);
    switch (four_tap_state.state) {
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
    switch (four_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_4);
        default: break;
    }
    four_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_5       5  Leader History 5
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_5 tap dances
static td_tap_t five_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_5
void five_finished(tap_dance_state_t *state, void *user_data) {
    five_tap_state.state = cur_dance(state);
    switch (five_tap_state.state) {
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
    switch (five_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_5);
        default: break;
    }
    five_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_6       6  Leader History 6
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_6 tap dances
static td_tap_t six_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_6
void six_finished(tap_dance_state_t *state, void *user_data) {
    six_tap_state.state = cur_dance(state);
    switch (six_tap_state.state) {
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
    switch (six_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_6);
        default: break;
    }
    six_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_7       7  Leader History 7
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_7 tap dances
static td_tap_t seven_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_7
void seven_finished(tap_dance_state_t *state, void *user_data) {
    seven_tap_state.state = cur_dance(state);
    switch (seven_tap_state.state) {
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
    switch (seven_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_7);
        default: break;
    }
    seven_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_8       8  Leader History 8
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_8 tap dances
static td_tap_t eight_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_8
void eight_finished(tap_dance_state_t *state, void *user_data) {
    eight_tap_state.state = cur_dance(state);
    switch (eight_tap_state.state) {
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
    switch (eight_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_8);
        default: break;
    }
    eight_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_9       9  Leader History 9
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_9 tap dances
static td_tap_t nine_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_9
void nine_finished(tap_dance_state_t *state, void *user_data) {
    nine_tap_state.state = cur_dance(state);
    switch (nine_tap_state.state) {
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
    switch (nine_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(KC_9);
        default: break;
    }
    nine_tap_state.state = TD_NONE;
}
