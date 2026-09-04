// ─────────────────────────────────────────────────────────────────
// Spacecentricity v0.1.0 — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// Source: https://github.com/LittleWalter/spacecentricity-mk47
// ─────────────────────────────────────────────────────────────────

#include "td_doom.h"
#include "tap_dance_actions.h"
#include "src/macros/mac_doom.h"

// ─────────────────────────────────────────────────────────────
// Doom (1993) Tap Dance Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_DOOM_MENU         Esc 🅧 y n
// ──────────────────────────────

// Create static `doom_menu_tap_dance` for TD_DOOM_MEN
TD_DEF(doom_menu);

// Send the appropriate Doom (1993) command for TD_DOOM_MENU
void doom_menu_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_menu);
    switch (TD_STATE(doom_menu)) {
        case TD_SINGLE_HOLD:
            register_and_update(KC_N); // N for “no”
            break;
        case TD_DOUBLE_TAP:
            register_and_update(KC_F10); // Quit game?
            break;
        case TD_DOUBLE_HOLD: // `y` for “yes”
            register_and_update(KC_Y);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_ESC);          // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_ESC);          // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_ESC);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_MENU and reset the state
void doom_menu_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_menu)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_N); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_F10); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_Y); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_ESC); break;
        default: break;
    }
    TD_RESET(doom_menu);
}

// ──────────────────────────────
// TD_DOOM_LOAD         Load Save
// ──────────────────────────────

// Create static `doom_load_tap_dance` for TD_DOOM_LOAD
TD_DEF(doom_load);

// Send the appropriate Doom (1993) command for TD_DOOM_LOAD
void doom_load_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_load);
    switch (TD_STATE(doom_load)) {
        case TD_SINGLE_HOLD:
            register_and_update(KC_F2); // 
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_F3);
        case TD_DOUBLE_TAP:                                    // fallthru
        case TD_DOUBLE_HOLD:                                   // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_F3);          // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_F3);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_LOAD and reset the state
void doom_load_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_load)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_F2); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_F3); break;
        default: break;
    }
    TD_RESET(doom_load);
}

// ──────────────────────────────
// TD_DOOM_MAP    Open Mark Clear (Automap)
// ──────────────────────────────

// Create static `doom_map_tap_dance` for TD_DOOM_MAP
TD_DEF(doom_map);

// Send the appropriate Doom (1993) command for TD_DOOM_MAP
void doom_map_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_map);
    switch (TD_STATE(doom_map)) {
        case TD_DOUBLE_HOLD:
            register_and_update(KC_C); // C for “clear” marks in automap
            break;
        case TD_SINGLE_HOLD:
            register_and_update(KC_M); // M to mark current spot in “automap”
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_TAB);        // Tab to open the “automap”
        case TD_DOUBLE_TAP:                                   // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_TAB);        // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_TAB);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_MAP
void doom_map_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_map)) {
        case TD_DOUBLE_HOLD: unregister_code16(KC_C); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_M); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_TAB); break;
        default: break;
    }
    TD_RESET(doom_map);
}

// ──────────────────────────────
// TD_DOOM_MUTE        🔇⏯ ⏹ Doom Audio
// ──────────────────────────────

// Create static `doom_mute_tap_dance` for TD_DOOM_MUTE
TD_DEF(doom_mute);

// Send the appropriate media function for TD_DOOM_MUTE
void doom_mute_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_mute);
    switch (TD_STATE(doom_mute)) {
        case TD_DOUBLE_TAP:  register_and_update(KC_MPLY); break; // ⏯  Play/Pause Media
        case TD_SINGLE_HOLD: register_and_update(KC_F4);   break; // Open Doom Audio Menu
        case TD_DOUBLE_HOLD: register_and_update(KC_MSTP); break; // ⏹  Stop Media
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_MUTE);
        case TD_SINGLE_TAP:  register_and_update(KC_MUTE); break; // 🔇 Audio/Volume Mute
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_MUTE and reset the state
void doom_mute_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_mute)) {
        case TD_SINGLE_TAP:  unregister_code16(KC_MUTE); break;
        case TD_DOUBLE_TAP:  unregister_code16(KC_MPLY); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_F4);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_MSTP); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_MUTE); break;
        default: break;
    }
    TD_RESET(doom_mute);
}

// ──────────────────────────────
// TD_DOOM_PREV   Bspc  Quit Game
// ──────────────────────────────

// Create static `doom_prev_tap_dance` for TD_DOOM_PREV
TD_DEF(doom_prev);

// Send the appropriate Doom (1993) command for TD_DOOM_PREV
void doom_prev_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_prev);
    switch (TD_STATE(doom_prev)) {
        case TD_DOUBLE_HOLD:
            register_and_update(KC_F7); // 
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_F3);          // fallthru
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_F3);          // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_BSPC);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_PREV and reset the state
void doom_prev_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_prev)) {
        case TD_DOUBLE_HOLD: unregister_code16(KC_F7); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_BSPC); break;
        default: break;
    }
    TD_RESET(doom_prev);
}

// ──────────────────────────────
// TD_DOOM_6                6   8 (Switch: Rocket (Tap), BFG 9000 (Hold)
// ──────────────────────────────

// Create static `doom_6_tap_dance` for TD_DOOM_6
TD_DEF(doom_6);

// Send the appropriate Doom (1993) command for TD_DOOM_6
void doom_6_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(doom_6);
    switch (TD_STATE(doom_6)) {
        case TD_SINGLE_HOLD:
            register_and_update(KC_8); // 
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_6);          // fallthru
        case TD_DOUBLE_TAP:                                   // fallthru
        case TD_DOUBLE_HOLD:                                  // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_6);          // fallthru
        case TD_SINGLE_TAP:        register_and_update(KC_6);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_DOOM_6 and reset the state
void doom_6_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(doom_6)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_8); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_6); break;
        default: break;
    }
    TD_RESET(doom_6);
}
