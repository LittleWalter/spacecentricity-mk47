# 🔧 Build Scripts/Tools for QMK

For convenience, this directory contains small POSIX-compliant helper scripts for installing, removing, and working with the symlink that connects this keymap repository to your local QMK firmware checkout.

These scripts are optional, but they make it easier to keep this firmware in its own repository while still using it with QMK.

> [!NOTE]
> `keymap_name` is optional and defaults to `spacecentricity`.

> [!TIP]
> The helper scripts are committed with executable permissions.
> If you run into permission issues, fix them with:
> `chmod +x scripts/*.sh`

## Table of Contents

- [`install.sh`](#install-sh)
- [`uninstall.sh`](#uninstall-sh)
- [`build.sh`](#build-sh)
  - [Options](#build-options)
  - [Example Runs](#example-runs)
- [Help](#help)
  - [Man Pages (`install_man.sh`)](#man-pages)
    - [Options](#man-page-options)
    - [Installing Man Pages](#installing-man-pages)
    - [Removing Man Pages](#removing-man-pages)
- [Custom QMK Path](#custom-qmk-path)
- [`license_headers.sh`](#license-headers-sh-add-remove-copyright-license-headers)

<a id="install-sh"></a>
## 📝 `install.sh`

Creates a symlink in your QMK keymaps directory pointing to the root of this repository.

Asks user to install the [optional man pages](#man-pages) for each of the scripts.

### Usage

```bash
cd ~/path/to/keymap/scripts
./install.sh [keymap_name]
```

<a id="uninstall-sh"></a>
## 🗑️ `uninstall.sh`

Removes the symlink created by `install.sh`.

Automatically removes the optionally installed [man pages](#man-pages) for the project’s scripts.

### Usage

```bash
cd ~/path/to/keymap/scripts
./uninstall.sh [keymap_name]
```

<a id="build-sh"></a>
## 🔨 `build.sh`

A unified convenience wrapper for building, cleaning, flashing, linting, and checking the status of this keymap inside your QMK firmware tree.

```bash
cd ~/path/to/keymap/scripts
./build.sh [keymap_name] [options]
```
> [!TIP]
> You can use the `build` wrapper in the project root without running `./scripts/build.sh` directly.
>
> This script should be able to handle 90%+ of `qmk` command scenarios.

<a id="build-options"></a>
### Options

| Flag                           | Description                                       |
|--------------------------------|---------------------------------------------------|
| -c, --clean, --clear           | Remove QMK build artifacts before building        |
| --clean-only, --clear-only     | Clean and exit without building                   |
| -C, --check                    | Run status check + strict lint in one pass        |
| -d, --console                  | Open the QMK HID debug console                    |
| -f, --flash                    | Build and flash the firmware                      |
| -h, --help                     | Show this help message and exit                   |
| -l, --lint                     | Lint the keymap before building                   |
| -S, --strict                   | Treat lint warnings as errors (requires `--lint)` |
| -s, --status                   | Show symlink/QMK status and exit                  |

### Example Runs

```bash
./build.sh                 # build w/ defaults
./build.sh my_keymap       # build w/ custom keymap name
./build.sh --clean-only    # remove cached build files
./build.sh --clean --flash # clean, build, and flash
./build.sh --check         # verify symlink and lint cleanliness together
./build.sh --status        # check symlink and QMK paths
./build.sh --console       # run the QMK HID debug console: hit the “debug key” on your keymap!
```

<a id="help"></a>
## ❓ Help

Display help messages with options `-h` and `--help`:

```bash
./install.sh -h
./uninstall.sh --help
./build.sh --help
./license_headers.sh --help
./install_man.sh --help
```

<a id="man-pages"></a>
### 📖 Man Pages (`install_man.sh`)

Install this project’s optional [manual pages](https://en.wikipedia.org/wiki/Man_page) — covering `install.sh`, `uninstall.sh`, `build.sh`, `license_headers.sh`, and `install_man.sh` — into your local man page directory, so they’re accessible via `man <script_name>.sh`.

Additionally, `spacecentricity.7` is installed to `~/.local/share/man/man7/` as an overview of the project’s scripts and development utilities.

<a id="man-page-options"></a>
#### Options

| Flag                             | Description                    |
|----------------------------------|--------------------------------|
| `-i`, `--install`                | Install man pages (default)    |
| `-r`, `--remove`, `--remove-all` | Remove installed man pages     |
| `-h`, `--help`                   | Show help message and exit     |

<a id="installing-man-pages"></a>
#### Installing Man Pages

```bash
cd ~/path/to/keymap/scripts
./install_man.sh
```

> [!NOTE] 
> Man pages are installed to `~/.local/share/man/man1` and `~/.local/share/man/man7`. If `man` can't find them after installation, add this to your shell configuration:
> `export MANPATH="$HOME/.local/share/man:$MANPATH"`
>
> These filenames are unlikely to conflict with existing man pages, but you can check beforehand with `man -w <script-name>.sh` to confirm nothing's already installed under that name.

#### Removing Man Pages

```bash
./install_man.sh --remove
```

#### Example Runs

```bash
man spacecentricity    # overview of build tools & friends
man build.sh           # how to use the main build script
man install.sh         # how to install spacecentricity
man uninstall.sh       # how to uninstall spacecentricity
man license_headers.sh # how to add/remove copyright & license headers
man install_man.sh     # how to install these handy man pages
```

<a id="custom-qmk-path"></a>
## 📁 Custom QMK Path

If your QMK checkout is not in `~/qmk_firmware`, set `QMK_PATH`:

```bash
QMK_PATH=/path/to/qmk_firmware ./install.sh
QMK_PATH=/path/to/qmk_firmware ./uninstall.sh
QMK_PATH=/path/to/qmk_firmware ./build.sh
```

Define `QMK_PATH` in your shell configuration if you want the path to persist.

For example, modify your Bash or Zsh configuration to include:
```bash
export QMK_PATH="$HOME/path/to/qmk_firmware"
```

<a id="license-headers-sh-add-remove-copyright-license-headers"></a>
## ⚖️ `license_headers.sh`: Add/Remove Copyright & License Headers

Adds or removes predefined license headers on each `.h` and `.c` file in `src/`, plus the root-level keymap.c` stub.

Edit the script directly to change the header content.

After adding headers to each source file, you can run `./build --lint` without warnings or errors.

```bash
# Invoke `license_headers.sh` from the project root

# Add missing license headers to all files in src/
./scripts/license_headers.sh

# Remove all headers from all files in src/
./scripts/license_headers.sh --remove-all
```

> [!TIP]
> To modify the copyright and license header, first remove the current headers with `./scripts/license_headers.sh --remove-all`, _then_ edit the header section within `./scripts/license_headers.sh`.
