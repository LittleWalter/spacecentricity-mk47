#include "utils.h"
#include "case_mode.h"
#include "src/core/keymap.h"

// Returns true if Caps Lock is active.
bool is_caps_lock_on(void) {
    return host_keyboard_led_state().caps_lock;
}

// Ensure Caps Lock is ON.
//
// QMK does not provide direct caps_lock_on/off helpers, so we check the
// host LED state and send a Caps Lock keypress only if needed. This keeps
// firmware and OS state perfectly in sync.
void caps_lock_on(void) {
    if (!is_caps_lock_on()) {
        tap_code(KC_CAPS);
    }
}

// Ensure Caps Lock is OFF.
//
// Same logic as caps_lock_on(): only send KC_CAPS if the OS currently
// reports Caps Lock as active. Prevents double‑toggling or desync.
void caps_lock_off(void) {
    if (is_caps_lock_on()) {
        tap_code(KC_CAPS);
    }
}

// Toggle Caps Lock. Turns off case mode, if active.
void caps_lock_toggle(void) {
    case_mode_off();
    is_caps_lock_on() ? caps_lock_off() : caps_lock_on();
}

// Returns true if any transient lexical mode (Caps Word, Numeric Expression, etc.) is active.
bool is_transient_lexical_mode_on(void) {
#if defined(CAPS_WORD_ENABLE)
    const bool caps_word = is_caps_word_on();
#else
    const bool caps_word = false;
#endif
    return caps_word || is_case_mode_on();
}

// Map QMK keycodes to visible ASCII characters (US layout).
// Returns 0 for non-printable / unsupported.
char keycode_to_ascii(uint16_t keycode, bool shift) {
    switch (keycode) {
        // ── Letters ─────────────────────────────
        case KC_A: return shift ? 'A' : 'a';
        case KC_B: return shift ? 'B' : 'b';
        case KC_C: return shift ? 'C' : 'c';
        case KC_D: return shift ? 'D' : 'd';
        case KC_E: return shift ? 'E' : 'e';
        case KC_F: return shift ? 'F' : 'f';
        case KC_G: return shift ? 'G' : 'g';
        case KC_H: return shift ? 'H' : 'h';
        case KC_I: return shift ? 'I' : 'i';
        case KC_J: return shift ? 'J' : 'j';
        case KC_K: return shift ? 'K' : 'k';
        case KC_L: return shift ? 'L' : 'l';
        case KC_M: return shift ? 'M' : 'm';
        case KC_N: return shift ? 'N' : 'n';
        case KC_O: return shift ? 'O' : 'o';
        case KC_P: return shift ? 'P' : 'p';
        case KC_Q: return shift ? 'Q' : 'q';
        case KC_R: return shift ? 'R' : 'r';
        case KC_S: return shift ? 'S' : 's';
        case KC_T: return shift ? 'T' : 't';
        case KC_U: return shift ? 'U' : 'u';
        case KC_V: return shift ? 'V' : 'v';
        case KC_W: return shift ? 'W' : 'w';
        case KC_X: return shift ? 'X' : 'x';
        case KC_Y: return shift ? 'Y' : 'y';
        case KC_Z: return shift ? 'Z' : 'z';

        // ── Digits ──────────────────────────────
        case KC_1: return shift ? '!' : '1';
        case KC_2: return shift ? '@' : '2';
        case KC_3: return shift ? '#' : '3';
        case KC_4: return shift ? '$' : '4';
        case KC_5: return shift ? '%' : '5';
        case KC_6: return shift ? '^' : '6';
        case KC_7: return shift ? '&' : '7';
        case KC_8: return shift ? '*' : '8';
        case KC_9: return shift ? '(' : '9';
        case KC_0: return shift ? ')' : '0';

        // ── Base punctuation / symbols ──────────
        case KC_MINUS: return shift ? '_' : '-';
        case KC_EQUAL: return shift ? '+' : '=';
        case KC_LBRC:  return shift ? '{' : '[';
        case KC_RBRC:  return shift ? '}' : ']';
        case KC_BSLS:  return shift ? '|' : '\\';
        case KC_SCLN:  return shift ? ':' : ';';
        case KC_QUOT:  return shift ? '"' : '\'';
        case KC_GRV:   return shift ? '~' : '`';
        case KC_COMM:  return shift ? '<' : ',';
        case KC_DOT:   return shift ? '>' : '.';
        case KC_SLSH:  return shift ? '?' : '/';

        // ── Pre-shifted aliases (ignore `shift`) ─
        case KC_EXLM: return '!';
        case KC_AT:   return '@';
        case KC_HASH: return '#';
        case KC_DLR:  return '$';
        case KC_PERC: return '%';
        case KC_CIRC: return '^';
        case KC_AMPR: return '&';
        case KC_ASTR: return '*';
        case KC_LPRN: return '(';
        case KC_RPRN: return ')';
        case KC_UNDS: return '_';
        case KC_PLUS: return '+';
        case KC_LCBR: return '{';
        case KC_RCBR: return '}';
        case KC_PIPE: return '|';
        case KC_COLN: return ':';
        case KC_DQUO: return '"';
        case KC_TILD: return '~';
        case KC_LABK: return '<';
        case KC_RABK: return '>';
        case KC_QUES: return '?';

        // ── Space ───────────────────────────────
        case KC_SPACE: return ' ';

        default:
            return 0; // Non-printable or unsupported
    }
}
