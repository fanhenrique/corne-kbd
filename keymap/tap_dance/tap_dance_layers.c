// Internal imports
#include "../layers.h"
#include "tap_dance_layers.h"

void tap_dance_layer_finished(tap_dance_state_t *state, void *user_data) {

    tap_dance_layer_t *config = (tap_dance_layer_t *) user_data;

    config->holding = false;

    // Single tap / Hold
    if (state->count == 1) {
        // Hold
        if (state->pressed) {
            if (config->hold) {
                layer_on(config->layer);
                config->holding = true;
            }
        // Tap
        } else {
            if (config->keycode != KC_NO) {
                tap_code16(config->keycode);
            }
        }
    }
    // Double Tap
    else if (state->count == 2) {
        if (config->double_tap) {
            layer_invert(config->layer);
        }
    }
}

void tap_dance_layer_reset(tap_dance_state_t *state, void *user_data) {
    
    tap_dance_layer_t *config = (tap_dance_layer_t *) user_data;

    if (config->holding) {
        layer_off(config->layer);
        config->holding = false;
    }
}

tap_dance_layer_t tdl_functions_numpad = {
    .keycode = KC_CIRC,
    .layer = FUNCTIONS_NUMPAD,
    .hold = false,
    .double_tap = true,
};

tap_dance_layer_t tdl_numbers_symbols = {
    .keycode = KC_NO,
    .layer = NUMBERS_SYMBOLS,
    .hold = true,
    .double_tap = true,
};

tap_dance_layer_t tdl_navigate = {
    .keycode = KC_NO,
    .layer = NAVIGATE,
    .hold = true,
    .double_tap = true,
};

tap_dance_layer_t tdl_special = {
    .keycode = KC_LALT,
    .layer = SPECIAL,
    .hold = false,
    .double_tap = true,
};

tap_dance_layer_t tdl_mouse = {
    .keycode = KC_GRV,
    .layer = MOUSE,
    .hold = false,
    .double_tap = true,
};
