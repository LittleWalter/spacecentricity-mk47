#!/bin/sh
# Removes the symbolic link to the QMK path of the keymap

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
CONFIG_FILE="$PROJECT_ROOT/config.h"

. "$SCRIPT_DIR/utils.sh"

print_banner() {
    VERSION=$(get_version)
    cat <<BANNER
               _              _           _  _          _
              (_)            | |         | || |        | |
 _   _  _ __   _  _ __   ___ | |_   __ _ | || |    ___ | |__
| | | || '_ \\ | || '_ \\ / __|| __| / _\` || || |   / __|| '_ \\
| |_| || | | || || | | |\\__ \\| |_ | (_| || || | _ \\__ \\| | | |
 \\__,_||_| |_||_||_| |_||___/ \\__| \\__,_||_||_|(_)|___/|_| |_| for Spacecentricity v${VERSION}
BANNER
}

print_help() {
    print_banner
    cat <<EOF

Usage: $(basename "$0") [keymap_name] [options]

This POSIX-compliant script removes the symbolic link from your QMK keymaps 
directory that was created by the install script. It does NOT delete any 
files from this repository — only the symlink inside your QMK tree.

This script also removes any optional man pages previously installed by
install_man.sh.

By default:
  - The keymap name is: spacecentricity
  - The QMK checkout is assumed to be at:
        \$HOME/qmk_firmware

You can override these defaults:

  Keymap name as an argument:
      $(basename "$0") my_keymap_name

  QMK directory (environment variable):
      QMK_PATH=/path/to/qmk_firmware $(basename "$0")

Options:
  -h, --help                      Show this help message and exit
  -n, --no-banner, --skip-banner  Suppress the ASCII art banner on output

Environment:
  QMK_PATH                Path to your QMK checkout (default: $HOME/qmk_firmware)
  SPACECENTRICITY_BANNER  Set to "false" or "0" to suppress the banner by default

Examples:
  $(basename "$0")
  $(basename "$0") my_keymap_name
  QMK_PATH=~/Projects/qmk_firmware $(basename "$0")

After removal, the keymap will no longer appear in:
  keyboards/<keyboard>/<revision>/keymaps/
EOF
}

# Defaults
NO_BANNER=0

# Allow SPACECENTRICITY_BANNER=false (or 0) to suppress the banner by default,
# without requiring --no-banner on every invocation.
case "$SPACECENTRICITY_BANNER" in
    [Ff][Aa][Ll][Ss][Ee]|0)
        NO_BANNER=1
        ;;
esac

case "$1" in
    -h|--help)
        print_help
        exit 0
        ;;
    -n|--no-banner|--skip-banner)
        NO_BANNER=1
        ;;
esac

## Display the ASCII banner (default)
if [ "$NO_BANNER" -eq 0 ]; then
    print_banner
    echo
fi

KEYMAP_NAME="${1:-spacecentricity}"
QMK_PATH="${QMK_PATH:-$HOME/qmk_firmware}" # Check if user has alternate QMK root
TARGET="$QMK_PATH/keyboards/inland/mk47/keymaps/$KEYMAP_NAME"
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
MAN_SCRIPT="$SCRIPT_DIR/install_man.sh"

if [ -L "$TARGET" ]; then
    rm "$TARGET"
    echo "Symlink removed: $TARGET"
else
    echo "No symlink found at $TARGET"
fi

if [ -f "$MAN_SCRIPT" ]; then
    echo ""
    echo "Using \`install_man --remove --no-banner\` to delete build scripts…"
    sh "$MAN_SCRIPT" --remove --no-banner
else
    echo "Note: install_man.sh not found at $MAN_SCRIPT — skipping man page removal" >&2
fi
