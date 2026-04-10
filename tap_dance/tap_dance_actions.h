#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Tap Dance Enum
// ─────────────────────────────────────────────────────────────

enum {                // │  Tap   │ 2xTap  │Tap+Hold│  Hold  │ Notes
    TD_ASTR = 0,      // │   *    │   %    │   @    │   #    │ Fun corner key for Vim commands on Base layer
    TD_BSPC,          // │  Bspc  │        │  Del   │  Bspc  │
    TD_C,             // │   c    │        │LOCK UPP│ MT(UPP)│ `c` on Tap; Lock Primary Number layer on Tap+Hold; Momentary Primary Number layer on Hold
    TD_CIRC,          // │   ^    │        │   ¢    │   $    │
    TD_COMM,          // │   ,    │   ;    │   |    │   &    │
    TD_DOT,           // │   .    │   …    │   ⋮    │   •    │ Vertical ellipse requires Unicode input source set, and only U.S. keyboard on macOS
    TD_DLR,           // │   $    │   ¥    │   £    │   €    │
    TD_DQUO,          // │   "    │   ‘    │   <    │   >    │ Double quote on Tap; typographic opening smart single quote on 2xTap
    TD_EQL,           // │   =    │        │        │   ≠    │
    TD_EXLM,          // │   !    │   ! ES │ grave  │ umlaut │ Spanish/Lang-related symbols on tap dances (macOS)
    TD_MINS,          // │   -    │        │   –    │   —    │ Hyphen/en dash/em dash
    TD_PLUS,          // │   +    │   -    │   /    │   *    │
    TD_PUNC,          // │  `, `  │   `; ` │  `: `  │   `. ` │ Punctuation + space bigrams
    TD_QUES,          // │   ?    │   ¿    │ ˜ tilde│ ´ acute│ Spanish/Lang-related symbols on tap dances (macOS)
    TD_QUOT,          // │   '    │   ’    │   ~    │   `    │ Single quote on Tap; typographic apostrophe/closing smart single quote on 2xTap 
    TD_SPC,           // │  Spc   │        │  Enter │  LGUI  │ LGUI = LCMD = Super (Linux) = Windows key
    TD_TAB,           // │  Tab   │        │        │ Sft+Tab│ Sft+Tab = Reverse Tab
    TD_U,             // │   u    │        │LOCK LOW│ MT(LOW)│ `u` on Tap; Lock Numpad layer on Tap+Hold; Momentary Numpad layer on Hold
                      // │        │        │        │        │
    TD_LPRN,          // │   (    │   [    │   <    │   {    │
    TD_RPRN,          // │   )    │   ]    │   >    │   }    │
    TD_LBRC,          // │   [    │   (    │   {    │   <    │
    TD_RBRC,          // │   ]    │   )    │   }    │   >    │
                      // │        │        │        │        │
    TD_MUTE,          // │  Mute  │Pl/Pause│  Stop  │ LCTL+M │ Media key; Browsers: Mute Tab on hold
    TD_VOLD,          // │  Vol-  │  Prev  │  Bght- │  Vol-  │ Media key
    TD_VOLU,          // │  Vol+  │  Next  │  Bght+ │  Vol+  │ Media key
                      // │        │        │        │        │
    TD_HOME,          // │  Home  │   ^    │   h    │   ←    │ Vim: ^ = jump to first curr line first char; h = move left 1 col
    TD_PGDN,          // │  PgDn  │   }    │   j    │   ↓    │ Vim: } = jump down paragraph; j = move down 1 row
    TD_PGUP,          // │  PgUp  │   {    │   k    │   ↑    │ Vim: { = jump up paragraph; k = move up 1 row
    TD_END,           // │  End   │   $    │   l    │   →    │ Vim: $ = jump to EOL; l = move right 1 col
                      // │        │        │        │        │
    TD_NUMPAD_1,      // │   1    │        │        │   A    │ Number pad 1 on Tap; Hex A on Hold
    TD_NUMPAD_2,      // │   2    │        │        │   B    │ Number pad 2 on Tap; Hex B on Hold
    TD_NUMPAD_3,      // │   3    │        │        │   C    │ Number pad 3 on Tap; Hex C on Hold
    TD_NUMPAD_4,      // │   4    │        │        │   D    │ Number pad 4 on Tap; Hex D on Hold
    TD_NUMPAD_5,      // │   5    │        │        │   E    │ Number pad 5 on Tap; Hex E on Hold
    TD_NUMPAD_6,      // │   6    │        │        │   F    │ Number pad 6 on Tap; Hex F on Hold
                      // │        │        │        │        │
    TD_ZIN,           // │CMD+S+= │        │        │ C+S+=  │ Browser Zoom Out
    TD_ZOUT,          // │  CMD+- │        │        │ LCTL+- │ Browser Zoom In
    TD_ZRS,           // │  CMD+0 │        │        │ LCTL+0 │ Browser Zoom Reset
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
    TD_WRITE,         // │   :w   │        │        │  :wa   │ Vim: Write/save current buffer on Tap; write/save all open buffers on Hold
    TD_SUB,           // │ :%s///g│        │        │:bufdo..│ Vim: substitute all in current buffer on Tap; substitute in all buffers on Hold
    TD_FOLD,          // │   za   │        │   zM   │   zR   │ Vim: toggle fold under cursor under Tap; close all folds on Tap+Hold; open all folds on Hold
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
                      // │        │        │        │        │
    TD_UNDO,          // │  CMD+Z │        │CMD+S+Z │  CMD+Z │ Defaults to macOS shortcuts, toggle OS for Linux/Windows on _FN layer
    TD_SMART_QUOTES,  // │   “|”  │        │        │  ‘|’   │ Smart double quotes w/ cursor inside on Tap; smart single quotes on Hold

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
    td_state_t state;
} td_tap_t;

extern tap_dance_action_t tap_dance_actions[TD_COUNT];

td_state_t cur_dance(tap_dance_state_t *state);
