#!/bin/sh
# install_man.sh — installs or removes this project's man pages from
# docs/man into the user's local man page directory.

print_help() {
    cat <<'ASCII_ART'
 _           _        _ _                               _
(_)         | |      | | |                             | |
 _ _ __  ___| |_ __ _| | |  _ __ ___   __ _ _ __    ___| |__ 
| | '_ \/ __| __/ _` | | | | '_ ` _ \ / _` | '_ \  / __| '_ \
| | | | \__ \ || (_| | | | | | | | | | (_| | | | |_\__ \ | | |
|_|_| |_|___/\__\__,_|_|_| |_| |_| |_|\__,_|_| |_(_)___/_| |_|
                       ______
                      |______|

ASCII_ART

    cat <<EOF
Usage: $(basename "$0") [options]

Installs (or removes) the man pages in docs/man into your local man
page directory, so they're accessible via 'man <script-name>.sh'.

Options:
  -i, --install   Install man pages (default)
  -r, --remove    Remove previously installed man pages
  -h, --help      Show this help message and exit

Examples:
  $(basename "$0")           # Install man pages
  $(basename "$0") --install # Same as above, explicit
  $(basename "$0") --remove  # Remove installed man pages

Tips:
  Before running this script, check man page namespace conflicts:
    man -w <script-name>.sh
  After installing man pages:
    man build.sh
    man install.sh
    man uninstall.sh
    man license_headers.sh
EOF
}

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJECT_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
MAN_SRC_DIR="$PROJECT_ROOT/docs/man"
MAN_DEST_DIR="$HOME/.local/share/man/man1"

MODE="install"
for arg in "$@"; do
    case "$arg" in
        -h|--help)
            print_help
            exit 0
            ;;
        -i|--install)
            MODE="install"
            ;;
        -r|--remove)
            MODE="remove"
            ;;
    esac
done

if [ ! -d "$MAN_SRC_DIR" ]; then
    echo "❌ Man page source directory not found: $MAN_SRC_DIR"
    exit 1
fi

if [ "$MODE" = "install" ]; then
    mkdir -p "$MAN_DEST_DIR"

    for page in "$MAN_SRC_DIR"/*.1; do
        [ -e "$page" ] || continue
        cp "$page" "$MAN_DEST_DIR/"
        echo "✅ Installed: $(basename "$page")"
    done

    if ! man -w "$(basename "$(ls "$MAN_SRC_DIR"/*.1 | head -n 1)" .1)" >/dev/null 2>&1; then
        echo
        echo "⚠️  Man pages were copied, but 'man' may not find them yet."
        echo "   Your MANPATH may not include:"
        echo "     $MAN_DEST_DIR"
        echo "   Add this to your shell configuration if needed:"
        echo "     export MANPATH=\"\$HOME/.local/share/man:\$MANPATH\""
    fi
else
    for page in "$MAN_SRC_DIR"/*.1; do
        [ -e "$page" ] || continue
        target="$MAN_DEST_DIR/$(basename "$page")"
        if [ -f "$target" ]; then
            rm "$target"
            echo "🗑️  Removed: $(basename "$page")"
        fi
    done
fi
