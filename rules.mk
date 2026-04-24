# NOTE: The following features can be safely disabled
# - RGB_MATRIX_ENABLE: entire rgb.c is wrapped
# - CAPS_WORD_ENABLE: only caps-word-specific calls are wrapped in rgb.c and td_chars.c
# - LEADER_ENABLE: leader.c and leader-dependent code are wrapped in rgb.c
# - MOUSEKEY_ENABLE: mouse layer + behavior wrapped; related keycodes unguarded
#
# TAP_DANCE_ENABLE is required for this keymap and not wrapped.

# Non-default QMK features
CAPS_WORD_ENABLE = yes
CONSOLE_ENABLE = no
DEBUG_ENABLE = no
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
RGB_MATRIX_ENABLE = yes
TAP_DANCE_ENABLE = yes

# Wildcard-based SRC approach does not seem to work here, so we manually add each new .c file,
# excluding src/core/keymap.c. QMK's Python precompilation validator needs exactly 1 file named
# keymap.c in the project root; in this project, it's a simple stub to wrangle all source files
# into src/.
SRC += src/core/custom_keys.c
SRC += src/features/caps_word.c
SRC += src/features/leader.c
SRC += src/features/rgb.c
SRC += src/features/tapping_term.c
SRC += src/macros/mac_macos.c
SRC += src/macros/mac_programming.c
SRC += src/macros/mac_special_char.c
SRC += src/macros/mac_surround.c
SRC += src/macros/mac_terminal.c
SRC += src/macros/mac_vim.c
SRC += src/macros/macros.c
SRC += src/tap_dance/tap_dance_actions.c
SRC += src/tap_dance/td_chars.c
SRC += src/tap_dance/td_macos.c
SRC += src/tap_dance/td_media.c
SRC += src/tap_dance/td_misc.c
SRC += src/tap_dance/td_numpad.c
SRC += src/tap_dance/td_programming.c
SRC += src/tap_dance/td_terminal.c
SRC += src/tap_dance/td_vim.c
