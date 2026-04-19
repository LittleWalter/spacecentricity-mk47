#pragma once

#include QMK_KEYBOARD_H

#define MACOS_EMOJI_MENU_DELAY       500 // ms to wait for macOS Emoji Menu to load
#define MACOS_EMOJI_MENU_INPUT_DELAY 800 // ms to wait for macOS Emoji Menu to respond to input

// Special characters not typically available w/ simple keystrokes on US keyboards
typedef enum {
    CHAR_INV_QUES,           // Spanish inverted question mark `¿`
    CHAR_INV_EXLM,           // Spanish inverted exclamation mark `¡`
    CHAR_COMB_ACUTE,         // Combining acute accent (◌́)
    CHAR_COMB_GRAVE,         // Combining grave symbol (◌̀)
    CHAR_COMB_TILDE,         // Combining tilde symbol (◌̃)
    CHAR_COMB_UMLAUT,        // Combining umlaut symbol (◌̈)
    CHAR_COMB_CIRCUMFLEX,    // Combining circumflex symbol (◌̂)
    CHAR_COMB_CARON,         // Combining caron symbol (◌̌) — Requires "ABC Extended" macOS setting
    CHAR_COMB_BREVE,         // Combining breve symbol (◌̆) — Requires "ABC Extended" macOS setting
    CHAR_COMB_INV_BREVE,     // Combining inverted breve (◌̑)
    CHAR_COMB_MACRON,        // Combining macron symbol (◌̄) — Requires "ABC Extended" macOS setting
    CHAR_CENT,               // Cent symbol (¢)
    CHAR_EURO,               // Euro pound symbol (€)
    CHAR_POUND,              // British pound symbol (£)
    CHAR_YEN,                // Yen/yuan symbol (¥)
    CHAR_DEGREE,             // Degree symbol (°)
    CHAR_EN_DASH,            // En dash (–) a.k.a. range dash
    CHAR_EM_DASH,            // Em dash (—)
    CHAR_NEQ,                // Inequality (≠)
    CHAR_APPROX,             // Approximation (≈)
    CHAR_ELLIPSIS,           // Three horizontal dots (…)
    CHAR_VERT_ELLIPSIS,      // Three vertical dots (⋮)
    CHAR_BULLET,             // Bullet symbol (•)
    CHAR_CENTER_DOT,         // Centered dot (·)
    CHAR_SMART_QUOTE_LEFT,   // Smart single quote open (‘)
    CHAR_SMART_QUOTE_RIGHT,  // Smart single quote close (’)
    CHAR_SMART_DQUOTE_LEFT,  // Smart double quote open (“)
    CHAR_SMART_DQUOTE_RIGHT, // Smart double quote close (”)
    CHAR_ANGLE_QUOTE_LEFT,   // Left single guillemet (‹)
    CHAR_ANGLE_QUOTE_RIGHT,  // Right single guillemet (›)
    CHAR_ANGLE_DQUOTE_LEFT,  // Left double guillemet («)
    CHAR_ANGLE_DQUOTE_RIGHT, // Right double guillemet (»)
    // Emojis
    CHAR_EMOJI_CRY,
    CHAR_EMOJI_FIRE,
    CHAR_EMOJI_HEART,
    CHAR_EMOJI_LAUGH,
    CHAR_EMOJI_POOP,
    CHAR_EMOJI_ROTFL,
    CHAR_EMOJI_SKULL,
    CHAR_EMOJI_SMILE,
    CHAR_EMOJI_SUNGLASSES,
    CHAR_EMOJI_THINK,
    CHAR_EMOJI_THUMB_UP,
    CHAR_EMOJI_THUMB_DOWN,
} special_char_t;

// Various special characters such as `¿`, `€`, and combining symbols `◌́`
void special_char_macro(const special_char_t special_char);

// Smart single quotes with cursor placed inside (‘|’)
void smart_single_quotes_macro(void);

// Smart double quotes with cursor placed inside (“|”)
void smart_double_quotes_macro(void);

// Single angle quotes (guillemet) with cursor place inside (‹|›)
void single_angle_quotes_macro(void);

// Double angle quotes (guillemet) with cursor place inside («|»)
void double_angle_quotes_macro(void);
