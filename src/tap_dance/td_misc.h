#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Miscellaneous Tap Dance Function Declarations
// ─────────────────────────────────────────────────────────────

// ─────────────────────────────
// App Shortcut Functions
// ─────────────────────────────

// TD_UNDO
void undo_finished(tap_dance_state_t *state, void *user_data);
void undo_reset(tap_dance_state_t *state, void *user_data);
