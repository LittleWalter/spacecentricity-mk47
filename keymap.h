#pragma once

#include QMK_KEYBOARD_H
#include "tap_dance/tap_dance_actions.h"
#include "macros/macros.h"

// ─────────────────────────────────────────────────────────────
//  Simplifying Keycodes and Combinations
// ─────────────────────────────────────────────────────────────

#define ____ KC_NO // KC_TRNS is aliased as _______
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_ALT OSM(MOD_LALT)

/*** MT Keycodes: Modifiers ***********************************/
#define COLN_LSFT MT(MOD_LSFT, KC_COLN)
#define DOT_LCTL  MT(MOD_LCTL, KC_DOT)
#define F8_RALT   MT(MOD_RALT, KC_F8)
#define F9_LALT   MT(MOD_LALT, KC_F9)
#define G_RALT    MT(MOD_RALT, KC_G)
#define L_RCTL    MT(MOD_RCTL, KC_L)
#define MINS_MEH  MT(MOD_MEH,  KC_MINS)
#define PERC_HYPR MT(MOD_HYPR, S(KC_5))
#define P_LALT    MT(MOD_LALT, KC_P)
#define Q_MEH     MT(MOD_MEH,  KC_Q)
#define R_RSFT    MT(MOD_RSFT, KC_R)
#define SCLN_LSFT MT(MOD_LSFT, KC_SCLN)
#define SLSH_HYPR MT(MOD_HYPR, KC_SLSH)
#define SPC_LSFT  MT(MOD_LSFT, KC_SPC)
#define UNDS_MEH  MT(MOD_MEH,  KC_UNDS)
#define V_MEH     MT(MOD_MEH,  KC_V)
#define Z_HYPR    MT(MOD_HYPR, KC_Z)

// Numpad Mod-Tap Keys
#define KP7_RALT MT(MOD_RALT, KC_P7)
#define KP7_LALT MT(MOD_LALT, KC_P7)
#define KP8_RCTL MT(MOD_RCTL, KC_P8)
#define KP8_LCTL MT(MOD_LCTL, KC_P8)
#define KP9_RSFT MT(MOD_RSFT, KC_P9)
#define KP9_LSFT MT(MOD_LSFT, KC_P9)

/*** LT/TO Keycodes: Layers ***********************************/

// TIP: LT only supports layers 0-15
                                      // │   Tap   │  Hold   │
#define ESC_MACOS LT(_MACOS,  KC_ESC) // │   ESC   │  macOS  │
#define E_VIM_R   LT(_VIM_R,  KC_E)   // │    e    │ Vim RHS │
#define H_ARR_L   LT(_ARR_L,  KC_H)   // │    h    │ArrowsLHS│
#define I_ARR_R   LT(_ARR_R,  KC_I)   // │    i    │ArrowsRHS│
#define M_TERM    LT(_TERM,   KC_M)   // │    m    │ Terminal│
#define N_PROG_L  LT(_PROG_L, KC_N)   // │    n    │CodingLHS│
#define O_PROG_R  LT(_PROG_R, KC_O)   // │    o    │CodingRHS│
#define T_VIM_L   LT(_VIM_L,  KC_T)   // │    t    │ Vim LHS │
#define ZERO_ADJ  LT(_ADJ,    KC_P0)  // │ Numpad 0│  F1-F12 │

#define RCLK_UPPER LT(_UPPER, MS_BTN2) // Doom

#define BASE TO(_BASE)
#define DOOM TO(_DOOM)

/*** TD Keycodes: Tap Dances **********************************/

// Thumb Layer Keys: Tap+Hold to "Lock" layer
#define C_UPPER TD(TD_C)
#define U_LOWER TD(TD_U)

// Char Keys
#define ASTR  TD(TD_ASTR)
#define BSPC  TD(TD_BSPC)
#define CARET TD(TD_CARET)
#define CIRC  TD(TD_CIRC)
#define COMM  TD(TD_COMM)
#define DEL   TD(TD_DEL)
#define DLR   TD(TD_DLR)
#define DOT   TD(TD_DOT)
#define DQUO  TD(TD_DQUO)
#define EQL   TD(TD_EQL)
#define EXLM  TD(TD_EXLM)
#define MINS  TD(TD_MINS)
#define PLUS  TD(TD_PLUS)
#define PUNC  TD(TD_PUNC)
#define QUES  TD(TD_QUES)
#define QUOT  TD(TD_QUOT)
#define SPC   TD(TD_SPC)
#define TAB   TD(TD_TAB)

#define LPRN TD(TD_LPRN)
#define RPRN TD(TD_RPRN)
#define LBRC TD(TD_LBRC)
#define RBRC TD(TD_RBRC)

// Media Keys
#define MUTE TD(TD_MUTE)
#define VOLD TD(TD_VOLD)
#define VOLU TD(TD_VOLU)

// Navigational Keys
#define HOME TD(TD_HOME)
#define PGDN TD(TD_PGDN)
#define PGUP TD(TD_PGUP)
#define END  TD(TD_END)

// Vim Keys
#define B         TD(TD_B)
#define GJ        TD(TD_GJ)
#define GK        TD(TD_GK)
#define W         TD(TD_W)

#define HALF_PGUP TD(TD_HALF_PGUP)
#define HALF_PGDN TD(TD_HALF_PGDN)

#define HIGH      TD(TD_HIGH)
#define MID       TD(TD_MID)
#define LOW       TD(TD_LOW)

#define WINL      TD(TD_WINL)
#define WINU      TD(TD_WINU)
#define WIND      TD(TD_WIND)
#define WINR      TD(TD_WINR)

#define SUB       TD(TD_SUB)
#define VIM_DEL   TD(TD_VIM_DEL)
#define FOLD      TD(TD_FOLD)
#define WRITE     TD(TD_WRITE)
#define QUIT      TD(TD_QUIT)

// Numpad
#define NP_1_A TD(TD_NUMPAD_1)
#define NP_2_B TD(TD_NUMPAD_2)
#define NP_3_C TD(TD_NUMPAD_3)
#define NP_4_D TD(TD_NUMPAD_4)
#define NP_5_E TD(TD_NUMPAD_5)
#define NP_6_F TD(TD_NUMPAD_6)

// Programming N-Grams
#define PROG_EQL   TD(TD_PROG_EQL)
#define AND        TD(TD_AND)
#define ASSIGN     TD(TD_ASSIGN)
#define PARENS     TD(TD_PARENS)
#define DBL_QUOTES TD(TD_DBL_QUOTES)
#define ARROW      TD(TD_ARROW)
#define CMPD       TD(TD_CMPD)
#define INC        TD(TD_INC)
#define COMMENT    TD(TD_COMMENT)
#define IF_KW      TD(TD_IF_KW)
#define TRUE_KW    TD(TD_TRUE_KW)
#define RETURN_KW  TD(TD_RETURN_KW)
#define BREAK_KW   TD(TD_BREAK_KW)
#define SWITCH_KW  TD(TD_SWITCH_KW)
#define FOR_KW     TD(TD_FOR_KW)
#define NULL_KW    TD(TD_NULL_KW)

#define MD_LINK TD(TD_MD_LINK)

// Terminal Commands
#define BTOP    TD(TD_BTOP)
#define CAT     TD(TD_CAT)
#define CLS     TD(TD_CLS)
#define SIGINT  TD(TD_SIGINT)
#define PIPE    TD(TD_PIPE)
#define PATH    TD(TD_PATH)
#define CD      TD(TD_CD)
#define SUDO    TD(TD_SUDO)

// Apple macOS
#define SPOTLGHT_MACOS TD(TD_SPOTLGHT_MACOS)
#define FS_MACOS       TD(TD_FS_MACOS)
#define SCRNSHOT_MACOS TD(TD_SCRNSHOT_MACOS)
#define DEL_MACOS      TD(TD_DEL_MACOS)

// Miscellaneous
#define UNDO         TD(TD_UNDO)
#define SMART_QUOTES TD(TD_SMART_QUOTES)
#define ANGLE_QUOTES TD(TD_ANGLE_QUOTES)

/*** Other Keycodes *******************************************/

#define MACOS_EMOJI_MENU LGUI(C(KC_SPC))

// Browser Navigation
#define TAB_LEFT C(KC_PGUP)
#define TAB_RGHT C(KC_PGDN)

// Doom Movement
#define STRAFE_LEFT A(KC_LEFT)
#define STRAFE_RGHT A(KC_RGHT)
#define STRAFE_UP   A(KC_UP)
#define STRAFE_DOWN A(KC_DOWN)

// ─────────────────────────────────────────────────────────────
// Layers Names
// ─────────────────────────────────────────────────────────────
enum layers {
    _BASE,      // Modified Programmer Dvorak
    _DOOM,      // Classic Doom layer
    _LOWER,     // Numpad (hold left thumb)
    _UPPER,     // Home row number and symbols layer (hold right thumb)
    _ADJ,       // Keyboard settings and adjustments (hold left thumb, then right thumb)
    _FN,        // F1-F12 keys (hold left thumb, then right thumb)
    _ARR_R,     // Directional arrows (hold left index finger on home row)
    _ARR_L,     // Directional arrows (hold right index finger on home row)
    _VIM_R,     // Vim navigation layer (hold left middle finger on home row)
    _VIM_L,     // Vim navigation layer (hold right middle finger on home row)
    _PROG_R,    // Programming-related bigrams (hold left ring finger on home row)
    _PROG_L,    // Programming-related bigrams (hold right ring finger on home row)
    _TERM,      // Terminal emulator macros (hold M key down, right index finger)
    _MACOS,     // macOS shortcuts
    _MOUSE,     // Mouse layer (tap left corner key w/ palm)
};
