#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Prose & Programming N-Grams
// ─────────────────────────────

// TD_EQL
void prog_eql_finished(tap_dance_state_t *state, void *user_data);
void prog_eql_reset(tap_dance_state_t *state, void *user_data);
// TD_AND
void prog_and_finished(tap_dance_state_t *state, void *user_data);
void prog_and_reset(tap_dance_state_t *state, void *user_data);
// TD_ASSIGN
void prog_assign_finished(tap_dance_state_t *state, void *user_data);
void prog_assign_reset(tap_dance_state_t *state, void *user_data);
// TD_PARENS
void prog_parens_finished(tap_dance_state_t *state, void *user_data);
void prog_parens_reset(tap_dance_state_t *state, void *user_data);
// TD_DBL_QUOTES
void prog_dbl_quotes_finished(tap_dance_state_t *state, void *user_data);
void prog_dbl_quotes_reset(tap_dance_state_t *state, void *user_data);
// TD_ARROW
void prog_arrow_finished(tap_dance_state_t *state, void *user_data);
void prog_arrow_reset(tap_dance_state_t *state, void *user_data);
// TD_CMPD
void prog_cmpd_finished(tap_dance_state_t *state, void *user_data);
void prog_cmpd_reset(tap_dance_state_t *state, void *user_data);
// TD_INC
void prog_inc_finished(tap_dance_state_t *state, void *user_data);
void prog_inc_reset(tap_dance_state_t *state, void *user_data);
// TD_COMMENT
void prog_comment_finished(tap_dance_state_t *state, void *user_data);
void prog_comment_reset(tap_dance_state_t *state, void *user_data);
// TD_IF_KW
void prog_if_finished(tap_dance_state_t *state, void *user_data);
void prog_if_reset(tap_dance_state_t *state, void *user_data);
// TD_TRUE_KW
void prog_true_finished(tap_dance_state_t *state, void *user_data);
void prog_true_reset(tap_dance_state_t *state, void *user_data);
// TD_RETURN_KW
void prog_return_finished(tap_dance_state_t *state, void *user_data);
void prog_return_reset(tap_dance_state_t *state, void *user_data);
// TD_BREAK_KW
void prog_break_finished(tap_dance_state_t *state, void *user_data);
void prog_break_reset(tap_dance_state_t *state, void *user_data);
// TD_SWITCH_KW
void prog_switch_finished(tap_dance_state_t *state, void *user_data);
void prog_switch_reset(tap_dance_state_t *state, void *user_data);
// TD_FOR_KW
void prog_for_finished(tap_dance_state_t *state, void *user_data);
void prog_for_reset(tap_dance_state_t *state, void *user_data);
// TD_NULL_KW
void prog_null_finished(tap_dance_state_t *state, void *user_data);
void prog_null_reset(tap_dance_state_t *state, void *user_data);

// TD_MD_LINK
void md_link_finished(tap_dance_state_t *state, void *user_data);
void md_link_reset(tap_dance_state_t *state, void *user_data);

// TD_CAMEL
void camel_finished(tap_dance_state_t *state, void *user_data);
void camel_reset(tap_dance_state_t *state, void *user_data);
// TD_SNAKE
void snake_finished(tap_dance_state_t *state, void *user_data);
void snake_reset(tap_dance_state_t *state, void *user_data);
