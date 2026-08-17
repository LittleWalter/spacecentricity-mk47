/*
 * mac_system.c — Cross‑platform OS macro utilities for QMK
 *
 * This module implements a unified set of operating-system-aware macros
 * used throughout the keymap. It provides consistent behavior for common
 * system actions across macOS, Linux, and Windows by branching on
 * `current_os` and emitting the appropriate shortcut sequence.
 *
 * Features included:
 *   • Virtual desktop navigation (left/right)
 *   • Spotlight / launcher / emoji picker access
 *   • File manager shortcuts (Finder, Explorer, etc.)
 *   • Screen lock, full-screen toggle, and delete-file actions
 *   • Screenshot macros (partial, window, full, toolbar)
 *   • App-level shortcuts (select all, copy, cut, paste, zoom controls)
 *   • App switcher modifier handling
 *
 * Many functions temporarily clear the modifier state using
 * `mod_state_save_and_clear()` and restore it afterward to avoid
 * interfering with user-held modifiers. Some macOS actions use Spotlight
 * search to open apps such as Finder or Calculator, as seen in:
 *
 *     "Open Finder via Spotlight"
 *     "Type 'trash' and hit Enter"
 *
 * This file is part of the system-integration layer for the keymap and
 * is intended to keep OS-specific logic isolated, readable, and easy to
 * extend with additional platform behaviors.
 */

#include "mac_system.h"
#include "macros.h"
#include "src/core/custom_keys.h"

// ─────────────────────────────────────────────────────────────
// Operating System Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+LEFT for macOS, otherwise uses LCTL+ALT+LEFT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+LEFT for Microsoft Windows.
void vdt_left_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS: tap_code16(C(KC_LEFT));       break; // macOS:   LCTL+LEFT
        case OS_LINUX: tap_code16(C(A(KC_LEFT)));    break; // Linux:   LCTL+ALT+LEFT
        case OS_WIN:   tap_code16(LGUI(C(KC_LEFT))); break; // Windows: WIN+LCTL+LEFT
        default: break;
    }

    mod_state_restore(&saved);
}

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+RIGHT for macOS, otherwise uses LCTL+ALT+RIGHT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+RIGHT for Microsoft Windows.
void vdt_right_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS: tap_code16(C(KC_RGHT));       break; // macOS:   LCTL+RIGHT
        case OS_LINUX: tap_code16(C(A(KC_RGHT)));    break; // Linux:   LCTL+ALT+RIGHT
        case OS_WIN:   tap_code16(LGUI(C(KC_RGHT))); break; // Windows: WIN+LCTL+RIGHT
        default: break;
    }

    mod_state_restore(&saved);
}

static void open_spotlight_search(const spotlight_t search) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(LGUI(KC_SPC)); // Open Spotlight Search
    wait_ms(MACOS_DIALOG_DELAY);
    switch (search) {
        case SL_FINDER:
            SEND_STRING("finder" SS_TAP(X_ENTER));
            break;
        case SL_CALCULATOR:
            SEND_STRING("calculator" SS_TAP(X_ENTER));
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Opens macOS Finder
void open_finder_macos(void) {
    open_spotlight_search(SL_FINDER);
}

// Opens macOS Calculator
void open_calculator_macos(void) {
    open_spotlight_search(SL_CALCULATOR);
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
    tap_code16(LGUI(S(KC_G)));            // Open "Go to Folder" dialog
    wait_ms(MACOS_DIALOG_DELAY);
    SEND_STRING("trash" SS_TAP(X_ENTER)); // Open Trash folder

    mod_state_restore(&saved);
}

// Open launcher or Windows Search.
void open_launcher_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(KC_SPC)); // macOS Spotlight Search
            break;
        case OS_LINUX:
            tap_code16(A(KC_SPC));    // Launch Albert/Rofi/etc.
            break;
        case OS_WIN:
            tap_code16(LGUI(KC_S));   // Windows Search
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Open emoji picker popup.
void open_emoji_picker_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(C(KC_SPC))); // macOS Emoji & Symbols popup
            break;
        case OS_LINUX:
            tap_code16(C(KC_DOT));       // TODO: Figure out a decent shortcut for Smile, etc.
            break;
        case OS_WIN:
            tap_code16(LGUI(KC_DOT));    // Windows Emoji Menu
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Open the system file manager.
// - macOS Finder
// - Windows Explorer (Win+E)
// - Linux: Super+E (works on most DEs; customize as needed)
void open_file_manager_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS: open_finder_macos(); break;
        case OS_LINUX: // Many DEs map Super+E to file manager
        case OS_WIN:
        default:
            tap_code16(LGUI(KC_E)); // Windows Explorer
            break;
    }

    mod_state_restore(&saved);
}

// Locks the screen on the current operating system.
// - macOS: ⌘ + Ctrl + Q (instant lock)
// - Linux: Ctrl + Alt + L (common DE shortcut; works on GNOME/KDE/XFCE)
// - Windows: Win + L (standard lock shortcut)
void lock_screen_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS: tap_code16(LGUI(C(KC_Q))); break;
        case OS_LINUX: tap_code16(C(A(KC_L)));    break;
        case OS_WIN:   tap_code16(LGUI(KC_L));    break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Toggles full-screen mode on the current operating system.
// - macOS: ⌘ + Ctrl + F (standard full-screen toggle)
// - Windows: F11 (common full‑screen shortcut in browsers and many apps)
// - Linux: F11 (supported by most DEs and applications)
void full_screen_toggle_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(C(KC_F)));
            break;
        case OS_LINUX:
        case OS_WIN:
            tap_code16(KC_F11);
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Deletes selected files using the OS-appropriate shortcut.
// - macOS: ⌘ + Delete (move to Trash)
// - Windows: Delete key (move to Recycle Bin)
// - Linux: Delete key (common default in most file managers)
void delete_files_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS: tap_code16(LGUI(KC_BSPC)); break;
        case OS_LINUX:
        case OS_WIN:
            tap_code16(KC_DEL);
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Takes a partial/area selection screenshot. On Microsoft Windows, it opens the Snipping Tool
// since there is no direct keyboard shortcut.
void screenshot_partial_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(S(KC_4)));      // macOS select area
            break;
        case OS_LINUX:
            tap_code16(S(KC_PRINT_SCREEN)); // Linux select area
            break;
        case OS_WIN:
            tap_code16(LGUI(S(KC_S)));      // Windows Snipping Tool
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Takes a screenshot of the currently active window.
void screenshot_window_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(S(KC_4)));
            wait_ms(MACOS_DIALOG_DELAY);
            tap_code(KC_SPC); // User must click on the window they want after hitting space
            break;
        case OS_LINUX:
        case OS_WIN:
            tap_code16(A(KC_PRINT_SCREEN));
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Takes full screenshots, all screens.
void screenshot_full_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (current_os) {
        case OS_MACOS:
            tap_code16(LGUI(S(KC_3)));         // macOS full/all screens
            break;
        case OS_LINUX:
            tap_code16(KC_PRINT_SCREEN);       // Linux full screenshot
            break;
        case OS_WIN:
            tap_code16(LGUI(KC_PRINT_SCREEN)); // Windows: saves full screenshot in Pictures/Screenshots
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Open the screenshots UI (toolbar).
void screenshot_toolbar_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    current_os == OS_MACOS
        ? tap_code16(LGUI(S(KC_5)))  // macOS screenshot toolbar
        : tap_code16(LGUI(S(KC_S))); // Windows Snipping Tool/Linux: Gnome screenshot UI

    mod_state_restore(&saved);
}

// ─────────────────────────────────────────────────────────────
// App Shortcuts
// ─────────────────────────────────────────────────────────────

// App shortcut: select all; defaults to CMD+A for macOS, otherwise
// uses LCTL+A for Microsoft Windows and Linux
void select_all_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_A) : C(KC_A));

    mod_state_restore(&saved);
}

// App shortcut: copy selected; defaults to CMD+C for macOS, otherwise
// uses LCTL+C for Microsoft Windows and Linux
void copy_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_C) : C(KC_C));

    mod_state_restore(&saved);
}

// App shortcut: cut selected; defaults to CMD+X for macOS, otherwise
// uses LCTL+X for Microsoft Windows and Linux
void cut_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_X) : C(KC_X));

    mod_state_restore(&saved);
}

// App shortcut: paste from clipboard; defaults to CMD+V for macOS, otherwise
// uses LCTL+V for Microsoft Windows and Linux
void paste_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_V) : C(KC_V));

    mod_state_restore(&saved);
}

// Browser shortcut: zoom in; defaults to CMD+SFT+= for macOS, otherwise
// uses LCTL+SFT+= for Microsoft Windows and Linux
void zoom_in_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(S(KC_EQL)) : C(S(KC_EQL)));

    mod_state_restore(&saved);
}

// Browser shortcut: zoom out; defaults to CMD+- for macOS, otherwise
// uses LCTL+- for Microsoft Windows and Linux
void zoom_out_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_MINS) : C(KC_MINS));

    mod_state_restore(&saved);
}

// Browser shortcut: zoom reset (100%); defaults to CMD+0 for macOS, otherwise
// uses LCTL+0 for Microsoft Windows and Linux
void zoom_reset_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    tap_code16(current_os == OS_MACOS ? LGUI(KC_0) : C(KC_0));

    mod_state_restore(&saved);
}

// Triggers operating system application switcher key: CMD for macOS or ALT for Linux and Windows.
// The passed Boolean means that the modifier key is currently held by the user.
void app_switch_macro(const bool is_active) {
    mod_state_t saved = mod_state_save_and_clear();

    const uint8_t modifier = MOD_BIT(current_os == OS_MACOS ? KC_LGUI : KC_LALT);
    if (is_active) {
        register_mods(modifier); // Hold the modifer down to activate app switcher
    } else {
        unregister_mods(modifier); // Release when done
    }

    mod_state_restore(&saved);
}
