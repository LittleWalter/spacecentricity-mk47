#pragma once

#ifdef RGB_MATRIX_ENABLE

#include QMK_KEYBOARD_H
#include "src/core/keymap.h"
#include "src/macros/macros.h"

// ms to flash success/fail of leader sequence, 150-200 ms is the sweetspot
#define RGB_LEADER_PASS_FAIL_DELAY 200

// ─────────────────────────────────────────────────────────────
// Caps Lock: Active Blinking
// ─────────────────────────────────────────────────────────────

#define RGB_CAPS_LOCK_BLINK_RATE 2000 // ms

typedef struct {
    bool blink_state;
    uint16_t timer;
} caps_lock_t;

// ─────────────────────────────────────────────────────────────
// RGB Preview Window: Used When Hitting RGB Keys on _FN
// ─────────────────────────────────────────────────────────────

#define RGB_PREVIEW_TIMEOUT 3000 // ms until layer indicators are allowed to activate again

typedef struct {
    bool triggered; // Guard prevents unintended preview on first-time layer changes
    uint16_t timer;
} rgb_preview_t;

extern rgb_preview_t rgb_preview;

// ─────────────────────────────────────────────────────────────
// Colors
// ─────────────────────────────────────────────────────────────

#define AMBER         255, 180, 0
#define APPLE_GREEN   80, 255, 120
#define BLUE          0, 0, 255
#define CRIMSON       220, 20, 60
#define CYAN          0, 255, 255
#define CYAN_MINT     120, 255, 230
#define DODGER_BLUE   30, 144, 255
#define ELECTRIC_BLUE 0, 150, 255
#define FOREST_GREEN  34, 139, 34
#define GOLD          255, 215, 0
#define GREEN         0, 255, 0
#define LIME_GREEN    0, 255, 80
#define MAGENTA       255, 0, 255
#define NAVY          0, 0, 128
#define NEON_MINT     80, 255, 230
#define ORANGE        255, 69, 0
#define PASTEL_CYAN   80, 220, 255
#define PURE_WHITE    255, 255, 255
#define PURPLE        128, 0, 255
#define RED           255, 0, 0
#define SPRING_GREEN  0, 255, 154
#define TEAL_GREEN    0, 200, 180
#define YELLOW        255, 255, 0

// ─────────────────────────────────────────────────────────────
// RGB Matrix Naming Scheme:
// LED_ROW<0-3>_<LEFT/RIGHT>_<INDEX/MIDDLE/RING/PINKY/CENTER>
// LED_ROW<1-2>_<COL0/COL11>
// LED_CORNER_<LEFT/RIGHT>_<TOP/BOTTOM>
// LED_THUMB_<LEFT/CENTER/RIGHT>
// ─────────────────────────────────────────────────────────────

/* Planck RGB Matrix Indices (0-46)
 *          COL0     PINKY     RING      MIDDLE    INDEX  ┣━━━━━ CENTER ━━━━━━┫  INDEX    MIDDLE     RING      PINKY     COL11
 *      ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
 * ROW0 │    0    │    1    │    2    │    3    │    4    │    5    │    6    │    7    │    8    │    9    │   10    │   11    │ TOP
 *      ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
 * ROW1 │   12    │   13    │   14    │   15    │   16    │   17    │   18    │   19    │   20    │   21    │   22    │   23    │ HOME
 *      ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
 * ROW2 │   24    │   25    │   26    │   27    │   28    │   29    │   30    │   31    │   32    │   33    │   34    │   35    │ LOWER
 *      ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
 * ROW3 │   36    │   37    │   38    │   39    │   40    │        41         │   42    │   43    │   44    │   45    │   46    │ BOTTOM
 *      └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
 *      ┣━━━━━━━━━━━━━━━━ LEFT ━━━━━━━━━━━━━━━━━ L THUMB ━┫    CENTER THUMB   ┣━ R THUMB ━━━━━━━━━━━━━━━━ RIGHT ━━━━━━━━━━━━━━━━┫
 */

// ─────────────────────────────
// Row 0: Top Row
// ─────────────────────────────
#define LED_ROW0_LEFT_PINKY   1
#define LED_ROW0_LEFT_RING    2
#define LED_ROW0_LEFT_MIDDLE  3
#define LED_ROW0_LEFT_INDEX   4
#define LED_ROW0_LEFT_CENTER  5

#define LED_ROW0_RIGHT_CENTER 6
#define LED_ROW0_RIGHT_INDEX  7
#define LED_ROW0_RIGHT_MIDDLE 8
#define LED_ROW0_RIGHT_RING   9
#define LED_ROW0_RIGHT_PINKY  10

// Corners
#define LED_CORNER_TOP_LEFT   0
#define LED_CORNER_TOP_RIGHT  11

// ─────────────────────────────
// Row 1: Home Row
// ─────────────────────────────
#define LED_ROW1_COL0         12

#define LED_ROW1_LEFT_PINKY   13
#define LED_ROW1_LEFT_RING    14
#define LED_ROW1_LEFT_MIDDLE  15
#define LED_ROW1_LEFT_INDEX   16
#define LED_ROW1_LEFT_CENTER  17

#define LED_ROW1_RIGHT_CENTER 18
#define LED_ROW1_RIGHT_INDEX  19
#define LED_ROW1_RIGHT_MIDDLE 20
#define LED_ROW1_RIGHT_RING   21
#define LED_ROW1_RIGHT_PINKY  22

#define LED_ROW1_COL11        23

// ─────────────────────────────
// Row 2: Lower Row
// ─────────────────────────────
#define LED_ROW2_COL0         24

#define LED_ROW2_LEFT_PINKY   25
#define LED_ROW2_LEFT_RING    26
#define LED_ROW2_LEFT_MIDDLE  27
#define LED_ROW2_LEFT_INDEX   28
#define LED_ROW2_LEFT_CENTER  29

#define LED_ROW2_RIGHT_CENTER 30
#define LED_ROW2_RIGHT_INDEX  31
#define LED_ROW2_RIGHT_MIDDLE 32
#define LED_ROW2_RIGHT_RING   33
#define LED_ROW2_RIGHT_PINKY  34

#define LED_ROW2_COL11        35

// ─────────────────────────────
// Row 3: Bottom Row
// ─────────────────────────────
#define LED_ROW3_LEFT_PINKY   37
#define LED_ROW3_LEFT_RING    38
#define LED_ROW3_LEFT_MIDDLE  39

// Thumb cluster
#define LED_THUMB_LEFT        40
#define LED_THUMB_CENTER      41 // Spacebar
#define LED_THUMB_RIGHT       42

#define LED_ROW3_RIGHT_MIDDLE 43
#define LED_ROW3_RIGHT_RING   44
#define LED_ROW3_RIGHT_PINKY  45

// Corners
#define LED_CORNER_BOTTOM_LEFT  36
#define LED_CORNER_BOTTOM_RIGHT 46

#endif
