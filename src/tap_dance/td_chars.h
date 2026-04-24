#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Character Key Functions
// ─────────────────────────────

// TD_ASTR
void astr_finished(tap_dance_state_t *state, void *user_data);
void astr_reset(tap_dance_state_t *state, void *user_data);
// TD_AT
void at_finished(tap_dance_state_t *state, void *user_data);
void at_reset(tap_dance_state_t *state, void *user_data);
// TD_BSC
void bspc_finished(tap_dance_state_t *state, void *user_data);
void bspc_reset(tap_dance_state_t *state, void *user_data);
// TD_C
void c_finished(tap_dance_state_t *state, void *user_data);
void c_reset(tap_dance_state_t *state, void *user_data);
// TD_CARET
void caret_finished(tap_dance_state_t *state, void *user_data);
void caret_reset(tap_dance_state_t *state, void *user_data);
// TD_CIRC
void circ_finished(tap_dance_state_t *state, void *user_data);
void circ_reset(tap_dance_state_t *state, void *user_data);
// TD_COMM
void comm_finished(tap_dance_state_t *state, void *user_data);
void comm_reset(tap_dance_state_t *state, void *user_data);
// TD_DEL
void del_finished(tap_dance_state_t *state, void *user_data);
void del_reset(tap_dance_state_t *state, void *user_data);
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
// TD_SPC
void spc_finished(tap_dance_state_t *state, void *user_data);
void spc_reset(tap_dance_state_t *state, void *user_data);
// TD_TAB
void tab_finished(tap_dance_state_t *state, void *user_data);
void tab_reset(tap_dance_state_t *state, void *user_data);
// TD_U
void u_finished(tap_dance_state_t *state, void *user_data);
void u_reset(tap_dance_state_t *state, void *user_data);
// TD_SMART_QUOTES
void smart_quotes_finished(tap_dance_state_t *state, void *user_data);
void smart_quotes_reset(tap_dance_state_t *state, void *user_data);
// TD_ANGLE_QUOTES
void angle_quotes_finished(tap_dance_state_t *state, void *user_data);
void angle_quotes_reset(tap_dance_state_t *state, void *user_data);

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

// TD_CAPS
void caps_finished(tap_dance_state_t *state, void *user_data);
void caps_reset(tap_dance_state_t *state, void *user_data);

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

// ─────────────────────────────
// Navigational Key Functions
// ─────────────────────────────

// TD_HOME
void home_finished(tap_dance_state_t *state, void *user_data);
void home_reset(tap_dance_state_t *state, void *user_data);
// TD_PGDN
void pgdn_finished(tap_dance_state_t *state, void *user_data);
void pgdn_reset(tap_dance_state_t *state, void *user_data);
// TD_PGUP
void pgup_finished(tap_dance_state_t *state, void *user_data);
void pgup_reset(tap_dance_state_t *state, void *user_data);
// TD_END
void end_finished(tap_dance_state_t *state, void *user_data);
void end_reset(tap_dance_state_t *state, void *user_data);
