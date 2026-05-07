#pragma once

#include QMK_KEYBOARD_H

// ──────────────────────────────
// Apple macOS-Related
// ──────────────────────────────

// TD_SPOTLGHT_MACOS
void spotlight_macos_finished(tap_dance_state_t *state, void *user_data);
void spotlight_macos_reset(tap_dance_state_t *state, void *user_data);
// TD_FS_MACOS
void fs_macos_finished(tap_dance_state_t *state, void *user_data);
void fs_macos_reset(tap_dance_state_t *state, void *user_data);
// TD_SCRNSHOT_MACOS
void scrnshot_macos_finished(tap_dance_state_t *state, void *user_data);
void scrnshot_macos_reset(tap_dance_state_t *state, void *user_data);
// TD_DEL_MACOS
void del_macos_finished(tap_dance_state_t *state, void *user_data);
void del_macos_reset(tap_dance_state_t *state, void *user_data);
