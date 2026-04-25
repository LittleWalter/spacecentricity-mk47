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

## Leader Replay

Leader actions can be replayed from either **History** or **Favorites** via the holds of the **Upper** layer’s number keys.

![Upper: Primary Numpad Layer](assets/03_UPPER.png)

The `@` key toggles replay modes and provides visual feedback:

| Action | `@` Key RGB | Meaning |
|--------------------|-----|---------|
| Tap-and-Hold | 🔴 Red when off | Replay **off** |
| Hold | 🟢 Green | Leader **Favorites** mode |

When the replay mode key is **red** (off), number-key holds do nothing. This eliminates accidental activation of Leader actions during normal typing.

When the replay mode key is **green**, number‑key holds trigger Favorites; otherwise, they replay **History**

By default, the keyboard boots into **History** replay mode with empty History and Favorites. These values are stored only in RAM to avoid unnecessary EEPROM wear.

### Leader History

Each time a Leader sequence completes successfully, the keymap stores it in a rolling history of the **last ten actions**. Each entry records:

* The _category_ (emoji, surround pair, developer annotation)
* The _specific macro_ invoked

History is replayed not through Leader itself, but via **hold‑actions on the number keys** in the **Upper** layer:

* Hold `0` → most recent
* Hold `1` → second most recent
* Hold `2` → third most recent
* …up to `9`

This provides a fast way to repeat your most recent Leader macros without re‑entering their sequences.

### Leader Favorites

Favorites let you pin up to **ten** frequently used Leader actions for quick access.

Favorites use the _same number‑key holds_ (`0`–`9`) as History on the **Upper** layer.

Because History and Favorites share the same keys, the keyboard uses a **mode toggle** (the `@` key) to switch between them.

To assign a Favorite:

* Complete a Leader sequence.
* **Tap‑and‑hold** a number key (`0`–`9`).
* The most recent Leader action is saved into that Favorite slot.

## Supported Leader Sequences

`★` represents the assigned leader key in the keymap.

### Emoji Sequences

Emoji sequences are prefixed with a second tap of the leader key (`★`). (Internally, this is implemented as a `KC_NO` placeholder in the same physical position as the Leader key.)

This system provides fast, mnemonic access to a curated set of commonly used emoji—both practical ones (`🔗`, `✔`) and a few fun extras (`🌮`, `🗿`). The goal is to build intuitive muscle memory for the expressions and symbols you reach for most.

Multi‑letter mnemonics are used when a single letter is already taken or when they improve clarity and recall. Exact sequences may be refined after some use.

| Sequence         | Mnemonic               | Emoji                              | Category            |
|------------------|------------------------|------------------------------------|---------------------|
| `★★a`            | Angry                  | 😡 Red Angry Face                  | Emotion             |
| `★★aa`           | Angry Angry            | 🤬 Face with Symbols Over Mouth    | Emotion             |
| `★★al`           | Alarm                  | ⏰ Alarm Clock                     | Object / Time       |
| `★★an`           | Angel                  | 😇 Smiling Face with Halo          | Emotion             |
| `★★ap`           | Airplane               | ✈️ Airplane                        | Travel              |
| `★★au`           | Automobile             | 🚗 Automobile/Car                  | Travel              |
| `★★b`            | Blush                  | 😊 Smiling Face with Smiling Eyes  | Emotion             |
| `★★be`           | Bullseye               | 🎯 Bullseye                        | Symbol              |
| `★★bi`           | Bicycle/Bike           | 🚲 Bicycle                         | Travel              |
| `★★bk`           | Blow Kiss              | 😘 Face Blowing a Kiss             | Emotion             |
| `★★br`           | Brain                  | 🧠 Brain                           | Body                |
| `★★bt`           | Bedtime                | 🛏️ Bed                             | Object / Sleep      |
| `★★bu`           | Bus                    | 🚌 Bus                             | Travel              |
| `★★c`            | Crying                 | 😢 Crying                          | Emotion             |
| `★★ca`           | Camera                 | 📷 Camera                          | Object / Tech       |
| `★★cb`           | Clipboard              | 📋 Clipboard (Paste Symbol)        | Object / Tech       |
| `★★cc`           | Crying Crying          | 😭 Loudly Crying Face              | Emotion             |
| `★★cd`           | Cloud                  | ☁️ Cloud                           | Nature / Tech       |
| `★★ch`           | Check                  | ✔️ Check Mark Symbol               | Symbol              |
| `★★cl`           | Clap                   | 👏 Clapping                        | Gesture             |
| `★★cm`           | Check Mark             | ✅ Check Mark Button               | Symbol              |
| `★★co`           | Compass                | 🧭 Compass                         | Travel / Navigation |
| `★★cu`           | Cut                    | ✂️ Scissors (Cut Selection Symbol) | Object / Tech       |
| `★★d`            | Death/Dead/Dying       | 💀 Skull                           | Symbol              |
| `★★da`           | Date                   | 📅 Calendar                        | Object / Time       |
| `★★de`           | Devil                  | 😈 Smiling Face with Horns         | Emotion             |
| `★★dr`           | Drink                  | 🥤 Cup with Straw                  | Food                |
| `★★dt`           | Desktop                | 🖥️ Desktop Computer                | Object / Tech       |
| `★★e`            | Eyes                   | 👀 Eyes                            | Body / Reaction     |
| `★★ea`           | Earth                  | 🌎 Globe Showing Americas          | Nature / Symbol     |
| `★★ee`           | Exclamation Exclamation| ‼️Red Double Exclamation Marks     | Symbol              |
| `★★ex`           | Exclamation            | ❗️Red Exclamation Mark             | Symbol              |
| `★★f`            | Fire                   | 🔥 Fire                            | Nature / Symbol     |
| `★★fd`           | Floppy Disk            | 💾 Floppy Disk (Save Symbol)       | Object / Tech       |
| `★★ff`           | File Folder            | 📁 File Folder                     | Object / Tech       |
| `★★fo`           | Folder Open            | 📂 Open File Folder                | Object / Tech       |
| `★★fp`           | Facepalm               | 🤦 Person Facepalming              | Gesture             |
| `★★fr`           | Frustrated             | 😤 Face with Steam From Nose       | Emotion             |
| `★★g`            | Grin/Grinning          | 😁 Beaming Face with Smiling Eyes  | Emotion             |
| `★★gi`           | Gift                   | 🎁 Present                         | Object              |
| `★★gr`           | Gross                  | 🤢 Nauseated Face                  | Emotion             |
| `★★gs`           | Grin w/ Sweat          | 😅 Grinning Face with Sweat        | Emotion             |
| `★★h`            | Heart                  | ❤️ Red Heart                       | Symbol              |
| `★★ha`           | Hamburger              | 🍔 Hamburger                       | Food                |
| `★★he`           | Heart Eyes             | 😍 Smiling Face with Heart-Eyes    | Emotion             |
| `★★hh`           | Huge Hug               | 🤗 Hugging Face                    | Emotion             |
| `★★hl`           | Hyperlink              | 🔗 Link Symbol                     | Symbol / Tech       |
| `★★ho`           | Home/House             | 🏠 House                           | Object / Place      |
| `★★hs`           | Handshake              | 🤝 Handshake                       | Gesture             |
| `★★ht`           | Holding Tears          | 🥹 Smiling Face Holding Back Tears | Emotion             |
| `★★hu`           | Hundred                | 💯 Hundred Points Symbol           | Symbol              |
| `★★hv`           | High Voltage           | ⚡️ High Voltage/Lightning Bolt     | Symbol              |
| `★★i`            | Ice Cream              | 🍦 Soft Ice Cream                  | Food                |
| `★★ic`           | Ice Cube               | 🧊 Ice                             | Object              |
| `★★in`           | Internet               | 🌐 Globe with Meridians            | Symbol              |
| `★★j`            | Joker/Jester           | 🤡 Clown                           | Emotion / Fun / Meme|
| `★★js`           | Joystick               | 🕹 Video Game Joystick             | Object / Tech       |
| `★★k`            | Key                    | 🔑 Key                             | Object              |
| `★★kb`           | Keyboard               | ⌨️ Keyboard                        | Object / Tech       |
| `★★l`            | Laugh                  | 😂 Face with Tears of Joy          | Emotion             |
| `★★lb`           | Light Bulb             | 💡 Light Bulb                      | Object              |
| `★★lc`           | Lock Closed            | 🔒 Closed Lock                     | Object              |
| `★★li`           | Lightning              | 🌩 Cloud with Lightning            | Nature              |
| `★★lo`           | Lock Open              | 🔒 Open Lock                       | Object              |
| `★★lt`           | Laptop                 | 💻 Laptop                          | Object / Tech       |
| `★★m`            | Mind Blown             | 🤯 Exploding Head                  | Emotion             |
| `★★mb`           | Money Bag              | 💰 Money Bag                       | Object              |
| `★★mc`           | Motorcycle             | 🏍 Motorcycle                      | Travel              |
| `★★me`           | Memo                   | 📝 Memo                            | Object              |
| `★★mf`           | Melting Face           | 🫠 Melting Face                    | Emotion             |
| `★★mg`           | Magnifying Glass       | 🔎 Magnifying Glass Tilted Right   | Object              |
| `★★ms`           | Motor Scooter          | 🛵 Motor Scooter                   | Travel              |
| `★★mu`           | Music                  | 🎵 Musical Notes (Beamed 8th Notes)| Symbol              |
| `★★mw`           | Milky Way              | 🌌 Milky Way (Galaxy)              | Nature              |
| `★★n`            | Night                  | 🌙 Crescent Moon                   | Nature              |
| `★★na`           | Not Amused             | 😒 Unamused                        | Emotion             |
| `★★ne`           | Neutral Emotion        | 😐 Neutral Face                    | Emotion             |
| `★★no`           | No                     | 🙅 Person Gesturing No             | Gesture             |
| `★★o`            | Oh no!                 | 😮 Surprised Face with Open Mouth  | Emotion             |
| `★★ok`           | OK                     | 👌 OK Hand Sign                    | Gesture             |
| `★★p`            | Poop                   | 💩 Pile of Poo                     | Fun / Meme          |
| `★★ph`           | Phone                  | 📞 Phone Receiver                  | Object              |
| `★★pk`           | Package                | 📦 Package/Box                     | Object              |
| `★★pl`           | Pleading               | 🥺 Pleading                        | Emotion             |
| `★★pp`           | Pushpin                | 📍 Round Pushpin                   | Object / Travel     |
| `★★pr`           | Printer                | 🖨️ Printer                         | Object / Tech       |
| `★★pt`           | Palms Together         | 🙏 Hands Pressed Together (Praying)| Gesture             |
| `★★q`            | Questioning            | 🤔 Thinking Face                   | Emotion             |
| `★★qm`           | Question Mark          | ❓ Red Question Mark               | Symbol              |
| `★★r`            | Robot                  | 🤖 Robot Face                      | Fun / Object        |
| `★★ra`           | Rain                   | 🌧️ Cloud with Rain                 | Nature              |
| `★★rb`           | Raised Brow            | 🤨 Face with Raised Eyebrow        | Emotion             |
| `★★rc`           | Recycle                | ♻️ Recycling Symbol                | Symbol              |
| `★★rf`           | Red Flag               | 🚩 Triangular Flag                 | Symbol              |
| `★★ro`           | Rolling                | 🤣 Rolling on the Floor Laughing   | Emotion             |
| `★★s`            | Smile                  | 🙂 Slightly Smiling Face           | Emotion             |
| `★★sc`           | Scooter                | 🛴 Kick/Electric Scooter           | Travel              |
| `★★se`           | Star Eyes              | 🤩 Star-Struck                     | Emotion             |
| `★★sf`           | Stoneface              | 🗿 Moai                            | Emotion / Fun / Meme|
| `★★sg`           | Sunglasses             | 😎 Smiling Face with Sunglasses    | Emotion             |
| `★★sh`           | Shush                  | 🤫 Shushing Face                   | Emotion / Gesture   |
| `★★sl`           | Sleeping               | 😴 Sleeping Face                   | Emotion             |
| `★★sm`           | Smirk                  | 😏 Smirking Face                   | Emotion             |
| `★★sn`           | Snow                   | ❄️ Snowflake                       | Nature              |
| `★★sp`           | Sparkles               | ✨ Sparkles                        | Symbol              |
| `★★ss`           | Stop Sign              | 🛑 Red Octagonal Sign              | Symbol              |
| `★★st`           | Star                   | ⭐️ Star                            | Symbol              |
| `★★su`           | Sunny                  | ☀️ Sun                             | Nature              |
| `★★t` or `★★tu`  | Thumbs Up              | 👍 Thumbs Up                       | Gesture             |
| `★★tt` or `★★td` | Thumbs Down            | 👎 Thumbs Down                     | Gesture             |
| `★★ta`           | Taco                   | 🌮 Taco                            | Food                |
| `★★te`           | Temperature            | 🌡️ Thermometer                     | Nature / Object     |
| `★★tr`           | Train                  | 🚆 Train                           | Travel              |
| `★★u`            | Upside-Down            | 🙃 Upside-Down Face                | Emotion             |
| `★★v`            | Victory/Peace Fingers  | ✌️ Peace Hand Sign                 | Gesture             |
| `★★vo`           | Vomiting               | 🤮 Vomiting Face                   | Emotion             |
| `★★vx`           | Vortex                 | 😵‍💫 Spiral Eyes                     | Emotion             |
| `★★w`            | Wink                   | 😉 Winking Face                    | Emotion             |
| `★★wa`           | Warning                | ⚠️ Warning                         | Symbol              |
| `★★wc`           | Wildcard               | 🃏 Joker (Playing Card)            | Object / Fun        |
| `★★we`           | Weary                  | 😩 Weary Face                      | Emotion             |
| `★★wi`           | Wind                   | 💨 Gust of Wind                    | Nature              |
| `★★wm`           | World Map              | 🗺️ World Map                       | Travel / Navigation |
| `★★wn`           | Wireless Network       | 🛜 Wireless/WiFi                   | Symbol / Tech       |
| `★★x`            | Expressionless         | 😑 Expressionless Face             | Emotion             |
| `★★xm`           | Cross Mark             | ❌ Cross Mark Symbol               | Symbol              |
| `★★y`            | Yay!                   | 🎉 Party Popper                    | Emotion             |
| `★★z`            | Za                     | 🍕 Pizza                           | Food                |
| `★★zz`           | Z’s                    | 💤 Zzz                             | Symbol / Sleep      |

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
| `★b` | Bug | `BUG: ` |
| `★.c` | Cleanup | `CLEANUP: ` |
| `★.d` | Deprecated | `DEPRECATED: ` |
| `★f` | Fix | `FIXME: ` |
| `★h` | Hack | `HACK: ` |
| `★i` | Important | `IMPORTANT: ` |
| `★n` | Note | `NOTE: ` |
| `★o` | Optimize | `OPTIMIZE: ` |
| `★r` | Reference | `REF: ` |
| `★.s` | Section Header | `// ------…` |
| `★t` | TODO | `TODO: ` |
| `★w` | Warning | `WARNING: ` |
