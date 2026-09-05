# utils.sh — shared helper functions for Spacecentricity's build scripts.
# Not meant to be executed directly; source this from other scripts:
#   . "$SCRIPT_DIR/utils.sh"

# get_version_part <MAJOR|MINOR|PATCH>
# Reads a single version component from config.h.
# Requires CONFIG_FILE to be set by the calling script.
get_version_part() {
    grep -o "SPACECENTRICITY_VERSION_$1 [0-9]*" "$CONFIG_FILE" 2>/dev/null | awk '{print $2}'
}

# get_version
# Prints the full "MAJOR.MINOR.PATCH" version string, or "unknown" if any
# part is missing or config.h can't be found.
get_version() {
    MAJOR=$(get_version_part MAJOR)
    MINOR=$(get_version_part MINOR)
    PATCH=$(get_version_part PATCH)

    if [ -n "$MAJOR" ] && [ -n "$MINOR" ] && [ -n "$PATCH" ]; then
        echo "${MAJOR}.${MINOR}.${PATCH}"
    else
        echo "unknown"
    fi
}
