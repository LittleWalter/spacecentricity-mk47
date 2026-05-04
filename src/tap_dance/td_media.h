/*
 * td_media.h — Tap Dance declarations for media, playback, and system controls.
 *
 * This module implements tap-dance behaviors for common media functions such as
 * volume control, playback navigation, mute toggling, and laptop brightness
 * adjustments. Each tap dance provides multiple related actions depending on
 * tap, hold, or multi-tap behavior, enabling fast and ergonomic control of
 * system audio and media playback.
 *
 * Included tap dances:
 *   - Mute / Play‑Pause / Stop / Browser Tab Mute
 *   - Volume Down / Previous Track / Brightness Down
 *   - Volume Up / Next Track / Brightness Up
 *
 * Behavior pattern (varies slightly per key):
 *   - Single tap:        Primary media action (mute, vol‑down, vol‑up)
 *   - Double tap:        Track navigation (previous/next) or play/pause
 *   - Single hold:       Repeat primary action or send browser mute shortcut
 *   - Double hold:       Laptop brightness adjustments or media stop
 *   - Double single tap: Repeat primary action (tap + register)
 *
 * This module centralizes all media-related tap‑dance logic so that audio,
 * playback, and brightness controls remain consistent and easy to maintain
 * across the keymap.
 */

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
