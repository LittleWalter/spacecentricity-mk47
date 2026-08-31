# `./docs/`

This directory wrangles Markdown documentation away from the project root.

## 🗺️ Project Directory Map: You Are Here → 📍 (w/ Description)

```text
..
├── assets/           → Visual documentation & layout data, mostly PNGs
│   └── json/         → Machine-readable layout definitions for keyboard-layout-editor.com
│
├── docs/ 📍 (Advanced firmware documentation)
│   ├── DESIGN.md     → Design notes
│   ├── LEADER.md     → Leader key documentation
│   │
│   └── README.md     → This Markdown file 👋
│
├── scripts/          → Build & “(un)installation” tooling
│   ├── build.sh      → The firmware build script, wraps `qmk`
│   ├── install.sh    → Create the project symlink
│   ├── uninstall.sh  → Remove the project symlink
│   │
│   └── README.md     → Tooling documentation
│
├── src/              → Source code
│   ├── core/         → Fundamental keymap definitions
│   ├── features/     → Reusable behaviors & features
│   ├── macros/       → Higher-level macros & system integrations
│   └── tap_dances/   → Semantic groups of tap-dance actions
│
├── build             → Project root wrapper/stub that invokes scripts/build.sh
│
├── config.h          → QMK configuration
├── keymap.c          → The primary keymap stub and entry point
├── rules.mk          → Build-time configuration
│
├── LICENCE.md        → MIT Licence
└── README.md         → The root README documentation
```
