/*
 * td_media.c — Tap Dance definitions for media, playback, and system controls.
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

#include "td_media.h"
#include "tap_dance_actions.h"
#include "src/features/case_mode.h"

// ─────────────────────────────────────────────────────────────
// Media Tap Dance Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_MUTE              🔇⏯ ⏹ C+M
// ──────────────────────────────

// Create static `mute_tap_dance` for TD_MUTE
TD_DEF(mute);

// Send the appropriate media function for TD_MUTE
void mute_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(mute);
    switch (TD_STATE(mute)) {
        case TD_DOUBLE_TAP:  register_and_update(KC_MPLY); break; // ⏯  Play/Pause Media
        case TD_SINGLE_HOLD: register_and_update(C(KC_M)); break; // LCTL+M (Browser Tab Mute)
        case TD_DOUBLE_HOLD: register_and_update(KC_MSTP); break; // ⏹  Stop Media
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_MUTE);
        case TD_SINGLE_TAP:  register_and_update(KC_MUTE); break; // 🔇 Audio/Volume Mute
        default: break;
    }
}

// Release any keys pressed by TD_MUTE and reset the state
void mute_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(mute)) {
        case TD_SINGLE_TAP:  unregister_code16(KC_MUTE); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MPLY); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_M)); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_MSTP); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_MUTE); break;
        default: break;
    }
    TD_RESET(mute);
}

// ──────────────────────────────
// TD_VOLD               🔉⏮ 🔅🔉
// ──────────────────────────────

// Create static `vold_tap_dance` for TD_VOLD
TD_DEF(vold);

// Send the appropriate media function for TD_VOLD
void vold_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(vold);
    switch (TD_STATE(vold)) {
        case TD_DOUBLE_TAP:  register_and_update(KC_MPRV); break; // Previous Track
        case TD_SINGLE_HOLD: register_and_update(KC_VOLD); break; // Volume Down
        case TD_DOUBLE_HOLD: register_and_update(KC_BRID); break; // Brightness Down (Laptop)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_VOLD);
        case TD_SINGLE_TAP:  register_and_update(KC_VOLD); break; // Volume Down
        default: break;
    }
}

// Release any keys pressed by TD_VOLD and reset the state
void vold_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(vold)) {
        case TD_SINGLE_TAP:  unregister_code16(KC_VOLD); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MPRV); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_VOLD); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_BRID);  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_VOLD); break;
        default: break;
    }
    TD_RESET(vold);
}

// ──────────────────────────────
// TD_VOLU               🔊⏭ 🔆🔊
// ──────────────────────────────

// Create static `volu_tap_dance` for TD_VOLU
TD_DEF(volu);

// Send the appropriate media function for TD_VOLU
void volu_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(volu);
    switch (TD_STATE(volu)) {
        case TD_DOUBLE_TAP:  register_and_update(KC_MNXT); break; // Next Track
        case TD_SINGLE_HOLD: register_and_update(KC_VOLU); break; // Volume Up
        case TD_DOUBLE_HOLD: register_and_update(KC_BRIU); break; // Brightness Up (Laptop)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_VOLU);
        case TD_SINGLE_TAP:  register_and_update(KC_VOLU); break; // Volume Up
        default: break;
    }
}

// Release any keys pressed by TD_VOLU and reset the state
void volu_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(volu)) {
        case TD_SINGLE_TAP:  unregister_code16(KC_VOLU); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MNXT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_VOLU); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_BRIU);  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_VOLU); break;
        default: break;
    }
    TD_RESET(volu);
}
