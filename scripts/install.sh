#!/bin/sh
# Creates the symbolic link to the QMK path of the keymap

print_help() {
    cat <<EOF
 _           _        _ _       _
(_)         | |      | | |     | |
 _ _ __  ___| |_ __ _| | |  ___| |__
| | '_ \/ __| __/ _\` | | | / __| '_ \\
| | | | \__ \ || (_| | | |_\__ \ | | |
|_|_| |_|___/\__\__,_|_|_(_)___/_| |_|
Usage: $(basename "$0") [keymap_name] [options]

This script creates a symbolic link from your QMK keymaps directory
to the root of this keymap repository. It allows QMK to use this
keymap without copying files into the QMK tree.

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
  -h, --help    Show this help message and exit

Examples:
  $(basename "$0")
  $(basename "$0") my_keymap_name
  QMK_PATH=~/Projects/qmk_firmware $(basename "$0")

After installation, build your firmware with:
  qmk compile -kb inland/mk47 -km <keymap_name>
EOF
}

case "$1" in
    -h|--help)
        print_help
        exit 0
        ;;
esac

# Directory where this script lives
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

# The repo root is the parent directory of scripts/
REPO_ROOT=$(dirname "$SCRIPT_DIR")

KEYMAP_NAME="${1:-spacecentricity}"
QMK_PATH="${QMK_PATH:-$HOME/qmk_firmware}" # Check if user has alternate QMK root
TARGET="$QMK_PATH/keyboards/inland/mk47/keymaps/$KEYMAP_NAME"

if [ -L "$TARGET" ]; then
    echo "Symlink already exists at $TARGET"
    exit 0
fi

ln -s "$REPO_ROOT" "$TARGET"
echo "Symlink created:"
echo "$TARGET -> $REPO_ROOT"
