# ⌨️ Keymap Graphics

This directory contains the rendered layer diagrams used throughout the project.

These graphics provide quick visual references for each layer in the keymap.

All graphics were created with [keyboard-layout-editor.com](https://www.keyboard-layout-editor.com) and exported as PNG images using [Ungoogled Chromium](https://ungoogled-software.github.io/).

Filenames use a numeric prefix to keep layers ordered consistently with the keymap itself. For example, `00_BASE.png` corresponds to the base layer, `02_LOWER.png` to the numpad layer, etc.

## 🎨 Color Conventions

These colors are used consistently across all diagrams to visually group related key types.

![Keymap Legend](legend.png)

| Key Type | Color | Hex Value |
|----------|-------|-----------|
| Standard | Default Gray | `#CCCCCC` |
| Modifier | Pastel Yellow | `#FFE082` |
| Layer    | Pastel Teal | `#80CBC4` |
| Layer Held | Dark Pastel Teal | `#2E7D78` |
| No Operation (`KC_NO`) | Medium Gray | `#B2BEB5` |
| Media    | Pastel Coral | `#FFD7CC` |
| Navigation | Seafoam Green | `#3DED97` |
| Navigation (Secondary) | Pastel Mint | `#B8F5D0` |
| Digits & Function Keys | Neutral Sand | `#DDD3C0` |
| Warning | Light Red | `#F8B8B5` |
| Mouse Pointer | Pastel Blue | `#A7C7E7` |
| Mouse Button | Pastel Orange | `#F7C59F` |
| Mouse Wheel | Pastel Purple | `#D7B8F3` |

> [!NOTE]
> When colors conflict, the layer color take precedence in diagrams, followed by the modifier color.

## JSON Diagram Data

The JSON files in [`json/`](json/) are the source data used to generate the PNG diagrams in this directory.

Occasionally, changes made in the editor may not save the JSON data as expected; this appears to be an intermittent issue with the site or browser handling of the JSON format.

Load them by dragging the file into the **Raw data** tab on [keyboard-layout-editor.com](https://www.keyboard-layout-editor.com).
