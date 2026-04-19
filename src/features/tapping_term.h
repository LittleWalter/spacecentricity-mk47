#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Tapping Term Differences: DELAY means slower tapping term
//                           REDUCE means faster tapping term
// ─────────────────────────────────────────────────────────────

#define HOME_ROW_LAYERS_DELAY 30            // ms added to reduce home-row misfires
#define HOME_ROW_RING_DELAY 40              // ms added to reduce delay for slower ring finger movement
#define MOUSE_FN_DELAY 200                 // ms to reduce palm triggering function keys layer

#define BASE_RIGHT_THUMB_TAP_TERM_REDUCE 20 // ms to make right thumb feel more responsive, SEE: custom_keys.c

// ─────────────────────────────────────────────────────────────
// Function Definitions
// ─────────────────────────────────────────────────────────────

// Home‑row layer/mod keys can misfire during fast touch typing because 150–180ms
// TAPPING_TERM is sometimes too short for hand alternations and natural rolls.
// Adding 20–40ms to only the affected keys improves reliability without slowing
// down the whole keyboard.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
