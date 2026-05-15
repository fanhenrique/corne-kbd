#pragma once

#include QMK_KEYBOARD_H

typedef struct {
    uint16_t keycode;
    uint8_t layer;
} tap_dance_layer_t;

void tap_dance_layer_finished(tap_dance_state_t *state, void *user_data);

void tap_dance_layer_reset( tap_dance_state_t *state, void *user_data);

extern tap_dance_layer_t td_lc_functions_numpad;

extern tap_dance_layer_t td_lc_numbers_symbols;