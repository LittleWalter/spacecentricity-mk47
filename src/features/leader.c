// REF: https://rgoulter.com/blog/posts/programming/2024-06-16-using-the-qmk-leader-key-for-fancy-keyboard-functionality.html

#include "leader.h"
#include "src/core/keymap.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_programming.h"

void leader_start_user(void) {
    // To avoid issues with tap-dance and mod-tap keys, go to dedicated alpha layer
    layer_on(_LEADER);
}

void leader_end_user(void) {
    // Emoji sequences
    if (leader_sequence_two_keys(EMOJI_LEADER, KC_C)) {        // mnemonic: Emoji Crying
        special_char_macro(CHAR_EMOJI_CRY);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_H)) { // mnemonic: Emoji Heart
        special_char_macro(CHAR_EMOJI_HEART);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_K)) { // mnemonic: Emoji Kool Sunglasses
        special_char_macro(CHAR_EMOJI_SUNGLASSES);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_F)) { // mnemonic: Emoji Fire
        special_char_macro(CHAR_EMOJI_FIRE);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_L)) { // mnemonic: Emoji Laugh
        special_char_macro(CHAR_EMOJI_LAUGH);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_P)) { // mnemonic: Emoji Poop
        special_char_macro(CHAR_EMOJI_POOP);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_D)) { // mnemonic: Emoji Death
        special_char_macro(CHAR_EMOJI_SKULL);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_S)) { // mnemonic: Emoji Smile
        special_char_macro(CHAR_EMOJI_SMILE);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_T) ||
               leader_sequence_three_keys(EMOJI_LEADER, KC_T, KC_U)) { // mnemonic: Emoji Thumbs up
        special_char_macro(CHAR_EMOJI_THUMB_UP);
    } else if (leader_sequence_three_keys(EMOJI_LEADER, KC_T, KC_T) ||
               leader_sequence_three_keys(EMOJI_LEADER, KC_T, KC_D)) { // mnemonic: Emoji Thumbs Down
        special_char_macro(CHAR_EMOJI_THUMB_DOWN);
    } else if (leader_sequence_two_keys(EMOJI_LEADER, KC_Q)) { // mnemonic: Emoji Questionable
        special_char_macro(CHAR_EMOJI_THINK);
#ifdef RGB_MATRIX_ENABLE
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_N)) { // mnemonic: RGB Next effect
        rgb_matrix_step_noeeprom();
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_P)) { // mnemonic: RGB Previous effect
        rgb_matrix_step_reverse_noeeprom();
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_R)) { // mnemonic: RGB Rainbow animation
        rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_J)) { // mnemonic: RGB Jellybean animation
        rgb_matrix_mode_noeeprom(RGB_MATRIX_JELLYBEAN_RAINDROPS);
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_M)) { // mnemonic: RGB Matrix-movie animation
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DIGITAL_RAIN);
    } else if (leader_sequence_two_keys(RGB_LEADER, KC_T)) { // mnemonic: RGB Toggle on/off
        rgb_matrix_toggle_noeeprom();
#endif
    } else if (leader_sequence_one_key(KC_M)) {
        SEND_STRING(EMAIL);
    // Surrounding symbol sequences
    } else if (leader_sequence_one_key(KC_A)) { // mnemonic: Angle brackets <>
        surround_macro(SUR_ABR);
    } else if (leader_sequence_one_key(KC_P)) { // mnemonic: Parenthesis ()
        surround_macro(SUR_PAREN);
    } else if (leader_sequence_one_key(KC_S)) { // mnemonic: Square brackets []
        surround_macro(SUR_BRC);
    } else if (leader_sequence_one_key(KC_D)) { // mnemonic: Double quotes ""
        surround_macro(SUR_DQUO);
    } else if (leader_sequence_one_key(KC_G)) { // mnemonic: Grave ``
        surround_macro(SUR_GRV);
    } else if (leader_sequence_one_key(KC_Q)) { // mnemonic: (single) Quotes ''
        surround_macro(SUR_QUOT);
    } else if (leader_sequence_one_key(KC_C)) { // mnemonic: Curly braces {}
        surround_macro(SUR_CBR);
    // Developer annotations
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_T)) {
        notes_macro(DEV_TODO);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_I)) {
        notes_macro(DEV_INFO);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_N)) {
        notes_macro(DEV_NOTE);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_H)) {
        notes_macro(DEV_TIP);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_F)) {
        notes_macro(DEV_FIXME);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_W)) {
        notes_macro(DEV_WARNING);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_R)) {
        notes_macro(DEV_REF);
    } else if (leader_sequence_two_keys(DEV_LEADER, KC_S)) {
        notes_macro(DEV_SECTION);
    } else {
        // Fallback: send BEL (system beep on macOS / some terminals)
        SEND_STRING("\a");
    }

    layer_off(_LEADER);
}
