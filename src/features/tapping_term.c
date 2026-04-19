#include "tapping_term.h"
#include "src/core/keymap.h"

// Home‑row layer/mod keys can misfire during fast touch typing because 150–180ms
// TAPPING_TERM is sometimes too short for hand alternations and natural rolls.
// Adding 20–40ms to only the affected keys improves reliability without slowing
// down the whole keyboard.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case E_VIM_R:
        case I_ARR_R:
        case H_ARR_L:
        case T_VIM_L:
            return TAPPING_TERM + HOME_ROW_LAYERS_DELAY;
        case O_PROG_R:
        case N_PROG_L:
            // Ring fingers move more slowly than index and middle
            return TAPPING_TERM + HOME_ROW_RING_DELAY;
        case C_UPPER: // Increase responsiveness of right-hand thumb on _BASE
            return TAPPING_TERM - BASE_RIGHT_THUMB_TAP_TERM_REDUCE;
    }
    return TAPPING_TERM;
}
