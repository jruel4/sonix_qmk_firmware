#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
USERSPACE_DIR="${SCRIPT_DIR}/../qmk-userspace"
KEYBOARD="keychron/k2/rgb/v2/ansi"
KEYMAP="${1:-dvorak_programmer_jruel4}"

echo "Building QMK firmware for ${KEYBOARD} with keymap ${KEYMAP}..."
make "${KEYBOARD}:${KEYMAP}"

CUSTOM_KEYMAPS_DIR="${SCRIPT_DIR}/keyboards/${KEYBOARD}/keymaps"
USERSPACE_KEYMAPS_DIR="${USERSPACE_DIR}/keyboards/${KEYBOARD}/keymaps"

echo "Copying custom keymaps to qmk-userspace..."
for keymap_dir in "${CUSTOM_KEYMAPS_DIR}"/*_jruel4; do
    keymap_name="$(basename "${keymap_dir}")"
    mkdir -p "${USERSPACE_KEYMAPS_DIR}/${keymap_name}"
    rsync -av "${keymap_dir}/" "${USERSPACE_KEYMAPS_DIR}/${keymap_name}/"
done
echo "Done."
