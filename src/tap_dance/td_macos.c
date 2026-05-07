#include "td_macos.h"
#include "src/core/custom_keys.h"
#include "src/core/keymap.h"
#include "src/macros/mac_macos.h"
#include "tap_dance_actions.h"

// ─────────────────────────────────────────────────────────────
//  Apple macOS-Related Tap Dances
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_SPOTLIGHT_MACOS  🔍 😀   📁
// ──────────────────────────────

// Create static `spotlight_macos_tap_dance` for TD_SPOTLIGHT_MACOS
TD_DEF(spotlight_macos);

// Send the appropriate Apple macOS command for TD_SPOTLGHT_MACOS
void spotlight_macos_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(spotlight_macos);
    uint16_t kc;
    switch (TD_STATE(spotlight_macos)) {
        case TD_SINGLE_TAP: // Launcher
            kc = LGUI(KC_SPC); // macOS Spotlight Search
            if (current_os == OS_WIN) {
                kc = LGUI(KC_S); // Windows Search
            } else if (current_os == OS_LINUX) {
                kc = A(KC_SPC); // Albert launcher
            }
            tap_and_update(kc);
            break;
        case TD_DOUBLE_TAP: // Open Emoji Picker
            kc = LGUI(C(KC_SPC)); // macOS Emoji & Symbols popup
            if (current_os == OS_WIN) {
                kc = LGUI(KC_DOT); // Windows Emoji Menu
            } else if (current_os == OS_LINUX) {
                kc = C(KC_DOT);
            }
            tap_and_update(kc);
            break;
        case TD_SINGLE_HOLD: // Open File Manager
            current_os == OS_MACOS ? open_finder_macos()
                                   : tap_and_update(LGUI(KC_E)); // Win+E: Windows Explorer
            break;
        default: break;
    }
}

// Release any keys pressed by TD_SPOTLGHT_MACOS and reset the state
void spotlight_macos_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(spotlight_macos);
}

// ──────────────────────────────
// TD_FS_MACOS      Full Screen 🔒
// ──────────────────────────────

// Create static `fs_macos_tap_dance` for TD_FS_MACOS
TD_DEF(fs_macos);

// Send the appropriate Apple macOS command for TD_FS_MACOS
void fs_macos_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(fs_macos);
    switch (TD_STATE(fs_macos)) {
        case TD_SINGLE_HOLD: // Lock screen
            uint16_t kc = LGUI(C(KC_Q)); // Lock Mac/iDevice
            if (current_os == OS_WIN) {
                kc = LGUI(KC_L);
            } else if (current_os == OS_LINUX) {
                kc = C(A(KC_L));
            }
            tap_and_update(kc);
            break;
        case TD_SINGLE_TAP: // Full screen toggle
            current_os == OS_MACOS ? tap_and_update(LGUI(C(KC_F)))
                                   : tap_and_update(KC_F11);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_FS_MACOS and reset the state
void fs_macos_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(fs_macos);
}

// ──────────────────────────────
// TD_SCRNSHOT_MACOS     ▣ Opts ⛶
// ──────────────────────────────

// Create static `scrnshot_macos_tap_dance` for TD_SCRNSHOT_MACOS
TD_DEF(scrnshot_macos);

// Send the appropriate Apple macOS command for TD_SCRNSHOT_MACOS
void scrnshot_macos_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(scrnshot_macos);
    switch (TD_STATE(scrnshot_macos)) {
        case TD_SINGLE_HOLD: register_and_update(LGUI(S(KC_3))); break; // Full Screenshot/All Screens
        case TD_DOUBLE_HOLD: register_and_update(LGUI(S(KC_5))); break; // Screenshot Toolbar, all options
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(S(KC_4)));                 // fallthru
        case TD_SINGLE_TAP:        register_and_update(LGUI(S(KC_4))); break; // Partial Screenshot
        default: break;
    }
}

// Release any keys pressed by TD_SCRNSHOT_MACOS and reset the state
void scrnshot_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(scrnshot_macos)) {
        case TD_SINGLE_HOLD: unregister_code16(LGUI(S(KC_3))); break;
        case TD_DOUBLE_HOLD: unregister_code16(LGUI(S(KC_5))); break;
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(LGUI(S(KC_4))); break;
        default: break;
    }
    TD_RESET(scrnshot_macos);
}

// ──────────────────────────────
// TD_DEL_MACOS          ␡ Empty🗑️
// ──────────────────────────────

// Create static `del_macos_tap_dance` for TD_DEL_MACOS
TD_DEF(del_macos);

// Send the appropriate Apple macOS command for TD_DEL_MACOS
void del_macos_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(del_macos);
    switch (TD_STATE(del_macos)) {
        case TD_DOUBLE_TAP:  open_trash_macos_macro();              break; // Open Trash in macOS Finder
        case TD_SINGLE_HOLD: register_and_update(LGUI(S(KC_BSPC))); break; // Empty Trash Can
        case TD_DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_BSPC));                 // fallthru
        case TD_SINGLE_TAP:        register_and_update(LGUI(KC_BSPC)); break; // Delete File
        default: break;
    }
}

// Release any keys pressed by TD_DEL_MACOS and reset the state
void del_macos_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(del_macos)) {
        case TD_SINGLE_HOLD: unregister_code16(LGUI(S(KC_BSPC))); break;
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(LGUI(KC_BSPC)); break;
        default: break;
    }
    TD_RESET(del_macos);
}
