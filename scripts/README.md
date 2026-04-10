# 🔧 Keymap Symlink Management Scripts

For convenience, this directory contains small POSIX-compliant helper scripts for installing, removing, and working with the symlink that connects this keymap repository to your local QMK firmware checkout. These scripts are optional, but they make it easier to keep this keymap in its own repository while still using it with QMK.

> [!NOTE]
> `keymap_name` is optional and defaults to `spacecentricity`.

> [!TIP]
> The helper scripts are committed with executable permissions.  
> If you run into permission issues, fix them with:
> `chmod +x scripts/*.sh`

## 📝 `install.sh`

Creates a symlink in your QMK keymaps directory pointing to the root of this repository.

### Usage

```bash
cd ~/path/to/keymap/scripts
./install.sh [keymap_name]
```

## 🗑️ `uninstall.sh`

Removes the symlink created by `install.sh`.

### Usage

```bash
cd ~/path/to/keymap/scripts
./uninstall.sh [keymap_name]
```

## 🔨 `build.sh`

A unified convenience wrapper for building, cleaning, flashing, and checking the status of this keymap inside your QMK firmware tree.

```bash
cd ~/path/to/keymap/scripts
./build.sh [keymap_name] [options]
```
> [!TIP]
> You can use the `build` wrapper in the project root without running `./scripts/build.sh` directly.

### Options

| Flag | Description |
|------|-------------|
| `-c`, `--clean` | Remove QMK build artifacts before building |
| `--clean-only` | Clean and exit without building |
| `-f`, `--flash` | Flash the firmware after building |
| `-s`, `--status` | Show symlink and QMK status and exit |
| `-h`, `--help` | Show help message |

### Example Runs

```bash
./build.sh                 # build w/ defaults
./build.sh my_keymap       # build w/ custom keymap name
./build.sh --clean-only    # remove cached build files
./build.sh --clean --flash # clean, build, and flash
./build.sh --status        # check symlink and QMK paths
```

## ❓ Help

Display help messages with options `-h` and `--help`:

```bash
./install.sh -h
./uninstall.sh --help
./build.sh --help
```

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
