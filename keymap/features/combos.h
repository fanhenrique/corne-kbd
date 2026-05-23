#pragma once

#include QMK_KEYBOARD_H

enum combo_events {
    COMBO_SEMICOLON,

    COMBO_COUNT
};

extern combo_t key_combos[COMBO_COUNT];