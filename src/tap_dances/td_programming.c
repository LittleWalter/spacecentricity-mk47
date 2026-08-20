#include "td_programming.h"
#include "tap_dance_actions.h"
#include "src/features/case_mode.h"
#include "src/macros/mac_programming.h"
#include "src/macros/mac_surround.h"

// ─────────────────────────────────────────────────────────────
//  Programming N-Gram Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_PROG_EQL        == != <= >=
// ──────────────────────────────

// Create static `prog_eql_tap_dance` for TD_PROG_EQL
TD_DEF(prog_eql);

// Send the appropriate macro for TD_PROG_EQL
void prog_eql_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_eql);
    switch (TD_STATE(prog_eql)) {
        case TD_DOUBLE_TAP:  // ` != ` (Inequality)
            prog_operator_macro(OP_NEQ, true);
            break;
        case TD_SINGLE_HOLD: // ` >= ` (Greater than or equal)
            prog_operator_macro(OP_GTE, true);
            break;
        case TD_DOUBLE_HOLD: // ` <= ` (Less than or equal)
            prog_operator_macro(OP_LTE, true);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_EQ, true); // fallthru
        case TD_SINGLE_TAP:  // ` == ` (Equality)
            prog_operator_macro(OP_EQ, true);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_PROG_EQL and reset the state
void prog_eql_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_eql);
}

// ──────────────────────────────
// TD_AND                   && ||
// ──────────────────────────────

// Create static `prog_and_tap_dance` for TD_AND
TD_DEF(prog_and);

// Send the appropriate macro for TD_AND
void prog_and_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_and);
    switch (TD_STATE(prog_and)) {
        case TD_SINGLE_HOLD: // ` || ` (Logical Or)
            prog_operator_macro(OP_OR, true);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_AND, true); // fallthru
        case TD_SINGLE_TAP: // ` && ` (Logical And)
            prog_operator_macro(OP_AND, true);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_AND and reset the state
void prog_and_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_and);
}

// ──────────────────────────────
// TD_ASSIGN                 = :=
// ──────────────────────────────

// Create static `prog_assign_tap_dance` for TD_ASSIGN
TD_DEF(prog_assign);

// Send the appropriate macro for TD_ASSIGN
void prog_assign_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_assign);
    switch (TD_STATE(prog_assign)) {
        case TD_SINGLE_HOLD: // ` := `
            prog_operator_macro(OP_COLN_ASSIGN, true);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_ASSIGN, true); // fallthru
        case TD_SINGLE_TAP:  // ` = `
            prog_operator_macro(OP_ASSIGN, true);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_ASSIGN and reset the state
void prog_assign_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_assign);
}

// ──────────────────────────────
// TD_PARENS          () [] {} <>
// ──────────────────────────────

// Create static `prog_parens_tap_dance` for TD_PARENS
TD_DEF(prog_parens);

// Send the appropriate macro for TD_PARENS
void prog_parens_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_parens);
    switch (TD_STATE(prog_parens)) {
        case TD_DOUBLE_TAP:  surround_macro(SUR_BRC);   break; // `[]` w/ cursor inside (left arrow)
        case TD_SINGLE_HOLD: surround_macro(SUR_CBR);   break; // `{}` w/ cursor inside w/ vertical whitespace, cursor inside
        case TD_DOUBLE_HOLD: surround_macro(SUR_ABR);   break; // `<>` w/ cursor inside (left arrow)
        case TD_DOUBLE_SINGLE_TAP: surround_macro(SUR_PAREN);        // fallthru
        case TD_SINGLE_TAP:        surround_macro(SUR_PAREN); break; // `()` w/ cursor inside (left arrow)
        default: break;
    }
}

// Release any keys pressed by TD_PARENS and reset the state
void prog_parens_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_parens);
}

// ──────────────────────────────
// TD_DBL_QUOTES     "" '' ``` ``
// ──────────────────────────────

// Create static `prog_dbl_tap_dance` for TD_DBL_QUOTES
TD_DEF(prog_dbl_quotes);

// Send the appropriate macro for TD_DBL_QUOTES
void prog_dbl_quotes_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_dbl_quotes);
    switch (TD_STATE(prog_dbl_quotes)) {
        case TD_DOUBLE_TAP:  surround_macro(SUR_QUOT);        break; // '' w/ cursor inside (left arrow)
        case TD_SINGLE_HOLD: surround_macro(SUR_GRV);         break; // `` w/ cursor inside (left arrow)
        case TD_DOUBLE_HOLD: code_macro(CODE_MARKDOWN_BLOCK); break; // ```
        case TD_DOUBLE_SINGLE_TAP: surround_macro(SUR_DQUO);         // fallthru
        case TD_SINGLE_TAP:        surround_macro(SUR_DQUO);  break; // "" w/ cursor inside (left arrow)
        default: break;
    }
}

// Release any keys pressed by TD_DBL_QUOTES and reset the state
void prog_dbl_quotes_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_dbl_quotes);
}

// ──────────────────────────────
// TD_ARROW              -> <- =>
// ──────────────────────────────

// Create static `prog_arrow_tap_dance` for TD_ARROW
TD_DEF(prog_arrow);

// Send the appropriate marcro for TD_ARROW
void prog_arrow_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_arrow);
    switch (TD_STATE(prog_arrow)) {
        case TD_DOUBLE_TAP:  // `<-`
            prog_operator_macro(OP_LEFT_ARROW, false);
            break;
        case TD_SINGLE_HOLD: // ` => `
            prog_operator_macro(OP_FAT_ARROW, true);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_RIGHT_ARROW, false); // fallthru
        case TD_SINGLE_TAP:  // `->`
            prog_operator_macro(OP_RIGHT_ARROW, false);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_ARROW and reset the state
void prog_arrow_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_arrow);
}

// ──────────────────────────────
// TD_CMPD_OPS        += -= /= *=
// ──────────────────────────────

// Create static `prog_cmpd_tap_dance` for TD_CMPD_OPS
TD_DEF(prog_cmpd);

// Send the appropriate macro for TD_CMPD_OPS
void prog_cmpd_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_cmpd);
    switch (TD_STATE(prog_cmpd)) {
        case TD_DOUBLE_TAP:  // ` -= `
            prog_operator_macro(OP_COMP_SUB, true);
            break;
        case TD_SINGLE_HOLD: // ` *= `
            prog_operator_macro(OP_COMP_MUL, true);
            break;
        case TD_DOUBLE_HOLD: // ` /= `
            prog_operator_macro(OP_COMP_DIV, true);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_COMP_ADD, true); // fallthru
        case TD_SINGLE_TAP:  // ` += `
            prog_operator_macro(OP_COMP_ADD, true);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_CMPD_OPS and reset the state
void prog_cmpd_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_cmpd);
}

// ──────────────────────────────
// TD_INC                   ++ --
// ──────────────────────────────

// Create static `prog_inc_tap_dance` for TD_INC
TD_DEF(prog_inc);

// Send the appropriate macro for TD_INC
void prog_inc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_inc);
    switch (TD_STATE(prog_inc)) {
        case TD_SINGLE_HOLD: // `--`
            prog_operator_macro(OP_DECREMENT, false);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            prog_operator_macro(OP_INCREMENT, false); // fallthru
        case TD_SINGLE_TAP:  // `++`
            prog_operator_macro(OP_INCREMENT, false);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_INC and reset the state
void prog_inc_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_inc);
}

// ──────────────────────────────
// TD_COMMENT      `// ` `/*  */`
// ──────────────────────────────

// Create static `prog_comment_tap_dance` for TD_COMMENT
TD_DEF(prog_comment);

// Send the appropriate macro for TD_COMMENT
void prog_comment_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_comment);
    switch (TD_STATE(prog_comment)) {
        case TD_DOUBLE_TAP:  // `<!--  -->`
            code_macro(CODE_COMMENT_HTML);
            break;
        case TD_SINGLE_HOLD: // `/*  */` cursor inside
            code_macro(CODE_COMMENT_MULTILINE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            code_macro(CODE_COMMENT_INLINE); // fallthru
        case TD_SINGLE_TAP:  // `// `
            code_macro(CODE_COMMENT_INLINE);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_COMMENT and reset the state
void prog_comment_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_comment);
}

// ──────────────────────────────
// TD_IF_KW  if/else if/elif/else
// ──────────────────────────────

// Create static `prog_if_tap_dance` for TD_IF_KW
TD_DEF(prog_if);

// Send the appropriate macro for TD_IF_KW
void prog_if_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_if);
    switch (TD_STATE(prog_if)) {
        case TD_DOUBLE_TAP:  keyword_macro(KW_ELSE_IF, true);  break; // `else if `
        case TD_DOUBLE_HOLD: keyword_macro(KW_ELIF, true);     break; // `elif `
        case TD_SINGLE_HOLD: keyword_macro(KW_ELSE, true);     break; // `else `
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_IF, true);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_IF, true); break; // `if `
        default: break;
    }
}

// Release any keys pressed by TD_IF_KW and reset the state
void prog_if_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_if);
}

// ──────────────────────────────
// TD_TRUE_KW          true false
// ──────────────────────────────

// Create static `prog_true_tap_dance` for TD_TRUE_KW
TD_DEF(prog_true);

// Send the appropriate macro for TD_TRUE_KW
void prog_true_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_true);
    switch (TD_STATE(prog_true)) {
        case TD_SINGLE_HOLD: keyword_macro(KW_FALSE, false);       break; // `false` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_TRUE, false);         // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_TRUE, false);  break; // `true` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_TRUE_KW and reset the state
void prog_true_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_true);
}

// ──────────────────────────────
// TD_RETURN_KW  return `return `
// ──────────────────────────────

// Create static `prog_return_tap_dance` for TD_RETURN_KW
TD_DEF(prog_return);

// Send the appropriate macro for TD_RETURN_KW
void prog_return_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_return);
    switch (TD_STATE(prog_return)) {
        case TD_SINGLE_HOLD: keyword_macro(KW_RETURN, true);        break; // `return ` w/ space
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_RETURN, false);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_RETURN, false); break; // `return` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_RETURN_KW and reset the state
void prog_return_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_return);
}

// ──────────────────────────────
// TD_BREAK_KW     break continue
// ──────────────────────────────

// Create static `prog_break_tap_dance` for TD_BREAK_KW
TD_DEF(prog_break);

// Send the appropriate macro for TD_BREAK_KW
void prog_break_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_break);
    switch (TD_STATE(prog_break)) {
        case TD_SINGLE_HOLD: keyword_macro(KW_CONTINUE, false);    break; // `continue` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_BREAK, false);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_BREAK, false); break; // `break` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_BREAK_KW and reset the state
void prog_break_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_break);
}

// ────────────────────────────────
// TD_SWITCH_KW switch default case
// ────────────────────────────────

// Create static `prog_switch_tap_dance` for TD_SWITCH_KW
TD_DEF(prog_switch);

// Send the appropriate macro for TD_SWITCH_KW
void prog_switch_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_switch);
    switch (TD_STATE(prog_switch)) {
        case TD_DOUBLE_TAP:  keyword_macro(KW_DEFAULT, false); break; // `default` programming keyword
        case TD_SINGLE_HOLD: keyword_macro(KW_CASE, true);     break; // `case ` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_SWITCH, false);         // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_SWITCH, true);   break; // `switch ` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_SWITCH_KW and reset the state
void prog_switch_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_switch);
}

// ──────────────────────────────
// TD_SWITCH_KW         for while
// ──────────────────────────────

// Create static `prog_switch_tap_dance` for TD_FOR_KW
TD_DEF(prog_for);

// Send the appropriate macro for TD_SWITCH_KW
void prog_for_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_for);
    switch (TD_STATE(prog_for)) {
        case TD_SINGLE_HOLD: keyword_macro(KW_WHILE, true); break; // `while ` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_FOR, true);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_FOR, true); break; // `for ` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_SWITCH_KW and reset the state
void prog_for_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_for);
}

// ──────────────────────────────
// TD_NULL_KW       null NULL nil
// ──────────────────────────────

// Create static `prog_null_tap_dance` for TD_NULL_KW
TD_DEF(prog_null);

// Send the appropriate macro for TD_NULL_KW
void prog_null_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(prog_null);
    switch (TD_STATE(prog_null)) {
        case TD_DOUBLE_TAP: // `NULL`
            keyword_macro(KW_NULL_CAPS, false);
            break;
        case TD_SINGLE_HOLD: // `nil` programming keyword
            keyword_macro(KW_NIL, false);
            break;
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_NULL, false); // fallthru
        case TD_SINGLE_TAP: // `null` programming keyword
            keyword_macro(KW_NULL, false);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_NULL_KW and reset the state
void prog_null_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(prog_null);
}

// ─────────────────────────────────────────────────────────────
// Markdown
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_MD_LINK
// ──────────────────────────────

// Create static `md_link_tap_dance` for TD_MD_LINK
TD_DEF(md_link);

// Send the appropriate macro for TD_MD_LINK
void md_link_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(md_link);
    switch (TD_STATE_SET(md_link)) {
        case TD_SINGLE_HOLD: // `![]()` w/ cursor inside brackets
            code_macro(CODE_MARKDOWN_IMAGE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            code_macro(CODE_MARKDOWN_LINK); // fallthru
        case TD_SINGLE_TAP: // `[]()` w/ cursor inside brackets
            code_macro(CODE_MARKDOWN_LINK);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_MD_LINK and reset the state
void md_link_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(md_link);
}

// ─────────────────────────────────────────────────────────────
// Case Modes
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_CAMEL
// ──────────────────────────────

// Create static `camel_tap_dance` for TD_CAMEL
TD_DEF(camel);

// Send the appropriate macro for TD_CAMEL
void camel_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(camel);
    switch (TD_STATE(camel)) {
        case TD_SINGLE_TAP:  camel_case_toggle(); break;
        case TD_SINGLE_HOLD: pascal_case_toggle(); break;
        default: break;
    }
}

// Release any keys pressed by TD_CAMEL and reset the state
void camel_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(camel);
}

// ──────────────────────────────
// TD_SNAKE
// ──────────────────────────────

// Create static `snake_tap_dance` for TD_SNAKE
TD_DEF(snake);

// Send the appropriate macro for TD_SNAKE
void snake_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(snake);
    switch (TD_STATE(snake)) {
        case TD_SINGLE_TAP:  snake_case_toggle(); break;
        case TD_SINGLE_HOLD: const_case_toggle(); break;
        default: break;
    }
}

// Release any keys pressed by TD_SNAKE and reset the state
void snake_reset(tap_dance_state_t *state, void *user_data) {
    TD_RESET(snake);
}
