#include "mac_macos.h"
#include "macros.h"

// ─────────────────────────────────────────────────────────────
// Apple macOS Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Opens macOS Finder
void open_finder_macos(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(LGUI(KC_SPC)); // Open Spotlight Search
    wait_ms(MACOS_DIALOG_DELAY);
    SEND_STRING("finder" SS_TAP(X_ENTER));

    mod_state_restore(&saved);
}

// Opens Trash folder in macOS Finder.
void open_trash_macos_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    // NOTE: There is no single shortcut to open the Trash folder in macOS.
    // This is a roundabout way of doing so:
    // 1. Open Finder via Spotlight
    // 2. CMD+SFT+G to go to folder
    // 3. Type "trash" and hit Enter
    open_finder_macos();
    wait_ms(MACOS_APP_SWITCH_DELAY);
    tap_code16(LGUI(S(KC_G))); // Open "Go to Folder" dialog
    wait_ms(MACOS_DIALOG_DELAY);
    SEND_STRING("trash" SS_TAP(X_ENTER)); // Open Trash folder

    mod_state_restore(&saved);
}
