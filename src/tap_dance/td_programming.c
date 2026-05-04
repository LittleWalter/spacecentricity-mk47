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

// Instance of 'td_tap_t' for the TD_PROG_EQL quad tap dance
static td_tap_t prog_eql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_PROG_EQL
void prog_eql_finished(tap_dance_state_t *state, void *user_data) {
    prog_eql_tap_state.state = cur_dance(state);
    switch (prog_eql_tap_state.state) {
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
    prog_eql_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_AND                   && ||
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_AND tap and hold dance
static td_tap_t prog_and_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_AND
void prog_and_finished(tap_dance_state_t *state, void *user_data) {
    prog_and_tap_state.state = cur_dance(state);
    switch (prog_and_tap_state.state) {
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
    prog_and_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_ASSIGN                 = :=
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_AND tap and hold dance
static td_tap_t prog_assign_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_ASSIGN
void prog_assign_finished(tap_dance_state_t *state, void *user_data) {
    prog_assign_tap_state.state = cur_dance(state);
    switch (prog_assign_tap_state.state) {
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
    prog_and_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PARENS          () [] {} <>
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PARENS quad tap dance
static td_tap_t prog_parens_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_PARENS
void prog_parens_finished(tap_dance_state_t *state, void *user_data) {
    prog_parens_tap_state.state = cur_dance(state);
    switch (prog_parens_tap_state.state) {
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
    prog_parens_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DBL_QUOTES     "" '' ``` ``
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DBL_QUOTES quad tap dance
static td_tap_t prog_dbl_quotes_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_DBL_QUOTES
void prog_dbl_quotes_finished(tap_dance_state_t *state, void *user_data) {
    prog_dbl_quotes_tap_state.state = cur_dance(state);
    switch (prog_dbl_quotes_tap_state.state) {
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
    prog_dbl_quotes_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_ARROW              -> <- =>
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_ARROW tap and hold dance.
static td_tap_t prog_arrow_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate marcro for TD_ARROW
void prog_arrow_finished(tap_dance_state_t *state, void *user_data) {
    prog_arrow_tap_state.state = cur_dance(state);
    switch (prog_arrow_tap_state.state) {
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
    prog_arrow_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CMPD_OPS        += -= /= *=
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CMPD_OPS quad tap dance.
static td_tap_t prog_cmpd_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_CMPD_OPS
void prog_cmpd_finished(tap_dance_state_t *state, void *user_data) {
    prog_cmpd_tap_state.state = cur_dance(state);
    switch (prog_cmpd_tap_state.state) {
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
    prog_cmpd_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_INC                   ++ --
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_INC quad tap dance.
static td_tap_t prog_inc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_INC
void prog_inc_finished(tap_dance_state_t *state, void *user_data) {
    prog_inc_tap_state.state = cur_dance(state);
    switch (prog_inc_tap_state.state) {
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
    prog_inc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_COMMENT      `// ` `/*  */`
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_COMMENT quad tap dance.
static td_tap_t prog_comment_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_COMMENT
void prog_comment_finished(tap_dance_state_t *state, void *user_data) {
    prog_comment_tap_state.state = cur_dance(state);
    switch (prog_comment_tap_state.state) {
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
    prog_comment_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_IF_KW  if/else if/elif/else
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_IF_KW quad tap dance
static td_tap_t prog_if_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_IF_KW
void prog_if_finished(tap_dance_state_t *state, void *user_data) {
    prog_if_tap_state.state = cur_dance(state);
    switch (prog_if_tap_state.state) {
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
    prog_if_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_TRUE_KW          true false
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_TRUE_KW tap and hold dance
static td_tap_t prog_true_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_TRUE_KW
void prog_true_finished(tap_dance_state_t *state, void *user_data) {
    prog_true_tap_state.state = cur_dance(state);
    switch (prog_true_tap_state.state) {
        case TD_SINGLE_HOLD: keyword_macro(KW_FALSE, false);       break; // `false` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_TRUE, false);         // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_TRUE, false);  break; // `true` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_TRUE_KW and reset the state
void prog_true_reset(tap_dance_state_t *state, void *user_data) {
    prog_true_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_RETURN_KW  return `return `
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_RETURN_KW tap and hold dance
static td_tap_t prog_return_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_RETURN_KW
void prog_return_finished(tap_dance_state_t *state, void *user_data) {
    prog_return_tap_state.state = cur_dance(state);
    switch (prog_return_tap_state.state) {
        case TD_SINGLE_HOLD: keyword_macro(KW_RETURN, true);        break; // `return ` w/ space
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_RETURN, false);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_RETURN, false); break; // `return` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_RETURN_KW and reset the state
void prog_return_reset(tap_dance_state_t *state, void *user_data) {
    prog_return_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_BREAK_KW     break continue
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_BREAK_KW tap and hold dance
static td_tap_t prog_break_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_BREAK_KW
void prog_break_finished(tap_dance_state_t *state, void *user_data) {
    prog_break_tap_state.state = cur_dance(state);
    switch (prog_break_tap_state.state) {
        case TD_SINGLE_HOLD: keyword_macro(KW_CONTINUE, false);    break; // `continue` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_BREAK, false);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_BREAK, false); break; // `break` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_BREAK_KW and reset the state
void prog_break_reset(tap_dance_state_t *state, void *user_data) {
    prog_break_tap_state.state = TD_NONE;
}

// ────────────────────────────────
// TD_SWITCH_KW switch default case
// ────────────────────────────────

// Instance of 'td_tap_t' for the TD_SWITCH_KW tap and hold dance
static td_tap_t prog_switch_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_SWITCH_KW
void prog_switch_finished(tap_dance_state_t *state, void *user_data) {
    prog_switch_tap_state.state = cur_dance(state);
    switch (prog_switch_tap_state.state) {
        case TD_DOUBLE_TAP:  keyword_macro(KW_DEFAULT, false); break; // `default` programming keyword
        case TD_SINGLE_HOLD: keyword_macro(KW_CASE, true);     break; // `case ` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_SWITCH, false);         // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_SWITCH, true);   break; // `switch ` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_SWITCH_KW and reset the state
void prog_switch_reset(tap_dance_state_t *state, void *user_data) {
    prog_switch_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SWITCH_KW         for while
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_FOR_KW tap and hold dance
static td_tap_t prog_for_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_SWITCH_KW
void prog_for_finished(tap_dance_state_t *state, void *user_data) {
    prog_for_tap_state.state = cur_dance(state);
    switch (prog_for_tap_state.state) {
        case TD_SINGLE_HOLD: keyword_macro(KW_WHILE, true); break; // `while ` programming keyword
        case TD_DOUBLE_SINGLE_TAP: keyword_macro(KW_FOR, true);        // fallthru
        case TD_SINGLE_TAP:        keyword_macro(KW_FOR, true); break; // `for ` programming keyword
        default: break;
    }
}

// Release any keys pressed by TD_SWITCH_KW and reset the state
void prog_for_reset(tap_dance_state_t *state, void *user_data) {
    prog_for_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_NULL_KW       null NULL nil
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_NULL_KW tap and hold dance
static td_tap_t prog_null_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_NULL_KW
void prog_null_finished(tap_dance_state_t *state, void *user_data) {
    prog_null_tap_state.state = cur_dance(state);
    switch (prog_null_tap_state.state) {
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
    prog_null_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Markdown
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_MD_LINK
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_MD_LINK tap and hold dance
static td_tap_t md_link_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_MD_LINK
void md_link_finished(tap_dance_state_t *state, void *user_data) {
    md_link_tap_state.state = cur_dance(state);
    switch (md_link_tap_state.state) {
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
    md_link_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Case Modes
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_CAMEL
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CAMEL tap and hold dance
static td_tap_t camel_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_CAMEL
void camel_finished(tap_dance_state_t *state, void *user_data) {
    camel_tap_state.state = cur_dance(state);
    switch (camel_tap_state.state) {
        case TD_SINGLE_TAP:  camel_case_toggle(); break;
        case TD_SINGLE_HOLD: pascal_case_toggle(); break;
        default: break;
    }
}

// Release any keys pressed by TD_CAMEL and reset the state
void camel_reset(tap_dance_state_t *state, void *user_data) {
    camel_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SNAKE
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SNAKE tap and hold dance
static td_tap_t snake_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate macro for TD_SNAKE
void snake_finished(tap_dance_state_t *state, void *user_data) {
    snake_tap_state.state = cur_dance(state);
    switch (snake_tap_state.state) {
        case TD_SINGLE_TAP:  snake_case_toggle(); break;
        case TD_SINGLE_HOLD: const_case_toggle(); break;
        default: break;
    }
}

// Release any keys pressed by TD_SNAKE and reset the state
void snake_reset(tap_dance_state_t *state, void *user_data) {
    snake_tap_state.state = TD_NONE;
}
