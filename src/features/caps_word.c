#include "caps_word.h"
#include "src/core/keymap.h"

// Caps Word behavior callback. Keys that should NOT deactivate Caps Word
// (digits, Backspace, Delete, arrows, underscore, hyphen) must be listed here.
// NOTE: Tap‑dance keys must be included explicitly since they bypass normal keycodes;
// refer to the constants defined in keymap.h.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case U_LOWER: // Left thumb
        case C_UPPER: // Right thumb
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0: // Skip numbers
        case KC_MINS:       // `-`
        case MINS:          // Tap dance key on _ARR_L/_ARR_R
        case KC_UNDS:       // `_`
        // Skip arrows
        case KC_LEFT:
        case KC_RGHT:
        case KC_UP:
        case KC_DOWN:
        // Skip Backspace and Delete
        case KC_BSPC:
        case BSPC:          // Semantic Backspace tap dance
        case KC_DEL:
        case DEL:           // Semantic Delete tap dance
            return true;

        default:
            return false;  // Deactivate Caps Word on any other key.
    }
}
