# QMK Leader Key

QMK supports [leader key functionality](https://docs.qmk.fm/features/leader_key) inspired by [Vim](https://stackoverflow.com/questions/1764263/what-is-the-leader-in-a-vimrc-file).

Spacecentrity includes a small, curated set of Leader key sequences for emoji insertion, RGB control, and text‑editing helpers. These sequences are optional, unobtrusive, and unlikely to be triggered accidentally.

## Implementation Details

To avoid conflicts with tap‑dance, mod‑tap, and layer‑tap behaviors, this keymap activates a dedicated alphabet‑only layer while processing Leader sequences.

Because this temporary layer exposes only letters and a limited set of safe symbols, some characters—such as numbers and certain punctuation—are unavailable for use in Leader sequences.

When the Leader layer is active, the **Base** layer indicator turns green, providing a clear visual cue that the system is waiting for a Leader sequence.

## Supported Leader Sequences

`★` is the assigned leader key in the keymap.

### Emoji Sequences

Emoji sequences are prefixed with `␣` (space).

Below is a list of the most commonly used emoji characters.

| Sequence         | Mnemonic     | Behavior                     |
|------------------|--------------|------------------------------|
| `★␣c`            | Cry          | 😭 Loudly Crying Face        |
| `★␣d`            | Death        | 💀 Skull                     |
| `★␣f`            | Fire         | 🔥 Fire                      |
| `★␣h`            | Heart        | ❤️ Red Heart                 |
| `★␣k`            | Kool         | 😎 Smiling Face With Sunglasses |
| `★␣l`            | Laugh        | 😂 Face With Tears of Joy    |
| `★␣p`            | Poop         | 💩 Pile of Poo               |
| `★␣q`            | Questioning  | 🤔 Thinking Face             |
| `★␣s`            | Smile        | 🙂 Slightly Smiling Face     |
| `★␣t` or `★␣tu`  | Thumbs Up    | 👍 Thumbs Up                 |
| `★␣tt` or `★␣td` | Thumbs Down  | 👎 Thumbs Down               |

> [!WARNING]
> **macOS:** Emoji insertion relies on the compact _Emoji & Symbols_ popup. It will not work if the extended character viewer is active. The position of the first emoji in the popup may also shift depending on system updates or personalization.
>
> **Linux & Microsoft Windows:** Emoji are inserted as direct Unicode characters, so behavior is consistent and does not depend on an OS emoji picker.

### RGB Sequences

RGB sequences are prefixed with `r`.

| Sequence | Mnemonic | Behavior |
|----------|----------|----------|
| `★rj` | Jellybean | Set RGB Matrix to Jellybean Raindrops |
| `★rm` | _The Matrix_ | Set RGB Matrix to Digital Rain |
| `★rn` | RGB Next | Cycle to next RGB Matrix effect |
| `★rp` | RGB Previous | Cycle to previous RGB Matrix effect |
| `★rr` | Rainbow | Set RGB Matrix to Rainbow Moving Chevron |
| `★rt` | Toggle | Toggle RGB Matrix on/off |

### Surrounding Sequences

These sequences wrap the cursor with the chosen pair of characters.

Unlike the **Programming** layers—which place these on physical key positions as tap dances—Leader surround sequences are mnemonic, making them easy to remember.

| Sequence | Mnemonic | Behavior |
|----------|----------|----------|
| `★a` | Angle | `<▮>` |
| `★c` | Curly | `{▮}` |
| `★d` | Double (Quotes) | `"▮"` |
| `★g` | Grave | ``` `▮` ``` |
| `★p` | Parentheses | `(▮)` |
| `★q` | (Single) Quotes | `'▮'` |
| `★s` | Square | `[▮]` |

### Code Annotations

Short, structured developer notes inserted directly into comments.
Each Leader sequence expands into a standardized annotation prefix.

Code annotation sequences are prefixed with `.` (dot/period).

| Sequence | Mnemonic | Behavior |
|----------|----------|----------|
| `★.f` | Fix | `FIXME: ` |
| `★.h` | Help | `TIP: ` |
| `★.i` | Information | `INFO: ` |
| `★.n` | Note | `NOTE: ` |
| `★.r` | Reference | `REF: ` |
| `★.s` | Section Header | `// ------…` |
| `★.t` | TODO | `TODO: ` |
| `★.w` | Warning | `WARNING: ` |
