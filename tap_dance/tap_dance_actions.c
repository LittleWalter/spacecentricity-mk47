#include "tap_dance_actions.h"
#include "td_chars.h"
#include "td_macos.h"
#include "td_media.h"
#include "td_misc.h"
#include "td_numpad.h"
#include "td_programming.h"
#include "td_terminal.h"
#include "td_vim.h"

// ─────────────────────────────────────────────────────────────
//  Tap Dance Registry
// ─────────────────────────────────────────────────────────────

tap_dance_action_t tap_dance_actions[TD_COUNT] = {
    // ─────────────────────────────────────────────────────────────
    // Character Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_ASTR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, astr_finished, astr_reset),
    [TD_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bspc_finished, bspc_reset),
    [TD_CIRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, circ_finished, circ_reset),
    [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comm_finished, comm_reset),
    [TD_C]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_finished,    c_reset),
    [TD_DLR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dlr_finished,  dlr_reset),
    [TD_DOT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_finished,  dot_reset),
    [TD_DQUO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dquo_finished, dquo_reset),
    [TD_EQL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eql_finished,  eql_reset),
    [TD_EXLM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, exlm_finished, exlm_reset),
    [TD_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mins_finished, mins_reset),
    [TD_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plus_finished, plus_reset),
    [TD_PUNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, punc_finished, punc_reset),
    [TD_QUES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ques_finished, ques_reset),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
    [TD_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished,  spc_reset),
    [TD_TAB]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished,  tab_reset),
    [TD_U]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u_finished,    u_reset),

    [TD_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lprn_finished, lprn_reset),
    [TD_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rprn_finished, rprn_reset),
    [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrc_finished, lbrc_reset),
    [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbrc_finished, rbrc_reset),
    // Navigational Tap Dances
    [TD_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, home_finished, home_reset),
    [TD_PGDN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgdn_finished, pgdn_reset),
    [TD_PGUP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgup_finished, pgup_reset),
    [TD_END]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, end_finished,  end_reset),

    // ─────────────────────────────────────────────────────────────
    // Media Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mute_finished, mute_reset),
    [TD_VOLD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, vold_finished, vold_reset),
    [TD_VOLU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volu_finished, volu_reset),

    // ─────────────────────────────────────────────────────────────
    // Numpad Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_NUMPAD_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_1_finished, numpad_1_reset),
    [TD_NUMPAD_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_2_finished, numpad_2_reset),
    [TD_NUMPAD_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_3_finished, numpad_3_reset),
    [TD_NUMPAD_4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_4_finished, numpad_4_reset),
    [TD_NUMPAD_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_5_finished, numpad_5_reset),
    [TD_NUMPAD_6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_6_finished, numpad_6_reset),

    // ─────────────────────────────────────────────────────────────
    // Vim Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_B]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished,         b_reset),
    [TD_GJ]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gj_finished,        gj_reset),
    [TD_GK]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gk_finished,        gk_reset),
    [TD_W]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, w_finished,         w_reset),
    // Page Down/Up, Top/Bottom of Buffer
    [TD_HALF_PGDN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, half_pgdn_finished, half_pgdn_reset),
    [TD_HALF_PGUP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, half_pgup_finished, half_pgup_reset),
    // Viewport Adjustments
    [TD_HIGH]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, high_finished,      high_reset),
    [TD_MID]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mid_finished,       mid_reset),
    [TD_LOW]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, low_finished,       low_reset),
    // Splits, Tabs, Buffers
    [TD_WINL]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, winl_finished,      winl_reset),
    [TD_WIND]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wind_finished,      wind_reset),
    [TD_WINU]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, winu_finished,      winu_reset),
    [TD_WINR]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, winr_finished,      winr_reset),

    [TD_SUB]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sub_finished,      sub_reset),
    [TD_FOLD]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fold_finished,     fold_reset),
    [TD_WRITE]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, write_finished,    write_reset),
    [TD_QUIT]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quit_finished,     quit_reset),

    // ─────────────────────────────────────────────────────────────
    // Programming N-Gram Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_PROG_EQL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_eql_finished,        prog_eql_reset),
    [TD_AND]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_and_finished,        prog_and_reset),
    [TD_ASSIGN]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_assign_finished,     prog_assign_reset),
    [TD_PARENS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_parens_finished,     prog_parens_reset),
    [TD_DBL_QUOTES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_dbl_quotes_finished, prog_dbl_quotes_reset),
    [TD_ARROW]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_arrow_finished,      prog_arrow_reset),
    [TD_CMPD]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_cmpd_finished,       prog_cmpd_reset),
    [TD_INC]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_inc_finished,        prog_inc_reset),
    [TD_COMMENT]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_comment_finished,    prog_comment_reset),
    [TD_IF_KW]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_if_finished,         prog_if_reset),
    [TD_TRUE_KW]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_true_finished,       prog_true_reset),
    [TD_RETURN_KW]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_return_finished,     prog_return_reset),
    [TD_BREAK_KW]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_break_finished,      prog_break_reset),
    [TD_SWITCH_KW]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_switch_finished,     prog_switch_reset),
    [TD_FOR_KW]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_for_finished,        prog_for_reset),
    [TD_NULL_KW]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, prog_null_finished,       prog_null_reset),

    [TD_MD_LINK]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, md_link_finished, md_link_reset),

    // ─────────────────────────────────────────────────────────────
    // Terminal Command Tap Dances
    // ─────────────────────────────────────────────────────────────

    [TD_BTOP]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_btop_finished,    term_btop_reset),
    [TD_CLS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_cls_finished,     term_cls_reset),
    [TD_CAT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_cat_finished,     term_cat_reset),
    [TD_SIGINT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_sigint_finished,  term_sigint_reset),
    [TD_PIPE]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_pipe_finished,    term_pipe_reset),
    [TD_PATH]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_path_finished,    term_path_reset),
    [TD_CD]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_cd_finished,      term_cd_reset),
    [TD_SUDO]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, term_sudo_finished,    term_sudo_reset),

    // ─────────────────────────────────────────────────────────────
    // Apple macOS-Related Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_SPOTLGHT_MACOS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spotlght_macos_finished, spotlght_macos_reset),
    [TD_FS_MACOS]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fs_macos_finished,       fs_macos_reset),
    [TD_SCRNSHOT_MACOS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scrnshot_macos_finished, scrnshot_macos_reset),
    [TD_DEL_MACOS]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, del_macos_finished,      del_macos_reset),

    // ─────────────────────────────────────────────────────────────
    // Miscellaneous Tap Dances
    // ─────────────────────────────────────────────────────────────
    [TD_UNDO]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, undo_finished, undo_reset),
    [TD_SMART_QUOTES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, smart_quotes_finished, smart_quotes_reset)
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 * REF: Sample code taken from https://docs.qmk.fm/features/tap_dance#examples
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}
