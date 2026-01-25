#!/bin/bash

set -e

KEYMAP_DIR="./keymap"
QMK_DIR="$HOME/qmk_firmware"
KEYBOARD="crkbd/rev4_1/standard"
KEYMAP="fanhenrique"

MOUNT_BASE="/media/$USER"
MOUNT_POINT="$MOUNT_BASE/rpi-rp2"


wait_for_bootloader() {
    echo "==> Waiting for RP2040 (RPI-RP2) BOOTLOADER mode (press QK_BOOTLOADER or QK_BOOT)..."

    while true; do
        DEVICE=$(lsblk -o NAME,SIZE,TRAN,MODEL -nr | awk '$2=="128M" && $3=="usb" && $4=="RP2" {print "/dev/"$1"1"}')
        echo "$DEVICE"
        [[ -n "$DEVICE" ]] && break
        sleep 0.5
    done
    echo "RP2040 detected in BOOTLOADER mode: $DEVICE"
}

wait_for_reboot() {
    echo "==> Waiting for RP2040 to reboot..."

    while true; do
        if ! lsblk -o LABEL -nr | grep -q "RPI-RP2"; then
            break
        fi
        sleep 0.3
    done

    echo "RP2040 reboot"
}


echo "==> Copying keymap files..."
cp -r "$KEYMAP_DIR"/* "$QMK_DIR/keyboards/crkbd/keymaps/$KEYMAP"

echo "==> Compiling QMK firmware..."
if ! qmk compile --keyboard "$KEYBOARD" --keymap "$KEYMAP" > /dev/null; then
    echo "ERROR: QMK compilation failed"
    exit 1
fi

wait_for_bootloader

# echo "==> Flashing QMK firmware..."
# if ! qmk flash --keyboard "$KEYBOARD" --keymap "$KEYMAP" > /dev/null; then
#     echo "ERROR: QMK flashing failed"
#     exit 1
# fi

echo "==> Creating mount point..."
sudo mkdir -p "$MOUNT_POINT"


echo "==> Mounting device..."
sudo mount -o uid=$(id -u),gid=$(id -g) "$DEVICE" "$MOUNT_POINT"


KB_SAFE="${KEYBOARD//\//_}"
UF2="$QMK_DIR/${KB_SAFE}_${KEYMAP}.uf2"
echo "==> Flashing firmware: $UF2"
cp "$UF2" "$MOUNT_POINT/"

wait_for_reboot

# echo "==> Unmounting device..."
# sudo umount "$MOUNT_POINT"

echo "Flash completed (device will reboot automatically)"