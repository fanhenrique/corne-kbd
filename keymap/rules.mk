RAW_ENABLE = yes

COMBO_ENABLE = yes

TAP_DANCE_ENABLE = yes

# CUT, PAST, UNDO ...
EXTRAKEY_ENABLE = yes

MOUSEKEY = yes

SRC += \
tap_dance/tap_dance.c \
tap_dance/tap_dance_layers.c \
features/combos.c \
features/custom.c
