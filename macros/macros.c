#include "macros.h"

// Prose/programming n-gram helper, with optional left key(s) and centered newline
// emission to place cursor inside. Pass QMK symbols array, count (0-255), the number
// of left arrow emits (0-255), and a Boolean whether you want Vim-compatible
// vertical whitespace.
void seq_with_cursor_helper(const uint16_t *symbols,
                                   const uint8_t count,
                                   const uint8_t cursor_back,
                                   const bool newline) {
    // Save & clear all modifiers
    mod_state_t saved = mod_state_save_and_clear();

    // Emit symbols
    for (uint8_t i = 0; i < count; i++) {
        tap_code16(symbols[i]);
    }

    // Emit left arrows: 0 value means do not move cursor into chars
    for (uint8_t i = 0; i < cursor_back; i++) {
        tap_code(KC_LEFT);
    }

    // Add Vim-compatible vertical whitespace, with proper tab-aligned cursor placement
    if (newline) {
        tap_code(KC_ENT);
        tap_code(KC_ENT);
        tap_code(KC_UP);
    }

    // Restore modifiers
    mod_state_restore(&saved);
}
