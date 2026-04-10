#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Terminal Macro Function Parameter Types
// ─────────────────────────────────────────────────────────────

typedef enum {
    COM_TOP = 1,        // `top`
    COM_BTOP,           // `btop`
    COM_HTOP,           // `htop`
    COM_CAT,            // `cat `
    COM_BAT,            // `bat `
    COM_LESS,           // `less `
    COM_CD_NONE,        // `cd `
    COM_CD_PARENT,      // `cd ..`
    COM_CD_GRANDPARENT, // `cd ..`
    COM_CD_PREV,        // `cd -`
    COM_CD_HOME,        // `cd ~`
    COM_CD_ROOT,        // `cd /`
    COM_CD_GITROOT,     // `cd $(git rev-parse --show-toplevel)`
    COM_MKDIR,          // `mkdir -p `
    COM_TOUCH,          // `touch `
    COM_FG,             // `fg`
    COM_LS_LONG,        // `ls -lah`
    COM_CLEAR,          // `clear`
    COM_PING,           // `ping `
    COM_EXIT,           // `exit`
    COM_SUDO            // `sudo `
} command_t;

typedef enum {
    PATH_CURRENT, // `./`
    PATH_PARENT,  // `../`
    PATH_HOME     // `~/`
} path_t;

// ─────────────────────────────────────────────────────────────
// Terminal Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// `exit` terminal emulator session command
void exit_term_macro(void);

// `clear` terminal emulator screen
void cls_term_macro(void);

// `fg`: resume background process
void fg_term_macro(void);

// `ls -lah`: long list directory command with human-readable values
void ls_long_term_macro(void);

// `top` et al.: system monitoring tools
void mon_term_macro(const command_t mon);

// File viewing tools: `cat`, `bat`, `less`
void view_term_macro(const command_t view);

// ` | `: pipelining w/ spacing
void pipe_term_macro(void);

// `./`, `../` or `~/`: shorthand to access file in current, parent, or home directory
void path_macro(const path_t path);

// `cd`: outputs various change directory terminal commands
void cd_macro(const command_t path, const bool with_bool);

// `sudo `or `sudo !!`: run command with admin privileges, `!!` means previous command
void sudo_macro(const bool prev_command);

// `mkdir -p ` terminal command: create new directory /w parent flag
void mkdir_macro(void);

// `touch ` terminal command: create new empty file
void touch_macro(void);

// `ping ` terminal command
void ping_macro(void);
