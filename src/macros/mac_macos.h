// ─────────────────────────────────────────────────────────────────
// Spacecentricity v0.1.0 — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// Source: https://github.com/LittleWalter/spacecentricity-mk47
// ─────────────────────────────────────────────────────────────────

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
// Apple macOS Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Opens macOS Finder
void open_finder_macos(void);

// Opens macOS Calculator
void open_calculator_macos(void);

// Opens Trash folder in macOS Finder.
void open_trash_macos_macro(void);
