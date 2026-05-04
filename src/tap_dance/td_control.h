#pragma once

#include QMK_KEYBOARD_H

// ──────────────────────────────
// Control/Action/State Functions
// ──────────────────────────────

// TD_BSC
void bspc_finished(tap_dance_state_t *state, void *user_data);
void bspc_reset(tap_dance_state_t *state, void *user_data);
// TD_CAPS
void caps_finished(tap_dance_state_t *state, void *user_data);
void caps_reset(tap_dance_state_t *state, void *user_data);
// TD_DEL
void del_finished(tap_dance_state_t *state, void *user_data);
void del_reset(tap_dance_state_t *state, void *user_data);
// TD_ENT
void enter_finished(tap_dance_state_t *state, void *user_data);
void enter_reset(tap_dance_state_t *state, void *user_data);
// TD_ESC
void esc_finished(tap_dance_state_t *state, void *user_data);
void esc_reset(tap_dance_state_t *state, void *user_data);
// TD_TAB
void tab_finished(tap_dance_state_t *state, void *user_data);
void tab_reset(tap_dance_state_t *state, void *user_data);

// ─────────────────────────────
// App Shortcut Functions
// ─────────────────────────────

// TD_UNDO
void undo_finished(tap_dance_state_t *state, void *user_data);
void undo_reset(tap_dance_state_t *state, void *user_data);

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
