# `./src/`

The base path of the QMK firmware source code.

## 🗺️ Project Directory Map: You Are Here → 📍 (w/ Description)

```text
..
├── assets/           → Visual documentation & layout data, mostly PNGs
│   └── json/         → Machine-readable layout definitions for keyboard-layout-editor.com
│
├── docs/             → Advanced firmware & build tooling documentation
│   ├── man/          → Man pages for build tooling
│   ├── DESIGN.md     → Design notes
│   └── LEADER.md     → Leader key documentation
│
├── scripts/                → Build & “(un)installation” tooling
│   ├── build.sh            → The firmware build script, wraps `qmk`
│   ├── install.sh          → Create the project symlink
│   ├── install_man.sh      → Copy build tooling man pages: $HOME/.local/share/man/man1
│   ├── uninstall.sh        → Remove the project symlink
│   ├── license_headers.sh  → Add/remove predefined license headers in `src/`
│   │
│   └── README.md           → Tooling documentation
│
├── src/ 📍 (Source code)
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
├── LICENCE.md        → MIT Licence
└── README.md         → The root README documentation
```
