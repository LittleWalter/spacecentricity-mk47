// ─────────────────────────────────────────────────────────────────
// Spacecentricity v0.1.0 — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// Source: https://github.com/LittleWalter/spacecentricity-mk47
// ─────────────────────────────────────────────────────────────────

#include "mac_doom.h"
#include "macros.h"
#include "src/core/custom_keys.h"
#include "src/tap_dances/tap_dance_actions.h"

// Taps `Delete` if using macOS, otherwise `Pause`.
// NOTE: Apple macOS assigns screen brightness up to `Pause`.
void toggle_doom_pause(void) {
    mod_state_t saved = mod_state_save_and_clear();

    current_os == OS_MACOS ? tap_and_update(KC_DEL)
                           : tap_and_update(KC_PAUSE);

    mod_state_restore(&saved);
}
