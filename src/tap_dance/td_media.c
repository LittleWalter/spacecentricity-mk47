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

// Instance of 'td_tap_t' for the TD_MUTE quad tap dance
static td_tap_t mute_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate media function for TD_MUTE
void mute_finished(tap_dance_state_t *state, void *user_data) {
    mute_tap_state.state = cur_dance(state);
    switch (mute_tap_state.state) {
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
    switch (mute_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(KC_MUTE); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MPLY); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_M)); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_MSTP); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_MUTE); break;
        default: break;
    }
    mute_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_VOLD               🔉⏮ 🔅🔉
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_VOLD (volume down) quad tap dance.
static td_tap_t vold_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate media function for TD_VOLD
void vold_finished(tap_dance_state_t *state, void *user_data) {
    vold_tap_state.state = cur_dance(state);
    switch (vold_tap_state.state) {
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
    switch (vold_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(KC_VOLD); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MPRV); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_VOLD); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_BRID);  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_VOLD); break;
        default: break;
    }
    vold_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_VOLU               🔊⏭ 🔆🔊
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_VOLU (volume up) quad tap dance.
static td_tap_t volu_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate media function for TD_VOLU
void volu_finished(tap_dance_state_t *state, void *user_data) {
    volu_tap_state.state = cur_dance(state);
    switch (volu_tap_state.state) {
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
    switch (volu_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(KC_VOLU); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MNXT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_VOLU); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_BRIU);  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_VOLU); break;
        default: break;
    }
    volu_tap_state.state = TD_NONE;
}
