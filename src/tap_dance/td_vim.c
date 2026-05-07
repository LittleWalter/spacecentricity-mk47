#include "td_vim.h"
#include "tap_dance_actions.h"
#include "src/features/case_mode.h"
#include "src/macros/mac_vim.h"

// ─────────────────────────────────────────────────────────────
// Vim Tap Dance Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_B             B gE g, Jump←
// ──────────────────────────────

// Create static `b_tap_dance` for TD_B
TD_DEF(b);

// Send the appropriate Vim command for TD_B
void b_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(b);
    switch (TD_STATE(b)) {
        case TD_DOUBLE_TAP: // `gE` (move 1 WORD back, end)
            vim_move_macro(NAV_PREV_END);
            break;
        case TD_SINGLE_HOLD: // Jump list previous
            register_code16(C(KC_O));
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`g,` (jump to previous edit)
            vim_change_list_macro(NAV_PREV);
            break;
        case TD_TRIPLE_TAP:        tap_code16(S(KC_B));          // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_B));          // fallthru
        case TD_SINGLE_TAP:        register_and_update(S(KC_B)); // `B` (move 1 WORD back)
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_B and reset the state
void b_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(b)) {
        case TD_SINGLE_HOLD: unregister_code16(C(KC_O)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(S(KC_B)); break;
        default: break;
    }
    TD_RESET(b);
}

// ──────────────────────────────
// TD_GJ                    gj <<
// ──────────────────────────────

// Create static `gj_tap_dance` for TD_GJ
TD_DEF(gj);

// Send the appropriate Vim command for TD_GJ
void gj_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(gj);
    switch (TD_STATE(gj)) {
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
    TD_RESET(gj);
}

// ──────────────────────────────
// TD_GK                    gk >>
// ──────────────────────────────

// Create static `gk_tap_dance` for TD_GK
TD_DEF(gk);

// Send the appropriate Vim command for TD_GK
void gk_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(gk);
    switch (TD_STATE(gk)) {
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
    TD_RESET(gk);
}

// ──────────────────────────────
// TD_W              W E g; Jump→
// ──────────────────────────────

// Create static `w_tap_dance` for TD_W
TD_DEF(w);

// Send the appropriate Vim command for TD_W
void w_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(w);
    switch (TD_STATE(w)) {
        case TD_DOUBLE_TAP:  register_and_update(S(KC_E));   break; // `E` (move 1 WORD right, end)
        case TD_SINGLE_HOLD: register_and_update(C(KC_I));   break; // Jump list next
        case TD_DOUBLE_HOLD: vim_change_list_macro(NAV_NEXT); break; // `Esc`+`g;`
        case TD_TRIPLE_TAP:        tap_code16(S(KC_W));                  // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(S(KC_W));                  // fallthru
        case TD_SINGLE_TAP:        register_and_update(S(KC_W)); break; // `W` (move 1 column right)
        default: break;
    }
}

// Release any keys pressed by TD_W and reset the state
void w_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(w)) {
        case TD_DOUBLE_TAP:  unregister_code16(S(KC_E)); break;
        case TD_SINGLE_HOLD: unregister_code16(C(KC_I)); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(S(KC_W)); break;
        default: break;
    }
    TD_RESET(w);
}

// ──────────────────────────────
// TD_HALF_PGDN           ½PD BOT
// ──────────────────────────────

// Create static `half_pgdn_tap_dance` for TD_HALF_PGDN
TD_DEF(half_pgdn);

// Send the appropriate Vim command for TD_HALF_PGDN
void half_pgdn_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(half_pgdn);
    switch (TD_STATE(half_pgdn)) {
        case TD_SINGLE_HOLD: // jump to bottom of buffer
            vim_move_macro(NAV_BOT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(C(KC_D));                 // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(C(KC_D));                 // fallthru
        case TD_SINGLE_TAP:        register_and_update(C(KC_D)); break; // `lctl+d` (jump down 1/2 page)
        default: break;
    }
}

// Release any keys pressed by TD_HALF_PGDN and reset the state
void half_pgdn_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(half_pgdn)) {
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP: unregister_code16(C(KC_D)); break;
        default: break;
    }
    TD_RESET(half_pgdn);
}

// ──────────────────────────────
// TD_HALF_PGUP           ½PU TOP
// ──────────────────────────────

// Create static `half_pgup_tap_dance` for TD_HALF_PGUP
TD_DEF(half_pgup);

// Send the appropriate macro for TD_HALF_PGUP
void half_pgup_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(half_pgup);
    switch (TD_STATE(half_pgup)) {
        case TD_SINGLE_HOLD: // Jump list previous
            vim_move_macro(NAV_TOP);
            break;
        case TD_TRIPLE_TAP:        tap_code16(C(KC_U));                 // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(C(KC_U));                 // fallthru
        case TD_SINGLE_TAP:        register_and_update(C(KC_U)); break; // `LCTL+u` (Jump up 1/2 page)
        default: break;
    }
}

// Release any keys pressed by TD_HALF_PGUP and reset the state
void half_pgup_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(half_pgup)) {
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP: unregister_code16(C(KC_U)); break;
        default: break;
    }
    TD_RESET(half_pgup);
}

// ──────────────────────────────
// TD_HIGH                   zt H
// ──────────────────────────────

// Create static `high_tap_dance` for TD_HIGH
TD_DEF(high);

// Send the appropriate Vim command for TD_HIGH
void high_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(high);
    switch (TD_STATE(high)) {
        case TD_SINGLE_HOLD: // `H` (cursor to top of viewport)
            register_and_update(S(KC_H));
            break;
        case TD_TRIPLE_TAP:        vim_viewport_alignment_macro(NAV_TOP); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_viewport_alignment_macro(NAV_TOP); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`zt` (adjust viewport to top of curr line)
                                   vim_viewport_alignment_macro(NAV_TOP);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_HIGH and reset the state
void high_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(high)) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_H)); break;
        default: break;
    }
    TD_RESET(high);
}

// ──────────────────────────────
// TD_MID                    zz M
// ──────────────────────────────

// Create static `mid_tap_dance` for TD_MID
TD_DEF(mid);

// Send the appropriate Vim command for TD_MID
void mid_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(mid);
    switch (TD_STATE(mid)) {
        case TD_SINGLE_HOLD: // `M` (cursor to middle of viewport)
            register_and_update(S(KC_M));
            break;
        case TD_TRIPLE_TAP:        vim_viewport_alignment_macro(NAV_MID); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_viewport_alignment_macro(NAV_MID); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`zz` (adjust viewport to middle of curr line)
                                   vim_viewport_alignment_macro(NAV_MID);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_MID and reset the state
void mid_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(mid)) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_M)); break;
        default: break;
    }
    TD_RESET(mid);
}

// ──────────────────────────────
// TD_LOW                    zb L
// ──────────────────────────────

// Create static `low_tap_dance` for TD_LOW
TD_DEF(low);

// Send the appropriate Vim command for TD_LOW
void low_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(low);
    switch (TD_STATE(low)) {
        case TD_SINGLE_HOLD: // `l` (cursor to bottom of viewport)
            register_and_update(S(KC_L));
            break;
        case TD_TRIPLE_TAP:        vim_viewport_alignment_macro(NAV_BOT); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_viewport_alignment_macro(NAV_BOT); // fallthru
        case TD_SINGLE_TAP: // `esc`+`zb` (adjust viewport to bottom of curr line)
                                   vim_viewport_alignment_macro(NAV_BOT);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_LOW and reset the state
void low_reset(tap_dance_state_t *state, void *user_data) {
    switch (TD_STATE(low)) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_L)); break;
        default: break;
    }
    TD_RESET(low);
}

// ────────────────────────────────
// TD_SUB `:%s///g` `bufdo :%s///g`
// ────────────────────────────────

// Create static `sub_tap_dance` for TD_SUB
TD_DEF(sub);

// Send the appropriate Vim command-line action for TD_SUB
void sub_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(sub);
    switch (TD_STATE(sub)) {
        case TD_SINGLE_HOLD: // `Esc`+`:bufdo %s///g | update` (substitute in all open buffers)
            vim_commandline_macro(VC_SUB_BUF_GLOBAL);
            break;
        case TD_TRIPLE_TAP:        vim_commandline_macro(VC_SUB_GLOBAL); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_commandline_macro(VC_SUB_GLOBAL); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`:%s///g` (substitute in current buffer)
                                   vim_commandline_macro(VC_SUB_GLOBAL);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_SUB and reset the state
void sub_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(sub);
}

// ────────────────────────────────
// TD_VIM_DEL   `db` `dB` `d^` `d$`
// ────────────────────────────────

// Create static `vim_del_tap_dance` for TD_VIM_DEL
TD_DEF(vim_del);

// Send the appropriate Vim command for TD_VIM_DEL
void vim_del_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(vim_del);
    switch (TD_STATE(vim_del)) {
        case TD_DOUBLE_TAP:  vim_delete_macro(DEL_PREV_BIG_WORD); break; // `dB` delete previous WORD
        case TD_DOUBLE_HOLD: vim_delete_macro(DEL_BOL);           break; // `d^` delete BOL
        case TD_SINGLE_HOLD: vim_delete_macro(DEL_EOL);           break; // `d$` delete EOL
        case TD_TRIPLE_TAP:        vim_delete_macro(DEL_PREV_WORD);            // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_delete_macro(DEL_PREV_WORD);            // fallthru
        case TD_SINGLE_TAP:        vim_delete_macro(DEL_PREV_WORD);     break; // `db` delete previous word
        default: break;
    }
}

// Release any keys pressed by TD_FOLD and reset the state
void vim_del_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(vim_del);
}

// ────────────────────────────────
// TD_FOLD           `za` `zM` `zR`
// ────────────────────────────────

// Create static `fold_tap_dance` for TD_FOLD
TD_DEF(fold);

// Send the appropriate Vim command for TD_FOLD
void fold_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(fold);
    switch (TD_STATE(fold)) {
        case TD_DOUBLE_HOLD: vim_fold_macro(FOLD_CLOSE_ALL); break; // `zM` close all folds in buffer
        case TD_SINGLE_HOLD: vim_fold_macro(FOLD_OPEN_ALL);  break; // `zR` open all folds in buffer
        case TD_TRIPLE_TAP:        vim_fold_macro(FOLD_TOGGLE);           // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_fold_macro(FOLD_TOGGLE);           // fallthru
        case TD_SINGLE_TAP:        vim_fold_macro(FOLD_TOGGLE);    break; // `za` toggle fold under cursor
        default: break;
    }
}

// Release any keys pressed by TD_FOLD and reset the state
void fold_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(fold);
}

// ──────────────────────────────
// TD_WRITE                :w :wa
// ──────────────────────────────

// Create static `write_tap_dance` for TD_WRITE
TD_DEF(write);

// Send the appropriate Vim command-line action for TD_WRITE
void write_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(write);
    switch (TD_STATE(write)) {
        case TD_SINGLE_HOLD: // `esc`+`:wa` (save all buffers)
            vim_commandline_macro(VC_WRITE_ALL);
            break;
        case TD_TRIPLE_TAP:        vim_commandline_macro(VC_WRITE); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_commandline_macro(VC_WRITE); // fallthru
        case TD_SINGLE_TAP: // `esc`+`:w`+ent (save current buffer)
                                   vim_commandline_macro(VC_WRITE);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_WRITE and reset the state
void write_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(write);
}

// ──────────────────────────────
// TD_QUIT               :qa :qa!
// ──────────────────────────────

// Create static `quit_tap_dance` for TD_QUIT
TD_DEF(quit);

// Send the appropriate Vim command-line action for TD_QUIT
void quit_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(quit);
    switch (TD_STATE(quit)) {
        case TD_SINGLE_HOLD: // `Esc`+`:qa!` (Quit Vim w/o saving)
            vim_commandline_macro(VC_QUIT_ALL_FORCE);
            break;
        case TD_TRIPLE_TAP:        vim_commandline_macro(VC_QUIT_ALL); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_commandline_macro(VC_QUIT_ALL); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`:qa`+Ent (safely quit Vim)
                                   vim_commandline_macro(VC_QUIT_ALL);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_QUIT and reset the state
void quit_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(quit);
}

// ──────────────────────────────
// TD_WINL  W← W_WIDTH- TAB⇤ BUF⇤
// ──────────────────────────────

// Create static `winl_tap_dance` for TD_WINL
TD_DEF(winl);

// Send the appropriate Vim command for TD_WINL
void winl_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(winl);
    switch (TD_STATE(winl)) {
        case TD_DOUBLE_TAP: // `LCTL+w`+`<` (Decrease win split width)
            vim_window_size_macro(SZ_WIDTH_DEC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bf`+`Ent` (Go to first buffer)
            vim_buffer_nav_macro(NAV_FIRST);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`:tabfirst`+`Ent` (Go to first tab)
            vim_tab_nav_macro(NAV_FIRST);
            break;
        case TD_TRIPLE_TAP:        vim_window_macro(NAV_LEFT); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_window_macro(NAV_LEFT); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`h` (Go to left win split)
                                   vim_window_macro(NAV_LEFT);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_WINL and reset the state
void winl_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(winl);
}

// ──────────────────────────────
// TD_WIND W↓ W_HEIGHT- TAB← BUF←
// ──────────────────────────────

// Create static `wind_tap_dance` for TD_WIND
TD_DEF(wind);

// Send he appropriate macro for TD_WINU
void wind_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(wind);
    switch (TD_STATE(wind)) {
        case TD_DOUBLE_TAP: // `LCTL+w`+`-` (Decrease win split height)
            vim_window_size_macro(SZ_HEIGHT_DEC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bp`+`Ent` (Go to previous buffer)
            vim_buffer_nav_macro(NAV_PREV);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`gT` (Go to previous tab)
            vim_tab_nav_macro(NAV_PREV);
            break;
        case TD_TRIPLE_TAP:        vim_window_macro(NAV_DOWN); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_window_macro(NAV_DOWN); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`j` (Go to win split below)
                                   vim_window_macro(NAV_DOWN);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_WINU and reset the state
void wind_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(wind);
}

// ──────────────────────────────
// TD_WINU W↑ W_HEIGHT+ TAB→ BUF→
// ──────────────────────────────

// Create static `winu_tap_dance` for TD_WINU
TD_DEF(winu);

// Send the appropriate macro for TD_WINU
void winu_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(winu);
    switch (TD_STATE(winu)) {
        case TD_DOUBLE_TAP: // `LCTL+w`+`+` (Increase win split height)
            vim_window_size_macro(SZ_HEIGHT_INC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bn`+`Ent` (Go to next buffer)
            vim_buffer_nav_macro(NAV_NEXT);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`gt` (Go to next tab)
            vim_tab_nav_macro(NAV_NEXT);
            break;
        case TD_TRIPLE_TAP:        vim_window_macro(NAV_UP); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_window_macro(NAV_UP); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`k` (Go to win split above)
                                   vim_window_macro(NAV_UP);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_WINU and reset the state
void winu_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(winu);
}

// ──────────────────────────────
// TD_WINR  W→ W_WIDTH+ TAB⇥ BUF⇥
// ──────────────────────────────

// Create static `winr_tap_dance` for TD_WINR
TD_DEF(winr);

// Send the appropriate Vim command for TD_WINR
void winr_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(winr);
    switch (TD_STATE(winr)) {
        case TD_DOUBLE_TAP: // `LCTL+w`+`>` (Increase win split width)
            vim_window_size_macro(SZ_WIDTH_INC);
            break;
        case TD_SINGLE_HOLD: // `Esc`+`:bl`+`Enter` (Go to last buffer)
            vim_buffer_nav_macro(NAV_LAST);
            break;
        case TD_DOUBLE_HOLD: // `Esc`+`:tablast`+`Ent` (Go to next tab)
            vim_tab_nav_macro(NAV_LAST);
            break;
        case TD_TRIPLE_TAP:        vim_window_macro(NAV_RIGHT); // fallthru
        case TD_DOUBLE_SINGLE_TAP: vim_window_macro(NAV_RIGHT); // fallthru
        case TD_SINGLE_TAP: // `Esc`+`LCTL+w`+`l` (Go to right win split)
                                   vim_window_macro(NAV_RIGHT);
                                   break;
        default: break;
    }
}

// Release any keys pressed by TD_WINR and reset the state
void winr_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(winr);
}
