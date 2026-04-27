#include "td_chars.h"
#include "tap_dance_actions.h"
#include "src/core/custom_keys.h"
#include "src/core/keymap.h"
#include "src/features/leader.h"
#include "src/macros/mac_programming.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_surround.h"

// ─────────────────────────────────────────────────────────────
//  Char Key Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_ASTR              * % @ # ×
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_ASTR quad tap dance
static td_tap_t astr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_ASTR
void astr_finished(tap_dance_state_t *state, void *user_data) {
    astr_tap_state.state = cur_dance(state);
    switch (astr_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_PERC); break; // `%` Vim, normal mode: Jump to matching brace/bracket/etc.
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_MULTIPLY); break; // `×`
        case TD_SINGLE_HOLD: register_code16(KC_HASH); break; // `#` Vim, normal mode: Reverse search word under cursor
        case TD_DOUBLE_HOLD: register_code16(KC_AT);   break; // `@` Vim, normal mode: Trigger macro
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PAST);       // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_PAST); break; // `*` Vim, normal mode: Search word under cursor
        default: break;
    }
}

// Release any keys pressed by TD_ASTR and reset the state
void astr_reset(tap_dance_state_t *state, void *user_data) {
    switch (astr_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_PERC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_HASH); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_AT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PAST); break;
        default: break;
    }
    astr_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_COMM                , ; | &
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_COMM quad tap dance.
static td_tap_t comm_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_COMM
void comm_finished(tap_dance_state_t *state, void *user_data) {
    comm_tap_state.state = cur_dance(state);
    switch (comm_tap_state.state) {
        case TD_DOUBLE_TAP:        register_code16(KC_SCLN); break; // `;`
        case TD_SINGLE_HOLD:       register_code16(KC_AMPR); break; // `&`
        case TD_DOUBLE_HOLD:       register_code16(KC_PIPE); break; // `|`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_COMM);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_COMM); break; // `,`
        default: break;
    }
}

// Release any keys pressed by TD_COMM and reset the state
void comm_reset(tap_dance_state_t *state, void *user_data) {
    switch (comm_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_AMPR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_PIPE); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_COMM); break;
        default: break;
    }
    comm_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PUNC space appended , ! ? .
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PUNC quad tap dance
static td_tap_t punc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_PUNC
void punc_finished(tap_dance_state_t *state, void *user_data) {
    punc_tap_state.state = cur_dance(state);
    switch (punc_tap_state.state) {
        case TD_DOUBLE_TAP:  punc_space_macro(KC_EXLM); break; // `! ` exclamation-space bigram w/ auto cap
        case TD_SINGLE_HOLD: punc_space_macro(KC_DOT);  break; // `. ` dot/period-space bigram w/ auto cap
        case TD_DOUBLE_HOLD: punc_space_macro(KC_QUES); break; // `? ` question-space bigram w/ auto cap
        case TD_DOUBLE_SINGLE_TAP: punc_space_macro(KC_COMM);  // fallthru
        case TD_SINGLE_TAP:  punc_space_macro(KC_COMM); break; // `, ` comma-space bigram
        default: break;
    }
}

// Release any keys pressed by TD_PUNC and reset the state
void punc_reset(tap_dance_state_t *state, void *user_data) {
    punc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_QUOT                ' ’ ~ `
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_QUOT quad tap dance
static td_tap_t quot_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_QUOT
void quot_finished(tap_dance_state_t *state, void *user_data) {
    quot_tap_state.state = cur_dance(state);
    switch (quot_tap_state.state) {
        case TD_DOUBLE_TAP: // `’` typographic apostrophe a.k.a. closing smart single quote
            special_char_macro(CHAR_SMART_QUOTE_RIGHT);
            break;
        case TD_SINGLE_HOLD:       register_code16(KC_GRV);  break; // backtick (`) symbol
        case TD_DOUBLE_HOLD:       register_code16(KC_TILD); break; // `~`
        case TD_TRIPLE_TAP:        tap_code16(KC_QUOT);             // `'''` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_QUOT);             // `''` fallthru
        case TD_SINGLE_TAP:        register_code16(KC_QUOT); break; // `'`
        default: break;
    }
}

// Release any keys pressed by TD_QUOT and reset the state
void quot_reset(tap_dance_state_t *state, void *user_data) {
    switch (quot_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_GRV);  break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_TILD); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_QUOT); break;
        default: break;
    }
    quot_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DQUO                " ‘ < >
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DQUO quad tap dance
static td_tap_t dquo_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_DQUO
void dquo_finished(tap_dance_state_t *state, void *user_data) {
    dquo_tap_state.state = cur_dance(state);
    switch (dquo_tap_state.state) {
        case TD_DOUBLE_TAP: // `‘` typographic closing smart single quote
            special_char_macro(CHAR_SMART_QUOTE_LEFT);
            break;
        case TD_SINGLE_HOLD:       register_code16(KC_GT);   break; // `>`
        case TD_DOUBLE_HOLD:       register_code16(KC_LT);   break; // `<`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DQUO);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_DQUO); break; // `"`
        default: break;
    }
}

// Release any keys pressed by TD_DQUO and reset the state
void dquo_reset(tap_dance_state_t *state, void *user_data) {
    switch (dquo_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_GT);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_DQUO); break;
        default: break;
    }
    dquo_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_EQL                 =   ≈ ≠
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_EQL quad tap dance
static td_tap_t eql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_EQL
void eql_finished(tap_dance_state_t *state, void *user_data) {
    eql_tap_state.state = cur_dance(state);
    switch (eql_tap_state.state) {
        case TD_SINGLE_HOLD:       special_char_macro(CHAR_NEQ);    break; // `>`
        case TD_DOUBLE_HOLD:       special_char_macro(CHAR_APPROX); break; // `≈`
        case TD_TRIPLE_TAP:        tap_code16(KC_PEQL);                    // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PEQL);                    // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_PEQL); break;        // `=`
        default: break;
    }
}

// Release any keys pressed by TD_EQL and reset the state
void eql_reset(tap_dance_state_t *state, void *user_data) {
    switch (eql_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_PEQL); break;
        default: break;
    }
    eql_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_QUES Cross Platform ? ¿ ◌̀ ◌́
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_QUES quad tap dance
static td_tap_t ques_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_QUES
void ques_finished(tap_dance_state_t *state, void *user_data) {
    ques_tap_state.state = cur_dance(state);
    switch (ques_tap_state.state) {
        case TD_DOUBLE_TAP: // `¿` (Spanish inverted question mark)
            special_char_macro(CHAR_INV_QUES);
            break;
        case TD_SINGLE_HOLD: // ◌́ (combining acute mark)
            special_char_macro(CHAR_COMB_ACUTE);
            break;
        case TD_DOUBLE_HOLD: // `◌̀` (combining grave accent mark)
            special_char_macro(CHAR_COMB_GRAVE);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_QUES);             // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_QUES);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_QUES); break; // `?`
        default: break;
    }
}

// Release any keys pressed by TD_QUES and reset the state
void ques_reset(tap_dance_state_t *state, void *user_data) {
    switch (ques_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_QUES); break;
        default: break;
    }
    ques_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_EXLM Cross Platform ! ¡ ◌̃ ◌̈
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_EXLM quad tap dance
static td_tap_t exlm_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_EXLM
void exlm_finished(tap_dance_state_t *state, void *user_data) {
    exlm_tap_state.state = cur_dance(state);
    switch (exlm_tap_state.state) {
        case TD_DOUBLE_TAP: // `¡` (Spanish inverted exclamation mark)
            special_char_macro(CHAR_INV_EXLM);
            break;
        case TD_SINGLE_HOLD: // `◌̈` (combining umlaut)
            special_char_macro(CHAR_COMB_UMLAUT);
            break;
        case TD_DOUBLE_HOLD: // ◌̃ (combining tilde)
            special_char_macro(CHAR_COMB_TILDE);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_EXLM);             // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_EXLM);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_EXLM); break; // `!`
        default: break;
    }
}

// Release any keys pressed by TD_EXLM and reset the state
void exlm_reset(tap_dance_state_t *state, void *user_data) {
    switch (exlm_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_EXLM); break;
        default: break;
    }
    exlm_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_MINS                -   – —
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_MINS quad tap dance
static td_tap_t mins_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_MINS
void mins_finished(tap_dance_state_t *state, void *user_data) {
    mins_tap_state.state = cur_dance(state);
    switch (mins_tap_state.state) {
        case TD_SINGLE_HOLD: special_char_macro(CHAR_EM_DASH); break; // `—` (em dash)
        case TD_DOUBLE_HOLD: special_char_macro(CHAR_EN_DASH); break; // `–` (en dash)
        case TD_TRIPLE_TAP:        tap_code16(KC_MINS);             // fallthru
        case TD_DOUBLE_TAP:                                         // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_MINS);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_MINS); break; // `-`
        default: break;
    }
}

// Release any keys pressed by TD_MINS and reset the state
void mins_reset(tap_dance_state_t *state, void *user_data) {
    switch (mins_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
            unregister_code16(KC_MINS); break;
        default: break;
    }
    mins_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_BSPC               ⌫  ⌫L ⌫w
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_BSPC quad tap dance
static td_tap_t bspc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate delete key for TD_BSPC
void bspc_finished(tap_dance_state_t *state, void *user_data) {
    bspc_tap_state.state = cur_dance(state);
    switch (bspc_tap_state.state) {
        case TD_SINGLE_HOLD: // ⌫ previous word
            register_code16(current_os == OS_MACOS ? A(KC_BSPC) : C(KC_BSPC));
            break;
        case TD_DOUBLE_HOLD: // ⌫ to BOL
            tap_code16(C(S(KC_LEFT)));
            tap_code(KC_BSPC);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_BSPC);             // fallthru
        case TD_DOUBLE_TAP:                                         // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_BSPC);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_BSPC); break; // ⌫ Backspace
        default: break;
    }
}

// Release any keys pressed by TD_BSPC and reset the state
void bspc_reset(tap_dance_state_t *state, void *user_data) {
    switch (bspc_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code16(current_os == OS_MACOS ? A(KC_BSPC) : C(KC_BSPC));
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_BSPC); break;
        default: break;
    }
    bspc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DEL                ⌦  ⌦L ⌦w
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DEL quad tap dance
static td_tap_t del_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate delete key for TD_DEL
void del_finished(tap_dance_state_t *state, void *user_data) {
    del_tap_state.state = cur_dance(state);
    switch (del_tap_state.state) {
        case TD_SINGLE_HOLD: // ⌦ next word
            register_code16(current_os == OS_MACOS ? A(KC_DEL) : C(KC_DEL));
            break;
        case TD_DOUBLE_HOLD: // ⌫ to EOL
            tap_code16(S(KC_END));
            tap_code(KC_DEL);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_DEL); // fallthru
        case TD_DOUBLE_TAP:                            // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DEL); // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_DEL); break; // ⌦ Delete
        default: break;
    }
}

// Release any keys pressed by TD_DEL and reset the state
void del_reset(tap_dance_state_t *state, void *user_data) {
    switch (del_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code16(current_os == OS_MACOS ? A(KC_DEL) : C(KC_DEL));
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_DEL); break;
        default: break;
    }
    del_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SPC                 ␣   ↵ ⌘
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SPC quad tap dance.
static td_tap_t spc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_SPC
void spc_finished(tap_dance_state_t *state, void *user_data) {
    spc_tap_state.state = cur_dance(state);
    switch (spc_tap_state.state) {
        case TD_SINGLE_HOLD: register_code16(KC_LGUI); break; // Left CMD/Super/Windows key
        case TD_DOUBLE_HOLD: register_code16(KC_ENT);  break; // Enter
        case TD_TRIPLE_TAP:        tap_code16(KC_SPC);             // fallthru
        case TD_DOUBLE_TAP:                                        // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_SPC);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_SPC); break; // Space
        default: break;
    }
}

// Release any keys pressed by TD_SPC and reset the state
void spc_reset(tap_dance_state_t *state, void *user_data) {
    switch (spc_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_ENT);  break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(KC_SPC); break;
        default: break;
    }
    spc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PLUS              + - / * ×
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PLUS quad tap dance.
static td_tap_t plus_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_PLUS
void plus_finished(tap_dance_state_t *state, void *user_data) {
    plus_tap_state.state = cur_dance(state);
    switch (plus_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_MINS);          break; // `-`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_MULTIPLY); break; // `×`
        case TD_SINGLE_HOLD: register_code16(KC_ASTR);          break; // `*`
        case TD_DOUBLE_HOLD: register_code16(KC_SLSH);          break; // `/`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PLUS);                // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_PLUS);          break; // `+`
        default: break;
    }
}

// Release any keys pressed by TD_PLUS and reset the state
void plus_reset(tap_dance_state_t *state, void *user_data) {
    switch (plus_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_MINS); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_ASTR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_SLSH); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PLUS); break;
        default: break;
    }
    plus_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_LPRN                ( [ { <
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_LPRN (left paren) quad tap dance.
static td_tap_t lprn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_LPRN
void lprn_finished(tap_dance_state_t *state, void *user_data) {
    lprn_tap_state.state = cur_dance(state);
    switch (lprn_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_LBRC); break; // `[`
        case TD_SINGLE_HOLD: register_code16(KC_LCBR); break; // `{`
        case TD_DOUBLE_HOLD: register_code16(KC_LT);   break; // `<`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LPRN);       // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_LPRN); break; // `(`
        default: break;
    }
}

// Release any keys pressed by TD_LPRN and reset the state
void lprn_reset(tap_dance_state_t *state, void *user_data) {
    switch (lprn_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LCBR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LPRN); break;
        default: break;
    }
    lprn_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_RPRN                ) ] > }
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_RPRN (right paren) quad tap dance.
static td_tap_t rprn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_RBRC
void rprn_finished(tap_dance_state_t *state, void *user_data) {
    rprn_tap_state.state = cur_dance(state);
    switch (rprn_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_RBRC); break; // `]`
        case TD_SINGLE_HOLD: register_code16(KC_RCBR); break; // `}`
        case TD_DOUBLE_HOLD: register_code16(KC_GT);   break; // `>`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RPRN);       // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_RPRN); break; // `)`
        default: break;
    }
}

// Release any keys pressed by TD_RPRN and reset the state
void rprn_reset(tap_dance_state_t *state, void *user_data) {
    switch (rprn_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RCBR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_GT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RPRN); break;
        default: break;
    }
    rprn_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_LBRC              [ ( { < ≤
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_LBRC (left bracket) quad tap dance.
static td_tap_t lbrc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_LBRC
void lbrc_finished(tap_dance_state_t *state, void *user_data) {
    lbrc_tap_state.state = cur_dance(state);
    switch (lbrc_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_LPRN);     break; // `(`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_LTE); break; // `≤`
        case TD_SINGLE_HOLD: register_code16(KC_LT);       break; // `<`
        case TD_DOUBLE_HOLD: register_code16(KC_LCBR);     break; // `{`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC);           // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_LBRC);     break; // `[`
        default: break;
    }
}

// Release any keys pressed by TD_LBRC and reset the state
void lbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (lbrc_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LCBR); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
        default: break;
    }
    lbrc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_RBRC                ] ) } >
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_RBRC (right bracket) quad tap dance.
static td_tap_t rbrc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_RBRC
void rbrc_finished(tap_dance_state_t *state, void *user_data) {
    rbrc_tap_state.state = cur_dance(state);
    switch (rbrc_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_RPRN);     break; // `)`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_GTE); break; // `≤`
        case TD_SINGLE_HOLD: register_code16(KC_GT);       break; // `>`
        case TD_DOUBLE_HOLD: register_code16(KC_RCBR);     break; // `}`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC);           // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_RBRC);     break; // `]`
        default: break;
    }
}

// Release any keys pressed by TD_RBRC and reset the state
void rbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (rbrc_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GT);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_RCBR); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
        default: break;
    }
    rbrc_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_TAB                     ⇥ ⇤
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_TAB tap and hold dance.
static td_tap_t tab_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_TAB
void tab_finished(tap_dance_state_t *state, void *user_data) {
    tab_tap_state.state = cur_dance(state);
    switch (tab_tap_state.state) {
        case TD_SINGLE_HOLD: register_code16(S(KC_TAB)); break; // ⇤ Shift+Tab (Reverse Tab)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_TAB);          // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_TAB);    break; // ⇥ Tab
        default: break;
    }
}

// Release any keys pressed by TD_TAB and reset the state
void tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (tab_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(S(KC_TAB)); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
        default: break;
    }
    tab_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_U                  u _LOWER
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_U tap, tap+hold, and hold dance
static td_tap_t u_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or layer for TD_U
void u_finished(tap_dance_state_t *state, void *user_data) {
    u_tap_state.state = cur_dance(state);
    switch (u_tap_state.state) {
        case TD_SINGLE_HOLD: layer_invert(_LOWER); break; // Momentary hold Numpad layer
        case TD_DOUBLE_HOLD: layer_on(_LOWER);     break; // "Lock" Numpad layer
        case TD_TRIPLE_TAP:        tap_code16(KC_U);             // fallthru
        case TD_DOUBLE_TAP:                                      // `uu`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_U);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_U); break; // `u`
        default: break;
    }
}

// Release any keys pressed by TD_U and reset the state
void u_reset(tap_dance_state_t *state, void *user_data) {
    switch (u_tap_state.state) {
        case TD_SINGLE_HOLD: layer_off(_LOWER); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(KC_U); break;
        default: break;
    }
    u_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_C                  c _UPPER
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_C tap, tap+hold, and hold dance
static td_tap_t c_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or layer for TD_C
void c_finished(tap_dance_state_t *state, void *user_data) {
    c_tap_state.state = cur_dance(state);
    switch (c_tap_state.state) {
        case TD_SINGLE_HOLD: layer_invert(_UPPER);  break; // Momentary hold Primary Number layer
        case TD_DOUBLE_HOLD: layer_on(_UPPER);      break; // "Lock" Primary Number layer
        case TD_TRIPLE_TAP:        tap_code16(KC_C);             // `ccc` fallthru
        case TD_DOUBLE_TAP:                                      // `cc` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_C);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_C); break; // `c`
        default: break;
    }
}

// Release any keys pressed by TD_C and reset the state
void c_reset(tap_dance_state_t *state, void *user_data) {
    switch (c_tap_state.state) {
        case TD_SINGLE_HOLD: layer_off(_UPPER); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_C); break;
        default: break;
    }
    c_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CARET                ^  ¢ $
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CARET tap dances
static td_tap_t caret_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_CARET
void caret_finished(tap_dance_state_t *state, void *user_data) {
    caret_tap_state.state = cur_dance(state);
    switch (caret_tap_state.state) {
        case TD_SINGLE_HOLD: register_code16(KC_DLR);       break;  // `$`
        case TD_DOUBLE_HOLD: special_char_macro(CHAR_CENT); break;  // `¢`
        case TD_TRIPLE_TAP:        tap_code16(KC_CIRC);             // `^^^` fallthru
        case TD_DOUBLE_TAP:                                         // `^^` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_CIRC);             // fallthru
        case TD_SINGLE_TAP:        register_code16(KC_CIRC); break; // `^`
        default: break;
    }
}

// Release any keys pressed by TD_CARET and reset the state
void caret_reset(tap_dance_state_t *state, void *user_data) {
    switch (caret_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_DLR);  break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_CIRC); break;
        default: break;
    }
    caret_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CIRC                ◌̂ ◌̄ ◌̆ ◌̌
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CIRC quad tap dance
static td_tap_t circ_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or layer for TD_CIRC
void circ_finished(tap_dance_state_t *state, void *user_data) {
    circ_tap_state.state = cur_dance(state);
    switch (circ_tap_state.state) {
        case TD_DOUBLE_TAP: // `◌̄` (combining macron)
            special_char_macro(CHAR_COMB_MACRON);
            break;
        case TD_SINGLE_HOLD: // `◌̌` (combining caron)
            special_char_macro(CHAR_COMB_CARON);
            break;
        case TD_DOUBLE_HOLD: // `◌̆` (combining breve)
            special_char_macro(CHAR_COMB_BREVE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            special_char_macro(CHAR_COMB_CIRCUMFLEX);
        case TD_SINGLE_TAP: // `◌̂` (combining circumflex)
            special_char_macro(CHAR_COMB_CIRCUMFLEX);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_CIRC and reset the state
void circ_reset(tap_dance_state_t *state, void *user_data) {
    circ_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_SMART_QUOTES
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SMART_QUOTES tap dances
static td_tap_t smart_quotes_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbols for TD_SMART_QUOTES
void smart_quotes_finished(tap_dance_state_t *state, void *user_data) {
    smart_quotes_tap_state.state = cur_dance(state);
    switch (smart_quotes_tap_state.state) {
        case TD_SINGLE_TAP:  surround_macro(SUR_SMART_DQUO); break; // “|”
        case TD_SINGLE_HOLD: surround_macro(SUR_SMART_QUOT); break; // ‘|’
        default: break;
    }
}

// Release any keys pressed by TD_SMART_QUOTES and reset the state
void smart_quotes_reset(tap_dance_state_t *state, void *user_data) {
    smart_quotes_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_ANGLE_QUOTES
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_ANGLE_QUOTES tap dances
static td_tap_t angle_quotes_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbols for TD_ANGLE_QUOTES
void angle_quotes_finished(tap_dance_state_t *state, void *user_data) {
    angle_quotes_tap_state.state = cur_dance(state);
    switch (angle_quotes_tap_state.state) {
        case TD_SINGLE_TAP:  surround_macro(SUR_ANGLE_DQUO); break; // «|»
        case TD_SINGLE_HOLD: surround_macro(SUR_ANGLE_QUOT); break; // ‹|›
        default: break;
    }
}

// Release any keys pressed by TD_ANGLE_QUOTES and reset the state
void angle_quotes_reset(tap_dance_state_t *state, void *user_data) {
    angle_quotes_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DLR                 $ ¥ £ €
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DLR quad tap dances
static td_tap_t dlr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_DLR
void dlr_finished(tap_dance_state_t *state, void *user_data) {
    dlr_tap_state.state = cur_dance(state);
    switch (dlr_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_DLR); break; // `$`
        case TD_DOUBLE_TAP: // `¥`
            special_char_macro(CHAR_YEN);
            break;
        case TD_SINGLE_HOLD: // `€`
            special_char_macro(CHAR_EURO);
            break;
        case TD_DOUBLE_HOLD: // `£` (British Pound)
            special_char_macro(CHAR_POUND);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DLR); register_code16(KC_DLR); break;
        default: break;
    }
}

// Release any keys pressed by TD_DLR and reset the state
void dlr_reset(tap_dance_state_t *state, void *user_data) {
    switch (dlr_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_DLR); break;
        default: break;
    }
    dlr_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_DOT               . … ⋮ • ·
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DOT quad tap dances
static td_tap_t dot_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_DOT
void dot_finished(tap_dance_state_t *state, void *user_data) {
    dot_tap_state.state = cur_dance(state);
    switch (dot_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_DOT); break; // `.`
        case TD_DOUBLE_TAP: // `…` (horizontal ellipsis)
            special_char_macro(CHAR_ELLIPSIS);
            break;
        case TD_TRIPLE_TAP: // `·` (centered dot)
            special_char_macro(CHAR_CENTER_DOT);
            break;
        case TD_SINGLE_HOLD: // `•`
            special_char_macro(CHAR_BULLET);
            break;
        case TD_DOUBLE_HOLD: // `⋮` (vertical ellipsis)
            special_char_macro(CHAR_VERT_ELLIPSIS);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
        default: break;
    }
}

// Release any keys pressed by TD_DOT and reset the state
void dot_reset(tap_dance_state_t *state, void *user_data) {
    switch (dot_tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
        default: break;
    }
    dot_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_CAPS
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_CAPS quad tap dances
static td_tap_t caps_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_CAPS
void caps_finished(tap_dance_state_t *state, void *user_data) {
    caps_tap_state.state = cur_dance(state);
    switch (caps_tap_state.state) {
#ifdef CAPS_WORD_ENABLE
        case TD_SINGLE_TAP:  caps_word_on(); break;
#endif
        case TD_SINGLE_HOLD: tap_code(KC_CAPS); break;
        default: break;
    }
}

// Release any keys pressed by TD_CAPS and reset the state
void caps_reset(tap_dance_state_t *state, void *user_data) {
    caps_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_AT
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_AT quad tap dances
static td_tap_t at_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_AT
void at_finished(tap_dance_state_t *state, void *user_data) {
    at_tap_state.state = cur_dance(state);
    switch (at_tap_state.state) {
        case TD_SINGLE_TAP:  tap_code16(KC_AT); break;
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD:
            // Toggle leader history or favorites on number keys
            toggle_leader_replay_favorites();
            break;
        case TD_DOUBLE_HOLD:
            toggle_leader_replay();
            break;
#endif
        default: break;
    }
}

// Release any keys pressed by TD_AT and reset the state
void at_reset(tap_dance_state_t *state, void *user_data) {
    at_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Number Key Function Key Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_0       0  Leader History 0
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_0 tap dances
static td_tap_t zero_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_0
void zero_finished(tap_dance_state_t *state, void *user_data) {
    zero_tap_state.state = cur_dance(state);
    switch (zero_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(0);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(0); break;
#endif
        case TD_TRIPLE_TAP:
            tap_code(KC_0);
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_0);
        case TD_SINGLE_TAP:
            tap_code(KC_0);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_0 and reset the state
void zero_reset(tap_dance_state_t *state, void *user_data) {
    zero_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_1       1  Leader History 1
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_1 tap dances
static td_tap_t one_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_1
void one_finished(tap_dance_state_t *state, void *user_data) {
    one_tap_state.state = cur_dance(state);
    switch (one_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(1);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(1); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_1);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_1);
        case TD_SINGLE_TAP:        tap_code(KC_1); break;
        default: break;
    }
}

// Release any keys pressed by TD_1 and reset the state
void one_reset(tap_dance_state_t *state, void *user_data) {
    one_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_2       2  Leader History 2
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_2 tap dances
static td_tap_t two_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_2
void two_finished(tap_dance_state_t *state, void *user_data) {
    two_tap_state.state = cur_dance(state);
    switch (two_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(2);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(2); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_2);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_2);
        case TD_SINGLE_TAP:        tap_code(KC_2); break;
        default: break;
    }
}

// Release any keys pressed by TD_2 and reset the state
void two_reset(tap_dance_state_t *state, void *user_data) {
    two_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_3       3  Leader History 3
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_3 tap dances
static td_tap_t three_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_3
void three_finished(tap_dance_state_t *state, void *user_data) {
    three_tap_state.state = cur_dance(state);
    switch (three_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(3);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(3); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_3);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_3);
        case TD_SINGLE_TAP:        tap_code(KC_3); break;
        default: break;
    }
}

// Release any keys pressed by TD_3 and reset the state
void three_reset(tap_dance_state_t *state, void *user_data) {
    three_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_4       4  Leader History 4
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_4 tap dances
static td_tap_t four_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_4
void four_finished(tap_dance_state_t *state, void *user_data) {
    four_tap_state.state = cur_dance(state);
    switch (four_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(4);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(4); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_4);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_4);
        case TD_SINGLE_TAP:        tap_code(KC_4); break;
        default: break;
    }
}

// Release any keys pressed by TD_4 and reset the state
void four_reset(tap_dance_state_t *state, void *user_data) {
    four_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_5       5  Leader History 5
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_5 tap dances
static td_tap_t five_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_5
void five_finished(tap_dance_state_t *state, void *user_data) {
    five_tap_state.state = cur_dance(state);
    switch (five_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(5);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(5); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_5);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_5);
        case TD_SINGLE_TAP:        tap_code(KC_5); break;
        default: break;
    }
}

// Release any keys pressed by TD_5 and reset the state
void five_reset(tap_dance_state_t *state, void *user_data) {
    five_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_6       6  Leader History 6
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_6 tap dances
static td_tap_t six_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_6
void six_finished(tap_dance_state_t *state, void *user_data) {
    six_tap_state.state = cur_dance(state);
    switch (six_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(6);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(6); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_6);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_6);
        case TD_SINGLE_TAP:        tap_code(KC_6); break;
        default: break;
    }
}

// Release any keys pressed by TD_6 and reset the state
void six_reset(tap_dance_state_t *state, void *user_data) {
    six_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_7       7  Leader History 7
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_7 tap dances
static td_tap_t seven_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_7
void seven_finished(tap_dance_state_t *state, void *user_data) {
    seven_tap_state.state = cur_dance(state);
    switch (seven_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(7);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(7); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_7);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_7);
        case TD_SINGLE_TAP:        tap_code(KC_7); break;
        default: break;
    }
}

// Release any keys pressed by TD_7 and reset the state
void seven_reset(tap_dance_state_t *state, void *user_data) {
    seven_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_8       8  Leader History 8
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_8 tap dances
static td_tap_t eight_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_8
void eight_finished(tap_dance_state_t *state, void *user_data) {
    eight_tap_state.state = cur_dance(state);
    switch (eight_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(8);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(8); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_8);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_8);
        case TD_SINGLE_TAP:        tap_code(KC_8); break;
        default: break;
    }
}

// Release any keys pressed by TD_8 and reset the state
void eight_reset(tap_dance_state_t *state, void *user_data) {
    eight_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_9       9  Leader History 9
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_9 tap dances
static td_tap_t nine_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_9
void nine_finished(tap_dance_state_t *state, void *user_data) {
    nine_tap_state.state = cur_dance(state);
    switch (nine_tap_state.state) {
#ifdef LEADER_ENABLE
        case TD_SINGLE_HOLD: replay_leader(9);         break;
        case TD_DOUBLE_HOLD: save_leader_favorites(9); break;
#endif
        case TD_TRIPLE_TAP:        tap_code(KC_9);
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_9);
        case TD_SINGLE_TAP:        tap_code(KC_9); break;
        default: break;
    }
}

// Release any keys pressed by TD_9 and reset the state
void nine_reset(tap_dance_state_t *state, void *user_data) {
    nine_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Navigation Key Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_HOME                ⇱ ^ h ←
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_HOME quad tap dance.
static td_tap_t home_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_HOME
void home_finished(tap_dance_state_t *state, void *user_data) {
    home_tap_state.state = cur_dance(state);
    switch (home_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_CIRC);            break; // `^` (Circumflex)
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_LEFT); break; // `→` (symbol)
        case TD_SINGLE_HOLD: register_code16(KC_LEFT);            break; // Left Arrow
        case TD_DOUBLE_HOLD: register_code16(KC_H);               break; // `h` (Vim left motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_HOME);                  // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_HOME);            break; // Home
        default: break;
    }
}

// Release any keys pressed by TD_HOME and reset the state
void home_reset(tap_dance_state_t *state, void *user_data) {
    switch (home_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_CIRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LEFT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_H);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_HOME); break;
        default: break;
    }
    home_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PGDN                ⇟ } j ↓
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PGDN quad tap dance.
static td_tap_t pgdn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_PGDN
void pgdn_finished(tap_dance_state_t *state, void *user_data) {
    pgdn_tap_state.state = cur_dance(state);
    switch (pgdn_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_RCBR); break;            // `}`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_DOWN); break; // `↓` (symbol)
        case TD_SINGLE_HOLD: register_code16(KC_DOWN); break;            // Down Arrow
        case TD_DOUBLE_HOLD: register_code16(KC_J);    break;            // `j` (Vim left motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PGDN);                  // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_PGDN); break;            // Page Down
        default: break;
    }
}

// Release any keys pressed by TD_PGDN and reset the state
void pgdn_reset(tap_dance_state_t *state, void *user_data) {
    switch (pgdn_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RCBR); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_DOWN); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_J);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PGDN); break;
        default: break;
    }
    pgdn_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_PGUP                ⇞ { k ↑
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_PGUP quad tap dance.
static td_tap_t pgup_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_PGUP
void pgup_finished(tap_dance_state_t *state, void *user_data) {
    pgup_tap_state.state = cur_dance(state);
    switch (pgup_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_LCBR);          break; // `{`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_UP); break; // `↑` (symbol)
        case TD_SINGLE_HOLD: register_code16(KC_UP);            break; // Up Arrow
        case TD_DOUBLE_HOLD: register_code16(KC_K);             break; // `k` (Vim up motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PGUP);                // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_PGUP);          break; // Page Up
        default: break;
    }
}

// Release any keys pressed by TD_PGUP and reset the state
void pgup_reset(tap_dance_state_t *state, void *user_data) {
    switch (pgup_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_UP);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_K);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PGUP); break;
        default: break;
    }
    pgup_tap_state.state = TD_NONE;
}

// ──────────────────────────────
// TD_END                 ⇲ $ l →
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_END quad tap dance.
static td_tap_t end_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol or navigation key for TD_END
void end_finished(tap_dance_state_t *state, void *user_data) {
    end_tap_state.state = cur_dance(state);
    switch (end_tap_state.state) {
        case TD_DOUBLE_TAP:  register_code16(KC_DLR);              break; // `$`
        case TD_TRIPLE_TAP:  special_char_macro(CHAR_ARROW_RIGHT); break; // `→` (symbol)
        case TD_SINGLE_HOLD: register_code16(KC_RGHT);             break; // Right Arrow
        case TD_DOUBLE_HOLD: register_code16(KC_L);                break; // `l` (Vim right motion)
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_END);                    // fallthru
        case TD_SINGLE_TAP:  register_code16(KC_END);              break; // End
        default: break;
    }
}

// Release any keys pressed by TD_END and reset the state
void end_reset(tap_dance_state_t *state, void *user_data) {
    switch (end_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_DLR);  break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RGHT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_L);    break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_END); break;
        default: break;
    }
    end_tap_state.state = TD_NONE;
}
