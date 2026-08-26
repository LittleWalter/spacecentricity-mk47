#pragma once

#include QMK_KEYBOARD_H

// Taps `Delete` if using macOS, otherwise `Pause`.
// NOTE: Apple macOS assigns screen brightness up to `Pause`.
void toggle_doom_pause(void);
