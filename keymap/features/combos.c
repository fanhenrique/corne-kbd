// Internal imports
#include "combos.h"

const uint16_t PROGMEM semicolon_combo[] = { 
    KC_COMM, 
    KC_DOT, 
    COMBO_END 
};

combo_t key_combos[] = {
    [COMBO_SEMICOLON] = COMBO(semicolon_combo, KC_SCLN),
};