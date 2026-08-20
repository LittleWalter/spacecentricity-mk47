/*
 * td_digits.h — Tap Dance declarations for digit keys and their alternate actions.
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

#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Number Key Functions
// ─────────────────────────────

// TD_0
void zero_finished(tap_dance_state_t *state, void *user_data);
void zero_reset(tap_dance_state_t *state, void *user_data);
// TD_1
void one_finished(tap_dance_state_t *state, void *user_data);
void one_reset(tap_dance_state_t *state, void *user_data);
// TD_2
void two_finished(tap_dance_state_t *state, void *user_data);
void two_reset(tap_dance_state_t *state, void *user_data);
// TD_3
void three_finished(tap_dance_state_t *state, void *user_data);
void three_reset(tap_dance_state_t *state, void *user_data);
// TD_4
void four_finished(tap_dance_state_t *state, void *user_data);
void four_reset(tap_dance_state_t *state, void *user_data);
// TD_5
void five_finished(tap_dance_state_t *state, void *user_data);
void five_reset(tap_dance_state_t *state, void *user_data);
// TD_6
void six_finished(tap_dance_state_t *state, void *user_data);
void six_reset(tap_dance_state_t *state, void *user_data);
// TD_7
void seven_finished(tap_dance_state_t *state, void *user_data);
void seven_reset(tap_dance_state_t *state, void *user_data);
// TD_8
void eight_finished(tap_dance_state_t *state, void *user_data);
void eight_reset(tap_dance_state_t *state, void *user_data);
// TD_9
void nine_finished(tap_dance_state_t *state, void *user_data);
void nine_reset(tap_dance_state_t *state, void *user_data);
