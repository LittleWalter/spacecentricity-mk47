# NOTE: The following features can be safely disabled w/o breaking the build
# - RGB_MATRIX_ENABLE: entire rgb.c is wrapped
# - CAPS_WORD_ENABLE: only caps-word-specific calls are wrapped in rgb.c and td_chars.c
# - LEADER_ENABLE: leader.c and leader-dependent code are wrapped in rgb.c, custom_keys.c
# - MOUSEKEY_ENABLE: mouse layer + behavior wrapped; related keycodes unguarded
#
# TAP_DANCE_ENABLE is required for this keymap as it is not wrapped; you cannot toggle this feature.

# Non-default QMK features: toggle `no` to disable…
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
REPEAT_KEY_ENABLE = yes
RGB_MATRIX_ENABLE = yes
TAP_DANCE_ENABLE = yes

# Debugging QMK features: toggle `yes` to enable…
CONSOLE_ENABLE = no
DEBUG_ENABLE = no

# WARNING: Wildcard-based SRC approach does not seem to work here, so we manually add each new .c
# file, excluding src/core/keymap.c. QMK's Python precompilation validator needs exactly 1 file
# named keymap.c in the project root; in this project, it's a simple stub to wrangle all source
# files into src/.
SRC += src/core/custom_keys.c
SRC += src/features/case_mode.c
SRC += src/features/leader.c
SRC += src/features/rgb.c
SRC += src/features/tapping_term.c
SRC += src/features/utils.c
SRC += src/macros/mac_programming.c
SRC += src/macros/mac_special_char.c
SRC += src/macros/mac_surround.c
SRC += src/macros/mac_system.c
SRC += src/macros/mac_terminal.c
SRC += src/macros/mac_vim.c
SRC += src/macros/macros.c
SRC += src/tap_dances/tap_dance_actions.c
SRC += src/tap_dances/td_chars.c
SRC += src/tap_dances/td_control.c
SRC += src/tap_dances/td_digits.c
SRC += src/tap_dances/td_media.c
SRC += src/tap_dances/td_numpad.c
SRC += src/tap_dances/td_programming.c
SRC += src/tap_dances/td_system.c
SRC += src/tap_dances/td_terminal.c
SRC += src/tap_dances/td_vim.c
