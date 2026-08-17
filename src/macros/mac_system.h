/*
 * mac_system.h — Cross‑platform OS macro utilities for QMK
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

#pragma once

#include QMK_KEYBOARD_H

#define MACOS_APP_SWITCH_DELAY 1000 // ms to delay for application switchiong on macOS
#define MACOS_DIALOG_DELAY     500  // ms to delay for dialogs to open/animate on macOS

// Applications launchable via macOS Spotlight Search
typedef enum {
    SL_FINDER,
    SL_CALCULATOR
} spotlight_t;

// ─────────────────────────────────────────────────────────────
// Operating System Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+LEFT for macOS, otherwise uses LCTL+ALT+LEFT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+LEFT for Microsoft Windows.
void vdt_left_macro(void);

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+RIGHT for macOS, otherwise uses LCTL+ALT+RIGHT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+RIGHT for Microsoft Windows.
void vdt_right_macro(void);

// Opens macOS Finder
void open_finder_macos(void);

// Opens macOS Calculator
void open_calculator_macos(void);

// Opens Trash folder in macOS Finder.
void open_trash_macos_macro(void);

// Open launcher or Windows Search.
void open_launcher_macro(void);

// Open emoji picker popup.
void open_emoji_picker_macro(void);

// Open the system file manager.
// - macOS Finder
// - Windows Explorer (Win+E)
// - Linux: Super+E (works on most DEs; customize as needed)
void open_file_manager_macro(void);

// Locks the screen on the current operating system.
// - macOS: ⌘ + Ctrl + Q (instant lock)
// - Linux: Ctrl + Alt + L (common DE shortcut; works on GNOME/KDE/XFCE)
// - Windows: Win + L (standard lock shortcut)
void lock_screen_macro(void);

// Toggles full-screen mode on the current operating system.
// - macOS: ⌘ + Ctrl + F (standard full-screen toggle)
// - Windows: F11 (common full‑screen shortcut in browsers and many apps)
// - Linux: F11 (supported by most DEs and applications)
void full_screen_toggle_macro(void);

// Deletes selected files using the OS-appropriate shortcut.
// - macOS: ⌘ + Delete (move to Trash)
// - Windows: Delete key (move to Recycle Bin)
// - Linux: Delete key (common default in most file managers)
void delete_files_macro(void);

// Takes a partial/area selection screenshot. On Microsoft Windows, it opens the Snipping Tool
// since there is no direct keyboard shortcut.
void screenshot_partial_macro(void);

// Takes a screenshot of the currently active window.
void screenshot_window_macro(void);

// Takes full screenshots, all screens.
void screenshot_full_macro(void);

// Open the screenshots UI (toolbar).
void screenshot_toolbar_macro(void);

// ─────────────────────────────────────────────────────────────
// App Shortcuts
// ─────────────────────────────────────────────────────────────

// App shortcut: select all; defaults to CMD+A for macOS, otherwise
// uses LCTL+A for Microsoft Windows and Linux
void select_all_macro(void);

// App shortcut: copy selected; defaults to CMD+C for macOS, otherwise
// uses LCTL+C for Microsoft Windows and Linux
void copy_macro(void);

// App shortcut: cut selected; defaults to CMD+X for macOS, otherwise
// uses LCTL+X for Microsoft Windows and Linux
void cut_macro(void);

// App shortcut: paste from clipboard; defaults to CMD+V for macOS, otherwise
// uses LCTL+V for Microsoft Windows and Linux
void paste_macro(void);

// Browser shortcut: zoom in; defaults to CMD+SFT+= for macOS, otherwise
// uses LCTL+SFT+= for Microsoft Windows and Linux
void zoom_in_macro(void);

// Browser shortcut: zoom out; defaults to CMD+- for macOS, otherwise
// uses LCTL+- for Microsoft Windows and Linux
void zoom_out_macro(void);

// Browser shortcut: zoom reset (100%); defaults to CMD+0 for macOS, otherwise
// uses LCTL+0 for Microsoft Windows and Linux
void zoom_reset_macro(void);

// Triggers operating system application switcher key: CMD for macOS or ALT for Linux and Windows.
// The passed Boolean means that the modifier key is currently held by the user.
void app_switch_macro(const bool is_active);
