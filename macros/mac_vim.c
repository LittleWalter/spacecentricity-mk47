#include "mac_vim.h"
#include "macros.h"

// ─────────────────────────────────────────────────────────────
// Vim Macro DRY Helpers
// ─────────────────────────────────────────────────────────────

// Vim macro helper: `Esc`, <pause>
static void vim_esc_helper(void) {
    tap_code(KC_ESC);
    wait_ms(VIM_MODE_DELAY);
}

// Vim macro helper: `Esc`, <pause>, `:`, <pause>
static void vim_esc_cmd_helper(void) {
    vim_esc_helper();
    tap_code16(KC_COLN);
    wait_ms(VIM_CMD_DELAY);
}

// Vim macro helper: `Esc`, <pause>, `g`
static void vim_esc_g_helper(void) {
    vim_esc_helper();
    tap_code(KC_G);
}

// Vim macro helper: `Esc`, <pause>, `LCTL+w`
static void vim_win_helper(const bool with_esc) {
    if (with_esc) {
        vim_esc_helper();
    }
    tap_code16(C(KC_W));
}

// ─────────────────────────────────────────────────────────────
// Vim Macro Function Definitions
// ─────────────────────────────────────────────────────────────

// Vim macro: basic cursor movements such as `gj`, `gk`, `gE`, `gg, `G`, etc.
// W/e to `gg` and `G`, none of these macros are prefixed w/ `Esc` to allow compound commands like
// `3gE`, etc.
void vim_move_macro(const nav_action_t direction) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (direction) {
        case NAV_DOWN: // Move 1 row down, line wrap support
            SEND_STRING("gj");
            break;
        case NAV_UP: //  Move 1 column down, line wrap support
            SEND_STRING("gk");
            break;
        case NAV_PREV: // Move back 1 WORD
            tap_code16(S(KC_B));
            break;
        case NAV_NEXT: // Move forward 1 WORD
            tap_code16(S(KC_W));
            break;
        case NAV_PREV_END: // Move 1 WORD back, on the end
            tap_code(KC_G);
            // fallthru to get `gE`
        case NAV_NEXT_END: // Move 1 WORD forword, on the end
            tap_code16(S(KC_E));
            break;
        case NAV_TOP: // Move to top of buffer
        case NAV_START:
        case NAV_FIRST:
            vim_esc_helper();
            SEND_STRING("gg");
            break;
        case NAV_BOT: // Move to bottom of buffer
        case NAV_END:
        case NAV_LAST:
            vim_esc_helper();
            SEND_STRING("G");
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim macros: `zt`, `zz`, `zb` w/ prefixed `Esc`
// Viewport alignment top, middle, bottom
void vim_viewport_alignment_macro(const nav_action_t viewport) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_helper();
    tap_code(KC_Z);
    switch (viewport) {
        case NAV_TOP: tap_code(KC_T); break; // `zt`: viewport align top
        case NAV_MID: tap_code(KC_Z); break; // `zz`: viewport align middle
        case NAV_BOT: tap_code(KC_B); break; // `zb`: viewport align bottom
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim buffer navigation: first (`:bf`), previous (`:bp`), next(`:bn`), last (`:bl`) w/
// prefixed Esc
void vim_buffer_nav_macro(const nav_action_t nav) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_cmd_helper();
    tap_code(KC_B);
    switch (nav) {
        case NAV_START:
        case NAV_FIRST:
            tap_code(KC_F);
            break;
        case NAV_LEFT:
        case NAV_PREV:
            tap_code(KC_P);
            break;
        case NAV_RIGHT:
        case NAV_NEXT:
            tap_code(KC_N);
            break;
        case NAV_END:
        case NAV_LAST:
            tap_code(KC_L);
            break;
        default: break;
    }
    tap_code(KC_ENT);

    mod_state_restore(&saved);
}

// Vim window split navigation
void vim_window_macro(const nav_action_t window) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_win_helper(true);
    switch (window) {
        case NAV_LEFT: // Go to the left window split
            tap_code(KC_H); break;
        case NAV_DOWN: // Go to the window split below
            tap_code(KC_J); break;
        case NAV_UP:   // Go to the window split above
            tap_code(KC_K); break;
        case NAV_RIGHT:// Go to the right window split
            tap_code(KC_L); break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim window split resizing
void vim_window_size_macro(const size_change_t size) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_win_helper(false);
    switch (size) {
        case SZ_HEIGHT_INC: // Increase window split height by 1 row
            tap_code16(KC_PLUS);
            break;
        case SZ_HEIGHT_DEC: // Decrease window split height by 1 row
            tap_code(KC_MINS);
            break;
        case SZ_WIDTH_INC:  // Increase window split width by 1 column
            tap_code16(KC_GT);
            break;
        case SZ_WIDTH_DEC:  // Decrease window split width by 1 column
            tap_code16(KC_LT);
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim tab navigation: first (`:tabfirst`), previous (`gT`), next (`gt`), last (`:tablast`)
void vim_tab_nav_macro(const nav_action_t nav) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (nav) {
        case NAV_START:
        case NAV_FIRST:
            vim_esc_cmd_helper();
            SEND_STRING("tabfirst" SS_TAP(X_ENTER));
            break;
        case NAV_PREV:
            vim_esc_g_helper();
            tap_code16(S(KC_T));
            break;
        case NAV_NEXT:
            vim_esc_g_helper();
            tap_code(KC_T);
        case NAV_END:
        case NAV_LAST:
            vim_esc_cmd_helper();
            SEND_STRING("tablast" SS_TAP(X_ENTER));
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim change list navigation
void vim_change_list_macro(const nav_action_t nav) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_g_helper();
    switch (nav) {
        case NAV_PREV: // Jump to previous edit in change list
        case NAV_LEFT: tap_code(KC_COMM);  break;
        case NAV_NEXT: // Jump to next edit in change list
        case NAV_RIGHT: tap_code(KC_SCLN); break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Vim indent text, current line
void vim_indent_macro(const nav_action_t direction) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_helper();
    switch (direction) {
        case NAV_LEFT:  tap_code16(KC_LT); tap_code16(KC_LT); break;
        case NAV_RIGHT: tap_code16(KC_GT); tap_code16(KC_GT); break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Various general Vim command-line actions such as `:w`, `:qa`, etc.
void vim_commandline_macro(const vim_commandline_t command) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_cmd_helper();
    switch (command) {
        case VC_WRITE:             // `:w`
            tap_code(KC_W);
            tap_code(KC_ENT);
            break;
        case VC_WRITE_ALL:         // `:wa`
            tap_code(KC_W);
            tap_code(KC_A);
            break;
        case VC_QUIT_ALL:          // `:qa`
            tap_code(KC_Q);
            tap_code(KC_A);
            tap_code(KC_ENT);
            break;
        case VC_QUIT_ALL_FORCE:    // `:qa!`
            tap_code(KC_Q);
            tap_code(KC_A);
            tap_code16(KC_EXLM);
            break;
        case VC_SUB_BUF_GLOBAL:    // `:bufdo %s///g | update`
            uint16_t sub_buf[] = { KC_B, KC_U, KC_F, KC_D, KC_O, KC_SPC,           // `bufdo `
                                   KC_PERC, KC_S, KC_SLSH, KC_SLSH, KC_SLSH, KC_G, // `%s///g`
                                   KC_SPC, KC_PIPE, KC_SPC,                        // ` | `
                                   KC_U, KC_P, KC_D, KC_A, KC_T, KC_E };           // `update`
            seq_with_cursor_helper(sub_buf, 22, 12, false);
            break;
        case VC_SUB_GLOBAL:
            SEND_STRING("%s///g" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
            break;
        default: break;
    }

    mod_state_restore(&saved);
}


// Fold actions: toggle under cursor `za`, close all folds in buffer `zM`, open all folds in
// buffer `zR`
void vim_fold_macro(const fold_t fold) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_helper();
    tap_code(KC_Z);
    switch (fold) {
        case FOLD_TOGGLE:    tap_code(KC_A);      break; // `za`
        case FOLD_CLOSE_ALL: tap_code16(S(KC_M)); break; // `zM`
        case FOLD_OPEN_ALL:  tap_code16(S(KC_R)); break; // `zR`
        default: break;
    }

    mod_state_restore(&saved);
}

// Switches to previously active buffer (CTRL-6)
void vim_buffer_toggle_macro(void) {
    mod_state_t saved = mod_state_save_and_clear();

    vim_esc_helper();
    tap_code16(C(KC_6));

    mod_state_restore(&saved);
}
