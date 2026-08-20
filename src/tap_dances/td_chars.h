/*
 * td_chars.c — Tap Dance declarations for symbol and character-entry keys.
 *
 * This module implements tap-dance behaviors for character-producing keys
 * that are not simple alphanumerics. These typically include:
 *   - Punctuation (e.g., ! ? : ; , .)
 *   - Paired symbols (e.g., () [] {})
 *   - Mathematical or programming symbols (e.g., + - * / = < >)
 *   - Special Unicode or macro‑generated characters
 *
 * The goal of this module is to centralize all symbol-entry tap-dance logic
 * so that character behaviors remain consistent, discoverable, and easy to
 * maintain across the keymap.
 */

#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Thumb Key Function Declarations
// ─────────────────────────────────────────────────────────────

// TD_U
void u_finished(tap_dance_state_t *state, void *user_data);
void u_reset(tap_dance_state_t *state, void *user_data);
// TD_C
void c_finished(tap_dance_state_t *state, void *user_data);
void c_reset(tap_dance_state_t *state, void *user_data);

// ─────────────────────────────────────────────────────────────
//  Char Key Function Declarations
// ─────────────────────────────────────────────────────────────

// TD_ASTR
void astr_finished(tap_dance_state_t *state, void *user_data);
void astr_reset(tap_dance_state_t *state, void *user_data);
// TD_AT
void at_finished(tap_dance_state_t *state, void *user_data);
void at_reset(tap_dance_state_t *state, void *user_data);
// TD_CARET
void caret_finished(tap_dance_state_t *state, void *user_data);
void caret_reset(tap_dance_state_t *state, void *user_data);
// TD_CIRC
void circ_finished(tap_dance_state_t *state, void *user_data);
void circ_reset(tap_dance_state_t *state, void *user_data);
// TD_COMM
void comm_finished(tap_dance_state_t *state, void *user_data);
void comm_reset(tap_dance_state_t *state, void *user_data);
// TD_DLR
void dlr_finished(tap_dance_state_t *state, void *user_data);
void dlr_reset(tap_dance_state_t *state, void *user_data);
// TD_DOT
void dot_finished(tap_dance_state_t *state, void *user_data);
void dot_reset(tap_dance_state_t *state, void *user_data);
// TD_DQUO
void dquo_finished(tap_dance_state_t *state, void *user_data);
void dquo_reset(tap_dance_state_t *state, void *user_data);
// TD_EQL
void eql_finished(tap_dance_state_t *state, void *user_data);
void eql_reset(tap_dance_state_t *state, void *user_data);
// TD_EXLM
void exlm_finished(tap_dance_state_t *state, void *user_data);
void exlm_reset(tap_dance_state_t *state, void *user_data);
// TD_MINS
void mins_finished(tap_dance_state_t *state, void *user_data);
void mins_reset(tap_dance_state_t *state, void *user_data);
// TD_PLUS
void plus_finished(tap_dance_state_t *state, void *user_data);
void plus_reset(tap_dance_state_t *state, void *user_data);
// TD_PUNC
void punc_finished(tap_dance_state_t *state, void *user_data);
void punc_reset(tap_dance_state_t *state, void *user_data);
// TD_QUES
void ques_finished(tap_dance_state_t *state, void *user_data);
void ques_reset(tap_dance_state_t *state, void *user_data);
// TD_QUOT
void quot_finished(tap_dance_state_t *state, void *user_data);
void quot_reset(tap_dance_state_t *state, void *user_data);
// TD_SCLN
void scln_finished(tap_dance_state_t *state, void *user_data);
void scln_reset(tap_dance_state_t *state, void *user_data);
// TD_SPC
void spc_finished(tap_dance_state_t *state, void *user_data);
void spc_reset(tap_dance_state_t *state, void *user_data);

// ─────────────────────────────────────────────────────────────
// Cursor-Centered Quote Function Definitions
// ─────────────────────────────────────────────────────────────

// TD_SMART_QUOTES
void smart_quotes_finished(tap_dance_state_t *state, void *user_data);
void smart_quotes_reset(tap_dance_state_t *state, void *user_data);
// TD_ANGLE_QUOTES
void angle_quotes_finished(tap_dance_state_t *state, void *user_data);
void angle_quotes_reset(tap_dance_state_t *state, void *user_data);

// ─────────────────────────────────────────────────────────────
// Paired Symbol Function Declarations
// ─────────────────────────────────────────────────────────────

// TD_LPRN
void lprn_finished(tap_dance_state_t *state, void *user_data);
void lprn_reset(tap_dance_state_t *state, void *user_data);
// TD_RPRN
void rprn_finished(tap_dance_state_t *state, void *user_data);
void rprn_reset(tap_dance_state_t *state, void *user_data);
// TD_LBRC
void lbrc_finished(tap_dance_state_t *state, void *user_data);
void lbrc_reset(tap_dance_state_t *state, void *user_data);
// TD_RBRC
void rbrc_finished(tap_dance_state_t *state, void *user_data);
void rbrc_reset(tap_dance_state_t *state, void *user_data);
