#!/bin/bash

VID="4653"
PID="0004"
INTERFACE="1"

LAYERS=(
    "TEXT"
    "I3"
    "I3_OPERATIONS"
    "NAVIGATE"
    "NUMBERS_SYMBOLS"
    "FUNCTIONS_NUMPAD"
    "SPECIAL"
    "MOUSE"
)

find_hidraw() {
    for device in /dev/hidraw*; do
        [ -e "$device" ] || continue

        path=$(readlink -f "/sys/class/hidraw/$(basename "$device")/device")

        # Verifica VID/PID
        [[ "$path" == *":${VID}:${PID}."* ]] || continue

        # Verifica interface USB
        [[ "$path" == *":1.${INTERFACE}/"* ]] || continue

        echo "$device"
        return 0
    done

    return 1
}

DEVICE=$(find_hidraw)

[ -n "$DEVICE" ] || exit 1

while true; do
    # Lê um report HID de 32 bytes
    data=$(dd if="$DEVICE" bs=32 count=1 2>/dev/null | od -An -tu1)

    # Garante que recebemos dados
    [ -n "$data" ] || continue

    # Byte 24 = posição 25 na saída do od
    # Byte 25 = posição 26
    bytes=($data)

    # Verifica o marcador 0x90 (144)
    [ "${bytes[24]}" = "144" ] || continue

    layer="${bytes[25]}"

    # Verifica se a camada existe
    [ -n "${LAYERS[$layer]}" ] || continue

    echo "${LAYERS[$layer]}"
done
