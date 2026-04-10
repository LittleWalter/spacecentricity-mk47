#!/bin/sh
# Removes the symbolic link to the QMK path of the keymap

print_help() {
    cat <<EOF
             _           _        _ _       _
            (_)         | |      | | |     | |
 _   _ _ __  _ _ __  ___| |_ __ _| | |  ___| |__
| | | | '_ \| | '_ \/ __| __/ _\` | | | / __| '_ \\
| |_| | | | | | | | \__ \ || (_| | | |_\__ \ | | |
 \__,_|_| |_|_|_| |_|___/\__\__,_|_|_(_)___/_| |_|
Usage: $(basename "$0") [keymap_name] [options]

This script removes the symbolic link from your QMK keymaps directory
that was created by the install script. It does NOT delete any files
from this repository — only the symlink inside your QMK tree.

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
  -h, --help    Show this help message and exit

Examples:
  $(basename "$0")
  $(basename "$0") my_keymap_name
  QMK_PATH=~/Projects/qmk_firmware $(basename "$0")

After removal, the keymap will no longer appear in:
  keyboards/<keyboard>/<revision>/keymaps/
EOF
}

case "$1" in
    -h|--help)
        print_help
        exit 0
        ;;
esac

KEYMAP_NAME="${1:-spacecentricity}"
QMK_PATH="${QMK_PATH:-$HOME/qmk_firmware}" # Check if user has alternate QMK root
TARGET="$QMK_PATH/keyboards/inland/mk47/keymaps/$KEYMAP_NAME"

if [ -L "$TARGET" ]; then
    rm "$TARGET"
    echo "Symlink removed: $TARGET"
else
    echo "No symlink found at $TARGET"
fi
