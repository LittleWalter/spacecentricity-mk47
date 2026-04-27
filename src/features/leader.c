// REF: https://rgoulter.com/blog/posts/programming/2024-06-16-using-the-qmk-leader-key-for-fancy-keyboard-functionality.html

#ifdef LEADER_ENABLE

#include "leader.h"
#include "src/core/keymap.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_surround.h"
#include "src/macros/mac_programming.h"

leader_state_t leader_state = {
    .enabled = true,
    .layer = _BASE,
    .active = false,
    .done = false,
    .success = false,
    .prev_active_replay_mode = LEADER_REPLAY_HISTORY,
    .replay_mode = LEADER_REPLAY_HISTORY,
    .flash_timer = 0,
    .buffer = {0},
    .size = 0,
};

// Enable/disable Leader Key sequences
void toggle_leader() {
    leader_state.enabled = !leader_state.enabled;
}

// ─────────────────────────────────────────────────────────────
// Leader Macro Action Tables
// ─────────────────────────────────────────────────────────────

// IMPORTANT: Emoji table invariants (required for optimized lookup)
//
// 1. Table MUST be sorted by first key (seq[0]) in ascending order.
// 2. Within each first-key group, entries MUST be sorted by second key (seq[1]).
// 3. 1-key sequences (len = 1) MUST appear before 2-key sequences for that key.
// 4. A second key of 0 is reserved for 1-key sequences.
// 5. If these invariants are broken, emoji_sequences() will fail.
//
// If the table grows too large, consider switching to a 2D lookup table or trie.
static const sequence_entry_t emoji_table[] = {
    // Sequence    Length  Emoji
    { {KC_A, 0},        1, CHAR_EMOJI_ANGRY },
    { {KC_A, KC_A},     2, CHAR_EMOJI_CENSORED },
    { {KC_A, KC_L},     2, CHAR_EMOJI_ALARM },
    { {KC_A, KC_N},     2, CHAR_EMOJI_HALO },
    { {KC_A, KC_P},     2, CHAR_EMOJI_AIRPLANE },
    { {KC_A, KC_U},     2, CHAR_EMOJI_AUTOMOBILE },
    { {KC_B, 0},        1, CHAR_EMOJI_BLUSH },
    { {KC_B, KC_A},     2, CHAR_EMOJI_EXCLAMATION },
    { {KC_B, KC_B},     2, CHAR_EMOJI_DOUBLE_EXCLAMATION },
    { {KC_B, KC_E},     2, CHAR_EMOJI_BULLSEYE },
    { {KC_B, KC_I},     2, CHAR_EMOJI_BICYCLE },
    { {KC_B, KC_K},     2, CHAR_EMOJI_BLOW_KISS },
    { {KC_B, KC_Q},     2, CHAR_EMOJI_EXLM_QUES },
    { {KC_B, KC_R},     2, CHAR_EMOJI_BRAIN },
    { {KC_B, KC_T},     2, CHAR_EMOJI_BED },
    { {KC_B, KC_U},     2, CHAR_EMOJI_BUS },
    { {KC_C, 0},        1, CHAR_EMOJI_CRY },
    { {KC_C, KC_A},     2, CHAR_EMOJI_CAMERA },
    { {KC_C, KC_B},     2, CHAR_EMOJI_CLIPBOARD },
    { {KC_C, KC_C},     2, CHAR_EMOJI_CRY_LOUDLY },
    { {KC_C, KC_D},     2, CHAR_EMOJI_CLOUD },
    { {KC_C, KC_H},     2, CHAR_EMOJI_CHECK_MARK },
    { {KC_C, KC_L},     2, CHAR_EMOJI_CLAP },
    { {KC_C, KC_M},     2, CHAR_EMOJI_CHECK_MARK_BUTTON },
    { {KC_C, KC_O},     2, CHAR_EMOJI_COMPASS },
    { {KC_C, KC_U},     2, CHAR_EMOJI_SCISSORS },
    { {KC_D, 0},        1, CHAR_EMOJI_SKULL },
    { {KC_D, KC_A},     2, CHAR_EMOJI_CALENDAR },
    { {KC_D, KC_E},     2, CHAR_EMOJI_DEVIL },
    { {KC_D, KC_L},     2, CHAR_EMOJI_DROOL },
    { {KC_D, KC_R},     2, CHAR_EMOJI_CUP_WITH_STRAW },
    { {KC_D, KC_T},     2, CHAR_EMOJI_DESKTOP_COMPUTER },
    { {KC_E, 0},        1, CHAR_EMOJI_EYES },
    { {KC_E, KC_A},     2, CHAR_EMOJI_EARTH },
    { {KC_E, KC_X},     2, CHAR_EMOJI_EXHALE },
    { {KC_F, 0},        1, CHAR_EMOJI_FIRE },
    { {KC_F, KC_D},     2, CHAR_EMOJI_FLOPPY_DISK },
    { {KC_F, KC_E},     2, CHAR_EMOJI_SCREAM_IN_FEAR },
    { {KC_F, KC_F},     2, CHAR_EMOJI_FILE_FOLDER },
    { {KC_F, KC_O},     2, CHAR_EMOJI_FILE_FOLDER_OPEN },
    { {KC_F, KC_P},     2, CHAR_EMOJI_FACEPALM },
    { {KC_F, KC_R},     2, CHAR_EMOJI_FRUSTRATED },
    { {KC_G, 0},        1, CHAR_EMOJI_GRIN },
    { {KC_G, KC_I},     2, CHAR_EMOJI_GIFT },
    { {KC_G, KC_M},     2, CHAR_EMOJI_GRIMACE },
    { {KC_G, KC_R},     2, CHAR_EMOJI_NAUSEATED },
    { {KC_G, KC_S},     2, CHAR_EMOJI_GRIN_SWEAT },
    { {KC_H, 0},        1, CHAR_EMOJI_HEART },
    { {KC_H, KC_A},     2, CHAR_EMOJI_HAMBURGER },
    { {KC_H, KC_E},     2, CHAR_EMOJI_HEART_EYES },
    { {KC_H, KC_H},     2, CHAR_EMOJI_HUG },
    { {KC_H, KC_L},     2, CHAR_EMOJI_LINK },
    { {KC_H, KC_O},     2, CHAR_EMOJI_HOUSE },
    { {KC_H, KC_S},     2, CHAR_EMOJI_HANDSHAKE },
    { {KC_H, KC_T},     2, CHAR_EMOJI_HOLDING_TEARS },
    { {KC_H, KC_U},     2, CHAR_EMOJI_HUNDRED },
    { {KC_H, KC_V},     2, CHAR_EMOJI_HIGH_VOLTAGE },
    { {KC_I, 0},        1, CHAR_EMOJI_ICE_CREAM },
    { {KC_I, KC_C},     2, CHAR_EMOJI_ICE_CUBE },
    { {KC_I, KC_N},     2, CHAR_EMOJI_INTERNET },
    { {KC_J, 0},        1, CHAR_EMOJI_CLOWN },
    { {KC_J, KC_S},     2, CHAR_EMOJI_JOYSTICK },
    { {KC_K, 0},        1, CHAR_EMOJI_KEY },
    { {KC_K, KC_B},     2, CHAR_EMOJI_KEYBOARD },
    { {KC_L, 0},        1, CHAR_EMOJI_LAUGH },
    { {KC_L, KC_B},     2, CHAR_EMOJI_LIGHT_BULB },
    { {KC_L, KC_C},     2, CHAR_EMOJI_LOCK_CLOSED },
    { {KC_L, KC_I},     2, CHAR_EMOJI_CLOUD_WITH_LIGHTNING },
    { {KC_L, KC_O},     2, CHAR_EMOJI_LOCK_OPEN },
    { {KC_L, KC_T},     2, CHAR_EMOJI_LAPTOP },
    { {KC_M, 0},        1, CHAR_EMOJI_EXPLODING_HEAD },
    { {KC_M, KC_B},     2, CHAR_EMOJI_MONEY_BAG },
    { {KC_M, KC_C},     2, CHAR_EMOJI_MOTORCYCLE },
    { {KC_M, KC_E},     2, CHAR_EMOJI_MEMO },
    { {KC_M, KC_F},     2, CHAR_EMOJI_MELTING_FACE },
    { {KC_M, KC_G},     2, CHAR_EMOJI_MAGNIFYING_GLASS },
    { {KC_M, KC_S},     2, CHAR_EMOJI_MOTOR_SCOOTER },
    { {KC_M, KC_U},     2, CHAR_EMOJI_MUSICAL_NOTES },
    { {KC_M, KC_W},     2, CHAR_EMOJI_MILKY_WAY },
    { {KC_N, 0},        1, CHAR_EMOJI_CRESCENT_MOON },
    { {KC_N, KC_A},     2, CHAR_EMOJI_UNAMUSED },
    { {KC_N, KC_E},     2, CHAR_EMOJI_NEUTRAL },
    { {KC_N, KC_O},     2, CHAR_EMOJI_GESTURING_NO },
    { {KC_O, 0},        1, CHAR_EMOJI_SURPRISED },
    { {KC_O, KC_K},     2, CHAR_EMOJI_OK },
    { {KC_P, 0},        1, CHAR_EMOJI_POOP },
    { {KC_P, KC_H},     2, CHAR_EMOJI_PHONE },
    { {KC_P, KC_K},     2, CHAR_EMOJI_PACKAGE },
    { {KC_P, KC_L},     2, CHAR_EMOJI_PLEAD },
    { {KC_P, KC_P},     2, CHAR_EMOJI_PUSHPIN_ROUND },
    { {KC_P, KC_R},     2, CHAR_EMOJI_PRINTER },
    { {KC_P, KC_T},     2, CHAR_EMOJI_PRAY },
    { {KC_Q, 0},        1, CHAR_EMOJI_THINK },
    { {KC_Q, KC_M},     2, CHAR_EMOJI_QUESTION_MARK },
    { {KC_R, 0},        1, CHAR_EMOJI_ROBOT },
    { {KC_R, KC_A},     2, CHAR_EMOJI_RAIN_CLOUD },
    { {KC_R, KC_B},     2, CHAR_EMOJI_RAISED_EYEBROW },
    { {KC_R, KC_C},     2, CHAR_EMOJI_RECYCLE },
    { {KC_R, KC_E},     2, CHAR_EMOJI_RELIEF },
    { {KC_R, KC_F},     2, CHAR_EMOJI_TRIANGULAR_FLAG },
    { {KC_R, KC_O},     2, CHAR_EMOJI_ROTFL },
    { {KC_S, 0},        1, CHAR_EMOJI_SMILE },
    { {KC_S, KC_C},     2, CHAR_EMOJI_SCOOTER },
    { {KC_S, KC_E},     2, CHAR_EMOJI_STARSTRUCK },
    { {KC_S, KC_F},     2, CHAR_EMOJI_MOAI },
    { {KC_S, KC_G},     2, CHAR_EMOJI_SUNGLASSES },
    { {KC_S, KC_H},     2, CHAR_EMOJI_SHUSH },
    { {KC_S, KC_L},     2, CHAR_EMOJI_SLEEPING },
    { {KC_S, KC_M},     2, CHAR_EMOJI_SMIRK },
    { {KC_S, KC_N},     2, CHAR_EMOJI_SNOWFLAKE },
    { {KC_S, KC_P},     2, CHAR_EMOJI_SPARKLES },
    { {KC_S, KC_S},     2, CHAR_EMOJI_STOP_SIGN },
    { {KC_S, KC_T},     2, CHAR_EMOJI_STAR },
    { {KC_S, KC_U},     2, CHAR_EMOJI_SUN },
    { {KC_T, 0},        1, CHAR_EMOJI_THUMB_UP },
    { {KC_T, KC_A},     2, CHAR_EMOJI_TACO },
    { {KC_T, KC_D},     2, CHAR_EMOJI_THUMB_DOWN },
    { {KC_T, KC_E},     2, CHAR_EMOJI_THERMOMETER },
    { {KC_T, KC_R},     2, CHAR_EMOJI_TRAIN },
    { {KC_T, KC_T},     2, CHAR_EMOJI_THUMB_DOWN },
    { {KC_T, KC_U},     2, CHAR_EMOJI_THUMB_UP },
    { {KC_U, 0},        1, CHAR_EMOJI_UPSIDE_DOWN },
    { {KC_V, 0},        1, CHAR_EMOJI_PEACE },
    { {KC_V, KC_O},     2, CHAR_EMOJI_VOMITING },
    { {KC_V, KC_X},     2, CHAR_EMOJI_SPIRAL_EYES },
    { {KC_W, 0},        1, CHAR_EMOJI_WINK },
    { {KC_W, KC_A},     2, CHAR_EMOJI_WARNING },
    { {KC_W, KC_C},     2, CHAR_EMOJI_JOKER },
    { {KC_W, KC_E},     2, CHAR_EMOJI_WEARY },
    { {KC_W, KC_I},     2, CHAR_EMOJI_WIND },
    { {KC_W, KC_M},     2, CHAR_EMOJI_WORLD_MAP },
    { {KC_W, KC_N},     2, CHAR_EMOJI_WIRELESS },
    { {KC_X, 0},        1, CHAR_EMOJI_EXPRESSIONLESS },
    { {KC_X, KC_M},     2, CHAR_EMOJI_CROSS_MARK },
    { {KC_Y, 0},        1, CHAR_EMOJI_PARTY_POPPER },
    { {KC_Y, KC_F},     2, CHAR_EMOJI_PARTY_FACE },
    { {KC_Z, 0},        1, CHAR_EMOJI_PIZZA },
    { {KC_Z, KC_Z},     2, CHAR_EMOJI_ZZZ },
};

// Table of non-emoji symbols
// NOTE: Lexicographic ordering is alpha sequences first, then whitespace
static const sequence_entry_t symbol_table[] = {
    // Sequence        Length  Annotation
    { {KC_A,    KC_P},      2, CHAR_APPROX },
    { {KC_C,    KC_D},      2, CHAR_CENTER_DOT },
    { {KC_C,    KC_R},      2, CHAR_COPYRIGHT },
    { {KC_D,    0},         1, CHAR_ARROW_DOWN },
    { {KC_D,    KC_D},      2, CHAR_DOUBLE_ARROW_DOWN },
    { {KC_D,    KC_E},      2, CHAR_DEGREE },
    { {KC_D,    KC_I},      2, CHAR_DIVIDE },
    { {KC_E,    KC_L},      2, CHAR_ELLIPSIS },
    { {KC_E,    KC_M},      2, CHAR_EM_DASH },
    { {KC_E,    KC_N},      2, CHAR_EN_DASH },
    { {KC_G,    KC_E},      2, CHAR_GTE },
    { {KC_I,    0},         1, CHAR_INFINITY },
    { {KC_L,    0},         1, CHAR_ARROW_LEFT },
    { {KC_L,    KC_D},      2, CHAR_DOUBLE_ARROW_LEFT },
    { {KC_L,    KC_E},      2, CHAR_LTE },
    { {KC_M,    KC_U},      2, CHAR_MULTIPLY },
    { {KC_N,    KC_E},      2, CHAR_NEQ },
    { {KC_P,    KC_A},      2, CHAR_PARAGRAPH },
    { {KC_R,    0},         1, CHAR_ARROW_RIGHT },
    { {KC_R,    KC_D},      2, CHAR_DOUBLE_ARROW_RIGHT },
    { {KC_R,    KC_E},      2, CHAR_REGISTERED },
    { {KC_S,    KC_E},      2, CHAR_SECTION },
    { {KC_S,    KC_T},      2, CHAR_STAR },
    { {KC_T,    KC_M},      2, CHAR_TRADEMARK },
    { {KC_U,    0},         1, CHAR_ARROW_UP },
    { {KC_U,    KC_D},      2, CHAR_DOUBLE_ARROW_UP },
    { {KC_V,    KC_E},      2, CHAR_VERT_ELLIPSIS },
    { {KC_ENT,  0},         1, CHAR_ENTER },
    { {KC_ENT,  KC_ENT},    2, CHAR_CARRIAGE_RETURN },
    { {KC_ESC,  0},         1, CHAR_ESCAPE },
    { {KC_BSPC, 0},         1, CHAR_BACKSPACE },
    { {KC_BSPC, KC_BSPC},   2, CHAR_DELETE },
    { {KC_TAB,  0},         1, CHAR_TAB },
    { {KC_TAB,  KC_TAB},    2, CHAR_TAB_REVERSE },
    { {KC_SPC,  0},         1, CHAR_OPEN_BOX },
};

// Table of available surround sequences leader sequences
static const sequence_entry_t surround_table[] = {
    // Sequence Length  Surround symbols
    { {KC_A, 0},     1, SUR_ABR },
    { {KC_C, 0},     1, SUR_CBR },
    { {KC_D, 0},     1, SUR_DQUO },
    { {KC_G, 0},     1, SUR_GRV },
    { {KC_P, 0},     1, SUR_PAREN },
    { {KC_Q, 0},     1, SUR_QUOT },
    { {KC_S, 0},     1, SUR_BRC },
};

// Table of available annotation sequences leader sequences
static const sequence_entry_t notes_table[] = {
    // Sequence Length  Annotation
    { {KC_B, 0},     1, DEV_BUG },
    { {KC_C, 0},     2, DEV_CLEANUP },
    { {KC_D, 0},     2, DEV_DEPRECATED },
    { {KC_F, 0},     1, DEV_FIXME },
    { {KC_H, 0},     1, DEV_HACK },
    { {KC_I, 0},     1, DEV_IMPORTANT },
    { {KC_N, 0},     1, DEV_NOTE },
    { {KC_O, 0},     1, DEV_OPTIMIZE },
    { {KC_R, 0},     1, DEV_REF },
    { {KC_S, 0},     2, DEV_SECTION },
    { {KC_T, 0},     1, DEV_TODO },
    { {KC_W, 0},     1, DEV_WARNING },
};

// ─────────────────────────────────────────────────────────────
// Leader Replay Private Globals
// ─────────────────────────────────────────────────────────────

// Circular buffer of history entries
static leader_entry_t leader_history[LEADER_HISTORY_SIZE];

// Index of the next history slot to write into. Wraps around using modulo arithmetic.
static uint8_t leader_history_index = 0;

// Leader favorites save slots
// TIP: Replace these init values w/ your favorites if you don't want these items blank when
// booting keyboard.
static leader_entry_t leader_favorites[LEADER_FAVORITES_SIZE] = {
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
    { LEAD_NONE, 0 },
};

// ─────────────────────────────────────────────────────────────
// Leader Replay Function Definitions
// ─────────────────────────────────────────────────────────────

// Execute a stored leader sequence action.
// The correct macro is chosen based on the entry's category.
static void run_leader_entry(const leader_entry_t entry) {
    switch (entry.leader) {
        case LEAD_SYMBOL:
        case LEAD_EMOJI:
            special_char_macro(entry.name);
            break;
        case LEAD_DEV_NOTE:
            notes_macro(entry.name);
            break;
        case LEAD_SURROUND:
            surround_macro(entry.name);
            break;
        case LEAD_NONE: // Invalid history
            break;
        default: break;
    }
}

// Replay a Leader entry (history or favorites) based on the current replay mode.
void replay_leader(const uint8_t index) {
    if (leader_state.enabled && leader_state.replay_mode != LEADER_REPLAY_OFF) {
        leader_state.replay_mode == LEADER_REPLAY_HISTORY ? run_leader_history(index)
                                                          : run_leader_favorites(index);
    }
}

// ──────────────────────────────
// Leader Replay Toggles
// ──────────────────────────────

// Toggle replay mode on/off, restoring the last active mode when re-enabled.
void toggle_leader_replay(void) {
    if (leader_state.replay_mode == LEADER_REPLAY_OFF) {
        leader_state.replay_mode = leader_state.prev_active_replay_mode;
    } else {
        leader_state.prev_active_replay_mode = leader_state.replay_mode;
        leader_state.replay_mode = LEADER_REPLAY_OFF;
    }
}

// Switch between History and Favorites replay (only when replay is active).
void toggle_leader_replay_favorites(void) {
    if (leader_state.replay_mode != LEADER_REPLAY_OFF) {
        leader_state.replay_mode =
            (leader_state.replay_mode == LEADER_REPLAY_HISTORY) ? LEADER_REPLAY_FAVORITES
                                                                : LEADER_REPLAY_HISTORY;
    }
}

// ──────────────────────────────
// Leader History
// ──────────────────────────────

/* The history subsystem records the last LEADER_HISTORY_SIZE successful leader actions
 * (emoji insertions, surround macros, dev-note macros, etc.).
 *
 * Each entry stores:
 *   - the category of leader action (emoji, surround, dev note)
 *   - the specific macro name/value used
 *
 * The history is implemented as a ring buffer so it always contains the most recent
 * LEADER_HISTORY_SIZE entries without shifting or reallocating memory.
 *
 * History replay occurs on _UPPER layer via hold tap-dance on the number keys.
 */

// Returns true if two leader_entry_t values represent the same entry.
static bool equals(const leader_entry_t *a, const leader_entry_t *b) {
    return a->name == b->name && a->leader == b->leader;
}

// Retrieve a history entry by "age":
//   offset = 0 → most recent
//   offset = 1 → second most recent
//   offset = 2 → third most recent
//
// If offset exceeds the buffer size, return an empty entry.
static leader_entry_t *leader_history_get(const uint8_t offset) {
    if (offset >= LEADER_HISTORY_SIZE) {
        return NULL;
    }
    // Convert logical offset into physical ring-buffer index.
    // Example: if index = 3 and offset = 0 → return index 2.
    int8_t idx = leader_history_index - 1 - offset;
    if (idx < 0) idx += LEADER_HISTORY_SIZE;

    return &leader_history[idx];
}

// Push a new entry into the history ring buffer.
// Overwrites the oldest entry when the buffer is full.
static void leader_history_push(leader_t leader, uint16_t name) {
    const leader_entry_t e = {leader, name};
    leader_entry_t *last = leader_history_get(0);
    // Disallow multiple duplicates in a row
    if (!last || !equals(&e, last)) {
        leader_history[leader_history_index] = e;
        // Advance write index (wrap around at buffer size)
        leader_history_index = (leader_history_index + 1) % LEADER_HISTORY_SIZE;
    }
}

// Execute a stored history entry.
// This is called from tap-dance or other triggers.
void run_leader_history(const uint8_t index) {
    if (index < LEADER_HISTORY_SIZE) {
        leader_entry_t *e = leader_history_get(index);
        if (e && e->leader != LEAD_NONE) {
            run_leader_entry(*e);
        }
    }
}

// ──────────────────────────────
// Leader Favorites
// ──────────────────────────────

// Saves the last Leader sequence action into a given favorites index.
void save_leader_favorites(const uint8_t index) {
    if (index < LEADER_FAVORITES_SIZE) {
        const leader_entry_t *last_ptr = leader_history_get(0);
        if (last_ptr && last_ptr->leader != LEAD_NONE) {
            leader_favorites[index] = *last_ptr;
        }
    }
}

// Executes a stored favorites entry.
void run_leader_favorites(const uint8_t index) {
    if (index < LEADER_FAVORITES_SIZE) {
        run_leader_entry(leader_favorites[index]);
    }
}

// ─────────────────────────────────────────────────────────────
// Leader Sequence Handler Function Definitions
// ─────────────────────────────────────────────────────────────

// Early-exit optimization helper:
// Since the tables are sorted, we can break or continue based on
// the key comparisons. This keeps the lookup O(N) but
// significantly reduces the average number of iterations.
//
// OPTIMIZE:
// If tables grow much larger, consider switching to 2D lookup
// table or trie for O(1) or O(k) matching.
//
// NOTE: Because sequences with larger tables begin with a prefix
// (EMOJI_LEADER, SYMBOL_LEADER), the user's actual first
// meaningful key is leader_state.buffer[1].
static loop_state_t check_early_exit(const sequence_entry_t *entry, const uint8_t has_prefix) {
    const uint8_t buffer_index_offset = has_prefix ? 1 : 0;
    // Guard for sequence size
    if (entry->len != leader_state.size - buffer_index_offset) {
        return LOOP_NEXT;
    }
    // Check each sequence char for lexicographic order
    for (uint8_t i = 0; i < entry->len; i++) {
        if (leader_state.buffer[buffer_index_offset+i] < entry->seq[i]) {
            return LOOP_EXIT; // past the possible match range, exit loop
        }
        if (leader_state.buffer[buffer_index_offset+i] > entry->seq[i]) {
            return LOOP_NEXT; // this entry's first keycode doesn't match
        }
    }
    return LOOP_OK;
}

// Handles emoji Leader sequences; returns true on success.
// The emoji_table is sorted by first key, then second key.
// This allows early-exit checks to skip entire groups of entries.
static bool emoji_sequences(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(emoji_table); i++) {
        const sequence_entry_t *e = &emoji_table[i];

        // Early-exit optimization
        const loop_state_t entry_check = check_early_exit(e, true);
        if (entry_check == LOOP_EXIT) {
            break;
        } else if (entry_check == LOOP_NEXT) {
            continue;
        }

        if ((e->len == 1 && leader_sequence_two_keys(EMOJI_LEADER, e->seq[0]))
            || (e->len == 2 && leader_sequence_three_keys(EMOJI_LEADER, e->seq[0], e->seq[1]))) {
            special_char_macro(e->name);
            leader_history_push(LEAD_EMOJI, e->name);
            return true;
        }
    }

    return false;
}

// Handles non-emoji special characters.
// The symbol_table is sorted by first key, then second key.
// This allows early-exit checks to skip entire groups of entries.
static bool symbol_sequences(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(emoji_table); i++) {
        const sequence_entry_t *e = &symbol_table[i];

        // Early-exit optimization
        const loop_state_t entry_check = check_early_exit(e, true);
        if (entry_check == LOOP_EXIT) {
            break;
        } else if (entry_check == LOOP_NEXT) {
            continue;
        }

        if ((e->len == 1 && leader_sequence_two_keys(SYMBOL_LEADER, e->seq[0]))
            || (e->len == 2 && leader_sequence_three_keys(SYMBOL_LEADER, e->seq[0], e->seq[1]))) {
            special_char_macro(e->name);
            leader_history_push(LEAD_SYMBOL, e->name);
            return true;
        }
    }

    return false;
}

#ifdef RGB_MATRIX_ENABLE
// Handles RGB matrix Leader sequences; returns true on success, false otherwise.
static bool rgb_sequences(void) {
    if (leader_sequence_two_keys(RGB_LEADER, KC_N)) { // mnemonic: RGB Next effect
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
    } else {
        return false;
    }

    return true;
}
#endif

// Handles surround-character Leader sequences.
// Iterates through the surround_table and executes the matching surround macro when a
// single-key Leader sequence matches the entry.
static bool surround_sequences(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(surround_table); i++) {
        const sequence_entry_t *e = &surround_table[i];
        if (leader_sequence_one_key(e->seq[0])) {
            surround_macro(e->name);
            leader_history_push(LEAD_SURROUND, e->name);
            return true;
        }
    }
    return false;
}

// Handles annotation Leader sequences.
// Iterates through the notes_table and executes the matching annotation macro when a single-key,
// and occasionally two-key, Leader sequence matches the entry.
static bool annotation_sequences(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(notes_table); i++) {
        const sequence_entry_t *e = &notes_table[i];
        if ((e->len == 1 && leader_sequence_one_key(e->seq[0]))
            || (e->len == 2 && leader_sequence_two_keys(DEV_LEADER, e->seq[0]))) {
            notes_macro(e->name);
            leader_history_push(LEAD_DEV_NOTE, e->name);
            return true;
        }
    }
    return false;
}

// Handles miscellaneous Leader sequences; returns true on success, false otherwise.
static bool misc_sequences(void) {
    if (leader_sequence_one_key(KC_M)) {
        SEND_STRING(EMAIL_PRIMARY);
    } else if (leader_sequence_two_keys(KC_M, KC_M)) {
        SEND_STRING(EMAIL_SECONDARY);
    } else if (leader_sequence_three_keys(KC_M, KC_M, KC_M)) {
        SEND_STRING(EMAIL_TERTIARY);
    } else {
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
// Public Leader Sequence Callbacks
// ─────────────────────────────────────────────────────────────

// Helper that resets the Leader state machine on each run
static void restart_leader_state(void) {
    leader_state.active = true;
    leader_state.done = false;
    leader_state.success = true; // Assume user entered valid sequence until proven otherwise
    leader_state.size = 0;
}

// Resets Leader sequence flash state and switches to temporary Leader layer.
void leader_start_user(void) {
    if (leader_state.enabled) {
        restart_leader_state();

        // To avoid issues with tap-dance and mod-tap keys, go to dedicated alpha layer
        uint8_t layer = get_highest_layer(layer_state);
        switch (layer) {
            case _UPPER:
                leader_state.layer = _LEAD_DIGIT;
                layer_on(leader_state.layer);
                break;
            case _ARR_L:
                leader_state.layer = _LEAD_ALPHA;
                layer_on(leader_state.layer);
                break;
            default: break;
        }
    }
}

/*
 * Handle the end of a Leader sequence.
 *
 * - Attempts to match the sequence against all handler groups
 *   (emoji, RGB, surround, annotation, misc).
 * - If no handler recognizes the sequence, marks it as unsuccessful.
 * - Updates Leader state flags and flash timer; flash green on success, red on failure.
 * - Exits the temporary Leader layer used during sequence entry.
 */
void leader_end_user(void) {
    if (!leader_state.enabled) return;

    if (!surround_sequences()
        && !annotation_sequences()
#ifdef RGB_MATRIX_ENABLE
        && !rgb_sequences()
#endif
        && !symbol_sequences()
        && !emoji_sequences()
        && !misc_sequences()) {
        leader_state.success = false;
    }

    leader_state.done = true;
    leader_state.active = false;
    leader_state.flash_timer = timer_read();

    layer_off(leader_state.layer);
}

#endif
