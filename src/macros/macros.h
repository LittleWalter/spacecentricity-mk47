#pragma once

#include QMK_KEYBOARD_H
#include "src/features/case_mode.h"

// ─────────────────────────────────────────────────────────────
// Modifier State
// ─────────────────────────────────────────────────────────────

typedef struct {
    uint8_t mods;
    uint8_t weak_mods;
    uint8_t oneshot_mods;
} mod_state_t;


// Save the currently active modifiers including oneshots and weak modifers, then clear them out
static inline mod_state_t mod_state_save_and_clear(void) {
    case_mode_off(); // Turn off case mode if active; all macros are invalid

    mod_state_t state = {
        .mods = get_mods(),
        .weak_mods = get_weak_mods(),
        .oneshot_mods = get_oneshot_mods()
    };

    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();

    return state;
}

// Restore a given state of modifiers, oneshots, and weak modifiers
static inline void mod_state_restore(const mod_state_t *state) {
    register_mods(state->mods);
    add_weak_mods(state->weak_mods);
    set_oneshot_mods(state->oneshot_mods);
}

// ─────────────────────────────────────────────────────────────
// Macro Helper Function Declarations
// ─────────────────────────────────────────────────────────────

// Prose/programming n-gram helper, with optional left key(s) and centered newline
// emission to place cursor inside. Pass QMK symbols array, count (0-255), the number
// of left arrow emits (0-255), and a Boolean whether you want Vim-compatible
// vertical whitespace.
void seq_with_cursor_helper(const uint16_t *symbols,
                                   const uint8_t count,
                                   const uint8_t cursor_back,
                                   const bool newline);
