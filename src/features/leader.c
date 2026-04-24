// REF: https://rgoulter.com/blog/posts/programming/2024-06-16-using-the-qmk-leader-key-for-fancy-keyboard-functionality.html

#ifdef LEADER_ENABLE

#include "leader.h"
#include "src/core/keymap.h"
#include "src/macros/mac_special_char.h"
#include "src/macros/mac_surround.h"
#include "src/macros/mac_programming.h"

leader_state_t leader_state = {
    .layer = _BASE,
    .active = false,
    .done = false,
    .success = false,
    .replay_history = true,
    .flash_timer = 0,
    .buffer = {0},
    .size = 0,
};

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
    { {KC_B, 0},        1, CHAR_EMOJI_BLUSH },
    { {KC_B, KC_E},     2, CHAR_EMOJI_BULLSEYE },
    { {KC_B, KC_K},     2, CHAR_EMOJI_BLOWING_KISS },
    { {KC_B, KC_R},     2, CHAR_EMOJI_BRAIN },
    { {KC_B, KC_T},     2, CHAR_EMOJI_BED },
    { {KC_C, 0},        1, CHAR_EMOJI_CRY },
    { {KC_C, KC_A},     2, CHAR_EMOJI_CAMERA },
    { {KC_C, KC_H},     2, CHAR_EMOJI_CHECK_MARK },
    { {KC_C, KC_L},     2, CHAR_EMOJI_CLAPPING },
    { {KC_C, KC_M},     2, CHAR_EMOJI_CHECK_MARK_BUTTON },
    { {KC_C, KC_O},     2, CHAR_EMOJI_COMPASS },
    { {KC_D, 0},        1, CHAR_EMOJI_SKULL },
    { {KC_D, KC_A},     2, CHAR_EMOJI_CALENDAR },
    { {KC_D, KC_E},     2, CHAR_EMOJI_DEVIL },
    { {KC_E, 0},        1, CHAR_EMOJI_EYES },
    { {KC_E, KC_A},     2, CHAR_EMOJI_EARTH },
    { {KC_E, KC_E},     2, CHAR_EMOJI_DOUBLE_EXCLAMATION },
    { {KC_F, 0},        1, CHAR_EMOJI_FIRE },
    { {KC_F, KC_P},     2, CHAR_EMOJI_FACEPALM },
    { {KC_F, KC_R},     2, CHAR_EMOJI_FRUSTRATED },
    { {KC_G, 0},        1, CHAR_EMOJI_GRIN },
    { {KC_G, KC_I},     2, CHAR_EMOJI_GIFT },
    { {KC_G, KC_S},     2, CHAR_EMOJI_GRIN_SWEAT },
    { {KC_H, 0},        1, CHAR_EMOJI_HEART },
    { {KC_H, KC_A},     2, CHAR_EMOJI_HAMBURGER },
    { {KC_H, KC_E},     2, CHAR_EMOJI_HEART_EYES },
    { {KC_H, KC_H},     2, CHAR_EMOJI_HUG },
    { {KC_H, KC_O},     2, CHAR_EMOJI_HOUSE },
    { {KC_H, KC_S},     2, CHAR_EMOJI_HANDSHAKE },
    { {KC_H, KC_T},     2, CHAR_EMOJI_HOLDING_TEARS },
    { {KC_H, KC_U},     2, CHAR_EMOJI_HUNDRED },
    { {KC_H, KC_V},     2, CHAR_EMOJI_HIGH_VOLTAGE },
    { {KC_I, 0},        1, CHAR_EMOJI_ICE_CREAM },
    { {KC_I, KC_C},     2, CHAR_EMOJI_ICE_CUBE },
    { {KC_I, KC_N},     2, CHAR_EMOJI_INTERNET },
    { {KC_J, 0},        1, CHAR_EMOJI_CLOWN },
    { {KC_K, 0},        1, CHAR_EMOJI_KEY },
    { {KC_L, 0},        1, CHAR_EMOJI_LAUGH },
    { {KC_L, KC_B},     2, CHAR_EMOJI_LIGHT_BULB },
    { {KC_L, KC_C},     2, CHAR_EMOJI_LOCK_CLOSED },
    { {KC_L, KC_I},     2, CHAR_EMOJI_LINK },
    { {KC_L, KC_O},     2, CHAR_EMOJI_LOCK_OPEN },
    { {KC_L, KC_T},     2, CHAR_EMOJI_LAPTOP },
    { {KC_M, 0},        1, CHAR_EMOJI_EXPLODING_HEAD },
    { {KC_M, KC_B},     2, CHAR_EMOJI_MONEY_BAG },
    { {KC_M, KC_E},     2, CHAR_EMOJI_MEMO },
    { {KC_M, KC_F},     2, CHAR_EMOJI_MELTING_FACE },
    { {KC_M, KC_G},     2, CHAR_EMOJI_MAGNIFYING_GLASS },
    { {KC_M, KC_S},     2, CHAR_EMOJI_MILKSHAKE },
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
    { {KC_P, KC_P},     2, CHAR_EMOJI_PUSHPIN_ROUND },
    { {KC_P, KC_R},     2, CHAR_EMOJI_PRAY },
    { {KC_Q, 0},        1, CHAR_EMOJI_THINK },
    { {KC_Q, KC_M},     2, CHAR_EMOJI_QUESTION_MARK },
    { {KC_R, 0},        1, CHAR_EMOJI_ROBOT },
    { {KC_R, KC_A},     2, CHAR_EMOJI_RAIN_CLOUD },
    { {KC_R, KC_B},     2, CHAR_EMOJI_RAISED_EYEBROW },
    { {KC_R, KC_C},     2, CHAR_EMOJI_RECYCLE },
    { {KC_R, KC_F},     2, CHAR_EMOJI_TRIANGULAR_FLAG },
    { {KC_S, 0},        1, CHAR_EMOJI_SMILE },
    { {KC_S, KC_F},     2, CHAR_EMOJI_MOAI },
    { {KC_S, KC_G},     2, CHAR_EMOJI_SUNGLASSES },
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
    { {KC_T, KC_T},     2, CHAR_EMOJI_THUMB_DOWN },
    { {KC_T, KC_U},     2, CHAR_EMOJI_THUMB_UP },
    { {KC_U, 0},        1, CHAR_EMOJI_UPSIDE_DOWN },
    { {KC_V, 0},        1, CHAR_EMOJI_PEACE },
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
    { {KC_Z, 0},        1, CHAR_EMOJI_PIZZA },
    { {KC_Z, KC_Z},     2, CHAR_EMOJI_ZZZ },
};

// Execute a stored leader sequence action.
// The correct macro is chosen based on the entry's category.
static void run_leader_entry(const leader_entry_t entry) {
    switch (entry.leader) {
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

// ─────────────────────────────────────────────────────────────
// Leader History
// ─────────────────────────────────────────────────────────────
//
// This subsystem records the last LEADER_HISTORY_SIZE successful
// leader actions (emoji insertions, surround macros,
// dev-note macros, etc.).
//
// Each entry stores:
//   - the category of leader action (emoji, surround, dev note)
//   - the specific macro name/value used
//
// The history is implemented as a ring buffer so it always
// contains the most recent LEADER_HISTORY_SIZE entries without
// shifting or reallocating memory.
//
// History replay occurs on _UPPER layer via hold tap-dance
// on the number keys.

// Circular buffer of history entries
static leader_entry_t leader_history[LEADER_HISTORY_SIZE];

// Index of the next slot to write into. Wraps around using modulo arithmetic.
static uint8_t leader_history_index = 0;

// Returns true if two leader_entry_t values represent the same entry
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
void run_leader_history_entry(const uint8_t index) {
    if (index < LEADER_HISTORY_SIZE) {
        leader_entry_t *e = leader_history_get(index);
        if (e && e->leader != LEAD_NONE) {
            run_leader_entry(*e);
        }
    }
}

// ─────────────────────────────────────────────────────────────
// Leader Favorites
// ─────────────────────────────────────────────────────────────

// TIP: Replace these init values w/ your favorites if you don't want these items blank when
// booting keyboard.
static leader_entry_t favorites[LEADER_FAVORITES_SIZE] = {
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

// Saves the last Leader sequence action into a given favorites index
void save_leader_favorite(const uint8_t index) {
    if (index < LEADER_FAVORITES_SIZE) {
        const leader_entry_t *last_ptr = leader_history_get(0);
        if (last_ptr && last_ptr->leader != LEAD_NONE) {
            favorites[index] = *last_ptr;
        }
    }
}

// Executes a stored favorites entry.
void run_leader_favorites(const uint8_t index) {
    if (index < LEADER_FAVORITES_SIZE) {
        run_leader_entry(favorites[index]);
    }
}

// ─────────────────────────────────────────────────────────────
// Leader Sequence Handler Functions
// ─────────────────────────────────────────────────────────────

// Handles emoji Leader sequences; returns true on success.
// The emoji_table is sorted by first key, then second key.
// This allows early-exit checks to skip entire groups of entries.
//
// NOTE: Because emoji sequences begin with EMOJI_LEADER, the user's
// actual first meaningful key is buffer[1].
static bool emoji_sequences(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(emoji_table); i++) {
        const sequence_entry_t *e = &emoji_table[i];

        // Early-exit optimization:
        // Since the table is sorted, we can break or continue based on the
        // first and second key comparisons. This keeps the lookup O(N) but
        // significantly reduces the average number of iterations.
        //
        // If the table grows much larger, consider switching to a 2D lookup
        // table or trie for O(1) or O(k) matching.
        if (leader_state.buffer[1] < e->seq[0]) {
            break; // past the possible match range, exit loop
        }
        if (leader_state.buffer[1] > e->seq[0]) {
            continue; // this entry's first keycode doesn't match
        }
        // Check second key
        if (e->len == 2) {
            if (leader_state.buffer[2] < e->seq[1]) {
                break;
            }
            if (leader_state.buffer[2] > e->seq[1]) {
                continue;
            }
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

// Table of available surround sequences leader sequences
static const sequence_entry_t surround_table[] = {
    // Sequence  Length  Surround symbols
    { {KC_A, 0},      1, SUR_ABR },
    { {KC_C, 0},      1, SUR_CBR },
    { {KC_D, 0},      1, SUR_DQUO },
    { {KC_G, 0},      1, SUR_GRV },
    { {KC_P, 0},      1, SUR_PAREN },
    { {KC_Q, 0},      1, SUR_QUOT },
    { {KC_S, 0},      1, SUR_BRC },
};

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

// Table of available annotation sequences leader sequences
static const sequence_entry_t notes_table[] = {
    // Sequence  Length  Annotation
    { {KC_F, 0},      1, DEV_FIXME },
    { {KC_H, 0},      1, DEV_TIP },
    { {KC_I, 0},      1, DEV_INFO },
    { {KC_N, 0},      1, DEV_NOTE },
    { {KC_R, 0},      1, DEV_REF },
    { {KC_S, 0},      2, DEV_SECTION },
    { {KC_T, 0},      1, DEV_TODO },
    { {KC_W, 0},      1, DEV_WARNING },
};

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

// Resets the Leader state machine on each run
static void restart_leader_state(void) {
    leader_state.active = true;
    leader_state.done = false;
    leader_state.success = true; // Assume user entered valid sequence until proven otherwise
    leader_state.size = 0;
}

// ─────────────────────────────────────────────────────────────
// Public Leader Sequence Callbacks
// ─────────────────────────────────────────────────────────────

// Resets Leader sequence flash state and switches to temporary Leader layer.
void leader_start_user(void) {
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
    if (!surround_sequences()
        && !annotation_sequences()
#ifdef RGB_MATRIX_ENABLE
        && !rgb_sequences()
#endif
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
