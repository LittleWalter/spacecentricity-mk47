// ─────────────────────────────────────────────────────────────────
// Spacecentricity v0.1.0 — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// Source: https://github.com/LittleWalter/spacecentricity-mk47
// ─────────────────────────────────────────────────────────────────

#pragma once

#include QMK_KEYBOARD_H

// ──────────────────────────────
// Operating System
// ──────────────────────────────

// TD_LAUNCHER_OS
void launcher_os_finished(tap_dance_state_t *state, void *user_data);
void launcher_os_reset(tap_dance_state_t *state, void *user_data);
// TD_FS_OS
void fs_os_finished(tap_dance_state_t *state, void *user_data);
void fs_os_reset(tap_dance_state_t *state, void *user_data);
// TD_SCRNSHOT_OS
void scrnshot_os_finished(tap_dance_state_t *state, void *user_data);
void scrnshot_os_reset(tap_dance_state_t *state, void *user_data);
// TD_DEL_OS
void del_os_finished(tap_dance_state_t *state, void *user_data);
void del_os_reset(tap_dance_state_t *state, void *user_data);
