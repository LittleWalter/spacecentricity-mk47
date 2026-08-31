# CHANGELOG

[![Last Commit](https://img.shields.io/github/last-commit/LittleWalter/spacecentricity-mk47)](https://github.com/LittleWalter/spacecentricity-mk47/commits/main)
[![OctoCounts](https://api.octocounts.com/badge/LittleWalter/spacecentricity-mk47/branch/main?lang=C)](https://octocounts.com/github/LittleWalter/spacecentricity-mk47/tree/main)
[![OctoCounts](https://api.octocounts.com/badge/LittleWalter/spacecentricity-mk47/branch/main?lang=C+Header)](https://octocounts.com/github/LittleWalter/spacecentricity-mk47/tree/main)
[![OctoCounts](https://api.octocounts.com/badge/LittleWalter/spacecentricity-mk47/branch/main?lang=Shell)](https://octocounts.com/github/LittleWalter/spacecentricity-mk47/tree/main)

## `TODO:`

- [ ] Test on Linux and Microsoft Windows
- [ ] Design a **Linux** layer as an analog to the **macOS** layer
- [ ] Consider adding `tmux` macros on **Terminal** layer
- [ ] Consider adding the Apple `fn` key via [QMK patch](https://gist.github.com/fauxpark/010dcf5d6377c3a71ac98ce37414c6c4) for macOS mode
- [ ] Complete Linux and Microsoft Windows compatiblity for OS layer
  - [ ] Generalize the layer name from **macOS** to **OS** or **System**, etc.
- [ ] Reimplement repeat key functionality to work with tap dance (refer to offical [repeat key API](https://docs.qmk.fm/features/repeat_key) to mimic behavior)
  - [ ] Create a temporary mode for repeat and alternative key (timeout after 5 seconds?)
- [ ] Port this keymap to the [ZSA Voyager](https://www.zsa.io/voyager)
- [ ] Design two layers, left and right sides, to use 2× Inland MK-47 keyboards as an affordable pseudo split

### `DONE:`
- [x] Make a fun vanilla ***Doom*** (1993) layer as an alternative to **Mouse** layer (2026-04/13-MO)

---

## 2026-08/30-SU
- **Doom** (1993)
  - `CHANGE:` Swapped game state key with message toggle key.
  - `NEW:` Added `6` (Tap), `8` (Hold) to switch to Rockets and BFG 9000.
- Minor documentation refinements.

## 2026-08/28-FR
- ***Doom*** (1993)
  - `BUGFIX`: `KC_8` → `KC_F8`
  - Updated `README.md` and related PNG
- Polishing documentation.

## 2026-08/27-TH
- ***Doom*** (1993)
  - Tinkering w/ layout by adding more tap dances.
  - [ ]`TODO:` Write the logic for “Run Toggle.” 2× keys are currently assigned to `KC_NO`.

## 2026-08/25-TU
- **Adjustment**: Added RGB (navy) to the Print **Leader** Favorites & History
- ***Doom*** (1993)
  - `BUGFIX:` Added guard to ***Doom*** (1993) RGB layer definition to exclude when `MOUSE_ENABLE` is set to `no` for RGB Matrix state.
  - `NEW:` Added 2× `Pause` keys to `ROW2` on left and right sides.
  - `NEW:` Created macro that emits `Delete` when trying to pause Doom, `Pause` emits for Linux and Windows.
  - `NEW:` Added `F10` to the top row, removing the unassigned `8` key.
  - Tinkering w/ digit arrangement.

## 2026-08/24-MO
- **Leader**: fixed state output-related bugs.
  - `BUGFIX:` Displaying `Leader off` message twice on `★as` to print “all saved” in Favorites and History.
  - `BUGFIX:` Displaying surround character **Leader** sequences improperly (now suppressingthe effects of an unintended left arrow), e.g., `<>`, `()`, etc.
- **Upper**: Added `dot.case` mode toggling on `Tap+Hold` for `Caps Lock` key.
- ***Doom*** (1993)
  - Enabled color LEDS for `Tab` (`YELLOW`) and `Esc` (`RED`).
  - Filled out `KC_NO` keys w/ `0`–`9` weapon changes and `-`/`+` to zoom screen out/in.

## 2026-08/23-SU
- ***Doom*** (1993) → `BUGFIX:` Removed mod-tap `LSFT` for `SPC` key. Fixed responsiveness of door-opening actions possibly regarding MT key issues.
  - `NEW:` Added `F2` and `F3` to open the load and save menus, respectively. Top row, index fingers.
- **macOS** → Swapped tap dances around on the delete key (right thumb); `Tap+Hold` → Open Trash folder in Finder, `Hold` → Empty Trash.
- RGB: Added reactive typing heatmap animation.
- **Leader**: Added print to editor to output the state of **Leader**
  - Print History w/ `★l` for “list”.
  - Print Favorites w/ `★v` for “saved”.
  - To print both use `★as` for “all saved”.
  - [x] Find and fix any remaining output bugs; update docs when mostly done.

## 2026-08/20-TH
- Added more Markdown files for `src` project path and subdirectories.
- **Mouse**: Filled in _ROW1_ blanks w/ tab previous/next.
- **Base**: Too many typos…
  - Removed tap dance for `.` key; it is only mod-tap for `LCTL`.
  - Removed tap dance for `;` key; it is only mod-tap for `LSFT`.

## 2026-08/17-MO
- Cleaned up documentation.
- Fixed ***Doom*** (1993) layer bug w/r/t **UPPER** layer.

## 2026-08/16-SU
- Swapped one-shot shift on **BASE** for [QMK’s repeat key](https://docs.qmk.fm/features/repeat_key)
  - `TODO:` Reimplement QMK’s functionality to be compatible with tap dance.
- Moved one-shot shift to space key on double tap.
- Added left strafe key to ***Doom*** (1993) layer for right-hand use.

## 2026-05/03-SU
- Added **Temporary Lexical Case Modes**, a text‑transformation system for programming, shell, and writing workflows.
  - Case modes:
    - `camelCase` / `PascalCase`
    - `snake_case` / `SCREAMING_SNAKE_CASE`
    - `kebab-case`
    - `dot.case`
    - `path/to/case`
    - `PUNC` mode (auto‑capitalizes after punctuation)
  - `Space` acts as a temporary separator key, capitalizing the next character for `camelCase`/`PascalCase` or inserting the appropriate symbol for other modes.
  - All case modes are temporary and automatically disable after a short idle timeout or when pressing non‑character keys (`Enter`, `Super`/`CMD`, etc.).
    - For `path/to/case`, `KC_TAB` does not disable case mode to support shell tab completions.
  - **Base** layer RGB matrix turns neon mint when any case mode is active.
- Updated **Base** tap dances:
  - Added “close active window” on tap-and-hold for `Esc`.
  - Added `LSFT-Enter` on tap-and-hold for `Enter`.
  - Added `…` on double tap, `⋮` on tap-and-hold for `.`.
  - Added `;␣` on double tap, `:␣` on tap-and-hold for `;`.

## 2026-04/26-SU
- Added global _Leader Key toggle_ on the **Adjustment** layer
  - Toggle key visual feedback: 🔵 Navy = enabled (default), 🔴 Red = disabled
- Added _symbol Leader sequences_ (prefixed with `␣` / space) as the foundation for an expanded symbol library

## 2026‑04/24‑FR
- Implemented RGB Matrix feedback for Leader sequences, including green flashes for successful completions and red flashes for failures or time‑outs.
- Expanded the Leader emoji set with several new sequences.
  - Completed full coverage for `a`–`z` and added select two‑character combinations.
  - These sequences will likely need to be tuned after regular use.
- Added Leader Key **History** replay, which stores the last 10 executed macros. Accessible on the **Upper** layer by holding the number keys.
- Added Leader Key **Favorites** replay, allowing up to 10 favorite macros, also accessed on the **Upper** layer via the number keys.
  - Use the Favorites toggle (**hold** `@`) to switch between replaying Favorites and replaying History. Default mode replays the last 10 History items.
  - To assign a Favorite, **tap‑and‑hold** a number key to save the most recent Leader sequence.
- Added on/off toggle for Leader Replay; **tap‑and‑hold** the `@` key to enable or disable it.
- Introduced preprocessor guards across the keymap to ensure optional QMK features (RGB Matrix, Caps Word, Leader, Mouse Keys) can be safely disabled without breaking the build.
  - Tap Dance remains unguarded because it is a core dependency of this keymap.

## 2026-04/18-SA
- Added experimental support for the [QMK Leader Key](https://docs.qmk.fm/features/leader_key), including a new alpha‑only layer for sequence handling.
  - The Leader key is triggered from the bottom‑corner key on the **Arrow** layers.
  - See [LEADER.md](LEADER.md) for documentation on available sequences.

## 2026-04/16-TH
- Updated **Vim** layers with a new semantic‑deletion key that mirrors `Backspace` and `Del`.
- Converted `Caps Lock` on **Upper** to a tap dance: tap activates `Caps Word`; hold toggles `Caps Lock`.
  - RGB of **Base** is gold when `Caps Word` is active.

## 2026-04/15-WE
- Updated `Backspace` and `Del` keys to use semantic behaviors:
  - Tap: delete character (`Backspace`/`Del`)
  - Tap-and-Hold: delete to beginning/end of line
  - Hold: Delete previous/next word
- Updated ***Doom*** (1993) layer:
  - Added mouse‑wheel keys on the right side of the lower row in a Vim‑style arrangement.
  - Added a `Backspace` tap‑dance key to the top‑right corner.

## 2026-04/14-TU
- Added application switching keys on **Arrow** and **Mouse** layers.
  - Uses `CMD` for macOS; otherwise `LALT`.
  - Tap `TAB`/`LSFT-TAB` to navigate the menu on bottow row of **Arrow** layers and home row **Mouse**.
- Changed semantic punctuation tap-dance key on **Upper** layer to support `!␣` and `?␣`
  - All end-of-sentence bigrams support auto-capitalizing the next character via oneshot `LSFT`.
  - Removed `;␣` and `:␣` because they appear less frequently in prose; I noticed I didn’t really use these bigrams much.

## 2026-04/13-MO
- Added the ***Doom*** (1993) layer (first draft). The layer is accessible via a tap on the **Mouse** layer, a center key on home row.
- Updated arrow‑key layers and expanded multilingual support.
  - Added cursor‑centered angle quotation marks: `«|»` and `‹|›`.
  - Added tap dance key on lower row for combining circumflex (`ˆ`) on tap, macron (`¯`) on double tap, breve (`˘`) on tap-and-hold, and caron (`ˇ`) on hold. On macOS, these require **ABC Extended** keyboard input set in the OS.
  - Reorganized combining accents: grave is now on `?`, tilde on `!`, improving mnemonic grouping.
- Updated Markdown docs, including `DESIGN.md`.

## 2026-04/10-FR
- Initial release.
- Untested for Linux and Microsoft Windows.
