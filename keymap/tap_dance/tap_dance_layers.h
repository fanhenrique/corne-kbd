#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    LAYER_INVERT,
    LAYER_MOVE,
} tap_dance_layer_action_t;


typedef struct {
    uint16_t keycode;
    uint8_t layer;

    bool hold;       // activate the layer by holding
    bool double_tap; // activate/deactivate with double tap

    tap_dance_layer_action_t action;

    bool holding;    // internal state
    
} tap_dance_layer_t;

void tap_dance_layer_finished(tap_dance_state_t *state, void *user_data);

void tap_dance_layer_reset( tap_dance_state_t *state, void *user_data);

extern tap_dance_layer_t tdl_base;
extern tap_dance_layer_t tdl_functions_numpad;
extern tap_dance_layer_t tdl_numbers_symbols;
extern tap_dance_layer_t tdl_navigate;
extern tap_dance_layer_t tdl_special;
extern tap_dance_layer_t tdl_mouse;
