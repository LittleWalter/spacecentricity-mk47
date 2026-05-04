#pragma once

#include QMK_KEYBOARD_H

// Ensure Caps Lock is ON.
//
// QMK does not provide direct caps_lock_on/off helpers, so we check the
// host LED state and send a Caps Lock keypress only if needed. This keeps
// firmware and OS state perfectly in sync.
void caps_lock_on(void);

// Ensure Caps Lock is OFF.
//
// Same logic as caps_lock_on(): only send KC_CAPS if the OS currently
// reports Caps Lock as active. Prevents double‑toggling or desync.
void caps_lock_off(void);

// Toggle Caps Lock. This simply sends a Caps Lock keypress. The OS handles the state change.
void caps_lock_toggle(void);

// Returns true if Caps Lock is active.
bool is_caps_lock_on(void);

// Returns true if any transient lexical mode (Caps Word, Numeric Expression, etc.) is active.
bool is_transient_lexical_mode_on(void);

// Map QMK keycodes to visible ASCII characters (US layout).
// Returns 0 for non-printable / unsupported.
char keycode_to_ascii(uint16_t keycode, bool shift);
