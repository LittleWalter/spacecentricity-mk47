/*
 * td_numpad.h — Tap Dance declarations for numpad digit and shifted-letter entry.
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

#pragma once

#include QMK_KEYBOARD_H

// TD_NUMPAD_1
void numpad_1_finished(tap_dance_state_t *state, void *user_data);
void numpad_1_reset(tap_dance_state_t *state, void *user_data);
// TD_NUMPAD_2
void numpad_2_finished(tap_dance_state_t *state, void *user_data);
void numpad_2_reset(tap_dance_state_t *state, void *user_data);
// TD_NUMPAD_3
void numpad_3_finished(tap_dance_state_t *state, void *user_data);
void numpad_3_reset(tap_dance_state_t *state, void *user_data);
// TD_NUMPAD_4
void numpad_4_finished(tap_dance_state_t *state, void *user_data);
void numpad_4_reset(tap_dance_state_t *state, void *user_data);
// TD_NUMPAD_5
void numpad_5_finished(tap_dance_state_t *state, void *user_data);
void numpad_5_reset(tap_dance_state_t *state, void *user_data);
// TD_NUMPAD_6
void numpad_6_finished(tap_dance_state_t *state, void *user_data);
void numpad_6_reset(tap_dance_state_t *state, void *user_data);
