/*
 * td_chars.c — Tap Dance definitions for symbol and character-entry keys.
 *
 * This module implements tap-dance behaviors for character-producing keys
 * that are not simple alphanumerics. These typically include:
 *   - Punctuation (e.g., ! ? : ; , .)
 *   - Paired symbols (e.g., () [] {})
 *   - Mathematical or programming symbols (e.g., + - * / = < >)
 *   - Special Unicode or macro‑generated characters
 *
 * The goal of this module is to centralize all symbol-entry tap-dance logic
 * so that character behaviors remain consistent, discoverable, and easy to
 * maintain across the keymap.
 */

#include "td_chars.h"
#include "tap_dance_actions.h"
#include "src/core/keymap.h"
#include "src/features/case_mode.h"
#include "src/features/leader.h"
#include "src/macros/mac_programming.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_surround.h"

// ─────────────────────────────────────────────────────────────
// Thumb Key Function Definitions
// ─────────────────────────────────────────────────────────────

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
        case TD_TRIPLE_TAP:        tap_code16(KC_U);      // fallthru
        case TD_DOUBLE_TAP:                               // `uu`
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_U);      // fallthru
        case TD_SINGLE_TAP:                               // `u`
            register_and_update(KC_U);
            break;
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
        case TD_SINGLE_HOLD: layer_invert(_UPPER); break; // Momentary hold Primary Number layer
        case TD_DOUBLE_HOLD: layer_on(_UPPER);     break; // "Lock" Primary Number layer
        case TD_TRIPLE_TAP:        tap_code16(KC_C);      // `ccc` fallthru
        case TD_DOUBLE_TAP:                               // `cc` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_C);      // fallthru
        case TD_SINGLE_TAP:                               // `c`
            register_and_update(KC_C);
            break;
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
        case TD_DOUBLE_TAP: // `%` Vim, normal mode: Jump to matching brace/bracket/etc.
            register_and_update(KC_PERC);
            break;
        case TD_TRIPLE_TAP: // `×` (Unicode multiplication symbol)
            special_char_macro(CHAR_MULTIPLY);
            break;
        case TD_SINGLE_HOLD: // `#` Vim, normal mode: Reverse search word under cursor
            register_and_update(KC_HASH);
            break;
        case TD_DOUBLE_HOLD: // `@` Vim, normal mode: Trigger macro
            register_and_update(KC_AT);
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PAST); // fallthru
        case TD_SINGLE_TAP: // `*` Vim, normal mode: Search word under cursor
            register_and_update(KC_PAST);
            break;
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
        case TD_SINGLE_TAP:
            register_and_update(KC_AT);
            break;
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
        case TD_SINGLE_HOLD: // `$`
            register_and_update(KC_DLR);
            break;
        case TD_DOUBLE_HOLD: // `¢`
            special_char_macro(CHAR_CENT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_CIRC); // `^^^` fallthru
        case TD_DOUBLE_TAP:                             // `^^` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_CIRC); // fallthru
        case TD_SINGLE_TAP: // `^`
            register_and_update(KC_CIRC);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_CARET and reset the state
void caret_reset(tap_dance_state_t *state, void *user_data) {
    switch (caret_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_DLR); break;
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
            special_char_macro(CHAR_COMB_CIRCUMFLEX); // fallthru
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
        case TD_DOUBLE_TAP: // `;`
            register_and_update(KC_SCLN);
            break;
        case TD_SINGLE_HOLD: // `&`
            register_and_update(KC_AMPR);
            break;
        case TD_DOUBLE_HOLD: // `|`
            register_and_update(KC_PIPE);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_COMM); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_COMM); // fallthru
        case TD_SINGLE_TAP: // `,`
            register_and_update(KC_COMM);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_COMM and reset the state
void comm_reset(tap_dance_state_t *state, void *user_data) {
    switch (comm_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_AMPR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_PIPE); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_COMM); break;
        default: break;
    }
    comm_tap_state.state = TD_NONE;
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
        case TD_DOUBLE_TAP: // `¥`
            special_char_macro(CHAR_YEN);
            break;
        case TD_SINGLE_HOLD: // `€`
            special_char_macro(CHAR_EURO);
            break;
        case TD_DOUBLE_HOLD: // `£` (British Pound)
            special_char_macro(CHAR_POUND);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_DLR); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DLR); // fallthru
        case TD_SINGLE_TAP: // `$`
            register_and_update(KC_DLR);
            break;
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
// TD_DOT          . … ⋮ LCTL/• ·
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_DOT quad tap dances
static td_tap_t dot_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_DOT
void dot_finished(tap_dance_state_t *state, void *user_data) {
    dot_tap_state.layer_origin = get_highest_layer(layer_state);
    dot_tap_state.state = cur_dance(state);
    switch (dot_tap_state.state) {
        case TD_DOUBLE_TAP:  // `…` (horizontal ellipsis)
            special_char_macro(CHAR_ELLIPSIS);
            break;
        case TD_TRIPLE_TAP:  // `·` (centered dot)
            special_char_macro(CHAR_CENTER_DOT);
            break;
        case TD_SINGLE_HOLD: // LCTL on _BASE or `•`
            if (dot_tap_state.layer_origin == _BASE) {
                register_and_update(KC_LCTL);
            } else {
                special_char_macro(CHAR_BULLET);
            }
            break;
        case TD_DOUBLE_HOLD: // `⋮` (vertical ellipsis)
            special_char_macro(CHAR_VERT_ELLIPSIS);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PDOT); // fallthru
        case TD_SINGLE_TAP: // `.`
            register_and_update(KC_PDOT);
        default: break;
    }
}

// Release any keys pressed by TD_DOT and reset the state
void dot_reset(tap_dance_state_t *state, void *user_data) {
    switch (dot_tap_state.state) {
        case TD_SINGLE_HOLD:
            if (dot_tap_state.layer_origin == _BASE) {
                unregister_code(KC_LCTL);
            }
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PDOT); break;
        default: break;
    }
    dot_tap_state.state = TD_NONE;
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
        case TD_SINGLE_HOLD: // `>`
            register_and_update(KC_GT);
            break;
        case TD_DOUBLE_HOLD: // `<`
            register_and_update(KC_LT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_DQUO); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_DQUO); // fallthru
        case TD_SINGLE_TAP: // `"`
            register_and_update(KC_DQUO);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_DQUO and reset the state
void dquo_reset(tap_dance_state_t *state, void *user_data) {
    switch (dquo_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_GT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT); break;
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
        case TD_SINGLE_HOLD: // `≠`
            special_char_macro(CHAR_NEQ);
            break;
        case TD_DOUBLE_HOLD: // `≈`
            special_char_macro(CHAR_APPROX);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_PEQL); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PEQL); // fallthru
        case TD_SINGLE_TAP: // `=`
            register_and_update(KC_PEQL);
            break;
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
        case TD_TRIPLE_TAP:        tap_code16(KC_EXLM); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_EXLM); // fallthru
        case TD_SINGLE_TAP: // `!`
            register_and_update(KC_EXLM);
            break;
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
        case TD_SINGLE_HOLD: // `—` (em dash)
            special_char_macro(CHAR_EM_DASH);
            break;
        case TD_DOUBLE_HOLD: // `–` (en dash)
            special_char_macro(CHAR_EN_DASH);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_MINS); // fallthru
        case TD_DOUBLE_TAP:                             // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_MINS); // fallthru
        case TD_SINGLE_TAP: // `-`
            register_and_update(KC_MINS);
            break;
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
        case TD_DOUBLE_TAP: // `-`
            register_and_update(KC_MINS);
            break;
        case TD_TRIPLE_TAP: // `×` (Unicode multiplication symbol)
            special_char_macro(CHAR_MULTIPLY);
            break;
        case TD_SINGLE_HOLD: // `*`
            register_and_update(KC_ASTR);
            break;
        case TD_DOUBLE_HOLD: // `/`
            register_and_update(KC_SLSH);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_PLUS); // fallthru
        case TD_SINGLE_TAP: // `+`
            register_and_update(KC_PLUS);
            break;
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
        case TD_DOUBLE_TAP: // `! ` exclamation-space bigram w/ auto cap
            punc_space_macro(KC_EXLM);
            break;
        case TD_SINGLE_HOLD: // `. ` dot/period-space bigram w/ auto cap
            punc_space_macro(KC_DOT);
            break;
        case TD_DOUBLE_HOLD: // `? ` question-space bigram w/ auto cap
            punc_space_macro(KC_QUES);
            break;
        case TD_DOUBLE_SINGLE_TAP: punc_space_macro(KC_COMM); // fallthru
        case TD_SINGLE_TAP: // `, ` comma-space bigram
            punc_space_macro(KC_COMM);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_PUNC and reset the state
void punc_reset(tap_dance_state_t *state, void *user_data) {
    punc_tap_state.state = TD_NONE;
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
        case TD_TRIPLE_TAP:        tap_code16(KC_QUES); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_QUES); // fallthru
        case TD_SINGLE_TAP: // `?`
            register_and_update(KC_QUES);
            break;
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
        case TD_SINGLE_HOLD: // backtick (`) symbol
            register_and_update(KC_GRV);
            break;
        case TD_DOUBLE_HOLD: // `~`
            register_and_update(KC_TILD);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_QUOT); // `'''` fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_QUOT); // `''` fallthru
        case TD_SINGLE_TAP: // `'`
            register_and_update(KC_QUOT);
            break;
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
// TD_SCLN           ; ;␣ :␣ LSFT
// ──────────────────────────────

// Instance of 'td_tap_t' for the TD_SLCN quad tap dance.
static td_tap_t scln_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_SLCN
void scln_finished(tap_dance_state_t *state, void *user_data) {
    scln_tap_state.state = cur_dance(state);
    switch (scln_tap_state.state) {
        case TD_SINGLE_HOLD: // `LSFT`
            register_and_update(KC_LSFT);
            break;
        case TD_DOUBLE_TAP: // `;␣`
            punc_space_macro(KC_SCLN);
            break;
        case TD_DOUBLE_HOLD: // `:␣`
            punc_space_macro(KC_COLN);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_SCLN); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_SCLN); // fallthru
        case TD_SINGLE_TAP: // `;`
            register_and_update(KC_SCLN);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_SLCN and reset the state
void scln_reset(tap_dance_state_t *state, void *user_data) {
    switch (scln_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(KC_SCLN); break;
        default: break;
    }
    scln_tap_state.state = TD_NONE;
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
    uint16_t spc_transformed = case_mode_separator(KC_SPC);
    switch (spc_tap_state.state) {
        case TD_SINGLE_HOLD: // Left CMD/Super/Windows key
            register_and_update(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD: // `↵`
            register_and_update(KC_ENT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(spc_transformed); // fallthru
        case TD_DOUBLE_TAP:                                     // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(spc_transformed); // fallthru
        case TD_SINGLE_TAP: // `␣`
            register_and_update(spc_transformed);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_SPC and reset the state
void spc_reset(tap_dance_state_t *state, void *user_data) {
    uint16_t spc_transformed = case_mode_separator(KC_SPC);
    switch (spc_tap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_ENT);  break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(spc_transformed); break;
        default: break;
    }
    spc_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Cursor-Centered Quote Function Definitions
// ─────────────────────────────────────────────────────────────

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
        case TD_SINGLE_TAP: // “|”
            surround_macro(SUR_SMART_DQUO);
            break;
        case TD_SINGLE_HOLD: // ‘|’
            surround_macro(SUR_SMART_QUOT);
            break;
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
        case TD_SINGLE_TAP: // «|»
            surround_macro(SUR_ANGLE_DQUO);
            break;
        case TD_SINGLE_HOLD: // ‹|›
            surround_macro(SUR_ANGLE_QUOT);
            break;
        default: break;
    }
}

// Release any keys pressed by TD_ANGLE_QUOTES and reset the state
void angle_quotes_reset(tap_dance_state_t *state, void *user_data) {
    angle_quotes_tap_state.state = TD_NONE;
}

// ─────────────────────────────────────────────────────────────
// Paired Symbol Function Definitions
// ─────────────────────────────────────────────────────────────

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
        case TD_DOUBLE_TAP: // `[`
            register_and_update(KC_LBRC);
            break;
        case TD_SINGLE_HOLD: // `{`
            register_and_update(KC_LCBR);
            break;
        case TD_DOUBLE_HOLD: // `<`
            register_and_update(KC_LT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_LPRN); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LPRN); // fallthru
        case TD_SINGLE_TAP: // `(`
            register_and_update(KC_LPRN); break;
        default: break;
    }
}

// Release any keys pressed by TD_LPRN and reset the state
void lprn_reset(tap_dance_state_t *state, void *user_data) {
    switch (lprn_tap_state.state) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LCBR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_TRIPLE_TAP:
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
        case TD_DOUBLE_TAP: // `]`
            register_and_update(KC_RBRC);
            break;
        case TD_SINGLE_HOLD: // `}`
            register_and_update(KC_RCBR);
            break;
        case TD_DOUBLE_HOLD: // `>`
            register_and_update(KC_GT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(KC_RPRN); // fallthru
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RPRN); // fallthru
        case TD_SINGLE_TAP: // `)`
            register_and_update(KC_RPRN);
            break;
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
        case TD_DOUBLE_TAP: // `(`
            register_and_update(KC_LPRN);
            break;
        case TD_TRIPLE_TAP: // `≤` (Unicode GTE symbol)
            special_char_macro(CHAR_LTE);
            break;
        case TD_SINGLE_HOLD: // `<`
            register_and_update(KC_LT);
            break;
        case TD_DOUBLE_HOLD: // `{`
            register_and_update(KC_LCBR);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); // fallthru
        case TD_SINGLE_TAP: // `[`
            register_and_update(KC_LBRC);
            break;
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
// TD_RBRC              ] ) } > ≥
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
        case TD_DOUBLE_TAP: // `)`
            register_and_update(KC_RPRN);
            break;
        case TD_TRIPLE_TAP: // `≤` (Unicode LTE symbol)
            special_char_macro(CHAR_GTE);
            break;
        case TD_SINGLE_HOLD: // `>`
            register_and_update(KC_GT);
            break;
        case TD_DOUBLE_HOLD: // `}`
            register_and_update(KC_RCBR);
            break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); // fallthru
        case TD_SINGLE_TAP: // `]`
            register_and_update(KC_RBRC);
            break;
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
