# 🔧 Build Environment: Helper Scripts for QMK

For convenience, this directory contains small POSIX-compliant helper scripts for installing, removing, and working with the symlink that connects this keymap repository to your local QMK firmware checkout.

These scripts are optional, but they make it easier to keep this firmware in its own repository while still using it with QMK.[^keep-it-simple]

See `man spacecentricity` (once [man pages are installed](#man-pages)) for a full overview of how these scripts relate to one another.

> [!NOTE]
> These scripts assume you already have a working QMK firmware checkout. If you haven't set one up yet, see [QMK's official setup guide](https://docs.qmk.fm/#/newbs_getting_started).
>
> `keymap_name` is optional and defaults to `spacecentricity`.

> [!TIP]
> The helper scripts are committed with executable permissions.
> If you run into permission issues, fix them with:
> `chmod +x scripts/*.sh`

[^keep-it-simple]: The goal is to keep the whole build tooling lean — under 1k [SLOC](https://en.wikipedia.org/wiki/Source_lines_of_code) of shell.

## Table of Contents

- [`install.sh`](#install-sh)
  - [Usage](#install-sh-usage)
  - [Options](#install-sh-options)
- [`uninstall.sh`](#uninstall-sh)
  - [Usage](#uninstall-sh-usage)
  - [Options](#uninstall-sh-options)
- [`build.sh`](#build-sh)
  - [Usage](#build-sh-usage)
  - [Options](#build-sh-options)
  - [Example Runs](#build-sh-example-runs)
- [Help](#help)
  - [`install_man.sh` (Manual Pages)](#man-pages)
    - [Options](#man-page-options)
    - [Installing Man Pages](#man-pages-installing)
    - [Removing Man Pages](#man-pages-removing)
    - [Example Runs](#man-page-example-runs)
- [Environment Variables](#environment-variables)
  - [Custom QMK Path](#custom-qmk-path)
  - [Suppress ASCII Art Banners](#suppress-ascii-art-banners)
  - [MANPATH for Installed Man Pages](#manpath)
- [`license_headers.sh`](#license-headers-sh-add-remove-copyright-license-headers)
  - [Usage](#license-headers-sh-usage)
  - [Options](#license-headers-sh-options)
  - [Example Runs](#license-headers-sh-example-runs)

<a id="install-sh"></a>
## 📝 `install.sh`

Creates a symlink in your QMK keymaps directory pointing to the root of this repository.

Asks user to install the [optional man pages](#man-pages) for this project’s scripts.

<a id="install-sh-usage"></a>
### ℹ Usage

```bash
cd ~/path/to/keymap/scripts
./install.sh [keymap_name]
```

<a id="install-sh-options"></a>
### ⋮ Options

| Flag                                 | Description                              |
|--------------------------------------|------------------------------------------|
| `-h`, `--help`                       | Show the help message and exit           |
| `-n`, `--no-banner`, `--skip-banner` | Suppress the ASCII art banner on output  |

<a id="uninstall-sh"></a>
## 🗑️ `uninstall.sh`

Removes the symlink created by `install.sh`.

Automatically removes the [optionally man pages](#man-pages) for this project’s scripts.

<a id="uninstall-sh-usage"></a>
### ℹ Usage

```bash
cd ~/path/to/keymap/scripts
./uninstall.sh [keymap_name]
```

<a id="uninstall-sh-options"></a>
### ⋮ Options

| Flag                                 | Description                              |
|--------------------------------------|------------------------------------------|
| `-h`, `--help`                       | Show the help message and exit           |
| `-n`, `--no-banner`, `--skip-banner` | Suppress the ASCII art banner on output  |

<a id="build-sh"></a>
## 🔨 `build.sh`

A unified convenience wrapper for this keymap's QMK workflow. Handles building, cleaning, flashing, linting, debugging, and status checks.

<a id="build-sh-usage"></a>
### ℹ Usage

```bash
cd ~/path/to/keymap/scripts
./build.sh [keymap_name] [options]
```
> [!TIP]
> You can use the `build` wrapper in the project root without running `./scripts/build.sh` directly.
>
> This script should be able to handle 90%+ of `qmk` command scenarios.

<a id="build-sh-options"></a>
### ⋮ Options

| Flag                                 | Description                                              |
|--------------------------------------|----------------------------------------------------------|
| `-c`, `--clean`, `--clear`           | Remove QMK build artifacts before building               |
| `--clean-only`, `--clear-only`       | Clean and exit without building                          |
| `-C`, `--check`                      | Run status check + strict lint in one pass               |
| `-d`, `--console`                    | Open the QMK HID debug console                           |
| `-f`, `--flash`                      | Build and flash the firmware                             |
| `-h`, `--help`                       | Show the help message and exit                           |
| `-l`, `--lint`                       | Lint the keymap before building                          |
| `-n`, `--no-banner`, `--skip-banner` | Suppress the ASCII art banner on output                  |
| `-S`, `--strict`                     | Treat lint warnings as errors (requires `--lint`)        |
| `-s`, `--status`                     | Show symlink/QMK status and exit                         |
| `-v`, `--verbose`                    | Show full live qmk compile output instead of the spinner |
| `--verbose=N`                        | Show a scrolling N-line window of live output (falls back to full output if N exceeds terminal height) |

<a id="build-sh-example-runs"></a>
### ❯ Example Runs

```bash
build.sh                 # build w/ defaults
build.sh my_keymap       # build w/ custom keymap name
build.sh --clean-only    # remove cached build files
build.sh --clean --flash # clean, build, and flash
build.sh --check         # verify symlink and lint cleanliness together
build.sh --status        # check symlink and QMK paths
build.sh -d              # open the QMK HID debug console
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
### 📖 `install_man.sh` (Manual Pages)

Install this project's optional [manual pages](https://en.wikipedia.org/wiki/Man_page) — covering `install.sh`, `uninstall.sh`, `build.sh`, `license_headers.sh`, and `install_man.sh` — into your local man page directory, so they're accessible via `man <script_name>.sh`.

Additionally, `spacecentricity.7` is installed to `~/.local/share/man/man7/` as an overview of the project's scripts and development utilities.

<a id="man-page-options"></a>
#### ⋮ Options

| Flag                                 | Description                              |
|--------------------------------------|------------------------------------------|
| `-i`, `--install`                    | Install man pages (default)              |
| `-h`, `--help`                       | Show the help message and exit           |
| `-n`, `--no-banner`, `--skip-banner` | Suppress the ASCII art banner on output  |
| `-r`, `--remove`, `--remove-all`     | Remove installed man pages               |

<a id="man-pages-installing"></a>
#### ＋ Installing Man Pages

```bash
cd ~/path/to/keymap/scripts
./install_man.sh
```

> [!NOTE]
> Man pages are installed to `~/.local/share/man/man1` and `~/.local/share/man/man7`. If `man` can't find them after installation, see [MANPATH for Installed Man Pages](#manpath) below.
>
> These filenames are unlikely to conflict with existing man pages, but you can check beforehand with `man -w <script-name>.sh` to confirm.

<a id="man-pages-removing"></a>
#### − Removing Man Pages

```bash
./install_man.sh --remove
```

<a id="man-page-example-runs"></a>
#### ❯ Example Runs

```bash
man spacecentricity    # overview of build tools & friends
man build.sh           # how to use the main build script
man install.sh         # how to install spacecentricity's build environment
man uninstall.sh       # how to uninstall spacecentricity's build environment
man license_headers.sh # how to add/remove copyright & license headers
man install_man.sh     # how to install/uninstall these handy man pages
```

<a id="environment-variables"></a>
## 🌎 Environment Variables

Project-wide environment variables used across the shell scripts. Define these variables to override
default behavior in your shell configuration, e.g., [Bash](https://www.gnu.org/software/bash/) (`~/.bashrc`), [Zsh](https://www.zsh.org/) (`~/.zshrc` or `~/.zshenv`).

<a id="custom-qmk-path"></a>
### 📁 Custom QMK Path

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

<a id="suppress-ascii-art-banners"></a>
### 🏁 Suppress ASCII Art Banners

Are you tired of having fun? Skip the ASCII art banners output by the build scripts.

Add to your Bash or Zsh configuration:
```bash
# Set the variable to "false" in your shell config to always skip the top banner
export SPACECENTRICITY_BANNER=false
# Alternatively, use "0"
export SPACECENTRICITY_BANNER=0
```

For a one-off suppression instead of a persistent setting, use the `--no-banner` (or `-n`/`--skip-banner`) flag directly:
```bash
./build.sh --no-banner
```

<a id="manpath"></a>
### 📖 MANPATH for Installed Man Pages

If `man` can't find the installed man pages after running `install_man.sh`, add this to your shell configuration:

```bash
export MANPATH="$HOME/.local/share/man:$MANPATH"
```

<a id="license-headers-sh-add-remove-copyright-license-headers"></a>
## ⚖️ `license_headers.sh`: Add/Remove Copyright & License Headers

Adds or removes predefined license headers on each `.h` and `.c` file in `src/`, plus the root-level `keymap.c` stub.

Edit the script directly to change the header content.

After adding headers to each source file, you can run `./build --lint` without warnings or errors.

<a id="license-headers-sh-usage"></a>
### ℹ Usage

```bash
cd ~/path/to/keymap/scripts
./license_headers.sh [options]
```

<a id="license-headers-sh-options"></a>
### ⋮ Options

| Flag                                     | Description                                                  |
|------------------------------------------|--------------------------------------------------------------|
| `-a`, `--add`                            | Add the header to files that don't already have it (default) |
| `-h`, `--help`                           | Show the help message and exit                               |
| `-n`, `--no-banner`, `--skip-banner`     | Suppress the ASCII art banner on output                      |
| `-r`, `--remove`, `--remove-all`         | Remove the header from files where it exactly matches        |
| `-s`, `--stamp-version`, `--set-version` | Stamp `VERSION` into the header instead of using `config.h` data (also accepts `--stamp-version=VERSION`), where `VERSION` is a `MAJOR.MINOR.PATCH` string |

<a id="license-headers-sh-example-runs"></a>
### ❯ Example Runs

```bash
# Invoke `license_headers.sh` from the project root

# Add missing license headers to all files in src/
./scripts/license_headers.sh

# Remove all headers from all files in src/
./scripts/license_headers.sh --remove-all
```

> [!TIP]
> To modify the copyright and license header, first remove the current headers with `./scripts/license_headers.sh --remove-all`, _then_ edit the header section within `./scripts/license_headers.sh`.
