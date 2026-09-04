#!/bin/sh
# license_headers.sh — prepends (or removes) a license header on all .c/.h

print_help() {
    cat <<'ASCII_ART'
 _  _                               
| |(_)                              
| | _   ___   ___  _ __   ___   ___ 
| || | / __| / _ \| '_ \ / __| / _ \
| || || (__ |  __/| | | |\__ \|  __/
|_||_| \___| \___||_| |_||___/ \___|   ______
          _                       _   |______|                _
         | |                     | |                         | |
         | |__    ___   __ _   __| |  ___  _ __  ___     ___ | |__
         | '_ \  / _ \ / _` | / _` | / _ \| '__|/ __|   / __|| '_ \
         | | | ||  __/| (_| || (_| ||  __/| |   \__ \ _ \__ \| | | |
         |_| |_| \___| \__,_| \__,_| \___||_|   |___/(_)|___/|_| |_|

ASCII_ART

    cat <<EOF
Usage: ./scripts/$(basename "$0") [options]

Adds or removes a standard license header on every .c/.h file under src/,
plus the root-level keymap.c stub.

Invoke this script from the project root.

Options:
  -a, --add                   Add the header to files that don't already have it (default)
  -r, --remove, --remove-all  Remove the header from files where it exactly matches
  -h, --help                  Show this help message and exit

Examples:
  ./scripts/$(basename "$0")              # Add headers where missing
  ./scripts/$(basename "$0") --add        # Same as above, explicit
  ./scripts/$(basename "$0") --remove-all # Remove headers where present

Tips:
  When this script successfully completes, you can run \`./build --lint\` to
  clean up and verify the formatting of the project’s codebase.
EOF
}

HEADER="// ─────────────────────────────────────────────────────────────────
// Spacecentricity v0.1.0 — A Planck MIT Keymap for the Inland MK-47
// Copyright © 2026 LittleWalter
// SPDX-License-Identifier: MIT
// Source: https://github.com/LittleWalter/spacecentricity-mk47
// ─────────────────────────────────────────────────────────────────
"

HEADER_LINES=$(printf '%s\n' "$HEADER" | wc -l | tr -d ' ')

# Write the header to a real temp file once, so removal can compare
# actual file bytes instead of shell strings (avoids any ambiguity
# around trailing newlines in string comparison).
HEADER_FILE=$(mktemp)
printf '%s\n' "$HEADER" > "$HEADER_FILE"

MODE="add"
for arg in "$@"; do
    case "$arg" in
        -h|--help)
            print_help
            rm -f "$HEADER_FILE"
            exit 0
            ;;
        -a|--add)
            MODE="add"
            ;;
        -r|--remove|--remove-all)
            MODE="remove"
            ;;
    esac
done

# Collect target files: everything under src/, plus the root keymap.c stub.
TARGET_FILES=$(find src -type f \( -name "*.c" -o -name "*.h" \))
if [ -f "keymap.c" ]; then
    TARGET_FILES=$(printf '%s\n%s\n' "$TARGET_FILES" "keymap.c")
fi

if [ "$MODE" = "add" ]; then
    printf '%s\n' "$TARGET_FILES" | while read -r file; do
        [ -z "$file" ] && continue

        TOP_TMP=$(mktemp)
        head -n "$HEADER_LINES" "$file" > "$TOP_TMP"

        if ! cmp -s "$TOP_TMP" "$HEADER_FILE"; then
            tmp=$(mktemp)
            printf '%s\n' "$HEADER" | cat - "$file" > "$tmp"
            mv "$tmp" "$file"
            echo "✅ Added header: $file"
        fi
        rm -f "$TOP_TMP"
    done
else
    printf '%s\n' "$TARGET_FILES" | while read -r file; do
        [ -z "$file" ] && continue
        TOP_TMP=$(mktemp)
        head -n "$HEADER_LINES" "$file" > "$TOP_TMP"

        if cmp -s "$TOP_TMP" "$HEADER_FILE"; then
            tail -n +$((HEADER_LINES + 1)) "$file" > "$file.tmp"
            mv "$file.tmp" "$file"
            echo "🗑️  Removed header: $file"
        fi
        rm -f "$TOP_TMP"
    done
fi

rm -f "$HEADER_FILE"
