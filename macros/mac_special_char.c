#include "mac_special_char.h"
#include "custom_keys.h"
#include "keymap.h"
#include "macros.h"

// Opens macOS Emoji Menu to input vertical ellipsis (⋮)
// NOTE: Vertical ellipsis not available via keyboard shortcut
static void macos_vertical_ellipsis(void) {
    tap_code16(MACOS_EMOJI_MENU);
    wait_ms(MACOS_EMOJI_MENU_DELAY);
    SEND_STRING("vertical ellipsis");
    wait_ms(MACOS_EMOJI_MENU_INPUT_DELAY);
    tap_code(KC_DOWN);
    tap_code(KC_ENT);
}

// Apple macOS special characters such as `¿`, `€`, and combining symbols `◌́`, etc.
// NOTE: macOS doesn't accept raw Unicode via HID. The shortcuts set assume the operating system
// is set to U.S. layout.
static void special_char_macos(const special_char_t special_char) {
    mod_state_t saved = mod_state_save_and_clear();

    switch(special_char) {
        case CHAR_INV_QUES: // Spanish inverted question mark `¿`// Spanish `¿`
            tap_code16(A(S(KC_SLSH)));
            break;
        case CHAR_INV_EXLM: // Spanish inverted exclamation mark `¡`
            tap_code16(A(KC_1));
            break;
        case CHAR_COMB_ACUTE: // Combining acute accent (◌́)
            tap_code16(A(KC_E));
            break;
        case CHAR_COMB_GRAVE: // Combining grave symbol (◌̀)
            tap_code16(A(KC_GRV));
            break;
        case CHAR_COMB_TILDE: // Combining tilde symbol (◌̃)
            tap_code16(A(KC_N));
            break;
        case CHAR_COMB_UMLAUT: // Combining umlaut symbol (◌̈)
            tap_code16(A(KC_U));
            break;
        case CHAR_CENT: // Cent symbol (¢)
            tap_code16(A(KC_4));
            break;
        case CHAR_EURO: // Euro pound symbol (€)
            tap_code16(A(S(KC_2)));
            break;
        case CHAR_POUND: // British pound symbol (£)
            tap_code16(A(KC_3));
            break;
        case CHAR_YEN: // Yen/yuan symbol (¥)
            tap_code16(A(KC_Y));
            break;
        case CHAR_DEGREE: // Degree symbol (°)
            tap_code16(A(S(KC_8)));
            break;
        case CHAR_EN_DASH: // En dash (–)
            tap_code16(A(KC_MINS));
            break;
        case CHAR_EM_DASH: // Em dash (—)
            tap_code16(A(S(KC_MINS)));
            break;
        case CHAR_NEQ: // Inequality (≠)
            tap_code16(A(KC_EQL));
            break;
        case CHAR_APPROX: // Approximation (≈)
            tap_code16(A(KC_X));
            break;
        case CHAR_BULLET: // Bullet (•)
            tap_code16(A(KC_8)); // Might not work on other inputs than U.S.
            break;
        case CHAR_ELLIPSIS: // Horizontal ellipsis (…)
            tap_code16(A(KC_SCLN));
            break;
        case CHAR_VERT_ELLIPSIS: // Vertical ellipsis (⋮)
            macos_vertical_ellipsis();
            break;
        case CHAR_SMART_QUOTE_LEFT: // Smart single quote open (‘)
            tap_code16(A(KC_RBRC));
            break;
        case CHAR_SMART_QUOTE_RIGHT: // Smart single quote close (’)
            tap_code16(A(S(KC_RBRC)));
            break;
        case CHAR_SMART_DQUOTE_LEFT: // Smart double quote open (“)
            tap_code16(A(KC_LBRC));
            break;
        case CHAR_SMART_DQUOTE_RIGHT: // Smart double quote close (”)
            tap_code16(A(S(KC_LBRC)));
            break;
        case CHAR_ANGLE_QUOTE_LEFT: // Left single guillemet (‹)
            tap_code16(A(S(KC_3)));
            break;
        case CHAR_ANGLE_QUOTE_RIGHT: // Right single guillemet (›)
            tap_code16(A(S(KC_4)));
            break;
        case CHAR_ANGLE_DQUOTE_LEFT: // Left double guillemet («)
            tap_code16(A(KC_BSLS));
            break;
        case CHAR_ANGLE_DQUOTE_RIGHT: // Right double guillemet (»)
            tap_code16(A(S(KC_BSLS)));
            break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Special characters such as `¿`, `€`, and combining symbols `◌́`, etc.
// Linux & Microsoft Windows should accept direct Unicode chars via HID.
static void special_char_unicode(const special_char_t special_char) {
    mod_state_t saved = mod_state_save_and_clear();

    switch (special_char) {
        case CHAR_INV_QUES:           SEND_STRING("¿");      break;
        case CHAR_INV_EXLM:           SEND_STRING("¡");      break;
        case CHAR_COMB_ACUTE:         SEND_STRING("\u0301"); break; // Combining acute (◌́)
        case CHAR_COMB_GRAVE:         SEND_STRING("\u0300"); break; // Combining grave (◌̀)
        case CHAR_COMB_TILDE:         SEND_STRING("\u0303"); break; // Combining tilde (◌̃)
        case CHAR_COMB_UMLAUT:        SEND_STRING("\u0308"); break; // Combining umlaut (◌̈)
        case CHAR_CENT:               SEND_STRING("¢");      break;
        case CHAR_EURO:               SEND_STRING("€");      break;
        case CHAR_POUND:              SEND_STRING("£");      break;
        case CHAR_YEN:                SEND_STRING("¥");      break;
        case CHAR_DEGREE:             SEND_STRING("°");      break;
        case CHAR_EN_DASH:            SEND_STRING("–");      break;
        case CHAR_EM_DASH:            SEND_STRING("—");      break;
        case CHAR_NEQ:                SEND_STRING("≠");      break;
        case CHAR_APPROX:             SEND_STRING("≈");      break;
        case CHAR_ELLIPSIS:           SEND_STRING("…");      break;
        case CHAR_VERT_ELLIPSIS:      SEND_STRING("⋮");      break;
        case CHAR_BULLET:             SEND_STRING("•");      break;
        case CHAR_SMART_QUOTE_LEFT:   SEND_STRING("‘");      break;
        case CHAR_SMART_QUOTE_RIGHT:  SEND_STRING("’");      break;
        case CHAR_SMART_DQUOTE_LEFT:  SEND_STRING("“");      break;
        case CHAR_SMART_DQUOTE_RIGHT: SEND_STRING("”");      break;
        case CHAR_ANGLE_QUOTE_LEFT:   SEND_STRING("‹");      break;
        case CHAR_ANGLE_QUOTE_RIGHT:  SEND_STRING("›");      break;
        case CHAR_ANGLE_DQUOTE_LEFT:  SEND_STRING("«");      break;
        case CHAR_ANGLE_DQUOTE_RIGHT: SEND_STRING("»");      break;
        default: break;
    }

    mod_state_restore(&saved);
}

// Various special characters such as `¿`, `€`, and combining symbols `◌́`
void special_char_macro(const special_char_t special_char) {
    (current_os == OS_MACOS) ? special_char_macos(special_char)
                             : special_char_unicode(special_char);
}

// Smart single quotes with cursor placed inside (‘|’)
void smart_single_quotes_macro(void) {
    special_char_macro(CHAR_SMART_QUOTE_LEFT);
    special_char_macro(CHAR_SMART_QUOTE_RIGHT);
    tap_code(KC_LEFT);
}

// Smart double quotes with cursor placed inside (“|”)
void smart_double_quotes_macro(void) {
    special_char_macro(CHAR_SMART_DQUOTE_LEFT);
    special_char_macro(CHAR_SMART_DQUOTE_RIGHT);
    tap_code(KC_LEFT);
}

// Single angle quotes (guillemet) with cursor place inside (‹|›)
void single_angle_quotes_macro(void) {
    special_char_macro(CHAR_ANGLE_QUOTE_LEFT);
    special_char_macro(CHAR_ANGLE_QUOTE_RIGHT);
    tap_code(KC_LEFT);
}

// Double angle quotes (guillemet) with cursor place inside («|»)
void double_angle_quotes_macro(void) {
    special_char_macro(CHAR_ANGLE_QUOTE_LEFT);
    special_char_macro(CHAR_ANGLE_QUOTE_RIGHT);
    tap_code(KC_LEFT);
}
