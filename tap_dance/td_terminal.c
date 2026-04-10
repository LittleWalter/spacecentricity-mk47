#include "td_terminal.h"
#include "tap_dance_actions.h"
#include "macros/mac_terminal.h"

// ─────────────────────────────────────────────────────────────
// Terminal Commands
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_BTOP          btop top htop
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_BTOP tap, tap+hold, and hold dance.
static td_tap_t term_btop_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_BTOP
void term_btop_finished(tap_dance_state_t *state, void *user_data) {
    term_btop_tap_state.state = cur_dance(state);
    switch (term_btop_tap_state.state) {
        case TD_SINGLE_TAP:  mon_term_macro(COM_BTOP); break; // `btop`: fancy system monitor
        case TD_DOUBLE_TAP:  mon_term_macro(COM_TOP);  break; // `top`: basic system monitor
        case TD_SINGLE_HOLD: mon_term_macro(COM_HTOP); break; // `htop`: better than `top`
        case TD_DOUBLE_SINGLE_TAP: mon_term_macro(COM_BTOP); mon_term_macro(COM_BTOP); break;
        default: break;
    }
}

// Release any keys pressed by TD_BTOP and reset the state
void term_btop_reset(tap_dance_state_t *state, void *user_data) {
    term_btop_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CAT            cat less bat
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CAT tap and hold dance.
static td_tap_t term_cat_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_CAT
void term_cat_finished(tap_dance_state_t *state, void *user_data) {
    term_cat_tap_state.state = cur_dance(state);
    switch (term_cat_tap_state.state) {
        case TD_SINGLE_TAP:  view_term_macro(COM_CAT);  break; // `cat`: plaintext print file to console
        case TD_DOUBLE_TAP:  view_term_macro(COM_LESS); break; // `less`: universal pager
        case TD_SINGLE_HOLD: view_term_macro(COM_BAT);  break; // `bat`: fancy print file to console
        case TD_DOUBLE_SINGLE_TAP: view_term_macro(COM_CAT); view_term_macro(COM_CAT); break;
        default: break;
    }
}

// Release any keys pressed by TD_CAT and reset the state
void term_cat_reset(tap_dance_state_t *state, void *user_data) {
    term_cat_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CLS              clear exit
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CLS tap and hold dance.
static td_tap_t term_cls_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_CLS
void term_cls_finished(tap_dance_state_t *state, void *user_data) {
    term_cls_tap_state.state = cur_dance(state);
    switch (term_cls_tap_state.state) {
        case TD_SINGLE_TAP:  cls_term_macro();  break; // `exit`: close terminal emulator shell
        case TD_SINGLE_HOLD: exit_term_macro(); break; // `clear`: clear screen in terminal emulator
        case TD_DOUBLE_SINGLE_TAP: cls_term_macro(); cls_term_macro(); break;
        default: break;
    }
}

// Release any keys pressed by TD_CLS and reset the state
void term_cls_reset(tap_dance_state_t *state, void *user_data) {
    term_cls_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SIGINT    SIGINT fg SIGTSTP
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SIGINT tap and hold dance.
static td_tap_t term_sigint_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_SIGINT
void term_sigint_finished(tap_dance_state_t *state, void *user_data) {
    term_sigint_tap_state.state = cur_dance(state);
    switch (term_sigint_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(C(KC_C)); break; // LCTL+c: SIGINT (stop process gracefully)
        case TD_DOUBLE_TAP:  fg_term_macro();          break; // `fg`: resume background process
        case TD_SINGLE_HOLD: register_code16(C(KC_Z)); break; // LCTL+z: SIGTSTP (suspend/pause process, put in background)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(C(KC_C)); register_code16(C(KC_C)); break;
        default: break;
    }
}

// Release any keys pressed by TD_SIGINT and reset the state
void term_sigint_reset(tap_dance_state_t *state, void *user_data) {
    switch (term_sigint_tap_state.state) {
        case TD_SINGLE_TAP:        unregister_code16(C(KC_C)); break;
        case TD_SINGLE_HOLD:       unregister_code16(C(KC_Z)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(C(KC_C)); break;
        default: break;
    }
    term_sigint_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PIPE                | ` | `
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PIPE tap and hold dance.
static td_tap_t term_pipe_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal symbol for TD_PIPE
void term_pipe_finished(tap_dance_state_t *state, void *user_data) {
    term_pipe_tap_state.state = cur_dance(state);
    switch (term_pipe_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(KC_PIPE); break; // `|`
        case TD_SINGLE_HOLD: pipe_term_macro();        break; // ` | `
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PIPE); register_code16(KC_PIPE); break;
        default: break;
    }
}

// Release any keys pressed by TD_PIPE and reset the state
void term_pipe_reset(tap_dance_state_t *state, void *user_data) {
    switch (term_pipe_tap_state.state) {
        case TD_SINGLE_TAP:        unregister_code16(KC_PIPE); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PIPE); break;
        default: break;
    }
    term_pipe_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CD             `cd ` `cd ..`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CD tap and hold dance.
static td_tap_t term_cd_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_CD
void term_cd_finished(tap_dance_state_t *state, void *user_data) {
    term_cd_tap_state.state = cur_dance(state);
    switch (term_cd_tap_state.state) {
        case TD_SINGLE_TAP:  cd_macro(COM_CD_NONE, false);  break; // `cd `
        case TD_SINGLE_HOLD: cd_macro(COM_CD_PARENT, true); break; // `cd ..`
        case TD_DOUBLE_SINGLE_TAP: cd_macro(COM_CD_NONE, false); cd_macro(COM_CD_NONE, false); break;
        default: break;
    }
}

// Release any keys pressed by TD_CD and reset the state
void term_cd_reset(tap_dance_state_t *state, void *user_data) {
    term_cd_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PATH              ./ ~/ ../
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PATH tap and hold dance.
static td_tap_t term_path_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal path shortcut for TD_PATH
void term_path_finished(tap_dance_state_t *state, void *user_data) {
    term_path_tap_state.state = cur_dance(state);
    switch (term_path_tap_state.state) {
        case TD_SINGLE_TAP:  path_macro(PATH_CURRENT); break; // `./` (current directory)
        case TD_DOUBLE_TAP:  path_macro(PATH_HOME);    break; // `~/` (home directory)
        case TD_SINGLE_HOLD: path_macro(PATH_PARENT);  break; // `../` (parent directory)
        default: break;
    }
}

// Release any keys pressed by TD_PATH and reset the state
void term_path_reset(tap_dance_state_t *state, void *user_data) {
    term_path_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SUDO       sudo ` `sudo !!`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SUDO tap and hold dance.
static td_tap_t term_sudo_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate terminal command for TD_SUDO
void term_sudo_finished(tap_dance_state_t *state, void *user_data) {
    term_sudo_tap_state.state = cur_dance(state);
    switch (term_sudo_tap_state.state) {
        case TD_SINGLE_TAP:  sudo_macro(false); break; // `sudo ` (run command w/ admin privileges)
        case TD_SINGLE_HOLD: sudo_macro(true);  break; // `sudo !!` (run command w/ admin privileges)
        default: break;
    }
}

// Release any keys pressed by TD_SUDO and reset the state
void term_sudo_reset(tap_dance_state_t *state, void *user_data) {
    term_sudo_tap_state.state = TD_NONE;
}
