#pragma once

#include QMK_KEYBOARD_H

#define VIM_MODE_DELAY 250  // ms to delay macro after hitting (`Esc`)
#define VIM_CMD_DELAY  300  // ms to delay command-line mode (`:`)

// ─────────────────────────────────────────────────────────────
// Vim Macro Function Parameter Types
// ─────────────────────────────────────────────────────────────

// Vim motion, buffer, tab, and window split navigational directions
typedef enum  {
    NAV_LEFT,     // Motion/window split left, etc.
    NAV_DOWN,     // Motion/window split down/line, etc.
    NAV_RIGHT,    // Motion/window split right, etc.
    NAV_UP,       // Motion/window split up/line, etc.
    NAV_FIRST,    // First buffer/tab, line, etc.
    NAV_PREV,     // Previous buffer/tab
    NAV_NEXT,     // Next buffer/tab/word/etc.
    NAV_LAST,     // Last buffer/tab, line, etc.
    NAV_TOP,      // `zt`: viewport align top, `gg`: jump to start of buffer
    NAV_MID,      // `zz`: viewport align middle
    NAV_BOT,      // `zb`: viewport align bottom, `G`: jump to bottom of buffer
    NAV_START,    // Synonym for beginning or top
    NAV_END,      // Can be synonym for bottom
    NAV_PREV_END, // End of previous word/WORD
    NAV_NEXT_END  // End of next word/WORD
} nav_action_t;

// Vim window split size changes
typedef enum {
    SZ_WIDTH_INC,  // Increase width
    SZ_WIDTH_DEC,  // Decrease width
    SZ_HEIGHT_INC, // Increase height
    SZ_HEIGHT_DEC  // Decrease height
} size_change_t;

// Various Vim command-line actions
typedef enum {
    VC_WRITE,          // `:w` (write current buffer)
    VC_WRITE_ALL,      // `:wa` (write all buffers)
    VC_QUIT_ALL,       // `:qa` (quit all buffers)
    VC_QUIT_ALL_FORCE, // `:qa!` (quit all buffers, no save)
    VC_SUB_GLOBAL,     // `:%s///g` (substitute in current buffer)
    VC_SUB_BUF_GLOBAL  // `:bufdo %s///g | update` (sub in open buffers)
} vim_commandline_t;

// Vim fold actions
typedef enum {
    FOLD_TOGGLE,    // `za`
    FOLD_CLOSE_ALL, // `zM`
    FOLD_OPEN_ALL   // `zR`
} fold_t;

// ─────────────────────────────────────────────────────────────
// Vim Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Vim macro: basic cursor movements such as `gj`, `gk`, `gE`, `gg, `G`, etc.
// W/e to `gg` and `G`, none of these macros are prefixed w/ `Esc` to allow compound commands like
// `3gE`, etc.
void vim_move_macro(const nav_action_t direction);

// Vim macros: `zt`, `zz`, `zb` w/ prefixed `Esc`
// Viewport alignment top, middle, bottom
void vim_viewport_alignment_macro(const nav_action_t viewport);

// Vim buffer navigation: first (`:bf`), previous (`:bp`), next(`:bn`), last (`:bl`) w/
// prefixed Esc
void vim_buffer_nav_macro(const nav_action_t nav);

// Vim window split navigation
void vim_window_macro(const nav_action_t window);

// Vim window split resizing
void vim_window_size_macro(const size_change_t size);

// Vim tab navigation: first (`:tabfirst`), previous (`gT`), next (`gt`), last (`:tablast`)
void vim_tab_nav_macro(const nav_action_t nav);

// Vim change list navigation
void vim_change_list_macro(const nav_action_t nav);

// Vim indent text, current line
void vim_indent_macro(const nav_action_t direction);

// Various general Vim command-line actions such as `:w`, `:qa`, etc.
void vim_commandline_macro(const vim_commandline_t command);

// Fold actions: toggle under cursor `za`, close all folds in buffer `zM`, open all folds in
// buffer `zR`
void vim_fold_macro(const fold_t fold);

// Switches to previously active buffer (CTRL-6)
void vim_buffer_toggle_macro(void);
