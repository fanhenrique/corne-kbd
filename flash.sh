#!/bin/bash

set -e

# Enable verbose mode with -v or --verbose
VERBOSE=false

usage() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS]

Compile and flash QMK firmware to a connected RPI-RP2 device.

Options:
    -v, --verbose   Show command output during execution
    -h, --help      Show this help message and exit

Examples:
    $(basename "$0")
    $(basename "$0") --verbose
    $(basename "$0") --help
EOF
}

check_dependencies() {
    local dependencies=(
        qmk
        udisksctl
        lsblk
        awk
        grep
        cp
        sync
    )

    for command in "${dependencies[@]}"; do
        if ! command -v "$command" >/dev/null 2>&1; then
            printf "ERROR: Required command not found: %s\n" "$command" >&2
            exit 1
        fi
    done
}

while [[ $# -gt 0 ]]; do
    case "$1" in

        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            printf "Unknown parameter: %s\n" "$1"
            exit 1
            ;;
    esac
done

check_dependencies

# Helper function to optionally suppress output
run_cmd() {
    if $VERBOSE; then
        "$@"
    else
        "$@" > /dev/null
    fi
}

# Local keymap directory
KEYMAP_DIR="./keymap"

# QMK firmware directory
QMK_DIR="$HOME/qmk_firmware"

KEYBOARD="crkbd/rev4_1/standard"
KEYMAP="fanhenrique"

# RPI-RP2 mount point (udisks)
MOUNT_POINT="/media/$USER/RPI-RP2"

# Wait for RPI-RP2 to enter BOOTLOADER (UF2) mode
wait_for_bootloader() {
    printf "\n==> Waiting for RPI-RP2 to enter BOOTLOADER mode (press QK_BOOTLOADER or QK_BOOT)...\n"

    # Timeout: ~30s
    for i in {1..300}; do
        # Detect block device with label RPI-RP2
        DEVICE=$(lsblk -nr -o NAME,LABEL | awk '$2=="RPI-RP2" {print "/dev/"$1; exit}')
        [[ -n "$DEVICE" ]] && break
        sleep 0.1
    done

    # Abort if not detected
    if [[ -z "$DEVICE" ]]; then
        printf "\n==> ERROR: RPI-RP2 not detected. Press QK_BOOT on the master side.\n"
        exit 1
    fi

    printf "\n==> RPI-RP2 detected: %s\n" "$DEVICE"
}

# Wait until RPI-RP2 reboots after flashing
wait_for_reboot() {
    printf "\n==> Waiting for RPI-RP2 to reboot...\n"
    while lsblk -nr -o LABEL | grep -q "^RPI-RP2$"; do
        sleep 0.3
    done
    printf "\n==> RPI-RP2 has rebooted!\n"
}

# Copy custom keymap into QMK tree
printf "\n==> Copying keymap files...\n"
if ! cp -r "$KEYMAP_DIR"/. "$QMK_DIR/keyboards/crkbd/keymaps/$KEYMAP"; then
    printf "\n==> ERROR: Failed to copy keymap files.\n"
    exit 1
fi

# Compile firmware
printf "\n==> Compiling QMK firmware...\n\n"
if ! run_cmd qmk compile --keyboard "$KEYBOARD" --keymap "$KEYMAP"; then
    printf "\n==> ERROR: QMK compilation failed\n"
    exit 1
fi
printf "\n==> Compilation successful!\n"

wait_for_bootloader

# Mount RPI-RP2
printf "\n==> Mounting device...\n"
if ! run_cmd udisksctl mount -b "$DEVICE"; then
    printf "\n==> ERROR: Mount operation failed for device %s\n" "$DEVICE"
    exit 1
fi

while [ ! -d "$MOUNT_POINT" ]; do
    sleep 0.1
done

printf "\n==> Mounted at %s\n" "$MOUNT_POINT"

# Flash UF2 firmware
KB_SAFE="${KEYBOARD//\//_}"
UF2="$QMK_DIR/${KB_SAFE}_${KEYMAP}.uf2"

printf "\n==> Flashing firmware: %s\n" "$UF2"

if ! cp "$UF2" "$MOUNT_POINT/"; then
    printf "\n==> ERROR: Failed to copy firmware file %s\n" "$UF2"
    exit 1
fi

# Ensure data is fully written in RPI-RP2
sync

wait_for_reboot

printf "\n==> Flash completed. The device will reboot automatically.\n"