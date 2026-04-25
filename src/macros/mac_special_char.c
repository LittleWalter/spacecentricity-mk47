#include "mac_special_char.h"
#include "src/core/custom_keys.h"
#include "src/core/keymap.h"
#include "macros.h"

// Each row describes a single symbol and how to emit it across platforms:
//   • unicode       → direct Unicode output (Linux/Microsoft Windows)
//   • macos_keycode → ABC‑Extended key combo (Apple macOS)
//   • emoji_search  → search term for macOS Emoji & Symbols popup (fallback)
// This unified table eliminates the use of long switch statements and makes adding new symbols a
// one‑line change.
// WARNING: This table must be in the same order as the enum for binary search table lookups.
// Symbols are grouped logically; emojis are grouped alphabetically.
//
// NOTE: Unicode code points available at https://emojiguide.org
static const special_char_entry_t special_chars[] = {
    // ─────────────────────────────────────────────
    // Basic punctuation & symbols
    // ─────────────────────────────────────────────
    // Spanish punctuation
    { CHAR_INV_QUES,           "¿",  A(S(KC_SLSH)), NULL, false },
    { CHAR_INV_EXLM,           "¡",  A(KC_1),       NULL, false },

    // Combining marks
    { CHAR_COMB_ACUTE,         "\u0301", A(KC_E),   NULL, false },
    { CHAR_COMB_GRAVE,         "\u0300", A(KC_GRV), NULL, false },
    { CHAR_COMB_TILDE,         "\u0303", A(KC_N),   NULL, false },
    { CHAR_COMB_UMLAUT,        "\u0308", A(KC_U),   NULL, false },
    { CHAR_COMB_CIRCUMFLEX,    "\u0302", A(KC_6),   NULL, false },
    { CHAR_COMB_CARON,         "\u030C", A(KC_V),   NULL, false },
    { CHAR_COMB_MACRON,        "\u0304", A(KC_A),   NULL, false },
    { CHAR_COMB_BREVE,         "\u0306", A(KC_B),   NULL, false },
    { CHAR_COMB_INV_BREVE,     "\u0311", 0,         NULL, false },

    // Currency
    { CHAR_CENT,               "¢",  A(KC_4),       NULL, false },
    { CHAR_EURO,               "€",  A(S(KC_2)),    NULL, false },
    { CHAR_POUND,              "£",  A(KC_3),       NULL, false },
    { CHAR_YEN,                "¥",  A(KC_Y),       NULL, false },

    // Dashes & math
    { CHAR_DEGREE,             "°",  A(S(KC_8)),    NULL, false },
    { CHAR_EN_DASH,            "–",  A(KC_MINS),    NULL, false },
    { CHAR_EM_DASH,            "—",  A(S(KC_MINS)), NULL, false },
    { CHAR_NEQ,                "≠",  A(KC_EQL),     NULL, false },
    { CHAR_APPROX,             "≈",  0,             "U+2248", true }, // A(KC_X) for US layout
    { CHAR_MULTIPLY,           "×",  0,             "U+00D7", true },
    { CHAR_DIVIDE,             "÷",  A(KC_SLSH),    NULL, false },
    { CHAR_GTE,                "≥",  A(KC_DOT),     NULL, false },
    { CHAR_LTE,                "≤",  A(KC_COMM),    NULL, false },
    { CHAR_INFINITY,           "∞",  0,             "U+221E", false }, // A(KC_5) for US layout

    // Dots & ellipses
    { CHAR_ELLIPSIS,           "…",  A(KC_SCLN),    NULL, false },
    { CHAR_VERT_ELLIPSIS,      "⋮",  0,             "vertical ellipsis", true },
    { CHAR_BULLET,             "•",  A(KC_8),       NULL, false },
    { CHAR_CENTER_DOT,         "·",  A(S(KC_9)),    NULL, false },

    // Smart quotes
    { CHAR_SMART_QUOTE_LEFT,   "‘",  A(KC_RBRC),    NULL, false },
    { CHAR_SMART_QUOTE_RIGHT,  "’",  A(S(KC_RBRC)), NULL, false },
    { CHAR_SMART_DQUOTE_LEFT,  "“",  A(KC_LBRC),    NULL, false },
    { CHAR_SMART_DQUOTE_RIGHT, "”",  A(S(KC_LBRC)), NULL, false },

    // Guillemets
    { CHAR_ANGLE_QUOTE_LEFT,   "‹",  A(S(KC_3)),    NULL, false },
    { CHAR_ANGLE_QUOTE_RIGHT,  "›",  A(S(KC_4)),    NULL, false },
    { CHAR_ANGLE_DQUOTE_LEFT,  "«",  A(KC_BSLS),    NULL, false },
    { CHAR_ANGLE_DQUOTE_RIGHT, "»",  A(S(KC_BSLS)), NULL, false },

    // Arrows
    { CHAR_ARROW_LEFT,         "←",  0, "U+2190", true },
    { CHAR_ARROW_RIGHT,        "→",  0, "U+2192", true },
    { CHAR_ARROW_UP,           "↑",  0, "U+2191", true },
    { CHAR_ARROW_DOWN,         "↓",  0, "U+2193", true },

    // ─────────────────────────────────────────────
    // Emojis (Unicode + macOS Emoji Menu popup)
    //
    // NOTE: Only the base Unicode code point is used
    // for macOS Emoji Menu search. Fully qualified
    // sequences (e.g., `U+2764 U+FE0F` for "red heart")
    // do not work in the search field under macOS 15 Sequoia.
    // ─────────────────────────────────────────────
    // Emoji name                Unicode  0  Search terms & auto-select Boolean
    { CHAR_EMOJI_AIRPLANE,             "✈️", 0, "airplane", true },
    { CHAR_EMOJI_ALARM,                "⏰", 0, "U+23F0",  true },
    { CHAR_EMOJI_ANGRY,                "😡", 0, "U+1F621", true },
    { CHAR_EMOJI_AUTOMOBILE,           "🚗", 0, "U+1F697", true },
    { CHAR_EMOJI_BED,                  "🛏️", 0, "U+1F6CF", true },
    { CHAR_EMOJI_BICYCLE,              "🚲", 0, "U+1F6B2", true },
    { CHAR_EMOJI_BLOWING_KISS,         "😘", 0, "U+1F618", true },
    { CHAR_EMOJI_BLUSH,                "😊", 0, "U+1F60A", true },
    { CHAR_EMOJI_BRAIN,                "🧠", 0, "U+1F9E0", true },
    { CHAR_EMOJI_BULLSEYE,             "🎯", 0, "U+1F3AF", true },
    { CHAR_EMOJI_BUS,                  "🚌", 0, "U+1F68C", true },
    { CHAR_EMOJI_CALENDAR,             "📅", 0, "U+1F4C5", true },
    { CHAR_EMOJI_CAMERA,               "📷", 0, "U+1F4F7", true },
    { CHAR_EMOJI_CENSORED,             "🤬", 0, "U+1F92C", true },
    { CHAR_EMOJI_CHECK_MARK,           "✔",  0, "U+2714",  true },
    { CHAR_EMOJI_CHECK_MARK_BUTTON,    "✅", 0, "U+2705",  true },
    { CHAR_EMOJI_CLAPPING,             "👏", 0, "U+1F44F", true },
    { CHAR_EMOJI_CLIPBOARD,            "📋", 0, "U+1F4CB", true },
    { CHAR_EMOJI_CLOUD,                "☁️", 0, "cloud", true },
    { CHAR_EMOJI_CLOUD_WITH_LIGHTNING, "🌩", 0, "U+1F329", true },
    { CHAR_EMOJI_CLOWN,                "🤡", 0, "U+1F921", true },
    { CHAR_EMOJI_COMPASS,              "🧭", 0, "U+1F9ED", true },
    { CHAR_EMOJI_CRESCENT_MOON,        "🌙", 0, "U+1F319", true },
    { CHAR_EMOJI_CROSS_MARK,           "❌", 0, "U+274C",  true },
    { CHAR_EMOJI_CRYING,               "😢", 0, "U+1F622", true },
    { CHAR_EMOJI_CRYING_LOUDLY,        "😭", 0, "U+1F62D", true },
    { CHAR_EMOJI_CUP_WITH_STRAW,       "🥤", 0, "U+1F964", true },
    { CHAR_EMOJI_DESKTOP_COMPUTER,     "🖥️", 0, "U+1F5A5", true },
    { CHAR_EMOJI_DEVIL,                "😈", 0, "U+1F608", true },
    { CHAR_EMOJI_DOUBLE_EXCLAMATION,   "‼️", 0, "U+203C",  true },
    { CHAR_EMOJI_EARTH,                "🌎", 0, "U+1F30E", true },
    { CHAR_EMOJI_EXCLAMATION,          "❗️", 0, "U+2757",  true },
    { CHAR_EMOJI_EXPLODING_HEAD,       "🤯", 0, "U+1F92F", true },
    { CHAR_EMOJI_EXPRESSIONLESS,       "😑", 0, "U+1F611", true },
    { CHAR_EMOJI_EYES,                 "👀", 0, "U+1F440", true },
    { CHAR_EMOJI_FACEPALM,             "🤦", 0, "U+1F926", true },
    { CHAR_EMOJI_FILE_FOLDER,          "📁", 0, "U+1F4C1", true },
    { CHAR_EMOJI_FILE_FOLDER_OPEN,     "📂", 0, "U+1F4C2", true },
    { CHAR_EMOJI_FIRE,                 "🔥", 0, "U+1F525", true },
    { CHAR_EMOJI_FLOPPY_DISK,          "💾", 0, "U+1F4BE", true },
    { CHAR_EMOJI_FRUSTRATED,           "😤", 0, "U+1F624", true },
    { CHAR_EMOJI_GESTURING_NO,         "🙅", 0, "U+1F645", true },
    { CHAR_EMOJI_GIFT,                 "🎁", 0, "U+1F381", true },
    { CHAR_EMOJI_GRIN,                 "😁", 0, "U+1F601", true },
    { CHAR_EMOJI_GRIN_SWEAT,           "😅", 0, "U+1F605", true },
    { CHAR_EMOJI_HALO,                 "😇", 0, "U+1F607", true },
    { CHAR_EMOJI_HAMBURGER,            "🍔", 0, "U+1F354", true },
    { CHAR_EMOJI_HANDSHAKE,            "🤝", 0, "U+1F91D", true },
    { CHAR_EMOJI_HEART,                "❤️", 0, "red heart", true },
    { CHAR_EMOJI_HEART_EYES,           "😍", 0, "U+1F60D", true },
    { CHAR_EMOJI_HIGH_VOLTAGE,         "⚡️", 0, "U+26A1",  true },
    { CHAR_EMOJI_HOLDING_TEARS,        "🥹", 0, "U+1F979", true },
    { CHAR_EMOJI_HOUSE,                "🏠", 0, "U+1F3E0", true },
    { CHAR_EMOJI_HUG,                  "🤗", 0, "U+1F917", true },
    { CHAR_EMOJI_HUNDRED,              "💯", 0, "U+1F4AF", true },
    { CHAR_EMOJI_ICE_CREAM,            "🍦", 0, "U+1F366", true },
    { CHAR_EMOJI_ICE_CUBE,             "🧊", 0, "U+1F9CA", true },
    { CHAR_EMOJI_INTERNET,             "🌐", 0, "U+1F310", true },
    { CHAR_EMOJI_JOKER,                "🃏", 0, "U+1F0CF", true },
    { CHAR_EMOJI_JOYSTICK,             "🕹️", 0, "U+1F579", true },
    { CHAR_EMOJI_KEY,                  "🔑", 0, "U+1F511", true },
    { CHAR_EMOJI_KEYBOARD,             "⌨️", 0, "computer keyboard", true },
    { CHAR_EMOJI_LAPTOP,               "💻", 0, "U+1F4BB", true },
    { CHAR_EMOJI_LAUGH,                "😂", 0, "U+1F602", true },
    { CHAR_EMOJI_LIGHT_BULB,           "💡", 0, "U+1F4A1", true },
    { CHAR_EMOJI_LINK,                 "🔗", 0, "U+1F517", true },
    { CHAR_EMOJI_LOCK_CLOSED,          "🔒", 0, "U+1F512", true },
    { CHAR_EMOJI_LOCK_OPEN,            "🔓", 0, "U+1F513", true },
    { CHAR_EMOJI_MAGNIFYING_GLASS,     "🔎", 0, "U+1F50E", true },
    { CHAR_EMOJI_MELTING_FACE,         "🫠", 0, "U+1FAE0", true },
    { CHAR_EMOJI_MEMO,                 "📝", 0, "U+1F4DD", true },
    { CHAR_EMOJI_MILKY_WAY,            "🌌", 0, "U+1F30C", true },
    { CHAR_EMOJI_MOAI,                 "🗿", 0, "U+1F5FF", true },
    { CHAR_EMOJI_MONEY_BAG,            "💰", 0, "U+1F4B0", true },
    { CHAR_EMOJI_MOTORCYCLE,           "🏍", 0, "U+1F3CD", true },
    { CHAR_EMOJI_MOTOR_SCOOTER,        "🛵", 0, "U+1F6F5", true },
    { CHAR_EMOJI_MUSICAL_NOTES,        "🎵", 0, "U+1F3B5", true },
    { CHAR_EMOJI_NAUSEATED,            "🤢", 0, "U+1F922", true },
    { CHAR_EMOJI_NEUTRAL,              "😐", 0, "U+1F610", true },
    { CHAR_EMOJI_OK,                   "👌", 0, "U+1F44C", true },
    { CHAR_EMOJI_PACKAGE,              "📦", 0, "U+1F4E6", true },
    { CHAR_EMOJI_PARTY_POPPER,         "🎉", 0, "U+1F389", true },
    { CHAR_EMOJI_PEACE,                "✌️", 0, "peace hand sign", true },
    { CHAR_EMOJI_PHONE,                "📞", 0, "U+1F4DE", true },
    { CHAR_EMOJI_PIZZA,                "🍕", 0, "U+1F355", true },
    { CHAR_EMOJI_PLEADING,             "🥺", 0, "U+1F97A", true },
    { CHAR_EMOJI_POOP,                 "💩", 0, "U+1F4A9", true },
    { CHAR_EMOJI_PRAY,                 "🙏", 0, "U+1F64F", true },
    { CHAR_EMOJI_PRINTER,              "🖨", 0, "U+1F5A8", true },
    { CHAR_EMOJI_PUSHPIN_ROUND,        "📍", 0, "U+1F4CD", true },
    { CHAR_EMOJI_QUESTION_MARK,        "❓", 0, "U+2753",  true },
    { CHAR_EMOJI_RAIN_CLOUD,           "🌧️", 0, "cloud with rain", true },
    { CHAR_EMOJI_RAISED_EYEBROW,       "🤨", 0, "U+1F928", true },
    { CHAR_EMOJI_RECYCLE,              "♻️", 0, "recycling symbol green", true },
    { CHAR_EMOJI_ROBOT,                "🤖", 0, "U+1F916", true },
    { CHAR_EMOJI_ROTFL,                "🤣", 0, "U+1F923", true },
    { CHAR_EMOJI_SCISSORS,             "✂️", 0, "scissors", true },
    { CHAR_EMOJI_SCOOTER,              "🛴", 0, "U+1F6F4", true },
    { CHAR_EMOJI_SHUSH,                "🤫", 0, "U+1F92B", true },
    { CHAR_EMOJI_SKULL,                "💀", 0, "U+1F480", true },
    { CHAR_EMOJI_SLEEPING,             "😴", 0, "U+1F634", true },
    { CHAR_EMOJI_SMILE,                "🙂", 0, "U+1F642", true },
    { CHAR_EMOJI_SMIRK,                "😏", 0, "U+1F60F", true },
    { CHAR_EMOJI_SNOWFLAKE,            "❄️", 0, "snowflake", true },
    { CHAR_EMOJI_SPARKLES,             "✨", 0, "U+2728",  true },
    { CHAR_EMOJI_SPIRAL_EYES,          "😵‍💫", 0, "spiral eyes", true },
    { CHAR_EMOJI_SPIRAL_NOTEPAD,       "🗒️", 0, "U+1F5D2", true },
    { CHAR_EMOJI_STAR,                 "⭐️", 0, "U+2B50",  true },
    { CHAR_EMOJI_STARSTRUCK,           "🤩", 0, "U+1F929", true },
    { CHAR_EMOJI_STOP_SIGN,            "🛑", 0, "U+1F6D1", true },
    { CHAR_EMOJI_SUN,                  "☀️", 0, "sun", true },
    { CHAR_EMOJI_SUNGLASSES,           "😎", 0, "U+1F60E", true },
    { CHAR_EMOJI_SURPRISED,            "😮", 0, "U+1F62E", true },
    { CHAR_EMOJI_TACO,                 "🌮", 0, "U+1F32E", true },
    { CHAR_EMOJI_THERMOMETER,          "🌡️", 0, "U+1F321", true },
    { CHAR_EMOJI_THINK,                "🤔", 0, "U+1F914", true },
    { CHAR_EMOJI_THUMB_DOWN,           "👎", 0, "U+1F44E", true },
    { CHAR_EMOJI_THUMB_UP,             "👍", 0, "U+1F44D", true },
    { CHAR_EMOJI_TRAIN,                "🚆", 0, "U+1F686", true },
    { CHAR_EMOJI_TRIANGULAR_FLAG,      "🚩", 0, "U+1F6A9", true },
    { CHAR_EMOJI_UNAMUSED,             "😒", 0, "U+1F612", true },
    { CHAR_EMOJI_UPSIDE_DOWN,          "🙃", 0, "U+1F643", true },
    { CHAR_EMOJI_VOMITING,             "🤮", 0, "U+1F92E", true },
    { CHAR_EMOJI_WARNING,              "⚠️", 0, "U+26A0",  true },
    { CHAR_EMOJI_WEARY,                "😩", 0, "U+1F629", true },
    { CHAR_EMOJI_WIND,                 "💨", 0, "U+1F4A8", true },
    { CHAR_EMOJI_WINK,                 "😉", 0, "U+1F609", true },
    { CHAR_EMOJI_WIRELESS,             "🛜", 0, "U+1F6DC", true },
    { CHAR_EMOJI_WORLD_MAP,            "🗺️", 0, "U+1F5FA", true },
    { CHAR_EMOJI_ZZZ,                  "💤", 0, "U+1F4A4", true },
};

// ─────────────────────────────────────────────────────────────
// Special Character Helper Functions
// ─────────────────────────────────────────────────────────────

// Opens the Apple macOS Emoji & Symbol popup; it only works in the compact view
static void open_emoji_menu(const char *search, bool auto_select) {
    tap_code16(MACOS_EMOJI_MENU);
    wait_ms(MACOS_EMOJI_MENU_DELAY);

    if (search) {
        SEND_STRING(search);
    }

    wait_ms(MACOS_EMOJI_MENU_INPUT_DELAY);
    tap_code(KC_DOWN);

    if (auto_select) {
        tap_code(KC_ENT);
    }
}

// Binary search lookup for special_chars[] (table is sorted by enum value)
static const special_char_entry_t *lookup_special_char(special_char_t key) {
    int low = 0;
    int high = ARRAY_SIZE(special_chars) - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        special_char_t mid_key = special_chars[mid].symbol_name;

        if (mid_key == key) {
            return &special_chars[mid];
        } else if (mid_key < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return NULL;
}

// ─────────────────────────────────────────────────────────────
// Special Character Function Definitions
// ─────────────────────────────────────────────────────────────

// Emit a special character
void special_char_macro(const special_char_t symbol) {
    mod_state_t saved = mod_state_save_and_clear();

    const special_char_entry_t *entry = lookup_special_char(symbol);
    if (!entry) {
        mod_state_restore(&saved);
        return;
    }

    if (current_os == OS_MACOS) {
        if (entry->macos_keycode) {
            // macOS ABC‑Extended
            tap_code16(entry->macos_keycode);
        } else {
            // macOS Emoji popup
            open_emoji_menu(entry->emoji_search, entry->auto_select);
        }
    } else {
        // Windows / Linux: direct Unicode
        SEND_STRING(entry->unicode);
    }

    mod_state_restore(&saved);
}
