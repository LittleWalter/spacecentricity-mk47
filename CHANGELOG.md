# CHANGELOG

## TODOs

- [ ] Test on Linux and Microsoft Windows
- [ ] Design a **Linux** layer as an analog to the **macOS** layer
- [ ] Consider adding `tmux` macros on **Terminal** layer
- [ ] Consider adding the Apple `fn` key via [QMK patch](https://gist.github.com/fauxpark/010dcf5d6377c3a71ac98ce37414c6c4) for macOS mode

### DONE
- [x] Make a fun vanilla **Doom** layer as an alternative to **Mouse** layer (2026-04/13-MO)

---

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
- Updated **Doom** layer:
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
- Added the **Doom Classic** layer (first draft). The layer is accessible via a tap on the **Mouse** layer, a center key on home row.
- Updated arrow‑key layers and expanded multilingual support.
  - Added cursor‑centered angle quotation marks: `«|»` and `‹|›`.
  - Added tap dance key on lower row for combining circumflex (`ˆ`) on tap, macron (`¯`) on double tap, breve (`˘`) on tap-and-hold, and caron (`ˇ`) on hold. On macOS, these require **ABC Extended** keyboard input set in the OS.
  - Reorganized combining accents: grave is now on `?`, tilde on `!`, improving mnemonic grouping.
- Updated Markdown docs, including `DESIGN.md`.

## 2026-04/10-FR
- Initial release.
- Untested for Linux and Microsoft Windows.
