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

// Create static `u_tap_dance` for TD_U
TD_DEF(u);

// Send the appropriate symbol or layer for TD_U
void u_finished(tap_dance_state_t *state, void *user_data) {
    //u_tap_dance.state = cur_dance(state);
    TD_STATE_SET(u);
    switch (TD_STATE(u)) {
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
    switch (TD_STATE(u)) {
        case TD_SINGLE_HOLD: layer_off(_LOWER); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(KC_U); break;
        default: break;
    }
    TD_RESET(u);
}

// ──────────────────────────────
// TD_C                  c _UPPER
// ──────────────────────────────

// Create static `c_tap_dance` for TD_C
TD_DEF(c);

// Send the appropriate symbol or layer for TD_C
void c_finished(tap_dance_state_t *state, void *user_data) {
    // c_tap_dance.state = cur_dance(state);
    TD_STATE_SET(c);
    switch (TD_STATE(c)) {
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
    switch (TD_STATE(c)) {
        case TD_SINGLE_HOLD: layer_off(_UPPER); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_C); break;
        default: break;
    }
    TD_RESET(c);
}

// ─────────────────────────────────────────────────────────────
//  Char Key Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_ASTR              * % @ # ×
// ──────────────────────────────

// Create static `astr_tap_dance` for TD_ASTR
TD_DEF(astr);

// Send the appropriate symbol for TD_ASTR
void astr_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(astr);
    switch (TD_STATE(astr)) {
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
    switch (TD_STATE(astr)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_PERC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_HASH); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_AT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PAST); break;
        default: break;
    }
    TD_RESET(astr);
}

// ──────────────────────────────
// TD_AT
// ──────────────────────────────

// Create static `at_tap_dance` for TD_AT
TD_DEF(at);

// Send the appropriate symbol for TD_AT
void at_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(at);
    switch (TD_STATE(at)) {
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
    TD_RESET(at);
}

// ──────────────────────────────
// TD_CARET                ^  ¢ $
// ──────────────────────────────

// Create static `caret_tap_dance` for TD_CARET
TD_DEF(caret);

// Send the appropriate symbol for TD_CARET
void caret_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(caret);
    switch (TD_STATE(caret)) {
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
    switch (TD_STATE(caret)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_DLR); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_CIRC); break;
        default: break;
    }
    TD_RESET(caret);
}

// ──────────────────────────────
// TD_CIRC                ◌̂ ◌̄ ◌̆ ◌̌
// ──────────────────────────────

// Create static `circ_tap_dance` for TD_CIRC
TD_DEF(circ);

// Send the appropriate symbol or layer for TD_CIRC
void circ_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(circ);
    switch (TD_STATE(circ)) {
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
    TD_RESET(circ);
}

// ──────────────────────────────
// TD_COMM                , ; | &
// ──────────────────────────────

// Create static `comm_tap_dance` for TD_COMM
TD_DEF(comm);

// Send the appropriate symbol for TD_COMM
void comm_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(comm);
    switch (TD_STATE(comm)) {
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
    switch (TD_STATE(comm)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_AMPR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_PIPE); break;
        case TD_TRIPLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_SINGLE_TAP:  unregister_code16(KC_COMM); break;
        default: break;
    }
    TD_RESET(comm);
}

// ──────────────────────────────
// TD_DLR                 $ ¥ £ €
// ──────────────────────────────

// Create static `dlr_tap_dance` for TD_DLR
TD_DEF(dlr);

// Send the appropriate symbol for TD_DLR
void dlr_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(dlr);
    switch (TD_STATE(dlr)) {
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
    switch (TD_STATE(dlr)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_DLR); break;
        default: break;
    }
    TD_RESET(dlr);
}

// ──────────────────────────────
// TD_DOT          . … ⋮ LCTL/• ·
// ──────────────────────────────

// Create static `dlr_tap_dance` for TD_DOT
static td_tap_t dot_tap_dance = {
    .layer_origin = _BASE,
    .is_press_action = true,
    .state = TD_NONE
};

// Send the appropriate symbol for TD_DOT
void dot_finished(tap_dance_state_t *state, void *user_data) {
    dot_tap_dance.layer_origin = get_highest_layer(layer_state);
    dot_tap_dance.state = cur_dance(state);
    switch (TD_STATE(dot)) {
        case TD_DOUBLE_TAP:  // `…` (horizontal ellipsis)
            special_char_macro(CHAR_ELLIPSIS);
            break;
        case TD_TRIPLE_TAP:  // `·` (centered dot)
            special_char_macro(CHAR_CENTER_DOT);
            break;
        case TD_SINGLE_HOLD: // LCTL on _BASE or `•`
            if (dot_tap_dance.layer_origin == _BASE) {
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
    switch (TD_STATE(dot)) {
        case TD_SINGLE_HOLD:
            if (dot_tap_dance.layer_origin == _BASE) {
                unregister_code(KC_LCTL);
            }
            break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PDOT); break;
        default: break;
    }
    TD_RESET(dot);
}

// ──────────────────────────────
// TD_DQUO                " ‘ < >
// ──────────────────────────────

// Create static `dquo_tap_dance` for TD_DQUO
TD_DEF(dquo);

// Send the appropriate symbol for TD_DQUO
void dquo_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(dquo);
    switch (TD_STATE(dquo)) {
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
    switch (TD_STATE(dquo)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_GT); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_DQUO); break;
        default: break;
    }
    TD_RESET(dquo);
}

// ──────────────────────────────
// TD_EQL                 =   ≈ ≠
// ──────────────────────────────

// Create static `eql_tap_dance` for TD_EQL
TD_DEF(eql);

// Send the appropriate symbol for TD_EQL
void eql_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(eql);
    switch (TD_STATE(eql)) {
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
    switch (TD_STATE(eql)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_PEQL); break;
        default: break;
    }
    TD_RESET(eql);
}

// ──────────────────────────────
// TD_EXLM Cross Platform ! ¡ ◌̃ ◌̈
// ──────────────────────────────

// Create static `exlm_tap_dance` for TD_EXLM
TD_DEF(exlm);

// Send the appropriate symbol for TD_EXLM
void exlm_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(exlm);
    switch (TD_STATE(exlm)) {
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
    switch (TD_STATE(exlm)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_EXLM); break;
        default: break;
    }
    TD_RESET(exlm);
}

// ──────────────────────────────
// TD_MINS                -   – —
// ──────────────────────────────

// Create static `mins_tap_dance` for TD_MINS
TD_DEF(mins);

// Send the appropriate symbol for TD_MINS
void mins_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(mins);
    switch (TD_STATE(mins)) {
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
    switch (TD_STATE(mins)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
            unregister_code16(KC_MINS); break;
        default: break;
    }
    TD_RESET(mins);
}

// ──────────────────────────────
// TD_PLUS              + - / * ×
// ──────────────────────────────

// Create static `plus_tap_dance` for TD_PLUS
TD_DEF(plus);

// Send the appropriate symbol for TD_PLUS
void plus_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(plus);
    switch (TD_STATE(plus)) {
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
    switch (TD_STATE(plus)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_MINS); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_ASTR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_SLSH); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PLUS); break;
        default: break;
    }
    TD_RESET(plus);
}

// ──────────────────────────────
// TD_PUNC space appended , ! ? .
// ──────────────────────────────

// Create static `punc_tap_dance` for TD_PUNC
TD_DEF(punc);

// Send the appropriate symbol for TD_PUNC
void punc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(punc);
    switch (TD_STATE(punc)) {
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
    TD_RESET(punc);
}

// ──────────────────────────────
// TD_QUES Cross Platform ? ¿ ◌̀ ◌́
// ──────────────────────────────

// Create static `ques_tap_dance` for TD_QUES
TD_DEF(ques);

// Send the appropriate symbol for TD_QUES
void ques_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(ques);
    switch (TD_STATE(ques)) {
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
    switch (TD_STATE(ques)) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_QUES); break;
        default: break;
    }
    TD_RESET(ques);
}

// ──────────────────────────────
// TD_QUOT                ' ’ ~ `
// ──────────────────────────────

// Create static `quot_tap_dance` for TD_QUOT
TD_DEF(quot);

// Send the appropriate symbol for TD_QUOT
void quot_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(quot);
    switch (TD_STATE(quot)) {
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
    switch (TD_STATE(quot)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_GRV);  break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_TILD); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP: unregister_code16(KC_QUOT); break;
        default: break;
    }
    TD_RESET(quot);
}

// ──────────────────────────────
// TD_SCLN           ; ;␣ :␣ LSFT
// ──────────────────────────────

// Create static `scln_tap_dance` for TD_SCLN
TD_DEF(scln);

// Send the appropriate symbol for TD_SLCN
void scln_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(scln);
    switch (TD_STATE(scln)) {
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
    switch (TD_STATE(scln)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(KC_SCLN); break;
        default: break;
    }
    TD_RESET(scln);
}

// ──────────────────────────────
// TD_SPC                 ␣   ↵ ⌘
// ──────────────────────────────

TD_DEF(spc);

// Send the appropriate symbol for TD_SPC
void spc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(spc);
    uint16_t spc_transformed = case_mode_separator(KC_SPC);
    switch (TD_STATE(spc)) {
        case TD_DOUBLE_TAP:
            auto_cap_next_char_only();
            break;
        case TD_SINGLE_HOLD: // Left CMD/Super/Windows key
            register_and_update(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD: // `↵`
            register_and_update(KC_ENT);
            break;
        case TD_TRIPLE_TAP:        tap_code16(spc_transformed); // fallthru
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
    switch (TD_STATE(spc)) {
        case TD_SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_ENT);  break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:  unregister_code16(spc_transformed); break;
        default: break;
    }
    TD_RESET(spc);
}

// ─────────────────────────────────────────────────────────────
// Cursor-Centered Quote Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_SMART_QUOTES
// ──────────────────────────────

// Create static `smart_quotes_tap_dance` for TD_SMART_QUOTES
TD_DEF(smart_quotes);

// Send the appropriate symbols for TD_SMART_QUOTES
void smart_quotes_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(smart_quotes);
    switch (TD_STATE(smart_quotes)) {
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
    TD_RESET(smart_quotes);
}

// ──────────────────────────────
// TD_ANGLE_QUOTES
// ──────────────────────────────

// Create static `angle_quotes_tap_dance` for TD_ANGLE_QUOTES
TD_DEF(angle_quotes);

// Send the appropriate symbols for TD_ANGLE_QUOTES
void angle_quotes_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(angle_quotes);
    switch (TD_STATE(angle_quotes)) {
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
    TD_RESET(angle_quotes);
}

// ─────────────────────────────────────────────────────────────
// Paired Symbol Function Definitions
// ─────────────────────────────────────────────────────────────

// ──────────────────────────────
// TD_LPRN                ( [ { <
// ──────────────────────────────

// Create static `lprn_tap_dance` for TD_LPRN
TD_DEF(lprn);

// Send the appropriate symbol for TD_LPRN
void lprn_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(lprn);
    switch (TD_STATE(lprn)) {
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
    switch (TD_STATE(lprn)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LCBR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_TRIPLE_TAP:
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LPRN); break;
        default: break;
    }
    TD_RESET(lprn);
}
// ──────────────────────────────
// TD_RPRN                ) ] > }
// ──────────────────────────────

// Create static `rprn_tap_dance` for TD_RPRN
TD_DEF(rprn);

// Send the appropriate symbol for TD_RBRC
void rprn_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(rprn);
    switch (TD_STATE(rprn)) {
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
    switch (TD_STATE(rprn)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RCBR); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_GT);   break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RPRN); break;
        default: break;
    }
    TD_RESET(rprn);
}

// ──────────────────────────────
// TD_LBRC              [ ( { < ≤
// ──────────────────────────────

// Create static `lbrc_tap_dance` for TD_LBRC
TD_DEF(lbrc);

// Send the appropriate symbol for TD_LBRC
void lbrc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(lbrc);
    switch (TD_STATE(lbrc)) {
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
    switch (TD_STATE(lbrc)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LT);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_LCBR); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
        default: break;
    }
    TD_RESET(lbrc);
}

// ──────────────────────────────
// TD_RBRC              ] ) } > ≥
// ──────────────────────────────

// Create static `rbrc_tap_dance` for TD_RBRC
TD_DEF(rbrc);

// Send the appropriate symbol for TD_RBRC
void rbrc_finished(tap_dance_state_t *state, void *user_data) {
    TD_STATE_SET(rbrc);
    switch (TD_STATE(rbrc)) {
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
    switch (TD_STATE(rbrc)) {
        case TD_DOUBLE_TAP:  unregister_code16(KC_RPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GT);   break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_RCBR); break;
        case TD_SINGLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
        default: break;
    }
    TD_RESET(rbrc);
}
