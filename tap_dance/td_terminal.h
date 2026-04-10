#pragma once

#include QMK_KEYBOARD_H

// ──────────────────────────────
// Terminal Commands
// ──────────────────────────────

// TD_BTOP
void term_btop_finished(tap_dance_state_t *state, void *user_data);
void term_btop_reset(tap_dance_state_t *state, void *user_data);
// TD_CAT
void term_cat_finished(tap_dance_state_t *state, void *user_data);
void term_cat_reset(tap_dance_state_t *state, void *user_data);
// TD_CLS
void term_cls_finished(tap_dance_state_t *state, void *user_data);
void term_cls_reset(tap_dance_state_t *state, void *user_data);
// TD_SIGINT
void term_sigint_finished(tap_dance_state_t *state, void *user_data);
void term_sigint_reset(tap_dance_state_t *state, void *user_data);
// TD_PIPE
void term_pipe_finished(tap_dance_state_t *state, void *user_data);
void term_pipe_reset(tap_dance_state_t *state, void *user_data);
// TD_PATH
void term_path_finished(tap_dance_state_t *state, void *user_data);
void term_path_reset(tap_dance_state_t *state, void *user_data);
// TD_CD
void term_cd_finished(tap_dance_state_t *state, void *user_data);
void term_cd_reset(tap_dance_state_t *state, void *user_data);
// TD_SUDO
void term_sudo_finished(tap_dance_state_t *state, void *user_data);
void term_sudo_reset(tap_dance_state_t *state, void *user_data);

