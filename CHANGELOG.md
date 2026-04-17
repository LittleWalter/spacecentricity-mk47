# CHANGELOG

## TODOs

- [ ] Test on Linux and Microsoft Windows
- [ ] Design a **Linux** layer as an analog to the **macOS** layer
- [ ] Consider adding `tmux` macros on **Terminal** layer
- [ ] Consider adding the Apple `fn` key via [QMK patch](https://gist.github.com/fauxpark/010dcf5d6377c3a71ac98ce37414c6c4) for macOS mode

### DONE
- [x] Make a fun vanilla **Doom layer** as an alternative to **Mouse layer** (2026-04/13-MO)

---

## 2026-04/16-TH
- Changed **Vim** layers: added semantic deletion key that mirrors `Backspace` and `Del`.

## 2026-04/15-WE
- Changed `Backspace` and `Del` keys to use semantic behaviors:
  - Tap: delete character (`Backspace`/`Del`)
  - Tap-and-Hold: delete to beginning/end of line
  - Hold: Delete previous/next word
- Change **Mouse** layer:
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
