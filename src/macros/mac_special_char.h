#pragma once

#include QMK_KEYBOARD_H

#define MACOS_EMOJI_MENU_DELAY       500 // ms to wait for macOS Emoji Menu to load
#define MACOS_EMOJI_MENU_INPUT_DELAY 800 // ms to wait for macOS Emoji Menu to respond to input

// Special characters not typically available w/ simple keystrokes or shortcuts on many keyboards
// TIP: Symbols are grouped logically; emojis are grouped alphabetically. The order of the table 
// entries must match this enum.
typedef enum {
    // Spanish punctuation
    CHAR_INV_QUES,           // Spanish inverted question mark `¿`
    CHAR_INV_EXLM,           // Spanish inverted exclamation mark `¡`
    // Combining marks
    CHAR_COMB_ACUTE,         // Combining acute accent (◌́)
    CHAR_COMB_GRAVE,         // Combining grave symbol (◌̀)
    CHAR_COMB_TILDE,         // Combining tilde symbol (◌̃)
    CHAR_COMB_UMLAUT,        // Combining umlaut symbol (◌̈)
    CHAR_COMB_CIRCUMFLEX,    // Combining circumflex symbol (◌̂)
    CHAR_COMB_CARON,         // Combining caron symbol (◌̌) — Requires "ABC Extended" macOS setting
    CHAR_COMB_BREVE,         // Combining breve symbol (◌̆) — Requires "ABC Extended" macOS setting
    CHAR_COMB_INV_BREVE,     // Combining inverted breve (◌̑)
    CHAR_COMB_MACRON,        // Combining macron symbol (◌̄) — Requires "ABC Extended" macOS setting
    // Currency
    CHAR_CENT,               // Cent symbol (¢)
    CHAR_EURO,               // Euro pound symbol (€)
    CHAR_POUND,              // British pound symbol (£)
    CHAR_YEN,                // Yen/yuan symbol (¥)
    // Dashes & math
    CHAR_DEGREE,             // Degree symbol (°)
    CHAR_EN_DASH,            // En dash (–) a.k.a. range dash
    CHAR_EM_DASH,            // Em dash (—)
    CHAR_NEQ,                // Inequality (≠)
    CHAR_APPROX,             // Approximation (≈)
    CHAR_MULTIPLY,           // Multiplication (×)
    CHAR_DIVIDE,             // Division (÷)
    CHAR_GTE,                // Greater than or equal to (≥)
    CHAR_LTE,                // Less than or equal to (≤)
    CHAR_INFINITY,           // Infinity symbol (∞)
    // Dots & ellipses
    CHAR_ELLIPSIS,           // Three horizontal dots (…)
    CHAR_VERT_ELLIPSIS,      // Three vertical dots (⋮)
    CHAR_BULLET,             // Bullet symbol (•)
    CHAR_CENTER_DOT,         // Centered dot (·)
    // Smart quotes
    CHAR_SMART_QUOTE_LEFT,   // Smart single quote open (‘)
    CHAR_SMART_QUOTE_RIGHT,  // Smart single quote close (’)
    CHAR_SMART_DQUOTE_LEFT,  // Smart double quote open (“)
    CHAR_SMART_DQUOTE_RIGHT, // Smart double quote close (”)
    // Guillemets
    CHAR_ANGLE_QUOTE_LEFT,   // Left single guillemet (‹)
    CHAR_ANGLE_QUOTE_RIGHT,  // Right single guillemet (›)
    CHAR_ANGLE_DQUOTE_LEFT,  // Left double guillemet («)
    CHAR_ANGLE_DQUOTE_RIGHT, // Right double guillemet (»)
    // Arrows
    CHAR_ARROW_LEFT,
    CHAR_ARROW_RIGHT,
    CHAR_ARROW_UP,
    CHAR_ARROW_DOWN,

    // Emojis
    CHAR_EMOJI_AIRPLANE,
    CHAR_EMOJI_ALARM,
    CHAR_EMOJI_ANGRY,
    CHAR_EMOJI_AUTOMOBILE,
    CHAR_EMOJI_BED,
    CHAR_EMOJI_BICYCLE,
    CHAR_EMOJI_BLOWING_KISS,
    CHAR_EMOJI_BLUSH,
    CHAR_EMOJI_BRAIN,
    CHAR_EMOJI_BULLSEYE,
    CHAR_EMOJI_BUS,
    CHAR_EMOJI_CALENDAR,
    CHAR_EMOJI_CAMERA,
    CHAR_EMOJI_CENSORED,
    CHAR_EMOJI_CHECK_MARK,
    CHAR_EMOJI_CHECK_MARK_BUTTON,
    CHAR_EMOJI_CLAPPING,
    CHAR_EMOJI_CLIPBOARD,
    CHAR_EMOJI_CLOUD,
    CHAR_EMOJI_CLOUD_WITH_LIGHTNING,
    CHAR_EMOJI_CLOWN,
    CHAR_EMOJI_COMPASS,
    CHAR_EMOJI_CRESCENT_MOON,
    CHAR_EMOJI_CROSS_MARK,
    CHAR_EMOJI_CRYING,
    CHAR_EMOJI_CRYING_LOUDLY,
    CHAR_EMOJI_CUP_WITH_STRAW,
    CHAR_EMOJI_DESKTOP_COMPUTER,
    CHAR_EMOJI_DEVIL,
    CHAR_EMOJI_DOUBLE_EXCLAMATION,
    CHAR_EMOJI_EARTH,
    CHAR_EMOJI_EXCLAMATION,
    CHAR_EMOJI_EXPLODING_HEAD,
    CHAR_EMOJI_EXPRESSIONLESS,
    CHAR_EMOJI_EYES,
    CHAR_EMOJI_FACEPALM,
    CHAR_EMOJI_FILE_FOLDER,
    CHAR_EMOJI_FILE_FOLDER_OPEN,
    CHAR_EMOJI_FIRE,
    CHAR_EMOJI_FLOPPY_DISK,
    CHAR_EMOJI_FRUSTRATED,
    CHAR_EMOJI_GESTURING_NO,
    CHAR_EMOJI_GIFT,
    CHAR_EMOJI_GRIN,
    CHAR_EMOJI_GRIN_SWEAT,
    CHAR_EMOJI_HALO,
    CHAR_EMOJI_HAMBURGER,
    CHAR_EMOJI_HANDSHAKE,
    CHAR_EMOJI_HEART,
    CHAR_EMOJI_HEART_EYES,
    CHAR_EMOJI_HIGH_VOLTAGE,
    CHAR_EMOJI_HOLDING_TEARS,
    CHAR_EMOJI_HOUSE,
    CHAR_EMOJI_HUG,
    CHAR_EMOJI_HUNDRED,
    CHAR_EMOJI_ICE_CREAM,
    CHAR_EMOJI_ICE_CUBE,
    CHAR_EMOJI_INTERNET,
    CHAR_EMOJI_JOKER,
    CHAR_EMOJI_JOYSTICK,
    CHAR_EMOJI_KEY,
    CHAR_EMOJI_KEYBOARD,
    CHAR_EMOJI_LAPTOP,
    CHAR_EMOJI_LAUGH,
    CHAR_EMOJI_LIGHT_BULB,
    CHAR_EMOJI_LINK,
    CHAR_EMOJI_LOCK_CLOSED,
    CHAR_EMOJI_LOCK_OPEN,
    CHAR_EMOJI_MAGNIFYING_GLASS,
    CHAR_EMOJI_MELTING_FACE,
    CHAR_EMOJI_MEMO,
    CHAR_EMOJI_MILKY_WAY,
    CHAR_EMOJI_MOAI,
    CHAR_EMOJI_MONEY_BAG,
    CHAR_EMOJI_MOTORCYCLE,
    CHAR_EMOJI_MOTOR_SCOOTER,
    CHAR_EMOJI_MUSICAL_NOTES,
    CHAR_EMOJI_NAUSEATED,
    CHAR_EMOJI_NEUTRAL,
    CHAR_EMOJI_OK,
    CHAR_EMOJI_PACKAGE,
    CHAR_EMOJI_PARTY_POPPER,
    CHAR_EMOJI_PEACE,
    CHAR_EMOJI_PHONE,
    CHAR_EMOJI_PIZZA,
    CHAR_EMOJI_PLEADING,
    CHAR_EMOJI_POOP,
    CHAR_EMOJI_PRAY,
    CHAR_EMOJI_PRINTER,
    CHAR_EMOJI_PUSHPIN_ROUND,
    CHAR_EMOJI_QUESTION_MARK,
    CHAR_EMOJI_RAIN_CLOUD,
    CHAR_EMOJI_RAISED_EYEBROW,
    CHAR_EMOJI_RECYCLE,
    CHAR_EMOJI_ROBOT,
    CHAR_EMOJI_ROTFL,
    CHAR_EMOJI_SCISSORS,
    CHAR_EMOJI_SCOOTER,
    CHAR_EMOJI_SHUSH,
    CHAR_EMOJI_SKULL,
    CHAR_EMOJI_SLEEPING,
    CHAR_EMOJI_SMILE,
    CHAR_EMOJI_SMIRK,
    CHAR_EMOJI_SNOWFLAKE,
    CHAR_EMOJI_SPARKLES,
    CHAR_EMOJI_SPIRAL_EYES,
    CHAR_EMOJI_SPIRAL_NOTEPAD,
    CHAR_EMOJI_STAR,
    CHAR_EMOJI_STARSTRUCK,
    CHAR_EMOJI_STOP_SIGN,
    CHAR_EMOJI_SUN,
    CHAR_EMOJI_SUNGLASSES,
    CHAR_EMOJI_SURPRISED,
    CHAR_EMOJI_TACO,
    CHAR_EMOJI_THERMOMETER,
    CHAR_EMOJI_THINK,
    CHAR_EMOJI_THUMB_DOWN,
    CHAR_EMOJI_THUMB_UP,
    CHAR_EMOJI_TRAIN,
    CHAR_EMOJI_TRIANGULAR_FLAG,
    CHAR_EMOJI_UNAMUSED,
    CHAR_EMOJI_UPSIDE_DOWN,
    CHAR_EMOJI_VOMITING,
    CHAR_EMOJI_WARNING,
    CHAR_EMOJI_WEARY,
    CHAR_EMOJI_WIND,
    CHAR_EMOJI_WINK,
    CHAR_EMOJI_WIRELESS,
    CHAR_EMOJI_WORLD_MAP,
    CHAR_EMOJI_ZZZ,
} special_char_t;

// Unified descriptor for a special characters. Each entry defines all platform-specific output
// methods (Unicode, macOS keycodes, emoji-search strings) plus an auto-select Boolean, allowing
// the keymap to produce consistent symbols regardless of operating system. This is used as a
// table entry of the available special characters.
typedef struct {
    // Logical symbol identifier defined as a predefined enum value
    special_char_t symbol_name;

    // Unicode output (Linux/Microsoft Windows)
    const char *unicode;

    // macOS ABC-Extended keycode shortcut (NULL if not applicable)
    uint16_t macos_keycode;

    // macOS Emoji popup search (NULL if not applicable)
    const char *emoji_search;

    // Auto-select emoji/symbol if it reliably appears as the first result
    bool auto_select;
} special_char_entry_t;

// ─────────────────────────────────────────────────────────────
// Special Character Function Declarations
// ─────────────────────────────────────────────────────────────

// Various special characters such as `¿`, `€`, and combining symbols `◌́`
void special_char_macro(const special_char_t special_char);
