# QMK Leader Key

QMK includes [Leader Key functionality](https://docs.qmk.fm/features/leader_key), inspired by [Vim’s “leader” concept](https://stackoverflow.com/questions/1764263/what-is-the-leader-in-a-vimrc-file). A Leader key allows you to trigger multi‑key mnemonic sequences that expand into actions, text, or macros.

Spacecentricity provides a curated set of Leader sequences for emoji insertion, RGB control, and text‑editing helpers. These sequences are:

* Mnemonic — designed to be easy to remember
* Optional — they never interfere with normal typing
* Low‑risk — unlikely to be triggered accidentally

Leader sequences may contain up to three keys, not counting the Leader key itself. This keeps them fast to type while still allowing a rich vocabulary of shortcuts.

## Implementation Details

To avoid conflicts with tap‑dance, mod‑tap, and layer‑tap behaviors, this keymap activates a dedicated alphabet‑only layer while processing Leader sequences. Because this temporary layer exposes only letters and a limited set of safe symbols, some characters—such as numbers and certain punctuation—are unavailable for use in Leader sequences.

While the Leader layer is active, the RGB matrix shifts to a dim navy blue to indicate that it is waiting for a Leader sequence. When the sequence completes, the keyboard briefly flashes green on success or red on failure before returning to normal per‑layer lighting.

| Leader State              | Color    | RGB Value   | Meaning                                    |
|---------------------------|----------|-------------|--------------------------------------------|
| Waiting for sequence      | 🔵 Navy  | `0, 0, 128` | Leader mode active; expecting key input    |
| Sequence successful       | 🟢 Green | `0, 255, 0` | A valid Leader sequence was recognized     |
| Sequence failed / timeout | 🔴 Red   | `255, 0, 0` | No matching sequence or sequence timed out |

### Leader History

Each time a Leader sequence completes successfully, the keymap stores it in a rolling history of the last ten actions. Entries record both the _category_ of action (emoji, surround pair, developer annotation) and the _specific macro_ invoked. RGB matrix sequences are intentionally excluded.

History is replayed not through Leader itself, but via **hold‑actions on the number keys** in the **UPPER** layer:

* Hold `0` → most recent
* Hold `1` → second most recent
* Hold `2` → third most recent
* …up to `9`

This provides a fast way to repeat frequently used Leader macros without re‑entering their sequences.

### Leader Favorites

Leader Favorites allow you to pin up to ten frequently used Leader actions for quick access. Like History, Favorites are replayed through **hold‑actions on the number keys** in the **UPPER** layer, using the same `0`–`9` positions.

Favorites and History share the same keys, so the keyboard provides a mode toggle:

* **Hold** `@` → switch between **Favorites** and **History** replay
  * The key’s RGB turns **green** when Favorites mode is active

To assign a Favorite, complete a Leader sequence, then **tap‑and‑hold** a number key (`0`–`9`) to save the most recent action into that slot.

## Supported Leader Sequences

`★` represents the assigned leader key in the keymap.

### Emoji Sequences

Emoji sequences are prefixed with a second tap of the leader key (`★`). (Technically this is a `KC_NO` placeholder in the same physical position as the Leader key.)

Below is a list of commonly used emoji characters and a few fun ones.

Multi‑letter mnemonics are used when a single letter is already assigned or when clarity improves recall.

| Sequence         | Mnemonic               | Emoji                              |
|------------------|------------------------|------------------------------------|
| `★★a`            | Angry                  | 😡 Red Angry Face                  |
| `★★aa`           | Angry Angry            | 🤬 Face with Symbols Over Mouth    |
| `★★al`           | Alarm                  | ⏰ Alarm Clock                     |
| `★★ap`           | Airplane               | ✈️ Airplane                        |
| `★★an`           | Angel                  | 😇 Smiling Face with Halo          |
| `★★b`            | Blush                  | 😊 Smiling Face with Smiling Eyes  |
| `★★be`           | Bullseye               | 🎯 Bullseye                        |
| `★★bk`           | Blow Kiss              | 😘 Face Blowing a Kiss             |
| `★★br`           | Brain                  | 🧠 Brain                           |
| `★★bt`           | Bedtime                | 🛏️ Bed                             |
| `★★c`            | Cry/Crying             | 😭 Loudly Crying Face              |
| `★★ca`           | Camera                 | 📷 Camera                          |
| `★★ch`           | Check                  | ✔️ Check Mark Symbol               |
| `★★cl`           | Clap                   | 👏 Clapping                        |
| `★★cm`           | Check Mark             | ✅ Check Mark Button               |
| `★★co`           | Compass                | 🧭 Compass                         |
| `★★d`            | Death/Dead/Dying       | 💀 Skull                           |
| `★★da`           | Date                   | 📅 Calendar                        |
| `★★de`           | Devil                  | 😈 Smiling Face with Horns         |
| `★★e`            | Eyes                   | 👀 Eyes                            |
| `★★ea`           | Earth                  | 🌎 Globe Showing Americas          |
| `★★ee`           | Exclamation Exclamation| ‼️Red Double Exclamation           |
| `★★f`            | Fire                   | 🔥 Fire                            |
| `★★fp`           | Facepalm               | 🤦 Person Facepalming              |
| `★★fr`           | Frustrated             | 😤 Face with Steam From Nose       |
| `★★g`            | Grin/Grinning          | 😁 Beaming Face with Smiling Eyes  |
| `★★gi`           | Gift                   | 🎁 Present                         |
| `★★gs`           | Grin w/ Sweat          | 😅 Grinning Face with Sweat        |
| `★★h`            | Heart                  | ❤️ Red Heart                       |
| `★★ha`           | Hamburger              | 🍔 Hamburger                       |
| `★★he`           | Heart Eyes             | 😍 Smiling Face with Heart-Eyes    |
| `★★hh`           | Huge Hug               | 🤗 Hugging Face                    |
| `★★ho`           | Home/House             | 🏠 House                           |
| `★★hs`           | Handshake              | 🤝 Handshake                       |
| `★★ht`           | Holding Tears          | 🥹 Smiling Face Holding Back Tears |
| `★★hu`           | Hundred                | 💯 Hundred Points Symbol           |
| `★★hv`           | High Voltage           | ⚡️ High Voltage/Lightning Bolt     |
| `★★i`            | Ice Cream              | 🍦 Soft Ice Cream                  |
| `★★ic`           | Ice Cube               | 🧊 Ice                             |
| `★★in`           | Internet               | 🌐 Globe with Meridians            |
| `★★j`            | Joker/Jester           | 🤡 Clown                           |
| `★★k`            | Key                    | 🔑 Key                             |
| `★★l`            | Laugh                  | 😂 Face with Tears of Joy          |
| `★★lb`           | Light Bulb             | 💡 Light Bulb                      |
| `★★lc`           | Lock Closed            | 🔒 Closed Lock                     |
| `★★li`           | Link                   | 🔗 Link Symbol                     |
| `★★lo`           | Lock Open              | 🔒 Open Lock                       |
| `★★lt`           | Laptop                 | 💻 Laptop                          |
| `★★m`            | Mind Blown             | 🤯 Exploding Head                  |
| `★★mb`           | Money Bag              | 💰 Money Bag                       |
| `★★me`           | Memo                   | 📝 Memo                            |
| `★★mf`           | Melting Face           | 🫠 Melting Face                    |
| `★★mg`           | Magnifying Glass       | 🔎 Magnifying Glass Tilted Right   |
| `★★ms`           | Milkshake              | 🥤 Cup with Straw                  |
| `★★mw`           | Milky Way              | 🌌 Milky Way (Galaxy)              |
| `★★mu`           | Music                  | 🎵 Musical Notes (Beamed 8th Notes)|
| `★★n`            | Night                  | 🌙 Crescent Moon                   |
| `★★na`           | Not Amused             | 😒 Unamused                        |
| `★★ne`           | Neutral Emotion        | 😐 Neutral Face                    |
| `★★no`           | No                     | 🙅 Person Gesturing No             |
| `★★o`            | Oh no!                 | 😮 Surprised Face with Open Mouth  |
| `★★ok`           | OK                     | 👌 OK Hand Sign                    |
| `★★p`            | Poop                   | 💩 Pile of Poo                     |
| `★★ph`           | Phone                  | 📞 Phone Receiver                  |
| `★★pp`           | Pushpin                | 📍 Round Pushpin                   |
| `★★pr`           | Pray                   | 🙏 Hands Pressed Together          |
| `★★q`            | Questioning            | 🤔 Thinking Face                   |
| `★★qm`           | Question Mark          | ❓ Red Question Mark               |
| `★★r`            | Robot                  | 🤖 Robot Face                      |
| `★★ra`           | Rain                   | 🌧️ Cloud with Rain                 |
| `★★rb`           | Raised Brow            | 🤨 Face with Raised Eyebrow        |
| `★★rc`           | Recycle                | ♻️ Recycling Symbol                |
| `★★rf`           | Red Flag               | 🚩 Triangular Flag                 |
| `★★s`            | Smile                  | 🙂 Slightly Smiling Face           |
| `★★se`           | Star Eyes              | 🤩 Star-Struck                     |
| `★★sf`           | Stoneface              | 🗿 Moai                            |
| `★★sg`           | Sunglasses             | 😎 Smiling Face with Sunglasses    |
| `★★sl`           | Sleeping               | 😴 Sleeping Face                   |
| `★★sm`           | Smirk                  | 😏 Smirking Face                   |
| `★★sn`           | Snow                   | ❄️ Snowflake                       |
| `★★sp`           | Sparkles               | ✨ Sparkles                        |
| `★★ss`           | Stop Sign              | 🛑 Red Octagonal Sign              |
| `★★st`           | Star                   | ⭐️ Star                            |
| `★★su`           | Sunny                  | ☀️ Sun                             |
| `★★t` or `★★tu`  | Thumbs Up              | 👍 Thumbs Up                       |
| `★★tt` or `★★td` | Thumbs Down            | 👎 Thumbs Down                     |
| `★★ta`           | Taco                   | 🌮 Taco                            |
| `★★te`           | Temperature            | 🌡️ Thermometer                     |
| `★★u`            | Upside-Down            | 🙃 Upside-Down Face                |
| `★★v`            | Victory/Peace Fingers  | ✌️ Peace Hand Sign                 |
| `★★w`            | Wink                   | 😉 Winking Face                    |
| `★★wa`           | Warning                | ⚠️ Warning                         |
| `★★wc`           | Wildcard               | 🃏 Joker (Playing Card)            |
| `★★we`           | Weary                  | 😩 Weary Face                      |
| `★★wi`           | Wind                   | 💨 Gust of Wind                    |
| `★★wm`           | World Map              | 🗺️ World Map                       |
| `★★wn`           | Wireless Network       | 🛜 Wireless/WiFi                   |
| `★★x`            | Expressionless         | 😑 Expressionless Face             |
| `★★xm`           | Cross Mark             | ❌ Cross Mark Symbol               |
| `★★y`            | Yay!                   | 🎉 Party Popper                    |
| `★★z`            | Za                     | 🍕 Pizza                           |
| `★★zz`           | Z’s                    | 💤 Zzz                             |

The goal of these Leader sequences is to build fast, intuitive muscle memory for your most frequently used emojis. This set intentionally covers more than you’ll typically need, ensuring you always have a quick mnemonic for the expressions and symbols you reach for most.

> [!WARNING]
> **macOS:** Emoji insertion relies on the compact _Emoji & Symbols_ popup. It will not work if the full Character Viewer is open. The emoji that appears in the **first** position of the popup can change based on system updates, personalization, or Apple’s internal ranking. Only emojis that appear as the top result will auto‑insert.
>
> When possible, I search using the emoji’s Unicode code point, but as of macOS 15 Sequoia the search field only accepts **single** code points. Fully qualified sequences (e.g., `U+2764 U+FE0F` for “red heart”) do not work in the search field. In those cases, I choose the most reliable search term to force the correct emoji to the top of the list; otherwise, it falls back to keyword search and leaves selection to the user.
>
> **Linux & Microsoft Windows:** Emoji are inserted as direct Unicode characters, so behavior is consistent and does not depend on an OS emoji picker.

### RGB Sequences

RGB Matrix effects are prefixed with `r`.

| Sequence | Mnemonic | Behavior |
|----------|----------|----------|
| `★rj` | Jellybean | Set RGB Matrix to Jellybean Raindrops |
| `★rm` | _The Matrix_ | Set RGB Matrix to Digital Rain |
| `★rn` | RGB Next | Cycle to next RGB Matrix effect |
| `★rp` | RGB Previous | Cycle to previous RGB Matrix effect |
| `★rr` | Rainbow | Set RGB Matrix to Rainbow Moving Chevron |
| `★rt` | Toggle | Toggle RGB Matrix on/off |

> [!NOTE]
> RGB Sequences are **not** recorded in Leader History.

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

Some sequences use a prefixed `.` (dot) to avoid conflicts with surrounding Leader namespaces.

| Sequence | Mnemonic | Behavior |
|----------|----------|----------|
| `★f` | Fix | `FIXME: ` |
| `★h` | Help | `TIP: ` |
| `★i` | Information | `INFO: ` |
| `★n` | Note | `NOTE: ` |
| `★r` | Reference | `REF: ` |
| `★.s` | Section Header | `// ------…` |
| `★t` | TODO | `TODO: ` |
| `★w` | Warning | `WARNING: ` |
