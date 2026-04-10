#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Vim
// ─────────────────────────────

// TD_B
void b_finished(tap_dance_state_t *state, void *user_data);
void b_reset(tap_dance_state_t *state, void *user_data);
// TD_GJ
void gj_finished(tap_dance_state_t *state, void *user_data);
void gj_reset(tap_dance_state_t *state, void *user_data);
// TD_GK
void gk_finished(tap_dance_state_t *state, void *user_data);
void gk_reset(tap_dance_state_t *state, void *user_data);
// TD_W
void w_finished(tap_dance_state_t *state, void *user_data);
void w_reset(tap_dance_state_t *state, void *user_data);

// TD_HALF_PGDN
void half_pgdn_finished(tap_dance_state_t *state, void *user_data);
void half_pgdn_reset(tap_dance_state_t *state, void *user_data);
// TD_HALF_PGUP
void half_pgup_finished(tap_dance_state_t *state, void *user_data);
void half_pgup_reset(tap_dance_state_t *state, void *user_data);

// TD_HIGH
void high_finished(tap_dance_state_t *state, void *user_data);
void high_reset(tap_dance_state_t *state, void *user_data);
// TD_MID
void mid_finished(tap_dance_state_t *state, void *user_data);
void mid_reset(tap_dance_state_t *state, void *user_data);
// TD_LOW
void low_finished(tap_dance_state_t *state, void *user_data);
void low_reset(tap_dance_state_t *state, void *user_data);

// TD_WINL
void winl_finished(tap_dance_state_t *state, void *user_data);
void winl_reset(tap_dance_state_t *state, void *user_data);
// TD_WIND
void wind_finished(tap_dance_state_t *state, void *user_data);
void wind_reset(tap_dance_state_t *state, void *user_data);
// TD_WINU
void winu_finished(tap_dance_state_t *state, void *user_data);
void winu_reset(tap_dance_state_t *state, void *user_data);
// TD_WINR
void winr_finished(tap_dance_state_t *state, void *user_data);
void winr_reset(tap_dance_state_t *state, void *user_data);

// TD_SUB
void sub_finished(tap_dance_state_t *state, void *user_data);
void sub_reset(tap_dance_state_t *state, void *user_data);
// TD_FOLD
void fold_finished(tap_dance_state_t *state, void *user_data);
void fold_reset(tap_dance_state_t *state, void *user_data);
// TD_WRITE
void write_finished(tap_dance_state_t *state, void *user_data);
void write_reset(tap_dance_state_t *state, void *user_data);
// TD_QUIT
void quit_finished(tap_dance_state_t *state, void *user_data);
void quit_reset(tap_dance_state_t *state, void *user_data);
