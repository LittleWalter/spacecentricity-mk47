#!/bin/sh
# Creates the symbolic link to the QMK path of the keymap

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
CONFIG_FILE="$PROJECT_ROOT/config.h"

. "$SCRIPT_DIR/utils.sh"

print_banner() {
    VERSION=$(get_version)
    cat <<BANNER
 _              _           _  _          _     
(_)            | |         | || |        | |    
 _  _ __   ___ | |_   __ _ | || |    ___ | |__  
| || '_ \\ / __|| __| / _\` || || |   / __|| '_ \\
| || | | |\\__ \\| |_ | (_| || || | _ \\__ \\| | | |
|_||_| |_||___/ \\__| \__,_||_||_|(_)|___/|_| |_| for Spacecentricity v${VERSION}
BANNER
}

print_help() {
    print_banner
    cat <<EOF

Usage: $(basename "$0") [keymap_name] [options]

This POSIX-complaint script creates a symbolic link from your QMK
keymaps directory to the root of this keymap repository. It allows
QMK to use this keymap without copying files into the QMK tree.

This script prompts you to install the optional man pages for this
keymap’s helper scripts, and invokes install_man.sh if you confirm.

By default:
  - The keymap name is: spacecentricity
  - The QMK checkout is assumed to be at:
        \$HOME/qmk_firmware

You can override these defaults:

  Keymap name as an argument:
      $(basename "$0") my_keymap_name

  QMK root path (environment variable):
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

After installation, build your firmware with:
  qmk compile -kb inland/mk47 -km <keymap_name>
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

# Directory where this script lives
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
# The repo root is the parent directory of scripts/
REPO_ROOT=$(dirname "$SCRIPT_DIR")
MAN_SCRIPT="$SCRIPT_DIR/install_man.sh"

KEYMAP_NAME="${1:-spacecentricity}"
QMK_PATH="${QMK_PATH:-$HOME/qmk_firmware}" # Check if user has alternate QMK root
TARGET="$QMK_PATH/keyboards/inland/mk47/keymaps/$KEYMAP_NAME"

if [ -L "$TARGET" ]; then
    echo "Symlink already exists at $TARGET"
else
    ln -s "$REPO_ROOT" "$TARGET"
    echo "Symlink created:"
    echo "$TARGET -> $REPO_ROOT"
fi

if [ -f "$MAN_SCRIPT" ]; then
    if [ -t 0 ]; then
        printf '\n%s' "Install man pages for this project's scripts? [y/N] "
        read -r REPLY
        case "$REPLY" in
            [Yy]*)
                sh "$MAN_SCRIPT" --install --no-banner
                ;;
            *)
                echo "Skipping man page installation. Run 'scripts/install_man.sh --install' later if you change your mind."
                ;;
        esac
    else
        echo "Non-interactive shell detected — skipping man page prompt."
        echo "Run 'scripts/install_man.sh --install' manually if you want them."
    fi
fi
