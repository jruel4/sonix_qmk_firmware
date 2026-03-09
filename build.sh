#!/usr/bin/env bash
set -euo pipefail

KEYBOARD="keychron/k2/rgb/v2/ansi"
KEYMAP="dvorak_programmer_jruel4"

echo "Building QMK firmware for ${KEYBOARD} with keymap ${KEYMAP}..."
make "${KEYBOARD}:${KEYMAP}"
