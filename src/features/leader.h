#pragma once

#ifdef LEADER_ENABLE

#include QMK_KEYBOARD_H

#define LEADER_MAX_SEQUENCE_LENGTH 3 // QMK Leader sequence ceiling is 5 keycodes
#define LEADER_HISTORY_SIZE 10 // Any more that 8-12 seems excessive
#define LEADER_FAVORITES_SIZE 10

// Leader prefixes for each command namespace
#define EMOJI_LEADER   KC_NO    // Emoji sequences
#define RGB_LEADER     KC_R     // RGB matrix controls
#define DEV_LEADER     KC_DOT   // Developer / annotation commands

// Email constants used by Leader sequences
#define EMAIL_PRIMARY   "mail@example.com"
#define EMAIL_SECONDARY "another@example.com"
#define EMAIL_TERTIARY  "third@example.com"

/*
 * Leader sequence table entry.
 *
 * Each entry defines a 1–2 key sequence that follows the Leader prefix.
 * When the user completes a Leader sequence, the dispatcher compares the
 * typed keys against this table. If a match is found, the associated
 * action identifier ('name') is executed via the appropriate macro.
 *
 * Fields:
 *   seq[2]  – keycodes entered after the Leader prefix (1 or 2 keys)
 *   len     – number of keys in the sequence
 *   name    – action constant (CHAR_EMOJI_*, DEV_*, SUR_*, etc.)
 */
typedef struct {
    uint16_t seq[2]; // up to 2 keys after leader and prefix
    uint8_t  len;    // 1 or 2 chars
    uint16_t name;   // Constants: CHAR_EMOJI_*, DEV_*, SUR_*
} sequence_entry_t;

/*
 * Leader state tracking.
 *
 * This struct represents the lifecycle of a Leader sequence:
 *   active           - true while a Leader sequence is in progress
 *   done             - set once the sequence has been fully processed
 *   success          - true if any handler recognized and executed the sequence
 *   replay_history   - true if user wants to replay Leader history
 *   layer            - the temporary Leader layer active during processing
 *   flash_timer      - timestamp used for success/failure LED feedback
 *   buffer           - keycodes entered as part of the Leader sequence
 *   size             - number of keycodes stored in the buffer
 */
typedef struct {
    bool     active;
    bool     done;
    bool     success;
    bool     replay_history;
    uint8_t  layer;
    uint16_t flash_timer;
    uint16_t buffer[LEADER_MAX_SEQUENCE_LENGTH];
    uint8_t  size;
} leader_state_t;

extern leader_state_t leader_state;

// ─────────────────────────────────────────────────────────────
// Leader History
// ─────────────────────────────────────────────────────────────

typedef enum {
    LEAD_NONE,
    LEAD_DEV_NOTE,
    LEAD_EMOJI,
    LEAD_SURROUND
} leader_t;

typedef struct {
    leader_t leader; // category of tracked Leader sequences
    uint16_t name;   // named constant of the macro
} leader_entry_t;

// extern leader_history_entry_t leader_history[LEADER_HISTORY_SIZE];
void run_leader_history_entry(const uint8_t offset);

// ─────────────────────────────────────────────────────────────
// Leader Favorites
// ─────────────────────────────────────────────────────────────

// Saves the last Leader sequence action into a given favorites index
void save_leader_favorite(const uint8_t index);

// Executes a stored favorites entry.
void run_leader_favorites(const uint8_t index);

#endif
