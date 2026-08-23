#include "td_system.h"
#include "src/core/custom_keys.h"
#include "src/core/keymap.h"
#include "src/macros/mac_system.h"
#include "tap_dance_actions.h"

// ─────────────────────────────────────────────────────────────
// Operating System Tap Dances:
// Keycode logic lives in src/macros/mac_system.c
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_LAUNCHER_OS      🔍 😀   📁
// ──────────────────────────────

// Create static `launcher_os_tap_dance` for TD_SPOTLIGHT_OS
TD_DEF(launcher_os);

// Send the appropriate Apple macOS command for TD_SPOTLGHT_OS
void launcher_os_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(launcher_os);
    switch (TD_STATE(launcher_os)) {
        case TD_SINGLE_TAP:  open_launcher_macro();     break;
        case TD_DOUBLE_TAP:  open_emoji_picker_macro(); break;
        case TD_SINGLE_HOLD: open_file_manager_macro(); break;
        default: break;
    }
}

// Release any keys pressed by TD_SPOTLGHT_OS and reset the state
void launcher_os_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(launcher_os);
}

// ──────────────────────────────
// TD_FS_OS         Full Screen 🔒
// ──────────────────────────────

// Create static `fs_os_tap_dance` for TD_FS_OS
TD_DEF(fs_os);

// Send the appropriate Apple macOS command for TD_FS_OS
void fs_os_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(fs_os);
    switch (TD_STATE(fs_os)) {
        case TD_SINGLE_TAP:  full_screen_toggle_macro(); break;
        case TD_SINGLE_HOLD: lock_screen_macro();        break;
        default: break;
    }
}

// Release any keys pressed by TD_FS_OS and reset the state
void fs_os_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(fs_os);
}

// ──────────────────────────────
// TD_SCRNSHOT_OS        ▣ Opts ⛶
// ──────────────────────────────

// Create static `scrnshot_os_tap_dance` for TD_SCRNSHOT_OS
TD_DEF(scrnshot_os);

// Send the appropriate Apple macOS command for TD_SCRNSHOT_OS
void scrnshot_os_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(scrnshot_os);
    switch (TD_STATE(scrnshot_os)) {
        case TD_SINGLE_TAP: // Partial Screenshot
            screenshot_partial_macro();
            break;
        case TD_DOUBLE_TAP: // Window Screenshot
            screenshot_window_macro();
            break;
        case TD_SINGLE_HOLD: // Full Screenshot/All Screens
            screenshot_full_macro();
            break;
        case TD_DOUBLE_HOLD: // Screenshot Toolbar (all options)
            screenshot_toolbar_macro();
            break;
        default: break;
    }
}

// Release any keys pressed by TD_SCRNSHOT_OS and reset the state
void scrnshot_os_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(scrnshot_os);
}

// ──────────────────────────────
// TD_DEL_OS       ␡ Empty🗑️ Open🗑️
// ──────────────────────────────

// Create static `del_os_tap_dance` for TD_DEL_OS
TD_DEF(del_os);

// Send the appropriate Apple macOS command for TD_DEL_OS
// TODO: Linux & Windows trash/recycle bin support
void del_os_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(del_os);
    switch (TD_STATE(del_os)) {
        case TD_SINGLE_TAP: delete_files_macro(); break;
        case TD_SINGLE_HOLD:
            if (current_os == OS_MACOS) {
                open_trash_macos_macro();
            }
            break;
        case TD_DOUBLE_HOLD: // Empty Trash
            if (current_os == OS_MACOS) {
                tap_and_update(LGUI(S(KC_BSPC)));
            }
            break;
        default: break;
    }
}

// Release any keys pressed by TD_DEL_OS and reset the state
void del_os_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(del_os);
}
