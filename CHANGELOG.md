# CHANGELOG

## TODOs

- [ ] Test on Linux and Microsoft Windows
- [ ] Design a **Linux** layer as an analog to the **macOS** layer
- [ ] Consider adding `tmux` macros on **Terminal** layer
- [ ] Consider adding the Apple `fn` key via [QMK patch](https://gist.github.com/fauxpark/010dcf5d6377c3a71ac98ce37414c6c4) for macOS mode

### DONE
- [x] Make a fun vanilla **Doom layer** as an alternative to **Mouse layer** (2026-04/13-MO)

---

## 2026-04/13-MO
- Added the **Doom Classic** layer (first draft). The layer is accessible via a tap on the **Mouse** layer.
- Updated arrow‑key layers and expanded multilingual support.
  - Added cursor‑centered angle quotation marks: `«|»` and `‹|›`.
  - Added tap dance key on lower row for combining circumflex (`ˆ`) on tap, macron (`¯`) on double tap, breve (`˘`) on tap-and-hold, and caron (`ˇ`) on hold. On macOS, these require **ABC Extended** keyboard input set in the OS.  
  - Reorganized combining accents: grave is now on `?`, tilde on `!`, improving mnemonic grouping.
- Updated Markdown docs, including `DESIGN.md`. 

## 2026-04/10-FR
- Initial release.
- Untested for Linux and Microsoft Windows.
