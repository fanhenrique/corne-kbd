#pragma once

#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_CCED = SAFE_RANGE,
    KC_ACUTE,
    KC_MICM,
    KC_MICU,
    KC_MICD,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record);