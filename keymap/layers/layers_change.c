#include "layers.h"
#include "layers_change.h"

void tap_dance_layer_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_layer_t *config = (tap_dance_layer_t *)user_data;

    if (state->count == 1) {

        if (state->pressed) {
            layer_on(config->layer);
        } else {
            tap_code16(config->keycode);
        }

    } else if (state->count == 2) {
        layer_invert(config->layer);
    }
}

void tap_dance_layer_reset( tap_dance_state_t *state, void *user_data) {
    tap_dance_layer_t *config = (tap_dance_layer_t *)user_data;

    if (state->count == 1 && state->pressed) {
        layer_off(config->layer);
    }
}

tap_dance_layer_t td_lc_functions_numpad = {
    .keycode = KC_Z,
    .layer = FUNCTIONS_NUMPAD,
};

tap_dance_layer_t td_lc_numbers_symbols = {
    .keycode = KC_NO,
    .layer = NUMBERS_SYMBOLS,
};