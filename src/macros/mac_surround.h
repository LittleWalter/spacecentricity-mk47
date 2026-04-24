#pragma once

#include QMK_KEYBOARD_H

// Common surround symbol pairs
typedef enum {
    SUR_PAREN,      // () parenthesis
    SUR_BRC,        // [] brackets
    SUR_CBR,        // {} curly braces
    SUR_VWS_CBR,    // {} curly braces w/ vertical whitespace
    SUR_ABR,        // <> angle brackets
    SUR_DQUO,       // "" double quotes
    SUR_QUOT,       // '' single quotes
    SUR_GRV,        // `` grave/backtick symbols
    SUR_SMART_DQUO, // “” smart double quotes
    SUR_SMART_QUOT, // ‘’ smart single quotes
    SUR_ANGLE_DQUO, // «» double angle quotes
    SUR_ANGLE_QUOT  // ‹› single angle quotes
} surround_char_t;

// ─────────────────────────────────────────────────────────────
// Surround Function Declarations
// ─────────────────────────────────────────────────────────────

// Common surrounding characters: `()`, `[]`, `{}`, `<>`, double/single quotes, grave/backtick
// symbols
void surround_macro(const surround_char_t pair);
