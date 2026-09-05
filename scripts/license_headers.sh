#!/bin/sh
# license_headers.sh — prepends (or removes) a license header on all .c/.h
# files under src/, plus the root-level keymap.c stub.

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
CONFIG_FILE="$PROJECT_ROOT/config.h"

. "$SCRIPT_DIR/utils.sh"

cd "$PROJECT_ROOT" || { echo "❌ Could not cd to project root: $PROJECT_ROOT"; exit 1; }

print_banner() {
    VERSION="${HEADER_VERSION:-$(get_version)}"

    cat <<BANNER
 _  _
| |(_)
| | _   ___   ___  _ __   ___   ___
| || | / __| / _ \\| '_ \\ / __| / _ \\
| || || (__ |  __/| | | |\\__ \\|  __/
|_||_| \\___| \\___||_| |_||___/ \\___|   ______
          _                       _   |______|                _
         | |                     | |                         | |
         | |__    ___   __ _   __| |  ___  _ __  ___     ___ | |__
         | '_ \\  / _ \\ / _\` | / _\` | / _ \\| '__|/ __|   / __|| '_ \\
         | | | ||  __/| (_| || (_| ||  __/| |   \\__ \\ _ \\__ \\| | | |
         |_| |_| \\___| \\__,_| \\__,_| \\___||_|   |___/(_)|___/|_| |_| for Spacecentricity v${VERSION}
BANNER
}

print_help() {
    print_banner
    cat <<EOF

Usage: ./scripts/$(basename "$0") [options]

Adds or removes a standard license header on every .c/.h file under src/,
plus the root-level keymap.c stub.

Invoke this script from the project root.

Options:
  -a, --add                       Add the header to files that don't already have it (default)
  -n, --no-banner, --skip-banner  Suppress the ASCII art banner on output
  -r, --remove, --remove-all      Remove the header from files where it exactly matches
  -v, --version VERSION           Stamp VERSION into the header instead of using config.h data
                                   (also accepts --version=VERSION)
  -h, --help                      Show this help message and exit

Environment:
  QMK_PATH                Path to your QMK checkout (default: $HOME/qmk_firmware)
  SPACECENTRICITY_BANNER  Set to "false" or "0" to suppress the banner by default

Examples:
  ./scripts/$(basename "$0")                     # Add headers where missing
  ./scripts/$(basename "$0") --add               # Same as above, explicit
  ./scripts/$(basename "$0") --remove-all        # Remove headers where present
  ./scripts/$(basename "$0") -v 0.9.0            # Stamp header with v0.9.0 instead of get_version()
  ./scripts/$(basename "$0") --version=0.9.0-rc1 # Same, long-flag form

Tips:
  When this script successfully completes, you can run \`./build --lint\` to
  clean up and verify the formatting of the project’s codebase.

  Note: because header detection uses a byte-exact comparison, running
  --remove-all with a --version that doesn't match what's actually stamped
  in the files won't remove anything — it'll just silently no-op per file.
EOF
}

# Defaults
NO_BANNER=0
MODE="add"
VERSION_OVERRIDE=""
DATE="$(date "+%Y-%m-%d (%A)")"

# Allow SPACECENTRICITY_BANNER=false (or 0) to suppress the banner by default,
# without requiring --no-banner on every invocation.
case "$SPACECENTRICITY_BANNER" in
    [Ff][Aa][Ll][Ss][Ee]|0)
        NO_BANNER=1
        ;;
esac

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help)
            print_help
            exit 0
            ;;
        -a|--add)
            MODE="add"
            ;;
        -n|--no-banner|--skip-banner)
            NO_BANNER=1
            ;;
        -r|--remove|--remove-all)
            MODE="remove"
            ;;
        -v|--version)
            if [ -z "$2" ]; then
                echo "❌ $1 requires an argument" >&2
                exit 1
            fi
            VERSION_OVERRIDE="$2"
            shift
            ;;
        --version=*)
            VERSION_OVERRIDE="${1#*=}"
            ;;
        *)
            echo "❌ Unknown option: $1" >&2
            exit 1
            ;;
    esac
    shift
done

# NOTE: --version/-v is the sanctioned way to override the stamped version.
# Don't hand-edit HEADER below to hardcode a version — that defeats the
# point of get_version() and this flag both, and it's an easy way to end
# up with a header that silently drifts from config.h/CHANGELOG.
#
# NOTE: Generated date not included in the header to preserve exact matches.
if [ -n "$VERSION_OVERRIDE" ]; then
    HEADER_VERSION="$VERSION_OVERRIDE"
else
    HEADER_VERSION="$(get_version)"
fi

HEADER="// ─────────────────────────────────────────────────────────────────
// Spacecentricity v$HEADER_VERSION — A Planck MIT Keymap for the Inland MK-47
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

# Display the ASCII banner (default)
if [ "$NO_BANNER" -eq 0 ]; then
    print_banner
    echo
fi

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
