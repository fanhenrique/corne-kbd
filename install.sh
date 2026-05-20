#!/bin/bash

set -e

printf "\n==> Updating system...\n"
sudo apt update

printf "\n==> Installing dependencies...\n"
sudo apt install -y \
    udisks2

# gcc-arm-none-eabi

printf "\n==> Installing QMK...\n"
curl -fsSL https://install.qmk.fm | sh

# ensure PATH
if ! grep -q 'export PATH="$HOME/.local/bin:$PATH"' ~/.bashrc; then
    echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc
fi

printf "\n==> QMK Setup...\n"

cd "$HOME"

if [ ! -d "$HOME/qmk_firmware" ]; then
    qmk setup -y
else
    printf "QMK Firmware already exists, skipping clone.\n"
fi

printf "\n==> Testing installation...\n"
qmk doctor

printf "\n==> Installation completed!\n"
printf "IMPORTANT: Restart your session (logout/login) before using QMK.\n"
