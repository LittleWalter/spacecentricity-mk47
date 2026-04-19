#include "mac_programming.h"
#include "macros.h"

// ──────────────────────────────
// Prose & Programming N-Grams
// ──────────────────────────────

// Auto-capitalization flag for next character
bool auto_cap_next = false;

// Punctuation-comma bigrams
void punc_space_macro(const uint16_t punc_keycode) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (punc_keycode) {
        // Capitalize the next alpha char for these end-of-sentence symbols
        case KC_DOT:  // `. `
        case KC_EXLM: // `! `
        case KC_QUES: // `? `
            auto_cap_next = true;
        case KC_COLN: // `: `
        case KC_COMM: // `, `
        case KC_SCLN: // `; `
            tap_code16(punc_keycode);
            tap_code(KC_SPC);
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Programming language operators
void prog_operator_macro(const operator_t operator, const bool extra_space) {
    mod_state_t saved = mod_state_save_and_clear();

    if (extra_space) {
        tap_code(KC_SPC);
    }

    switch (operator) {
        case OP_COLN_ASSIGN:    // `:=`
            tap_code16(KC_COLN);
            // fallthru
        case OP_ASSIGN:         // `=`
            tap_code16(KC_EQL);
            break;
        case OP_EQ:             // `==`
            tap_code16(KC_EQL);
            tap_code16(KC_EQL);
            break;
        case OP_NEQ:            // `!=`
            tap_code16(KC_EXLM);
            tap_code16(KC_EQL);
            break;
        case OP_LTE:            // `<=`
            tap_code16(KC_LT);
            tap_code16(KC_EQL);
            break;
        case OP_GTE:            // `>=`
            tap_code16(KC_GT);
            tap_code16(KC_EQL);
            break;
        case OP_AND:            // `&&`
            tap_code16(KC_AMPR);
            tap_code16(KC_AMPR);
            break;
        case OP_OR:             // `||`
            tap_code16(KC_PIPE);
            tap_code16(KC_PIPE);
            break;
        case OP_COMP_ADD:       // `+=`
            tap_code16(KC_PLUS);
            tap_code16(KC_EQL);
            break;
        case OP_COMP_SUB:      // `-=`
            tap_code(KC_MINS);
            tap_code16(KC_EQL);
            break;
        case OP_COMP_MUL:      // `*=`
            tap_code16(KC_ASTR);
            tap_code16(KC_EQL);
            break;
        case OP_COMP_DIV:       // `/=`
            tap_code(KC_SLSH);
            tap_code16(KC_EQL);
            break;
        case OP_INCREMENT:      // `++`
            tap_code16(KC_PLUS);
            tap_code16(KC_PLUS);
            break;
        case OP_DECREMENT:      // `--`
            tap_code(KC_MINS);
            tap_code(KC_MINS);
            break;
        case OP_RIGHT_ARROW:    // `->`
            tap_code(KC_MINS);
            tap_code16(KC_GT);
            break;
        case OP_LEFT_ARROW:     // `<-`
            tap_code16(KC_LT);
            tap_code(KC_MINS);
            break;
        case OP_FAT_ARROW:      // `=>`
            tap_code16(KC_EQL);
            tap_code16(KC_GT);
            break;
        case OP_TERNARY:        // ` ? : ` w/ cursor placed at start
            uint16_t ternary[] = { KC_SPC, KC_QUES, KC_SPC, KC_COLN, KC_SPC };
            seq_with_cursor_helper(ternary, 5, 5, false);
            break;
        default: break;
    }

    if (extra_space) {
        tap_code(KC_SPC);
    }

    mod_state_restore(&saved);
}

// Common surrounding characters: `()`, `[]`, `{}`, `<>`, double/single quotes, grave/backtick
// symbols, etc.
void surround_macro(const surround_char_t pair) {
    switch (pair) {
        case SUR_PAREN: // `()`
            uint16_t parens[] = { KC_LPRN, KC_RPRN };
            seq_with_cursor_helper(parens, 2, 1, false);
            break;
        case SUR_BRC:   // `[]`
            uint16_t brackets[] = { KC_LBRC, KC_RBRC };
            seq_with_cursor_helper(brackets, 2, 1, false);
            break;
        case SUR_CBR:   // `{}`
            uint16_t curly_braces[] = { KC_LCBR, KC_RCBR };
            seq_with_cursor_helper(curly_braces, 2, 1, false);
            break;
        case SUR_VWS_CBR: // `{}` w/ vertical whitespace
            uint16_t curly_braces_whitespace[] = { KC_LCBR, KC_RCBR };
            seq_with_cursor_helper(curly_braces_whitespace, 2, 1, true);
            break;
        case SUR_ABR:   // `<>`
            uint16_t angle_brackets[] = { KC_LT, KC_GT };
            seq_with_cursor_helper(angle_brackets, 2, 1, false);
            break;
        case SUR_DQUO:  // `""`
            uint16_t dquotes[] = { KC_DQUO, KC_DQUO };
            seq_with_cursor_helper(dquotes, 2, 1, false);
            break;
        case SUR_QUOT:  // `''`
            uint16_t quotes[] = { KC_QUOT, KC_QUOT };
            seq_with_cursor_helper(quotes, 2, 1, false);
            break;
        case SUR_GRV:   // ``
            uint16_t backticks[] = { KC_GRV, KC_GRV };
            seq_with_cursor_helper(backticks, 2, 1, false);
            break;
        default: break;
    }
}

// Various coding n-grams such as C-style comments, Markdown Images/Links, etc.
void code_macro(const code_t ngram) {
    switch (ngram) {
        case CODE_COMMENT_INLINE:    // `// `
            uint16_t inline_comment[] = { KC_SLSH, KC_SLSH, KC_SPC };
            seq_with_cursor_helper(inline_comment, 3, 0, false);
            break;
        case CODE_COMMENT_MULTILINE: // `/*  */`
            uint16_t multiline_comment[] = { KC_SLSH, KC_ASTR, KC_SPC, KC_SPC, KC_ASTR, KC_SLSH };
            seq_with_cursor_helper(multiline_comment, 6, 3, false);
            break;
        case CODE_MARKDOWN_BLOCK:    // ```
            uint16_t backticks[] = { KC_GRV, KC_GRV, KC_GRV };
            seq_with_cursor_helper(backticks, 3, 0, false);
            break;
        case CODE_MARKDOWN_IMAGE:    // `![]()`
            tap_code16(KC_EXLM);
            // fallthru: same as Markdown link but prefixed w/ `!`
        case CODE_MARKDOWN_LINK:     // `[]()`
            uint16_t md_link[] = { KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN };
            seq_with_cursor_helper(md_link, 4, 3, false);
            break;
        case CODE_COMMENT_HTML:      // `<!--  -->`
            uint16_t html_comment[] = { KC_LT,   KC_EXLM, KC_MINS, KC_MINS,
                                        KC_SPC,  KC_SPC,
                                        KC_MINS, KC_MINS, KC_GT };
            seq_with_cursor_helper(html_comment, 9, 4, false);
            break;
        default: break;
    }
}

// Common keywords used by most programming languages
void keyword_macro(const keyword_t keyword, const bool with_space) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (keyword) {
        case KW_IF:        SEND_STRING("if");       break;
        case KW_ELSE_IF:   SEND_STRING("else if");  break;
        case KW_ELIF:      SEND_STRING("elif");     break;
        case KW_ELSE:      SEND_STRING("else");     break;
        case KW_BREAK:     SEND_STRING("break");    break;
        case KW_CONTINUE:  SEND_STRING("continue"); break;
        case KW_TRUE:      SEND_STRING("true");     break;
        case KW_FALSE:     SEND_STRING("false");    break;
        case KW_FOR:       SEND_STRING("for");      break;
        case KW_WHILE:     SEND_STRING("while");    break;
        case KW_SWITCH:    SEND_STRING("switch");   break;
        case KW_CASE:      SEND_STRING("case");     break;
        case KW_DEFAULT:   SEND_STRING("default");  break;
        case KW_RETURN:    SEND_STRING("return");   break;
        case KW_NULL:      SEND_STRING("null");     break;
        case KW_NULL_CAPS: SEND_STRING("NULL");     break;
        case KW_NIL:       SEND_STRING("nil");      break;
        default: break;
    }

    if (with_space) {
        tap_code(KC_SPC);
    }

    mod_state_restore(&saved);
}

// Common code annotations
void notes_macro(const dev_notes_t note) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (note) {
        case DEV_FIXME:   SEND_STRING("FIXME: ");   break;
        case DEV_INFO:    SEND_STRING("INFO: ");    break;
        case DEV_NOTE:    SEND_STRING("NOTE: ");    break;
        case DEV_REF:     SEND_STRING("REF: ");     break;
        case DEV_TIP:     SEND_STRING("TIP: ");     break;
        case DEV_TODO:    SEND_STRING("TODO: ");    break;
        case DEV_WARNING: SEND_STRING("WARNING: "); break;
        case DEV_SECTION: // A 78-column C-style section header
            SEND_STRING("// ---------------------------------------------------------------------------");
            tap_code(KC_ENT);
            break;
        default: break;
    }
    mod_state_restore(&saved);
}
