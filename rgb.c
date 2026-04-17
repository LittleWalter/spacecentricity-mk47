#include "rgb.h"
#include "custom_keys.h"

// Caps Lock blink state w/ timer
static caps_lock_t caps_lock = { false, 0 };
// RGB preview mode state w/ timer
rgb_preview_t rgb_preview = { false, 0 };

// ─────────────────────────────────────────────────────────────
// RGB Helper Functions
// ─────────────────────────────────────────────────────────────

// Turn off all RGB lights in matrix
static void rgb_off(void) {
    rgb_matrix_set_color_all(RGB_OFF);
}

// Set held and to-layer keys to pure white
static void set_layer_key_color(uint8_t keyIndex) {
    rgb_matrix_set_color(keyIndex, PURE_WHITE);
}

// Sets RGB matrix to GOLD if OSM Shift is active and return true; otherwise, do nothing and return
// false.
static bool set_on_osm_shift_active(void) {
    const bool osm_shift = (get_oneshot_mods() & MOD_MASK_SHIFT) ||
                           (get_oneshot_locked_mods() & MOD_MASK_SHIFT);
    if (osm_shift) {
        rgb_matrix_set_color_all(GOLD);
        return true;
    }
    return false;
}

// Sets RGB matrix to blink RED if Caps Lock is active and return true; otherwise, do nothing and
// return false.
static bool set_on_caps_lock_active(void) {
    if (host_keyboard_led_state().caps_lock) {
        if (timer_elapsed(caps_lock.timer) > RGB_CAPS_LOCK_BLINK_RATE) {
            caps_lock.blink_state = !caps_lock.blink_state;
            caps_lock.timer = timer_read();
        }
        (caps_lock.blink_state) ? rgb_matrix_set_color_all(RED)
                                : rgb_off();
        return true;
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
// RGB Matrix
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

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    // Skip layer indicators when user hits RGB-related key on _FN; this allows you to see changes
    // immediately instead of back-and-forthing _BASE and _FN. Timer is (re)set inside the function
    // process_record_user. rgb_preview.triggered prevents unwanted previews on first boot.
    if (rgb_preview.triggered && timer_elapsed(rgb_preview.timer) < RGB_PREVIEW_TIMEOUT) {
        return true;
    }

    switch (layer) {
        // Change Base layer only if OSM Shift or Caps Lock is currently active
        case _BASE:
            // OSM Shift
            if (set_on_osm_shift_active()) {
                return false;
            }
            // Caps Lock
            if (set_on_caps_lock_active()) {
                return false;
            }
            break;

        /* Numpad Layer: Hold Left Thumb Key
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │   ESC   │ * % @ # │ 9  LSFT │ 8  LCTL │ 7  LALT │    .    │ ^   ¢ $ │ 7  RALT │ 8  RCTL │ 9  RSFT │ * % @ # │ ⌫  ⌫L ⌫w│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  ⇥   ⇤  │    +    │    6  F │    5  E │    4  D │ ( [ < { │ ) ] > } │    4  D │    5  E │    6  F │    +    │    ↵    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │    /    │    -    │    3  C │    2  B │    1  A │ , ; | & │ $ ¥ £ € │    1  A │    2  B │    3  C │    -    │    /    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  MOUSE  │🔇⏯ ⏹ C+M│🔉⏮ 🔅🔉 │🔊⏭ 🔆🔊 │<<H>>BASE│   =       ≈   ≠   │    0 ADJ│ ⇱ ^ h ← │ ⇟ } j ↓ │ ⇞ { k ↑ │ ⇲ $ l → │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         * Hold right thumb key (0), to momentarily activate _ADJ layer to get access to F1-F12 keys
         */
        case _LOWER:
            rgb_off();
            // Held Key: Left Thumb
            set_layer_key_color(LED_THUMB_LEFT);
            // Momentary Toggle
            set_layer_key_color(LED_CORNER_BOTTOM_LEFT);
            // Numbers
            rgb_matrix_set_color(LED_THUMB_RIGHT,       MAGENTA); // 0
            rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX,  MAGENTA); // 1
            rgb_matrix_set_color(LED_ROW2_LEFT_INDEX,   MAGENTA); // 1
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE, MAGENTA); // 2
            rgb_matrix_set_color(LED_ROW2_LEFT_MIDDLE,  MAGENTA); // 2
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,   MAGENTA); // 3
            rgb_matrix_set_color(LED_ROW2_LEFT_RING,    MAGENTA); // 3
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  MAGENTA); // 4
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,   MAGENTA); // 4
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, MAGENTA); // 5
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE,  MAGENTA); // 5
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   MAGENTA); // 6
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,    MAGENTA); // 6
            rgb_matrix_set_color(LED_ROW0_RIGHT_INDEX,  MAGENTA); // 7
            rgb_matrix_set_color(LED_ROW0_LEFT_INDEX,   MAGENTA); // 7
            rgb_matrix_set_color(LED_ROW0_RIGHT_MIDDLE, MAGENTA); // 8
            rgb_matrix_set_color(LED_ROW0_LEFT_MIDDLE,  MAGENTA); // 8
            rgb_matrix_set_color(LED_ROW0_RIGHT_RING,   MAGENTA); // 9
            rgb_matrix_set_color(LED_ROW0_LEFT_RING,    MAGENTA); // 9
            // Decimal Point
            rgb_matrix_set_color(LED_ROW0_LEFT_CENTER,  CYAN);
            break;

        /* Primary Number Layer: Hold Right Thumb Key
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │    `    │ , ; | & │    :    │ . … ⋮ • │    9    │    &    │    |    │    8    │ + - / * │    #    │ ^   ¢ $ │ ⌦  ⌦L ⌦w│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │    ~    │    7    │    5    │    1    │    3    │ ( [ < { │ ) ] > } │    2    │    0    │    4    │    6    │    ↵    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │    %    │    \    │    _    │ [ ( { < │CAPS LOCK│ $ ¥ £ € │    @    │ , ! ? . │ ] ) } > │    -    │    ?    │ “|” ‘|’ │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  MOUSE  │🔇⏯ ⏹ C+M│🔉⏮ 🔅🔉 │🔊⏭ 🔆🔊 │    ⌫    │   =       ≈   ≠   │<<H>>BASE│ ⇱ ^ h ← │ ⇟ } j ↓ │ ⇞ { k ↑ │ ⇲ $ l → │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _UPPER:
            rgb_off();
            // Held Key: Right Thumb
            set_layer_key_color(LED_THUMB_RIGHT);
            // Momentary Toggle
            set_layer_key_color(LED_CORNER_BOTTOM_LEFT);
            // Numbers
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, MAGENTA); // 0
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE,  MAGENTA); // 1
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  MAGENTA); // 2
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,   MAGENTA); // 3
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   MAGENTA); // 4
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,    MAGENTA); // 5
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  MAGENTA); // 6
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,   MAGENTA); // 7
            rgb_matrix_set_color(LED_ROW0_RIGHT_INDEX,  MAGENTA); // 8
            rgb_matrix_set_color(LED_ROW0_LEFT_INDEX,   MAGENTA); // 9
            // Decimal Point
            rgb_matrix_set_color(LED_ROW0_LEFT_MIDDLE,  CYAN);

            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(LED_ROW2_LEFT_INDEX, RED); // Caps Lock active
            } else {
                caps_lock.timer = 0;
                caps_lock.blink_state = false;
            }
            break;

        /* Keyboard Settings & Adjustments: Hold Left Thumb Key, Then Right Thumb Key
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │ BOOTLDR │         │         │         │         │         │         │         │RGB MODE-│RGB MODE+│         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │    🔆   │    🔅   │         │         │         │RGB TOGL │   RGB-  │   RGB+  │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │         │         │ OS Mode │ RGB HUE-│ RGB HUE+│SATURATN-│SATURATN+│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │<<HOLD1>>│                   │<<HOLD2>>│ ANIMATN-│ ANIMATN+│         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _ADJ:
            rgb_off();
            // Held Keys: Left & Right Thumbs
            set_layer_key_color(LED_THUMB_LEFT);
            set_layer_key_color(LED_THUMB_RIGHT);
            // RGB Light Setting Keys
            rgb_matrix_set_color(LED_ROW0_RIGHT_MIDDLE, YELLOW); // RGB Mode Previous
            rgb_matrix_set_color(LED_ROW0_RIGHT_RING,   YELLOW); // RGB Mode Next
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, YELLOW); // RGB Brightness-
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   YELLOW); // RGB Brightness+
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE, YELLOW); // RGB Hue-
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,   YELLOW); // RGB Hue+
            rgb_matrix_set_color(LED_ROW3_RIGHT_MIDDLE, YELLOW); // RGB Animation Speed-
            rgb_matrix_set_color(LED_ROW3_RIGHT_RING,   YELLOW); // RGB Animation Speed+
            rgb_matrix_set_color(LED_ROW2_RIGHT_PINKY,  YELLOW); // RGB Saturation-
            rgb_matrix_set_color(LED_ROW2_COL11,        YELLOW); // RGB Saturation+
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  RED); // RGB On/Off Toggle
            // Bootloader Mode Key
            rgb_matrix_set_color(LED_CORNER_TOP_LEFT, RED);
            // Computer Screen Brightness Keys
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, SPRING_GREEN);
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   SPRING_GREEN);
            // OS Toggle
            switch (current_os) {
                case OS_MACOS: rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX, ELECTRIC_BLUE); break;
                case OS_LINUX: rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX, GREEN);         break;
                case OS_WIN:   rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX, RED);           break;
                default: break;
            }
            break;

        /* Function Keys & Modifiers: Hold Bottom Left Key w/ Palm for 350 ms to Activate
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │         │         │  LSFT   │  LCTL   │ F9 LALT │         │         │ F8 RALT │  RCTL   │  RSFT   │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │   F7    │   F5    │   F1    │   F3    │   F11   │   F12   │   F2    │   F10   │   F4    │   F6    │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │   F1    │   F2    │   F3    │   F4    │   F5    │   F6    │   F7    │   F8    │   F9    │   F10   │   F11   │   F12   │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  BASE   │🔇⏯ ⏹ C+M│🔉⏮ 🔅🔉 │🔊⏭ 🔆🔊 │  Hyper  │       LGUI        │   Meh   │ ⇱ ^ h ← │ ⇟ } j ↓ │ ⇞ { k ↑ │ ⇲ $ l → │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _FN:
            rgb_off();
            // Back to BASE
            set_layer_key_color(LED_CORNER_BOTTOM_LEFT);
            // Function Keys: Primary Number analog formation
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE,  ORANGE); // F1
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  ORANGE); // F2
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,   ORANGE); // F3
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   ORANGE); // F4
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,    ORANGE); // F5
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  ORANGE); // F6
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,   ORANGE); // F7
            rgb_matrix_set_color(LED_ROW0_RIGHT_INDEX,  ORANGE); // F8
            rgb_matrix_set_color(LED_ROW0_LEFT_INDEX,   ORANGE); // F9
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, ORANGE); // F10
            rgb_matrix_set_color(LED_ROW1_LEFT_CENTER,  ORANGE); // F11
            rgb_matrix_set_color(LED_ROW1_RIGHT_CENTER, ORANGE); // F12
            break;

        /* Home Row Arrows (RHS): Hold Left Index Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │   CUT   │UNDO REDO│  PASTE  │  COPY   │         │         │ «|» ‹|› │ SEL ALL │  COPY   │  PASTE  │UNDO REDO│   CUT   │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │    °    │    \    │ ! ¡ ◌̃ ◌̈ │    _    │<<HOLD>> │AppSwitch│ ? ¿ ◌̀ ◌́ │    ←    │    ↓    │    ↑    │    →    │  ZOOM+  │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │         │ ◌̂ ◌̄ ◌̆ ◌̌ │DESKTOP ←│DESKTOP →│  TAB ←  │  TAB →  │  ZOOM-  │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │   -       –   —   │ , ; | & │         │    ⇤    │    ⇥    │ ZOOM RS │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _ARR_R:
            rgb_off();
            // Held Key, Left Index Finger (Home Row)
            set_layer_key_color(LED_ROW1_LEFT_INDEX);
            // Arrow Keys
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  GREEN); // Left
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, GREEN); // Down
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   GREEN); // Up
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  GREEN); // Right
            break;

        /* Home Row Arrows (LHS): Hold Right Index Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │   CUT   │UNDO REDO│  PASTE  │  COPY   │ SEL ALL │ «|» ‹|› │         │         │  COPY   │  PASTE  │UNDO REDO│   CUT   │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  ZOOM+  │    ←    │    ↑    │    ↓    │    →    │ ? ¿ ◌̀ ◌́ │AppSwitch│ <<HOLD>>│    _    │ ! ¡ ◌̃ ◌̈ │    \    │    °    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  ZOOM-  │  TAB ←  │  TAB →  │DESKTOP ←│DESKTOP →│ ◌̂ ◌̄ ◌̆ ◌̌ │         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │ ZOOM RS │    ⇤    │    ⇥    │         │ , ; | & │   -       –   —   │         │         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
       case _ARR_L:
            rgb_off();
            // Held Key: Right Index Finger (Home Row)
            set_layer_key_color(LED_ROW1_RIGHT_INDEX);
            // Arrow Keys
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,  GREEN); // Left
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   GREEN); // Up
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, GREEN); // Down
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  GREEN); // Right
            break;

        /* (Neo)Vim (RHS): Hold Left Middle Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │         │         │         │         │         │         │ zt    H │za  zM zR│ ½PD BOT │ ½PU TOP │         │ DEL bB^$│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │    A    │    D    │<<HOLD>> │VIEWPORT+│:qa  :qa!│ zz    M │B gE E←J←│ gj   << │ gk   >> │W E E→ J→│ BUF TOGL│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │VIEWPORT-│         │ zb    L │ :%s///g │ :w  :wa │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │         :         │   ESC   │W← T⇤ B⇤ │W↓ T← B← │W↑ T→ B→ │W→ T⇥ B⇥ │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         * Bottom row: Move Vim window splits (Tap), resize (2xTap), change buffers (Hold), change tabs (Tap+Hold)
         */
       case _VIM_R:
            rgb_off();
            // Held Key: Left Middle Finger (Home Row)
            set_layer_key_color(LED_ROW1_LEFT_MIDDLE);
            // Directional Keys
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  SPRING_GREEN); // Left: `B`
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, SPRING_GREEN); // Left: `gj`
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   SPRING_GREEN); // Left: `gk`
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  SPRING_GREEN); // Left: `W`

            rgb_matrix_set_color(LED_ROW1_LEFT_CENTER, RED); // Quit Vim
            break;

        /* (Neo)Vim (LHS): Hold Right Middle Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │ DEL bB^$│         │ ½PU TOP │ ½PD BOT │za  zM zR│ zt    H │         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │ BUF TOGL│B gE E←J←│ gk   >> │ gj   << │W E E→ J→│ zz    M │:qa  :qa!│VIEWPORT+│ <<HOLD>>│    D    │    A    │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │   :w    │ :%s///g │ zb    L │         │VIEWPORT-│         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │W← T⇤ B⇤ │W↑ T→ B→ │W↓ T← B← │W→ T⇥ B⇥ │   ESC   │         :         │         │         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         * Bottom row: Move Vim window splits (Tap), resize (2xTap), change buffers (Hold), change tabs (Tap+Hold)
         */
        case _VIM_L:
            rgb_off();
            // Held Key: Right Middle Finger
            set_layer_key_color(LED_ROW1_RIGHT_MIDDLE);
            // Directional Keys
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,  SPRING_GREEN); // Left: `h`
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   SPRING_GREEN); // Left: `gk`
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, SPRING_GREEN); // Left: `gj`
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  SPRING_GREEN); // Left: `l`

            rgb_matrix_set_color(LED_ROW1_RIGHT_CENTER, RED); // Quit Vim: Red
            break;

        /* Programming N-Grams (RHS): Hold Left Ring Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │         │         │         │         │         │         │  null   │ &&   || │+= - / * │ =    := │         │ MD LINK │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │  WS {}  │<<HOLD>> │ ++   -- │ //      │         │truefalse│""←''←``←│()[]<>{}←│-> <-  =>│ return  │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │         │break con│ switch  │ if else │for while│ ` ? : ` │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │  ==  !=   <=  >=  │  ⇥   ⇤  │         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _PROG_R:
            rgb_off();
            // Held Key: Left Ring Finger
            set_layer_key_color(LED_ROW1_LEFT_RING);
            // Coding Keys
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, ELECTRIC_BLUE); // `++` `--`
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  ELECTRIC_BLUE); // `// ` `<!--  -->` `/*  */`
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,  ELECTRIC_BLUE); // ` {}`with vertical whitespace

            rgb_matrix_set_color(LED_ROW0_RIGHT_CENTER, ELECTRIC_BLUE); // `null`, `NULL`, `nil` keywords
            rgb_matrix_set_color(LED_ROW0_RIGHT_INDEX,  ELECTRIC_BLUE); // Logical And/Or
            rgb_matrix_set_color(LED_ROW0_RIGHT_MIDDLE, ELECTRIC_BLUE); // Compound assignment operator bigrams
            rgb_matrix_set_color(LED_ROW0_RIGHT_RING,   ELECTRIC_BLUE); // Assignment operators
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  ELECTRIC_BLUE); // Quote symbol bigrams
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, ELECTRIC_BLUE); // Paren, bracket, braces bigrams
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   ELECTRIC_BLUE); // Arrow bigrams
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  ELECTRIC_BLUE); // `return` keywords
            rgb_matrix_set_color(LED_ROW1_RIGHT_CENTER, ELECTRIC_BLUE); // `true` & `false` keywords
            rgb_matrix_set_color(LED_ROW2_RIGHT_CENTER, ELECTRIC_BLUE); // `break` & `continue` keywords
            rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX,  ELECTRIC_BLUE); // `switch`, `default`, `case` keywords
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE, ELECTRIC_BLUE); // `if`, `else if`, `elif`, `else` keywords
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,   ELECTRIC_BLUE); // `for`, `while` keywords
            rgb_matrix_set_color(LED_ROW2_RIGHT_PINKY,  ELECTRIC_BLUE); // ` ? : ` terniary operator
            rgb_matrix_set_color(LED_THUMB_CENTER,      ELECTRIC_BLUE); // Equality logical operators

            rgb_matrix_set_color(LED_CORNER_TOP_RIGHT, ELECTRIC_BLUE); // Markdown link and image symbols
            break;

        /* Programming N-Grams (LHS): Hold Right Ring Finger on Home Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │ MD LINK │         │ =    := │+= - / * │ &&   || │  null   │         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │ return  │-> <-  =>│()[]<>{}←│""←''←``←│truefalse│         │ //      │ ++   -- │<<HOLD>> │  WS {}  │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │ ` ? : ` │for while│ if else │ switch  │break con│         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │  ⇥   ⇤  │  ==  !=   <=  >=  │         │         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _PROG_L:
            rgb_off();
            // Held Key: Right Ring Finger
            set_layer_key_color(LED_ROW1_RIGHT_RING);
            // Coding Keys
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, ELECTRIC_BLUE); // `++` `--`
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  ELECTRIC_BLUE); // `// ` `<!--  -->` `/*  */`
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  ELECTRIC_BLUE); // ` {}`with vertical whitespace

            rgb_matrix_set_color(LED_ROW0_LEFT_CENTER, ELECTRIC_BLUE); // `null`, `NULL`, `nil` keywords
            rgb_matrix_set_color(LED_ROW0_LEFT_INDEX,  ELECTRIC_BLUE); // Logical And/Or
            rgb_matrix_set_color(LED_ROW0_LEFT_MIDDLE, ELECTRIC_BLUE); // Compound assigment operator bigrams
            rgb_matrix_set_color(LED_ROW0_LEFT_RING,   ELECTRIC_BLUE); // Assignment operators
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  ELECTRIC_BLUE); // Quote symbol bigrams
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, ELECTRIC_BLUE); // Paren, bracket, braces bigrams
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   ELECTRIC_BLUE); // Arrow bigrams
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,  ELECTRIC_BLUE); // `return` keywords
            rgb_matrix_set_color(LED_ROW1_LEFT_CENTER, ELECTRIC_BLUE); // `true` & `false` keywords
            rgb_matrix_set_color(LED_ROW2_LEFT_CENTER, ELECTRIC_BLUE); // `break` & `continue` keywords
            rgb_matrix_set_color(LED_ROW2_LEFT_INDEX,  ELECTRIC_BLUE); // `switch`, `default`, `case` keywords
            rgb_matrix_set_color(LED_ROW2_LEFT_MIDDLE, ELECTRIC_BLUE); // `if`, `else if`, `elif`, `else` keywords
            rgb_matrix_set_color(LED_ROW2_LEFT_RING,   ELECTRIC_BLUE); // `for`, `while` keywords
            rgb_matrix_set_color(LED_ROW2_LEFT_PINKY,  ELECTRIC_BLUE); // ` ? : ` terniary operator
            rgb_matrix_set_color(LED_THUMB_CENTER,     ELECTRIC_BLUE); // Equality logical operators

            rgb_matrix_set_color(LED_CORNER_TOP_LEFT, ELECTRIC_BLUE); // Markdown link and image symbols
            break;

        /* Terminal Emulator: Hold Right Index Finger on Lower Row
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │ sudo !! │         │ mkdir -p│ cat bat │  ping   │         │         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  touch  │ ⇱ ^ h ← │ ⇞ { k ↑ │ ⇟ } j ↓ │ ⇲ $ l → │cls  exit│         │         │         │         │         │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │./ ~/ ../│ ls -lah │         │         │ <<HOLD>>│ cd cd ..│   cd ~  │cd gitrt │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │ | ` | ` │         │         │         │   cd -  │   btop top htop   │  SIGINT │         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         * SIGINT: LCTL+c, stop process (Tap); `fg`, resume background process (2xTap); LCTL+z, suspend/pause process into background (Hold)
         */
        case _TERM:
            rgb_off();
            // Held Key: Right Index Finder, Bottom Alpha Row (M)
            set_layer_key_color(LED_ROW2_RIGHT_INDEX);
            // Navigation Keys
            rgb_matrix_set_color(LED_ROW1_LEFT_PINKY,    GREEN); // Home
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE,   GREEN); // Page Down
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,     GREEN); // Page Up
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,    GREEN); // End
            // Quitting/Exiting/Admin Keys: Red
            rgb_matrix_set_color(LED_ROW1_LEFT_CENTER,   RED); // `exit`: Red
            rgb_matrix_set_color(LED_THUMB_RIGHT,        RED); // LCTL+C (Abort): Red
            rgb_matrix_set_color(LED_CORNER_TOP_LEFT,    RED); // Tap->`sudo Hold->`sudo !!`
            // Terminal Commands
            rgb_matrix_set_color(LED_ROW0_LEFT_RING,     BLUE); // Tap->`mkdir -p `
            rgb_matrix_set_color(LED_ROW0_LEFT_MIDDLE,   BLUE); // Tap->`cat ` 2xTap->`less ` Hold->`bat `
            rgb_matrix_set_color(LED_ROW0_LEFT_INDEX,    BLUE); // Tap->`ping `
            rgb_matrix_set_color(LED_ROW1_COL0,          BLUE); // Tap->`touch `
            rgb_matrix_set_color(LED_ROW2_LEFT_INDEX,    BLUE); // Tap->`ls -lah`
            rgb_matrix_set_color(LED_ROW2_LEFT_MIDDLE,   BLUE); // Tap->`./` 2xTap->`~/` Hold->`../`
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE,  BLUE); // Tap->`cd ` Hold->`cd ..`
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,    BLUE); // Tap->`cd ~`
            rgb_matrix_set_color(LED_ROW2_RIGHT_PINKY,   BLUE); // Tap->`cd `
            rgb_matrix_set_color(LED_THUMB_LEFT,         BLUE); // Tap->`cd -`
            rgb_matrix_set_color(LED_CORNER_BOTTOM_LEFT, BLUE); // Tap->`|` Hold->` | `
            rgb_matrix_set_color(LED_THUMB_CENTER,       BLUE); // Tap->`btop` 2xTap->`top` Hold->`htop`
            break;

        /* Apple macOS Layer: Hold Inner Left Key on Home Row (ESC)
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │         │         │         │         │         │         │         │DESKTOP ←│  APPS ↓ │MISSION ↑│DESKTOP →│▣ Opts ⛶ │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │  ⌫ Word │<<HOLD>> │ FS    🔒│  Word ← │ End Ln⇥ │Start Ln⇤│  Word → │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │         │ForceQuit│Sel Word←│Sel Line↓│Sel Line↑│Sel Word→│         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │         │         │  🔍  😀       📁  │␡ Empty🗑️│         │         │         │         │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _MACOS:
            rgb_off();
            // Held Key: Center Left (ESC)
            set_layer_key_color(LED_ROW1_LEFT_CENTER);
            // Jump Word Keys
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  SPRING_GREEN); // Jump to prev word
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, SPRING_GREEN); // Jump to EOL
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   SPRING_GREEN); // Jump to start of line
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  SPRING_GREEN); // Jump to next word
            // Select Word Keys
            rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX,  FOREST_GREEN); // Select previous word
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE, FOREST_GREEN); // Select line below
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,   FOREST_GREEN); // Select line above
            rgb_matrix_set_color(LED_ROW2_RIGHT_PINKY,  FOREST_GREEN); // Select next word

            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,   YELLOW);    // Backspace Word: Yellow
            rgb_matrix_set_color(LED_THUMB_RIGHT,       RED);       // Delete File: Red
            rgb_matrix_set_color(LED_CORNER_TOP_RIGHT,  CYAN_MINT); // Screenshot: Cyan-Mint
            rgb_matrix_set_color(LED_ROW2_RIGHT_CENTER, AMBER);     // Open Force Quit Menu: Amber
            break;

        /* Mouse Layer: Tap Bottom Left Key w/ Palm to Activate/Exit
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │   CUT   │UNDO REDO│  PASTE  │  COPY   │ SEL ALL │DESKTOP ←│DESKTOP →│ ⇱ ^ h ← │ ⇟ } j ↓ │ ⇞ { k ↑ │ ⇲ $ l → │ ⌫  ⌫L ⌫w│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │Mid Click│Lft Click│Rgt Click│   ESC   │  DOOM   │Pointer ←│Pointer ↓│Pointer ↑│Pointer →│    ↵    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │DESKTOP ←│         │         │  Back   │ Forward │  TAB ←  │  TAB →  │ Wheel → │ Wheel ↑ │ Wheel ↓ │ Wheel ← │DESKTOP →│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  BACK   │🔇⏯ ⏹ C+M│🔉⏮ 🔅🔉 │🔊⏭ 🔆🔊 │ Wheel ↑ │      Wheel ↓      │ Wheel ↑ │ SEL ALL │  COPY   │  PASTE  │UNDO REDO│
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
        case _MOUSE:
            rgb_off();
            // Exit Mouse Mode Layer: Tap Bottom Left Key
            set_layer_key_color(LED_CORNER_BOTTOM_LEFT);
            // Mouse Pointer Movement Keys (Move/Go)
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  SPRING_GREEN); // Move Left
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, SPRING_GREEN); // Move Down
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   SPRING_GREEN); // Move Up
            rgb_matrix_set_color(LED_ROW1_RIGHT_PINKY,  SPRING_GREEN); // Move Right
            // Mouse Button Keys (Interact)
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, ORANGE); // Left Click
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  ORANGE); // Right Click
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   ORANGE); // Middle Click
            rgb_matrix_set_color(LED_ROW2_LEFT_MIDDLE, ORANGE); // Back
            rgb_matrix_set_color(LED_ROW2_LEFT_INDEX,  ORANGE); // Forward
            // Mouse Wheel Keys (Scroll/Navigate)
            rgb_matrix_set_color(LED_ROW2_RIGHT_INDEX,  DODGER_BLUE); // Right
            rgb_matrix_set_color(LED_ROW2_RIGHT_MIDDLE, DODGER_BLUE); // Up
            rgb_matrix_set_color(LED_ROW2_RIGHT_RING,   DODGER_BLUE); // Down
            rgb_matrix_set_color(LED_ROW2_RIGHT_PINKY,  DODGER_BLUE); // Left
            rgb_matrix_set_color(LED_THUMB_LEFT,        DODGER_BLUE); // Up
            rgb_matrix_set_color(LED_THUMB_CENTER,      DODGER_BLUE); // Down
            rgb_matrix_set_color(LED_THUMB_RIGHT,       DODGER_BLUE); // Up
            // Navigation Keys
            rgb_matrix_set_color(LED_ROW0_RIGHT_INDEX,  GREEN); // Home
            rgb_matrix_set_color(LED_ROW0_RIGHT_MIDDLE, GREEN); // Page Down
            rgb_matrix_set_color(LED_ROW0_RIGHT_RING,   GREEN); // Page Up
            rgb_matrix_set_color(LED_ROW0_RIGHT_PINKY,  GREEN); // End
            break;

        /* Classic Doom Layer
         * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
         * │   ESC   │         │         │    ↑    │         │         │         │         │Pointer ↑│         │         │ ⌫  ⌫L ⌫w│
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  ⇥   ⇤  │ Strife ←│    ←    │    ↓    │    →    │ Strife →│         │Pointer ←│Pointer ↓│Pointer →│ Strife →│    ↵    │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │         │         │         │ Strife ↓│         │         │         │ Wheel → │ Wheel ↑ │ Wheel ↓ │ Wheel ← │         │
         * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
         * │  BASE   │🔇⏯ ⏹ C+M│🔉⏮ 🔅🔉 │🔊⏭ 🔆🔊 │Lft Click│   ␣           LSFT│Rgt Click│ ⇱ ^ h ← │ ⇟ } j ↓ │ ⇞ { k ↑ │ ⇲ $ l → │
         * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
         */
       case _DOOM:
            rgb_off();
            // Exit Mouse Mode Layer: Tap Bottom Left Key
            set_layer_key_color(LED_CORNER_BOTTOM_LEFT);
            // Mouse Pointer Movement Keys (Move/Go)
            rgb_matrix_set_color(LED_ROW0_RIGHT_MIDDLE, SPRING_GREEN); // Move Up
            rgb_matrix_set_color(LED_ROW1_RIGHT_INDEX,  SPRING_GREEN); // Move Left
            rgb_matrix_set_color(LED_ROW1_RIGHT_MIDDLE, SPRING_GREEN); // Move Down
            rgb_matrix_set_color(LED_ROW1_RIGHT_RING,   SPRING_GREEN); // Move Right
            // Mouse Button Keys (Interact)
            rgb_matrix_set_color(LED_THUMB_LEFT,  ORANGE); // Left Click
            rgb_matrix_set_color(LED_THUMB_RIGHT, ORANGE); // Right Click
            // Arrow Keys
            rgb_matrix_set_color(LED_ROW0_LEFT_MIDDLE, GREEN); // Up
            rgb_matrix_set_color(LED_ROW1_LEFT_RING,   GREEN); // Left
            rgb_matrix_set_color(LED_ROW1_LEFT_MIDDLE, GREEN); // Down
            rgb_matrix_set_color(LED_ROW1_LEFT_INDEX,  GREEN); // Right
            break;
    }

    return true;
}
