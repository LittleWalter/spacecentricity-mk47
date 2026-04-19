#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Media Key Functions
// ─────────────────────────────

// TD_MUTE
void mute_finished(tap_dance_state_t *state, void *user_data);
void mute_reset(tap_dance_state_t *state, void *user_data);
// TD_VOLD
void vold_finished(tap_dance_state_t *state, void *user_data);
void vold_reset(tap_dance_state_t *state, void *user_data);
// TD_VOLU
void volu_finished(tap_dance_state_t *state, void *user_data);
void volu_reset(tap_dance_state_t *state, void *user_data);
