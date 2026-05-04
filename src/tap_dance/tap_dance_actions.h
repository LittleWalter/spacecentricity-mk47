#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Tap Dance Enum
// ─────────────────────────────────────────────────────────────

enum {                // │  Tap   │ 2xTap  │Tap+Hold│  Hold  │ Notes
    TD_U = 0,         // │   u    │        │LOCK LOW│ MT(LOW)│ `u` on Tap; Lock Numpad layer on Tap+Hold; Momentary Numpad layer on Hold
    TD_C,             // │   c    │        │LOCK UPP│ MT(UPP)│ `c` on Tap; Lock Primary Number layer on Tap+Hold; Momentary Primary Number layer on Hold
                      // │        │        │        │        │
    TD_ASTR,          // │   *    │   %    │   @    │   #    │ Triple tap: × (multiplication symbol)
    TD_AT,            // │   @    │        │        │ToggLEAD│ On hold: Toggle replay Leader History/Favorites
    TD_CARET,         // │   ^    │        │   ¢    │   $    │
    TD_CIRC,          // │   ◌̂    │   ◌̄    │   ◌̆    │   ◌̌    │ Combining circumflex on Tap; macron on 2xTap; breve on Tap+Hold; caron on Hold
    TD_COMM,          // │   ,    │   ;    │   |    │   &    │
    TD_DOT,           // │   .    │   …    │   ⋮    │   •    │ Triple tap: · (centered dot)
    TD_DLR,           // │   $    │   ¥    │   £    │   €    │
    TD_DQUO,          // │   "    │   ‘    │   <    │   >    │ Double quote on Tap; typographic opening smart single quote on 2xTap
    TD_EQL,           // │   =    │        │        │   ≠    │
    TD_EXLM,          // │   !    │   ¡    │   ◌̃    │   ◌̈    │
    TD_MINS,          // │   -    │        │   –    │   —    │ Hyphen/en dash/em dash
    TD_PLUS,          // │   +    │   -    │   /    │   *    │ Triple tap: × (multiplication symbol)
    TD_PUNC,          // │   ,␣   │   !␣   │   ?␣   │   .␣   │ Punctuation + space bigrams; sentence-ending symbols auto capitalize the next char
    TD_QUES,          // │   ?    │   ¿    │   ◌̀    │   ◌́    │
    TD_QUOT,          // │   '    │   ’    │   ~    │   `    │ Single quote on Tap; typographic apostrophe/closing smart single quote on 2xTap
    TD_SCLN,          // │   ;    │   ;␣   │   :␣   │  LSFT  │
    TD_SPC,           // │  Spc   │        │  Enter │  LGUI  │ LGUI = LCMD = Super (Linux) = Windows key
                      // │        │        │        │        │
    TD_SMART_QUOTES,  // │   “|”  │        │        │  ‘|’   │ Smart double quotes w/ cursor inside on Tap; smart single quotes on Hold
    TD_ANGLE_QUOTES,  // │   «|»  │        │        │  ‹|›   │ Angle double quotes w/ cursor inside on Tap; angle single quotes on Hold
                      // │        │        │        │        │
    TD_LPRN,          // │   (    │   [    │   <    │   {    │
    TD_RPRN,          // │   )    │   ]    │   >    │   }    │
    TD_LBRC,          // │   [    │   (    │   {    │   <    │ Triple tap: ≤
    TD_RBRC,          // │   ]    │   )    │   }    │   >    │ Triple tap: ≥
                      // │        │        │        │        │
    TD_0,             // │   0    │        │        │LEADER 0│
    TD_1,             // │   1    │        │        │LEADER 1│
    TD_2,             // │   2    │        │        │LEADER 2│
    TD_3,             // │   3    │        │        │LEADER 3│
    TD_4,             // │   4    │        │        │LEADER 4│
    TD_5,             // │   5    │        │        │LEADER 5│
    TD_6,             // │   6    │        │        │LEADER 6│
    TD_7,             // │   7    │        │        │LEADER 7│
    TD_8,             // │   8    │        │        │LEADER 8│
    TD_9,             // │   9    │        │        │LEADER 9│
                      // │        │        │        │        │
    TD_NUMPAD_1,      // │   1    │        │        │   A    │ Number pad 1 on Tap; Hex A on Hold
    TD_NUMPAD_2,      // │   2    │        │        │   B    │ Number pad 2 on Tap; Hex B on Hold
    TD_NUMPAD_3,      // │   3    │        │        │   C    │ Number pad 3 on Tap; Hex C on Hold
    TD_NUMPAD_4,      // │   4    │        │        │   D    │ Number pad 4 on Tap; Hex D on Hold
    TD_NUMPAD_5,      // │   5    │        │        │   E    │ Number pad 5 on Tap; Hex E on Hold
    TD_NUMPAD_6,      // │   6    │        │        │   F    │ Number pad 6 on Tap; Hex F on Hold
                      // │        │        │        │        │
    TD_BSPC,          // │  Bspc  │        │BspcLine│BspcWord│
    TD_CAPS,          // │CapsWord│        │        │CapsLock│
    TD_DEL,           // │  Del   │        │Del Line│Del Word│
    TD_ENT,           // │   ↵    │        │        │ SFT+Ent│
    TD_ESC,           // │  Esc   │        │CloseWin│  Esc   │ Close Window: CMD+w (macOS), Alt+F4 (Linux/Microsoft Windows)
    TD_TAB,           // │  Tab   │        │        │ SFT+Tab│ SFT+Tab = Reverse Tab
                      // │        │        │        │        │
    TD_UNDO,          // │  CMD+Z │        │CMD+S+Z │  CMD+Z │ Defaults to macOS shortcuts, toggle OS for Linux/Windows on _FN layer
                      // │        │        │        │        │
    TD_HOME,          // │  Home  │   ^    │   h    │   ←    │ Vim: ^ = jump to first curr line first char; h = move left 1 col
    TD_PGDN,          // │  PgDn  │   }    │   j    │   ↓    │ Vim: } = jump down paragraph; j = move down 1 row
    TD_PGUP,          // │  PgUp  │   {    │   k    │   ↑    │ Vim: { = jump up paragraph; k = move up 1 row
    TD_END,           // │  End   │   $    │   l    │   →    │ Vim: $ = jump to EOL; l = move right 1 col
                      // │        │        │        │        │
    TD_MUTE,          // │  Mute  │Pl/Pause│  Stop  │ LCTL+M │ Media key; Browsers: Mute Tab on hold
    TD_VOLD,          // │  Vol-  │  Prev  │  Bght- │  Vol-  │ Media key
    TD_VOLU,          // │  Vol+  │  Next  │  Bght+ │  Vol+  │ Media key
                      // │        │        │        │        │
    TD_B,             // │   B    │   gE   │PrevEdit│ LCTL+O │ Vim: Jump 1 WORD back on Tap; jump to end of 1 WORD back on 2xTap; jump list backward on Hold
    TD_GJ,            // │   gj   │        │   <<   │        │ Vim: Directly move down 1 row on long line on Tap; left indent on Tap+Hold
    TD_GK,            // │   gk   │        │   >>   │        │ Vim: Directly move up 1 row on long line on Tap; right indent on Tap+Hold
    TD_W,             // │   W    │   E    │NextEdit│ LCTL+I │ Vim: Jump 1 WORD forward on Tap; jump to end 1 WORD forward on 2xTap; jump list forward on Hold
                      // │        │        │        │        │
    TD_HALF_PGDN,     // │1/2PgDn │        │        │ Bottom │ Vim: 1/2 Page Down on Tap; Bottom of current buffer on Hold
    TD_HALF_PGUP,     // │1/2PgUp │        │        │  Top   │ Vim: 1/2 Page Up on Tap; Top of current buffer on Hold
                      // │        │        │        │        │
    TD_HIGH,          // │   zt   │        │        │   H    │ Vim: Adjust viewport to top; jump cursor to top of viewport on Hold
    TD_MID,           // │   zz   │        │        │   M    │ Vim: Adjust viewport to middle; jump cursor to mid of viewport on Hold
    TD_LOW,           // │   zb   │        │        │   L    │ Vim: Adjust viewport to bottom; jump cursor to bottom of viewport on Hold
                      // │        │        │        │        │
    TD_WINL,          // │GotoWinL│ Width- │1st Tab │1st Buf │ Vim: Go to left window split on Tap; decrease width on 2xTap
    TD_WIND,          // │GotoWinD│Height- │Tab Prev│Buf Prev│ Vim: Go to window split below on Tap; decrease height on 2xTap
    TD_WINU,          // │GotoWinU│Height+ │Tab Next│Buf Next│ Vim: Go to window above below on Tap; increase height on 2xTap
    TD_WINR,          // │GotoWinR│ Width+ │Last Tab│Last Buf│ Vim: Go to right window split on Tap; increase width on 2xTap
                      // │        │        │        │        │
    TD_SUB,           // │ :%s///g│        │        │:bufdo..│ Vim: substitute all in current buffer on Tap; substitute in all buffers on Hold
    TD_VIM_DEL,       // │   db   │   dB   │   d^   │   d$   │ Vim: delete word/WORD/BOL/EOL
    TD_FOLD,          // │   za   │        │   zM   │   zR   │ Vim: toggle fold under cursor under Tap; close all folds on Tap+Hold; open all folds on Hold
    TD_WRITE,         // │   :w   │        │        │  :wa   │ Vim: Write/save current buffer on Tap; write/save all open buffers on Hold
    TD_QUIT,          // │  :qa   │        │        │  :qa!  │ Vim: Safely quit all on Tap; Quit all w/o saving buffers on Hold
                      // │        │        │        │        │
    TD_PROG_EQL,      // │   ==   │   !=   │   <=   │   >=   │ Logical comparison operators
    TD_AND,           // │   &&   │        │        │   ||   │ Logical and/or operators
    TD_ASSIGN,        // │   =    │        │        │   :=   │ Assignment operators
    TD_PARENS,        // │   ()←  │   []←  │   <>←  │ { CR } │ Surrounding symbols w/ centered cursor
    TD_DBL_QUOTES,    // │   ""←  │   ''←  │   ```  │   ``←  │ Double, single quotes, and backticks w/ cursor inside
    TD_ARROW,         // │   ->   │   <-   │        │   =>   │ Programming arrow operators: right, left, fat
    TD_CMPD,          // │   +=   │   -=   │   /=   │   *=   │ Compound assignment operators
    TD_INC,           // │   ++   │        │        │   --   │ Increment/decrement uniary operators
    TD_COMMENT,       // │   //   │        │        │ /*  */ │ C-style comments
    TD_IF_KW,         // │   if   │else if │  elif  │  else  │ Conditional branching programming keywords
    TD_TRUE_KW,       // │  true  │        │        │  false │ Boolean programming keywords
    TD_RETURN_KW,     // │ return │        │        │w/ Space│
    TD_BREAK_KW,      // │ break  │        │        │continue│
    TD_SWITCH_KW,     // │ switch │default │        │  case  │
    TD_FOR_KW,        // │  for   │        │        │  while │ Iteration keywords
    TD_NULL_KW,       // │  null  │  NULL  │        │  nil   │ Null pointer references
                      // │        │        │        │        │
    TD_MD_LINK,       // │  []()  │        │        │  ![]() │
                      // │        │        │        │        │
    TD_CAMEL,         // │        │        │        │        │
    TD_SNAKE,         // │        │        │        │        │
                      // │        │        │        │        │
    TD_BTOP,          // │  btop  │  top   │        │  htop  │ Terminal-based system monitoring tools
    TD_CLS,           // │ clear  │        │        │  exit  │ Clear screen on Tap; exit shell
    TD_CAT,           // │  cat   │  less  │        │  bat   │ File-viewing terminal commands
    TD_SIGINT,        // │ LCTL+c │   fg   │        │ LCTL+z │ LCTL+c = SIGINT on Tap; fg = resume background process on 2xTap; LCTL+z = SIGTSTP on Hold
    TD_PIPE,          // │   |    │        │        │ ` | `  │ Pipelining symbol w/ and w/o spacing
    TD_PATH,          // │   ./   │   ~/   │        │  ../   │ Path/directory shorthand symbols
    TD_CD,            // │ `cd `  │        │        │ `cd ..`│
    TD_SUDO,          // │  sudo  │        │        │ sudo !!│ `sudo !!` to repeat last command w/ admin privileges
                      // │        │        │        │        │
    TD_SPOTLGHT_MACOS,// │Spotlght│EmojiMnu│        │ Finder │ Open Spotlight Search on Tap; Open Emoji Menu on 2xTap; Open Finder on Hold
    TD_FS_MACOS,      // │FullScrn│        │        │Lock Mac│
    TD_SCRNSHOT_MACOS,// │   ▣    │        │Options │   ⛶    │ Partial screenshot on Tap; Screenshot Toolbar, all options on Tap+Hold; Full screenshot on Hold
    TD_DEL_MACOS,     // │Del File│  🗑️ 📂 │        │Empty 🗑️│ Delete file on Tap; Open trash folder in Finder on Tap+Hold, Empty trash can on Hold

    TD_COUNT // Sentinel value for tap_dance_actions array
};

// ─────────────────────────────────────────────────────────────
// Tap Dance State Machine
// ─────────────────────────────────────────────────────────────

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,        // 1x tap
    TD_SINGLE_HOLD,       // Hold
    TD_DOUBLE_TAP,        // 2x tap
    TD_DOUBLE_HOLD,       // 2x tap+hold
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    uint8_t layer_origin;
    td_state_t state;
} td_tap_t;

extern tap_dance_action_t tap_dance_actions[TD_COUNT];

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 * REF: Sample code taken from https://docs.qmk.fm/features/tap_dance#examples
 */
td_state_t cur_dance(tap_dance_state_t *state);

// ─────────────────────────────────────────────────────────────
// Tap Dance Helpers
// ─────────────────────────────────────────────────────────────

// Registers a given keycode and checks active case mode for valid chars.
void register_and_update(const uint16_t keycode);

// Taps a given keycode and checks active case mode for valid chars.
void tap_and_update(const uint16_t keycode);
