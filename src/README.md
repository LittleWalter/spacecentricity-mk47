# `./src`

## 🗺️ Project Directory Map: You Are Here → 📍

```text
..
├── assets/           → Visual documentation & layout data, mostly PNGs
│   └── json/         → Machine-readable layout definitions for keyboard-layout-editor.com
│
├── scripts/          → Build & “(un)installation” tooling
│   ├── build.sh      → The firmware build script, wraps `qmk`
│   ├── install.sh    → Create the project symlink
│   ├── uninstall.sh  → Remove the project symlink
│   │
│   └── README.md     → Tooling documentation
│
├── src/ 📍
│   ├── core/         → Fundamental keymap definitions
│   ├── features/     → Reusable behaviors & features
│   ├── macros/       → Higher-level macros & system integrations
│   ├── tap_dances/   → Semantic groups of tap-dance actions
│   │
│   └── README.md     → This Markdown file 👋
│
├── build             → Project root wrapper/stub that invokes scripts/build.sh
│
├── config.h          → QMK configuration
├── keymap.c          → The primary keymap stub and entry point
├── rules.mk          → Build-time configuration
│
├── DESIGN.md         → Design notes
├── LEADER.md         → Leader key documentation
├── LICENCE.md        → MIT Licence
└── README.md         → The root README documentation
```
