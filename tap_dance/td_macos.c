#include "td_macos.h"
#include "keymap.h"
#include "macros/mac_macos.h"
#include "tap_dance_actions.h"

// ─────────────────────────────────────────────────────────────
//  Apple macOS-Related Tap Dances
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_SPOTLGHT_MACOS   🔍 😀   📁
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SPOTLGHT_MACOS tap and hold dance.
static td_tap_t spotlght_macos_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Apple macOS command for TD_SPOTLGHT_MACOS
void spotlght_macos_finished(tap_dance_state_t *state, void *user_data) {
    spotlght_macos_tap_state.state = cur_dance(state);
    switch (spotlght_macos_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(LGUI(KC_SPC));     break; // Open Spotlight Search
        case TD_DOUBLE_TAP:  register_code16(MACOS_EMOJI_MENU); break; // Open Emoji Menu
        case TD_SINGLE_HOLD: open_finder_macos();               break; // Open Finder
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(C(KC_F))); register_code16(LGUI(C(KC_F))); break;
        default: break;
    }
}

// Release any keys pressed by TD_SPOTLGHT_MACOS and reset the state
void spotlght_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (spotlght_macos_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(LGUI(KC_SPC));    break;
        case TD_DOUBLE_TAP: unregister_code16(LGUI(C(KC_SPC))); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(LGUI(C(KC_F))); break;
        default: break;
    }
    spotlght_macos_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_FS_MACOS               FS 🔒
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_FS_MACOS tap and hold dance.
static td_tap_t fs_macos_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Apple macOS command for TD_FS_MACOS
void fs_macos_finished(tap_dance_state_t *state, void *user_data) {
    fs_macos_tap_state.state = cur_dance(state);
    switch (fs_macos_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(LGUI(C(KC_F))); break; // Full screen app toggle
        case TD_SINGLE_HOLD: register_code16(LGUI(C(KC_Q))); break; // Lock Mac/iDevice
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(C(KC_F))); register_code16(LGUI(C(KC_F))); break;
        default: break;
    }
}

// Release any keys pressed by TD_FS_MACOS and reset the state
void fs_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (fs_macos_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(LGUI(C(KC_F))); break;
        case TD_SINGLE_HOLD: unregister_code16(LGUI(C(KC_Q))); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(LGUI(C(KC_F))); break;
        default: break;
    }
    fs_macos_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SCRNSHOT_MACOS     ▣ Opts ⛶
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SCRNSHOT_MACOS tap, tap+hold, and hold dance.
static td_tap_t scrnshot_macos_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Apple macOS command for TD_SCRNSHOT_MACOS
void scrnshot_macos_finished(tap_dance_state_t *state, void *user_data) {
    scrnshot_macos_tap_state.state = cur_dance(state);
    switch (scrnshot_macos_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(LGUI(S(KC_4))); break; // Partial Screenshot
        case TD_SINGLE_HOLD: register_code16(LGUI(S(KC_3))); break; // Full Screenshot/All Screens
        case TD_DOUBLE_HOLD: register_code16(LGUI(S(KC_5))); break; // Screenshot Toolbar, all options
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(S(KC_4))); register_code16(LGUI(S(KC_4))); break;
        default: break;
    }
}

// Release any keys pressed by TD_SCRNSHOT_MACOS and reset the state
void scrnshot_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (scrnshot_macos_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(LGUI(S(KC_4))); break;
        case TD_SINGLE_HOLD: unregister_code16(LGUI(S(KC_3))); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(S(KC_5))); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(LGUI(S(KC_4))); break;
        default: break;
    }
    scrnshot_macos_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DEL_MACOS          ␡ Empty🗑️
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DEL_MACOS tap, tap+hold, and hold dance.
static td_tap_t del_macos_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Apple macOS command for TD_DEL_MACOS
void del_macos_finished(tap_dance_state_t *state, void *user_data) {
    del_macos_tap_state.state = cur_dance(state);
    switch (del_macos_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(LGUI(KC_BSPC));    break; // Delete File
        case TD_DOUBLE_TAP:  open_trash_macos_macro();          break; // Open Trash in macOS Finder
        case TD_SINGLE_HOLD: register_code16(LGUI(S(KC_BSPC))); break; // Empty Trash Can
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_BSPC)); register_code16(LGUI(KC_BSPC)); break;
        default: break;
    }
}

// Release any keys pressed by TD_DEL_MACOS and reset the state
void del_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (del_macos_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(LGUI(KC_BSPC)); break;
        case TD_SINGLE_HOLD: unregister_code16(LGUI(S(KC_BSPC))); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_BSPC)); break;
        default: break;
    }
    del_macos_tap_state.state = TD_NONE;
}
