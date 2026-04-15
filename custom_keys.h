#pragma once

#include QMK_KEYBOARD_H

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
    // Miscellaneous (Non-Macros)
    // ─────────────────────────────────────────────────────────────
    TG_MOUSE,             // Toggle Mouse/previous layer
    MOUSE_FN,             // Mouse layer on tap, Function keys layer on hold
    TG_OS,                // Toggles current operating system mode
    APP                   // Application switching key on hold; CMD or ALT
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
// App Shortcuts
// ─────────────────────────────────────────────────────────────

// App shortcut: select all; defaults to CMD+A for macOS, otherwise
// uses LCTL+A for Microsoft Windows and Linux
void select_all(void);

// App shortcut: copy selected; defaults to CMD+C for macOS, otherwise
// uses LCTL+C for Microsoft Windows and Linux
void copy(void);

// App shortcut: cut selected; defaults to CMD+X for macOS, otherwise
// uses LCTL+X for Microsoft Windows and Linux
void cut(void);

// App shortcut: paste from clipboard; defaults to CMD+V for macOS, otherwise
// uses LCTL+V for Microsoft Windows and Linux
void paste(void);

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+LEFT for macOS, otherwise uses LCTL+ALT+LEFT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+LEFT for Microsoft Windows.
void vdt_left(void);

// Operating system shortcut: change to left virtual desktop/workspace; defaults
// to LCTL+RIGHT for macOS, otherwise uses LCTL+ALT+RIGHT for most Linux desktop
// environments w/e to Gnome, or WIN+LCTL+RIGHT for Microsoft Windows.
void vdt_right(void);

// Browser shortcut: zoom in; defaults to CMD+SFT+= for macOS, otherwise
// uses LCTL+SFT+= for Microsoft Windows and Linux
void zoom_in(void);

// Browser shortcut: zoom out; defaults to CMD+- for macOS, otherwise
// uses LCTL+- for Microsoft Windows and Linux
void zoom_out(void);

// Browser shortcut: zoom reset (100%); defaults to CMD+0 for macOS, otherwise
// uses LCTL+0 for Microsoft Windows and Linux
void zoom_reset(void);

// Triggers operating system application switcher key: CMD for macOS or ALT for Linux and Windows.
// The passed Boolean means that the modifier key is currently held by the user.
void app_switch(const bool is_active);

// ─────────────────────────────────────────────────────────────
// Miscellaneous
// ─────────────────────────────────────────────────────────────

// Toggle mouse layer, go back to previous layer
void toggle_mouse(void);

// Switch to mouse layer on shorter key presses, otherwise go to function keys layer
void mouse_fn(uint16_t mouse_key_timer);

// Toggle operating system mode between macOS, Linux, and Windows
void toggle_os(void);
