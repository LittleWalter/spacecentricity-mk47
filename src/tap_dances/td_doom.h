// ─────────────────────────────────────────────────────────────
// Spacecentricity — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// ─────────────────────────────────────────────────────────────

#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────
// Custom Doom Keys
// ─────────────────────────────

void doom_menu_finished(tap_dance_state_t *state, void *user_data);
void doom_menu_reset(tap_dance_state_t *state, void *user_data);

void doom_load_finished(tap_dance_state_t *state, void *user_data);
void doom_load_reset(tap_dance_state_t *state, void *user_data);

void doom_map_finished(tap_dance_state_t *state, void *user_data);
void doom_map_reset(tap_dance_state_t *state, void *user_data);

void doom_mute_finished(tap_dance_state_t *state, void *user_data);
void doom_mute_reset(tap_dance_state_t *state, void *user_data);

void doom_prev_finished(tap_dance_state_t *state, void *user_data);
void doom_prev_reset(tap_dance_state_t *state, void *user_data);

void doom_6_finished(tap_dance_state_t *state, void *user_data);
void doom_6_reset(tap_dance_state_t *state, void *user_data);
