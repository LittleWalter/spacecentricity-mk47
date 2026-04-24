#include "macros.h"
#include "mac_surround.h"
#include "mac_special_char.h"

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
        case SUR_SMART_DQUO: // “”
            special_char_macro(CHAR_SMART_DQUOTE_LEFT);
            special_char_macro(CHAR_SMART_DQUOTE_RIGHT);
            tap_code(KC_LEFT);
            break;
        case SUR_SMART_QUOT: // ‘’
            special_char_macro(CHAR_SMART_QUOTE_LEFT);
            special_char_macro(CHAR_SMART_QUOTE_RIGHT);
            tap_code(KC_LEFT);
            break;
        case SUR_ANGLE_DQUO: // «»
            special_char_macro(CHAR_ANGLE_DQUOTE_LEFT);
            special_char_macro(CHAR_ANGLE_DQUOTE_RIGHT);
            tap_code(KC_LEFT);
            break;
        case SUR_ANGLE_QUOT: // ‹›
            special_char_macro(CHAR_ANGLE_QUOTE_LEFT);
            special_char_macro(CHAR_ANGLE_QUOTE_RIGHT);
            tap_code(KC_LEFT);
            break;
        default: break;
    }
}

