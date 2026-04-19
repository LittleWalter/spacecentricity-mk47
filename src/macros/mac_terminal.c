#include "mac_terminal.h"
#include "macros.h"

// ──────────────────────────────
// Terminal Commands
// ──────────────────────────────

// Sends a given command, pass true if you want the macro to auto-run in the terminal.
// Most commands are sent here w/e to `cd` and `sudo`.
static void command_macro(const command_t command, const bool with_enter) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (command) {
        case COM_TOP:     SEND_STRING("top");       break;
        case COM_HTOP:    SEND_STRING("htop");      break;
        case COM_BTOP:    SEND_STRING("btop");      break;
        case COM_LS_LONG: SEND_STRING("ls -lah");   break;
        case COM_MKDIR:   SEND_STRING("mkdir -p "); break;
        case COM_TOUCH:   SEND_STRING("touch ");    break;
        case COM_FG:      SEND_STRING("fg");        break;
        case COM_CAT:     SEND_STRING("cat ");      break;
        case COM_BAT:     SEND_STRING("bat ");      break;
        case COM_LESS:    SEND_STRING("less ");     break;
        case COM_PING:    SEND_STRING("ping ");     break;
        case COM_CLEAR:   SEND_STRING("clear");     break;
        case COM_EXIT:    SEND_STRING("exit");      break;
        default: break;
    }

    if (with_enter) {
        tap_code(KC_ENT);
    }

    mod_state_restore(&saved);
}

// `exit` terminal emulator session command
void exit_term_macro(void) {
    command_macro(COM_EXIT, true);
}

// `clear` terminal emulator screen
void cls_term_macro(void) {
    command_macro(COM_CLEAR, true);
}

// `fg`: resume background process
void fg_term_macro(void) {
    command_macro(COM_FG, true);
}

// `ls -lah`: long list directory command with human-readable values
void ls_long_term_macro(void) {
    command_macro(COM_LS_LONG, true);
}

// `top` et al.: system monitoring tools
void mon_term_macro(const command_t mon) {
    command_macro(mon, true);
}

// File viewing tools: `cat`, `bat`, `less`
void view_term_macro(const command_t view) {
    command_macro(view, false);
}

// ` | `: pipelining w/ spacing
void pipe_term_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();
    SEND_STRING(" | ");
    mod_state_restore(&saved);
}

// `./`, `../` or `~/`: shorthand to access file in current, parent, or home directory
void path_macro(const path_t path) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (path) {
        case PATH_CURRENT: SEND_STRING(".");  break;
        case PATH_PARENT:  SEND_STRING(".."); break;
        case PATH_HOME:    SEND_STRING("~");  break;
        default: break;
    }
    tap_code(KC_SLSH);

    mod_state_restore(&saved);
}

// `cd`: outputs various change directory terminal commands
void cd_macro(const command_t path, const bool with_enter) {
    mod_state_t saved = mod_state_save_and_clear();

    SEND_STRING("cd"); // Base command
    switch (path) {
        case COM_CD_PARENT:      SEND_STRING(" ..");    break;
        case COM_CD_GRANDPARENT: SEND_STRING(" ../.."); break;
        case COM_CD_HOME:        SEND_STRING(" ~");     break;
        case COM_CD_PREV:        SEND_STRING(" -");     break;
        case COM_CD_ROOT:        SEND_STRING(" /");     break;
        case COM_CD_GITROOT:
            SEND_STRING(" $(git rev-parse --show-toplevel)"); break;
        default: tap_code(KC_SPC); break; // `cd `
    }

    if (with_enter) {
        tap_code(KC_ENT);
    }

    mod_state_restore(&saved);
}

// `sudo `or `sudo !!`: run command with admin privileges, `!!` means previous command
// TIP: Auto-entering `sudo !!` is not a great idea and potentially dangerous, don't do it!
void sudo_macro(const bool prev_command) {
    mod_state_t saved = mod_state_save_and_clear();

    SEND_STRING("sudo ");
    if (prev_command) {
        SEND_STRING("!!");
    }

    mod_state_restore(&saved);
}

// `mkdir -p ` terminal command: create new directory /w parent flag
void mkdir_macro(void) {
    command_macro(COM_MKDIR, false);
}

// `touch ` terminal command: create new empty file
void touch_macro(void) {
    command_macro(COM_TOUCH, false);
}

// `ping ` terminal command
void ping_macro(void) {
    command_macro(COM_PING, false);
}
