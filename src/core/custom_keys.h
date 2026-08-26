#pragma once

#include QMK_KEYBOARD_H

#define BASIC_KEYCODES 0xFF

// ─────────────────────────────────────────────────────────────
// Operating System State
// ─────────────────────────────────────────────────────────────

typedef enum {
    OS_MACOS, // Apple macOS, and probably useful for iOS, iPadOS
    OS_LINUX, // GNU/Linux
    OS_WIN    // Microsoft Windows
} os_t;

extern os_t current_os;

// ─────────────────────────────────────────────────────────────
// Macros & Other Custom Keys
// ─────────────────────────────────────────────────────────────

enum custom_keycodes {
    // ─────────────────────────────────────────────────────────────
    // Terminal Command Macros
    // ─────────────────────────────────────────────────────────────
    LS_TERM = SAFE_RANGE, // `ls -lah`: long list w/ human-readable values
    CD_HOME,              // `cd ~`
    CD_PREV,              // `cd -`
    CD_GITROOT,           // `cd $(git rev-parse --show-toplevel)`
    MKDIR,                // `mkdir -p `
    TOUCH,                // `touch `
    PING,                 // `ping `

    // ─────────────────────────────────────────────────────────────
    // Symbols
    // ─────────────────────────────────────────────────────────────
    DEG,                  // Degree symbol (°)

    // ─────────────────────────────────────────────────────────────
    // Vim
    // ─────────────────────────────────────────────────────────────
    BUF_TOGGLE,           // Switches to previously active buffer

    // ─────────────────────────────────────────────────────────────
    // Programming Macros
    // ─────────────────────────────────────────────────────────────
    TERN,                 // ` ? : ` ternary operator w/ cursor placed at start
    VWS_CBR,              // Vertical whitespace curly braces `{}`

    // ─────────────────────────────────────────────────────────────
    // App/Operating System Shortcuts (Non-Macros)
    // ─────────────────────────────────────────────────────────────
    ALL,                  // Shortcut: Select All
    COPY,                 // Shortcut: Copy Selected
    PASTE,                // Shortcut: Select All
    CUT,                  // Shortcut: Cut Selected

    VDT_LEFT,             // Virtual Desktop/Workspace Left
    VDT_RIGHT,            // Virtual Desktop/Workspace Right

    ZOOM_IN,              // Browser Zoom+
    ZOOM_OUT,             // Browser Zoom-
    ZOOM_RESET,           // Browser Zoom Reset (100%)


    // ─────────────────────────────────────────────────────────────
    // DOOM Macros
    // ─────────────────────────────────────────────────────────────
    DOOM_PAUSE,           // Pause Game 

    // ─────────────────────────────────────────────────────────────
    // Miscellaneous (Non-Macros)
    // ─────────────────────────────────────────────────────────────
    TG_MOUSE,             // Toggle Mouse/previous layer
    MOUSE_FN,             // Mouse layer on tap, Function keys layer on hold
    TG_OS,                // Toggles current operating system mode
    TG_LEAD,              // Toggles Leader Keys on/off
    APP,                  // Application switching key on hold; CMD or ALT
    TG_PATH_CASE,         // Turn on path/mode/to/something casing
    LIST_LEADER_ALL_SAVED,// List Leader Favorites and Leader History
};

// Intercepts custom keycodes and runs their associated macros and miscellenous
// non-macros. This function handles all higher‑level behaviors that aren't
// simple keypresses, including programming bigrams (e.g., ", ", "; ", ": ",
// ". "), Vim navigation motions (gj/gk, buffer and tab movement, window
// resizing), viewport controls, and buffer‑level commands (write, quit,
// substitute). Returning false prevents QMK from sending the underlying
// keycode so the macro can fully replace it.
bool process_record_user(uint16_t keycode, keyrecord_t *record);

// ─────────────────────────────────────────────────────────────
// Miscellaneous
// ─────────────────────────────────────────────────────────────

// Toggle mouse layer, go back to previous layer
void toggle_mouse(void);

// Switch to mouse layer on shorter key presses, otherwise go to function keys layer
void mouse_fn(uint16_t mouse_key_timer);

// Toggle operating system mode between macOS, Linux, and Windows
void toggle_os(void);
