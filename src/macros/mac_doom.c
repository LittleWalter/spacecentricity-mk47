#include "mac_doom.h"
#include "src/core/custom_keys.h"
#include "macros.h"

// Taps `Delete` if using macOS, otherwise `Pause`.
// NOTE: Apple macOS assigns screen brightness up to `Pause`.
void toggle_doom_pause(void) {
    mod_state_t saved = mod_state_save_and_clear();

    current_os == OS_MACOS ? tap_code16(KC_DEL)
                           : tap_code16(KC_PAUSE);

    mod_state_restore(&saved);
}
