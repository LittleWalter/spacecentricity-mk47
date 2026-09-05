#!/bin/sh
# A wrapper for `qmk` to centralize repeated commands

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
CONFIG_FILE="$PROJECT_ROOT/config.h"

. "$SCRIPT_DIR/utils.sh"

print_banner() {
    VERSION=$(get_version)

    cat <<BANNER
 _             _  _      _          _     
| |           (_)| |    | |        | |    
| |__   _   _  _ | |  __| |    ___ | |__  
| '_ \\ | | | || || | / _\` |   / __|| '_ \\ 
| |_) || |_| || || || (_| | _ \\__ \\| | | |
|_.__/  \\__,_||_||_| \\__,_|(_)|___/|_| |_| for Spacecentricity v${VERSION}
BANNER
}

print_help() {
    print_banner
    cat <<EOF

Usage: $(basename "$0") [keymap_name] [options]

A POSIX-compliant convenience wrapper for building, cleaning, flashing, linting,
and checking the status of this keymap inside your QMK firmware checkout.

By default:
  - The keymap name is: spacecentricity
  - The QMK checkout is assumed to be:
        \$HOME/qmk_firmware

Options:
  -c, --clean, --clear            Remove QMK build artifacts before building
  --clean-only, --clear-only      Clean and exit without building
  -C, --check                     Run status check + strict lint in one pass
  -d, --console                   Open the QMK HID debug console
  -f, --flash                     Build and flash the firmware
  -h, --help                      Show this help message and exit
  -l, --lint                      Lint the keymap before building
  -n, --no-banner, --skip-banner  Suppress the ASCII art banner on output
  -S, --strict                    Treat lint warnings as errors (requires --lint)
  -s, --status                    Show symlink/QMK status and exit

Environment:
  QMK_PATH                Path to your QMK checkout (default: $HOME/qmk_firmware)
  SPACECENTRICITY_BANNER  Set to "false" or "0" to suppress the banner by default

Examples:
  $(basename "$0")                  # Build spacecentricity
  $(basename "$0") -f               # Build and flash spacecentricity
  $(basename "$0") --no-banner -f   # Build and flash without the banner
  $(basename "$0") my_keymap_name   # Build a given keymap name
  $(basename "$0") --clean --flash  # Clean build artifacts, then flash spacecentricity
  QMK_PATH=~/Projects/qmk_firmware $(basename "$0") -s  # Display status w/ custom QMK path
  SPACECENTRICITY_BANNER=false $(basename "$0")  # Skip banner via environment variable

  From Project Root:
    ./build
    ./build -f             
    ./build my_keymap_name
    ./build --clean --flash
    QMK_PATH=~/Projects/qmk_firmware ./build -s
EOF
}

# Defaults
CHECK_ONLY=0
CLEAN=0
CLEAN_ONLY=0
CONSOLE=0
FLASH=0
KEYMAP_NAME=""
LINT=0
NO_BANNER=0
STATUS_ONLY=0
STRICT=0

# Allow SPACECENTRICITY_BANNER=false (or 0) to suppress the banner by default,
# without requiring --no-banner on every invocation.
case "$SPACECENTRICITY_BANNER" in
    [Ff][Aa][Ll][Ss][Ee]|0)
        NO_BANNER=1
        ;;
esac

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
        -c|--clean|--clear)
            CLEAN=1
            ;;
        -C|--check)
            CHECK_ONLY=1
            ;;
        --clean-only|--clear-only)
            CLEAN_ONLY=1
            ;;
         -d|--console)
            CONSOLE=1
            ;;
        -l|--lint)
            LINT=1
            ;;
        -n|--no-banner|--skip-banner)
            NO_BANNER=1
            ;;
        -S|--strict)
            STRICT=1
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

# Display the ASCII banner (default)
if [ "$NO_BANNER" -eq 0 ]; then
    print_banner
    echo
fi

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
# Console (QMK HID debug console)
# -------------------------
if [ "$CONSOLE" -eq 1 ]; then
    echo "🖥️  Opening QMK HID console..."
    echo "💡 Enable debug output on the keyboard (hold the debug-toggle key) to see live output."
    qmk console
    exit $?
fi

# -------------------------
# Combined check (status + strict lint)
# -------------------------
if [ "$CHECK_ONLY" -eq 1 ]; then
    show_status
    STATUS_RESULT=$?
    echo

    if [ "$STATUS_RESULT" -ne 0 ]; then
        echo "❌ Status check failed. Skipping lint."
        exit 1
    fi

    echo "🔍 Linting keymap (strict)..."
    qmk lint -kb "$KEYBOARD" -km "$KEYMAP_NAME" --strict
    LINT_RESULT=$?

    if [ "$LINT_RESULT" -ne 0 ]; then
        echo "❌ Lint failed."
        exit "$LINT_RESULT"
    fi

    echo "✅ Check complete: symlink OK, lint passed."
    exit 0
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
# Lint
# -------------------------
if [ "$LINT" -eq 1 ]; then
    echo "🔍 Linting keymap..."
    if [ "$STRICT" -eq 1 ]; then
        qmk lint -kb "$KEYBOARD" -km "$KEYMAP_NAME" --strict
    else
        qmk lint -kb "$KEYBOARD" -km "$KEYMAP_NAME"
    fi
    STATUS=$?

    if [ "$STATUS" -ne 0 ]; then
        echo "❌ Lint failed. Aborting."
        exit "$STATUS"
    fi
    echo "✅ Lint completed."
fi

# -------------------------
# Build
# -------------------------

# Set this to the actual flash size for the mk47's MCU (WB32FQ95).
# Check your QMK checkout's linker script to confirm the real value:
#   find "$QMK_PATH" -path "*wb32*" -iname "*.ld"
FLASH_TOTAL_BYTES=262144  # 256KB — confirm against the .ld file above before trusting this

BUILD_LOG=$(mktemp)
START_TIME=$(date +%s)

qmk compile -kb "$KEYBOARD" -km "$KEYMAP_NAME" >"$BUILD_LOG" 2>&1 &
BUILD_PID=$!

# Fancy rotating spinner
SPINNER_FRAMES='◒ ◐ ◓ ◑'
FRAME_INDEX=0

format_elapsed() {
    _secs="$1"
    _m=$((_secs / 60))
    _s=$((_secs % 60))
    if [ "$_m" -gt 0 ]; then
        printf '%dm%02ds' "$_m" "$_s"
    else
        printf '%ds' "$_s"
    fi
}

if [ -t 1 ]; then
    printf '◒ Compiling…'
    while kill -0 "$BUILD_PID" 2>/dev/null; do
        FRAME=$(printf '%s' "$SPINNER_FRAMES" | awk -v i="$FRAME_INDEX" '{print $((i % NF) + 1)}')

        NOW=$(date +%s)
        LIVE_ELAPSED=$((NOW - START_TIME))
        LIVE_FMT=$(format_elapsed "$LIVE_ELAPSED")

        printf '\r%s Compiling… (%s) ' "$FRAME" "$LIVE_FMT"
        FRAME_INDEX=$((FRAME_INDEX + 1))
        sleep 0.15
    done
    printf '\r%*s\r' 30 ''  # clear the spinner line (widened to cover the timer text too)
fi

wait "$BUILD_PID"
STATUS=$?

END_TIME=$(date +%s)
ELAPSED=$((END_TIME - START_TIME))
ELAPSED_FMT=$(format_elapsed "$ELAPSED")

BUILD_OUTPUT=$(cat "$BUILD_LOG")
rm -f "$BUILD_LOG"

if [ "$STATUS" -ne 0 ]; then
    echo "❌ Build failed after ${ELAPSED_FMT}:"
    printf '%s\n' "$BUILD_OUTPUT" | tail -n 20
    exit "$STATUS"
fi

echo "✅ Build completed successfully in ${ELAPSED_FMT}."

SIZE_BYTES=$(printf '%s\n' "$BUILD_OUTPUT" | awk '/^[[:space:]]*[0-9]+[[:space:]]+[0-9]+[[:space:]]+[0-9]+[[:space:]]+[0-9]+[[:space:]]+[0-9a-f]+[[:space:]]/ {print $4; exit}')

if [ -n "$SIZE_BYTES" ]; then
    PERCENT=$(awk -v used="$SIZE_BYTES" -v total="$FLASH_TOTAL_BYTES" 'BEGIN { printf "%.1f", (used / total) * 100 }')
    USED_KB=$(awk -v b="$SIZE_BYTES" 'BEGIN { printf "%.1f", b / 1024 }')
    TOTAL_KB=$(awk -v b="$FLASH_TOTAL_BYTES" 'BEGIN { printf "%.0f", b / 1024 }')

    BAR_WIDTH=30
    FILLED=$(awk -v pct="$PERCENT" -v w="$BAR_WIDTH" 'BEGIN { printf "%d", (pct / 100) * w }')
    [ "$FILLED" -gt "$BAR_WIDTH" ] && FILLED="$BAR_WIDTH"
    EMPTY=$((BAR_WIDTH - FILLED))

    BAR=$(printf '%*s' "$FILLED" '' | tr ' ' '█')
    BAR="${BAR}$(printf '%*s' "$EMPTY" '' | tr ' ' '░')"

    echo "📦 Firmware size: ${USED_KB}KB / ${TOTAL_KB}KB (${PERCENT}%)"
    echo "   [${BAR}]"
fi

FIRMWARE_BASENAME="$(printf '%s' "$KEYBOARD" | tr '/' '_')_${KEYMAP_NAME}"
FIRMWARE_FILE=$(find "$QMK_PATH" -maxdepth 1 -type f \
    \( -name "${FIRMWARE_BASENAME}.bin" -o -name "${FIRMWARE_BASENAME}.hex" -o -name "${FIRMWARE_BASENAME}.uf2" \) \
    2>/dev/null | head -n 1)

if [ -n "$FIRMWARE_FILE" ]; then
    echo "📍 Binary: $FIRMWARE_FILE"
else
    echo "⚠️  Could not locate compiled binary (expected ${FIRMWARE_BASENAME}.[bin|hex|uf2] in $QMK_PATH)"
fi

exit 0
