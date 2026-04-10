#include "td_vim.h"
#include "tap_dance_actions.h"
#include "macros/mac_vim.h"

// ─────────────────────────────────────────────────────────────
// Vim Tap Dance Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_B             B gE g, Jump←
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_B tap dance
static td_tap_t b_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_B
void b_finished(tap_dance_state_t *state, void *user_data) {
    b_tap_state.state = cur_dance(state);
    switch (b_tap_state.state) {
        case TD_SINGLE_TAP: // `B` (move 1 WORD back)
            register_code16(S(KC_B));
            break;
        case TD_DOUBLE_TAP: // `gE` (move 1 WORD back, end)
            vim_move_macro(NAV_PREV_END);
            break;
        case TD_SINGLE_HOLD: // Jump list previous
            register_code16(C(KC_O));
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`g,` (jump to previous edit)
            vim_change_list_macro(NAV_PREV);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_B)); register_code16(S(KC_B)); break;
        default: break;
    }
}

// Release any keys pressed by TD_B and reset the state
void b_reset(tap_dance_state_t *state, void *user_data) {
    switch (b_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(S(KC_B)); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_O)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_B)); break;
        default: break;
    }
    b_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_GJ                    gj <<
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_GJ tap and hold dance
static td_tap_t gj_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_GJ
void gj_finished(tap_dance_state_t *state, void *user_data) {
    gj_tap_state.state = cur_dance(state);
    switch (gj_tap_state.state) {
        case TD_SINGLE_TAP: // `gj` (move 1 row down on long line)
            vim_move_macro(NAV_DOWN);
            break;
        case TD_DOUBLE_HOLD: // `<<` Indent left, current line
            vim_indent_macro(NAV_LEFT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_GJ and reset the state
void gj_reset(tap_dance_state_t *state, void *user_data) {
    gj_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_GK                    gk >>
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_GK tap and hold dance
static td_tap_t gk_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_GK
void gk_finished(tap_dance_state_t *state, void *user_data) {
    gk_tap_state.state = cur_dance(state);
    switch (gk_tap_state.state) {
        case TD_SINGLE_TAP: // `gk` (move 1 row up on long line)
            vim_move_macro(NAV_UP);
            break;
        case TD_DOUBLE_HOLD: // `>>` Indent right, current line
            vim_indent_macro(NAV_RIGHT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_GK and reset the state
void gk_reset(tap_dance_state_t *state, void *user_data) {
    gk_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_W              W E g; Jump→
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_W tap and hold dance.
static td_tap_t w_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_W
void w_finished(tap_dance_state_t *state, void *user_data) {
    w_tap_state.state = cur_dance(state);
    switch (w_tap_state.state) {
        case TD_SINGLE_TAP:  register_code16(S(KC_W)); break; // `W` (move 1 column right)
        case TD_DOUBLE_TAP:  register_code16(S(KC_E)); break; // `E` (move 1 WORD right, end)
        case TD_SINGLE_HOLD: register_code16(C(KC_I)); break; // Jump list next
        case TD_DOUBLE_HOLD: vim_change_list_macro(NAV_NEXT); break; // `Esc`+`g;`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_W)); register_code16(S(KC_W)); break;
        default: break;
    }
}

// Release any keys pressed by TD_W and reset the state
void w_reset(tap_dance_state_t *state, void *user_data) {
    switch (w_tap_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(S(KC_W)); break;
        case TD_DOUBLE_TAP:  unregister_code16(S(KC_E)); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_I)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(S(KC_W)); break;
        default: break;
    }
    w_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_HALF_PGDN           ½PD BOT
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_HALF_PGDN tap and hold dance.
static td_tap_t half_pgdn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_HALF_PGDN
void half_pgdn_finished(tap_dance_state_t *state, void *user_data) {
    half_pgdn_tap_state.state = cur_dance(state);
    switch (half_pgdn_tap_state.state) {
        case TD_SINGLE_TAP: // `LCTL+d` (Jump down 1/2 page)
            register_code16(C(KC_D));
            break;
        case TD_SINGLE_HOLD: // Jump to bottom of buffer
            vim_move_macro(NAV_BOT);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(C(KC_D)); register_code16(C(KC_D)); break;
        default: break;
    }
}

// Release any keys pressed by TD_HALF_PGDN and reset the state
void half_pgdn_reset(tap_dance_state_t *state, void *user_data) {
    switch (half_pgdn_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(C(KC_D)); break;
        default: break;
    }
    half_pgdn_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_HALF_PGUP           ½PU TOP
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_HALF_PGUP tap and hold dance.
static td_tap_t half_pgup_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_HALF_PGUP
void half_pgup_finished(tap_dance_state_t *state, void *user_data) {
    half_pgup_tap_state.state = cur_dance(state);
    switch (half_pgup_tap_state.state) {
        case TD_SINGLE_TAP: // `LCTL+u` (Jump up 1/2 page)
            register_code16(C(KC_U));
            break;
        case TD_SINGLE_HOLD: // Jump list previous
            vim_move_macro(NAV_TOP);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(C(KC_U)); register_code16(C(KC_U)); break;
        default: break;
    }
}

// Release any keys pressed by TD_HALF_PGUP and reset the state
void half_pgup_reset(tap_dance_state_t *state, void *user_data) {
    switch (half_pgup_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(C(KC_U)); break;
        default: break;
    }
    half_pgup_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_HIGH                   zt H
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_HIGH tap and hold dance.
static td_tap_t high_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_HIGH
void high_finished(tap_dance_state_t *state, void *user_data) {
    high_tap_state.state = cur_dance(state);
    switch (high_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`zt` (adjust viewport to top of curr line)
            vim_viewport_alignment_macro(NAV_TOP);
            break;
        case TD_SINGLE_HOLD: // `H` (cursor to top of viewport)
            register_code16(S(KC_H));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_viewport_alignment_macro(NAV_TOP);
            vim_viewport_alignment_macro(NAV_TOP);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_HIGH and reset the state
void high_reset(tap_dance_state_t *state, void *user_data) {
    switch (high_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_H)); break;
        default: break;
    }
    high_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_MID                    zz M
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_MID tap and hold dance.
static td_tap_t mid_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_MID
void mid_finished(tap_dance_state_t *state, void *user_data) {
    mid_tap_state.state = cur_dance(state);
    switch (mid_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`zz` (adjust viewport to middle of curr line)
            vim_viewport_alignment_macro(NAV_MID);
            break;
        case TD_SINGLE_HOLD: // `M` (cursor to middle of viewport)
            register_code16(S(KC_M));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_viewport_alignment_macro(NAV_MID);
            vim_viewport_alignment_macro(NAV_MID);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_MID and reset the state
void mid_reset(tap_dance_state_t *state, void *user_data) {
    switch (mid_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_M)); break;
        default: break;
    }
    mid_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_LOW                    zb L
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_LOW tap and hold dance.
static td_tap_t low_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_LOW
void low_finished(tap_dance_state_t *state, void *user_data) {
    low_tap_state.state = cur_dance(state);
    switch (low_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`zb` (adjust viewport to bottom of curr line)
            vim_viewport_alignment_macro(NAV_BOT);
            break;
        case TD_SINGLE_HOLD: // `L` (cursor to bottom of viewport)
            register_code16(S(KC_L));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_viewport_alignment_macro(NAV_BOT);
            vim_viewport_alignment_macro(NAV_BOT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_LOW and reset the state
void low_reset(tap_dance_state_t *state, void *user_data) {
    switch (low_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_L)); break;
        default: break;
    }
    low_tap_state.state = TD_NONE;
}

// ────────────────────────────────
// TD_SUB `:%s///g` `bufdo :%s///g`
// ────────────────────────────────

// Instance of 'td_tap_t' for the TD_SUB tap and hold dance.
static td_tap_t sub_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command-line action for TD_SUB
void sub_finished(tap_dance_state_t *state, void *user_data) {
    sub_tap_state.state = cur_dance(state);
    switch (sub_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`:%s///g` (substitute in current buffer)
            vim_commandline_macro(VC_SUB_GLOBAL);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bufdo %s///g | update` (substitute in all open buffers)
            vim_commandline_macro(VC_SUB_BUF_GLOBAL);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_commandline_macro(VC_SUB_GLOBAL);
            vim_commandline_macro(VC_SUB_GLOBAL);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_SUB and reset the state
void sub_reset(tap_dance_state_t *state, void *user_data) {
    sub_tap_state.state = TD_NONE;
}

// ────────────────────────────────
// TD_FOLD           `za` `zM` `zR`
// ────────────────────────────────

// Instance of 'td_tap_t' for the TD_FOLD tap and hold dance.
static td_tap_t fold_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_FOLD
void fold_finished(tap_dance_state_t *state, void *user_data) {
    fold_tap_state.state = cur_dance(state);
    switch (fold_tap_state.state) {
        case TD_SINGLE_TAP:  vim_fold_macro(FOLD_TOGGLE);    break; // `za` toggle fold under cursor
        case TD_DOUBLE_HOLD: vim_fold_macro(FOLD_CLOSE_ALL); break; // `zM` close all folds in buffer
        case TD_SINGLE_HOLD: vim_fold_macro(FOLD_OPEN_ALL);  break; // `zR` open all folds in buffer
        case TD_DOUBLE_SINGLE_TAP:
            vim_fold_macro(FOLD_TOGGLE);
            vim_fold_macro(FOLD_TOGGLE);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_FOLD and reset the state
void fold_reset(tap_dance_state_t *state, void *user_data) {
    fold_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_WRITE                :w :wa
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_WRITE tap and hold dance.
static td_tap_t write_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command-line action for TD_WRITE
void write_finished(tap_dance_state_t *state, void *user_data) {
    write_tap_state.state = cur_dance(state);
    switch (write_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`:w`+Ent (save current buffer)
            vim_commandline_macro(VC_WRITE);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:wa` (save all buffers)
            vim_commandline_macro(VC_WRITE_ALL);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_commandline_macro(VC_WRITE);
            vim_commandline_macro(VC_WRITE);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_WRITE and reset the state
void write_reset(tap_dance_state_t *state, void *user_data) {
    write_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_QUIT               :qa :qa!
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_QUIT tap and hold dance.
static td_tap_t quit_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command-line action for TD_QUIT
void quit_finished(tap_dance_state_t *state, void *user_data) {
    quit_tap_state.state = cur_dance(state);
    switch (quit_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`:qa`+Ent (safely quit Vim)
            vim_commandline_macro(VC_QUIT_ALL);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:qa!` (Quit Vim w/o saving)
            vim_commandline_macro(VC_QUIT_ALL_FORCE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_commandline_macro(VC_QUIT_ALL);
            vim_commandline_macro(VC_QUIT_ALL);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_QUIT and reset the state
void quit_reset(tap_dance_state_t *state, void *user_data) {
    low_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_WINL  W← W_WIDTH- TAB⇤ BUF⇤
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_WINL tap and hold dance.
static td_tap_t winl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_WINL
void winl_finished(tap_dance_state_t *state, void *user_data) {
    winl_tap_state.state = cur_dance(state);
    switch (winl_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`h` (Go to left win split)
            vim_window_macro(NAV_LEFT);
            break;
        case TD_DOUBLE_TAP: // `LCTL+w`+`<` (Decrease win split width)
            vim_window_size_macro(SZ_WIDTH_DEC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bf`+`Ent` (Go to first buffer)
            vim_buffer_nav_macro(NAV_FIRST);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`:tabfirst`+`Ent` (Go to first tab)
            vim_tab_nav_macro(NAV_FIRST);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_window_macro(NAV_LEFT);
            vim_window_macro(NAV_LEFT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_WINL and reset the state
void winl_reset(tap_dance_state_t *state, void *user_data) {
    winl_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_WINU W↓ W_HEIGHT- TAB← BUF←
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_WIND tap and hold dance
static td_tap_t wind_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send he appropriate macro for TD_WINU
void wind_finished(tap_dance_state_t *state, void *user_data) {
    wind_tap_state.state = cur_dance(state);
    switch (wind_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`j` (Go to win split below)
            vim_window_macro(NAV_DOWN);
            break;
        case TD_DOUBLE_TAP: // `LCTL+w`+`-` (Decrease win split height)
            vim_window_size_macro(SZ_HEIGHT_DEC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bp`+`Ent` (Go to previous buffer)
            vim_buffer_nav_macro(NAV_PREV);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`gT` (Go to previous tab)
            vim_tab_nav_macro(NAV_PREV);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_window_macro(NAV_DOWN);
            vim_window_macro(NAV_DOWN);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_WINU and reset the state
void wind_reset(tap_dance_state_t *state, void *user_data) {
    wind_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_WINU W↑ W_HEIGHT+ TAB→ BUF→
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_WINU tap and hold dance
static td_tap_t winu_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_WINU
void winu_finished(tap_dance_state_t *state, void *user_data) {
    winu_tap_state.state = cur_dance(state);
    switch (winu_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`k` (Go to win split above)
            vim_window_macro(NAV_UP);
            break;
        case TD_DOUBLE_TAP: // `LCTL+w`+`+` (Increase win split height)
            vim_window_size_macro(SZ_HEIGHT_INC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bn`+`Ent` (Go to next buffer)
            vim_buffer_nav_macro(NAV_NEXT);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`gt` (Go to next tab)
            vim_tab_nav_macro(NAV_NEXT);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_window_macro(NAV_UP);
            vim_window_macro(NAV_UP);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_WINU and reset the state
void winu_reset(tap_dance_state_t *state, void *user_data) {
    winu_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_WINR  W→ W_WIDTH+ TAB⇥ BUF⇥
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_WINL tap and hold dance
static td_tap_t winr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate Vim command for TD_WINR
void winr_finished(tap_dance_state_t *state, void *user_data) {
    winr_tap_state.state = cur_dance(state);
    switch (winr_tap_state.state) {
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`l` (Go to right win split)
            vim_window_macro(NAV_RIGHT);
            break;
        case TD_DOUBLE_TAP: // `LCTL+w`+`>` (Increase win split width)
            vim_window_size_macro(SZ_WIDTH_INC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bl`+`Enter` (Go to last buffer)
            vim_buffer_nav_macro(NAV_LAST);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`:tablast`+`Ent` (Go to next tab)
            vim_tab_nav_macro(NAV_LAST);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            vim_window_macro(NAV_RIGHT);
            vim_window_macro(NAV_RIGHT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_WINR and reset the state
void winr_reset(tap_dance_state_t *state, void *user_data) {
    winr_tap_state.state = TD_NONE;
}
