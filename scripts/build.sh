#!/bin/sh
# A wrapper for `qmk` to centralize repeated commands

print_help() {
    cat <<EOF
 _           _ _     _       _
| |         (_) |   | |     | |
| |__  _   _ _| | __| |  ___| |__
| '_ \| | | | | |/ _\` | / __| '_ \\
| |_) | |_| | | | (_| |_\__ \ | | |
|_.__/ \__,_|_|_|\__,_(_)___/_| |_|
Usage: $(basename "$0") [keymap_name] [options]

Convenience wrapper for building, cleaning, flashing, and checking the
status of this keymap inside your QMK firmware checkout.

By default:
  - The keymap name is: spacecentricity
  - The QMK checkout is assumed to be:
        \$HOME/qmk_firmware

Options:
  -c, --clean         Remove QMK build artifacts before building
  --clean-only        Clean and exit without building
  -f, --flash         Flash the firmware after building
  -s, --status        Show symlink/QMK status and exit
  -h, --help          Show this help message and exit

Examples:
  $(basename "$0")
  $(basename "$0") my_keymap_name
  $(basename "$0") --clean --flash
  QMK_PATH=~/Projects/qmk_firmware $(basename "$0") -s
EOF
}

# Defaults
KEYMAP_NAME=""
FLASH=0
CLEAN=0
CLEAN_ONLY=0
STATUS_ONLY=0

# Parse flags + positional keymap name
for arg in "$@"; do
    case "$arg" in
        -h|--help)
            print_help
            exit 0
            ;;
        -f|--flash)
            FLASH=1
            ;;
        -c|--clean)
            CLEAN=1
            ;;
        --clean-only)
            CLEAN_ONLY=1
            ;;
        -s|--status)
            STATUS_ONLY=1
            ;;
        -*)
            # ignore other flags
            ;;
        *)
            # first non-flag argument = keymap name
            if [ -z "$KEYMAP_NAME" ]; then
                KEYMAP_NAME="$arg"
            fi
            ;;
    esac
done

KEYMAP_NAME="${KEYMAP_NAME:-spacecentricity}"
QMK_PATH="${QMK_PATH:-$HOME/qmk_firmware}"
KEYBOARD="inland/mk47"
TARGET="$QMK_PATH/keyboards/$KEYBOARD/keymaps/$KEYMAP_NAME"

# -------------------------
# Status check function
# -------------------------
show_status() {
    echo "QMK directory: $QMK_PATH"
    echo "Keyboard:      $KEYBOARD"
    echo "Keymap:        $KEYMAP_NAME"
    echo "Target path:   $TARGET"
    echo

    if [ ! -d "$QMK_PATH" ]; then
        echo "❌ QMK directory does not exist."
        return 1
    fi

    if [ -L "$TARGET" ]; then
        LINK_TARGET=$(readlink "$TARGET")
        echo "✅ Symlink exists."
        echo "   → Points to: $LINK_TARGET"
        return 0
    fi

    if [ -e "$TARGET" ]; then
        echo "⚠️  A file or directory exists at the target path, but it is not a symlink."
        return 1
    fi

    echo "❌ No symlink found."
    return 1
}

# If --status was requested, show it and exit
if [ "$STATUS_ONLY" -eq 1 ]; then
    show_status
    exit $?
fi

# Validate QMK directory
if [ ! -d "$QMK_PATH" ]; then
    echo "❌ QMK directory does not exist."
    exit 1
fi

# Require symlink for build/flash
if [ ! -L "$TARGET" ]; then
    echo "❌ No symlink found at:"
    echo "   $TARGET"
    echo "   Run ./install.sh to link this keymap into QMK."
    exit 1
fi

# -------------------------
# Clean operations
# -------------------------
if [ "$CLEAN" -eq 1 ] || [ "$CLEAN_ONLY" -eq 1 ]; then
    echo "🧹 Cleaning QMK build artifacts..."
    rm -rf "$QMK_PATH/.build"
    mkdir -p "$QMK_PATH/.build"
    echo "✅ Clean complete."

    if [ "$CLEAN_ONLY" -eq 1 ]; then
        exit 0
    fi
fi

# -------------------------
# Flash
# -------------------------
if [ "$FLASH" -eq 1 ]; then
    echo "⚡ Building and flashing firmware via qmk..."

    qmk flash -kb "$KEYBOARD" -km "$KEYMAP_NAME"
    STATUS=$?

    echo
    if [ "$STATUS" -ne 0 ]; then
        echo "❌ Flash failed."
        exit "$STATUS"
    fi

    echo "✅ Flash completed successfully."
    exit 0
fi

# -------------------------
# Build
# -------------------------
echo "🔨 Building firmware..."
qmk compile -kb "$KEYBOARD" -km "$KEYMAP_NAME"
STATUS=$?

echo
if [ "$STATUS" -ne 0 ]; then
    echo "❌ Build failed."
    exit "$STATUS"
fi

echo "✅ Build completed successfully."

exit 0
