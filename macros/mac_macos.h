#pragma once

#include QMK_KEYBOARD_H

#define MACOS_APP_SWITCH_DELAY 1000 // ms to delay for application switchiong on macOS
#define MACOS_DIALOG_DELAY     500  // ms to delay for dialogs to open/animate on macOS

// ─────────────────────────────────────────────────────────────
// Apple macOS Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Opens macOS Finder
void open_finder_macos(void);

// Opens Trash folder in macOS Finder.
void open_trash_macos_macro(void);
