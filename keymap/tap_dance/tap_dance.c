// Intenal imports
#include "tap_dance.h"

tap_dance_action_t tap_dance_actions[TD_COUNT] = {
    [TD_DQUO_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_DQUO, KC_QUOT),
    [TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    
    // Tap Dance Layer - TDL
    [TDL_FUNCTIONS_NUMPAD] = {
        .fn = {
            .on_each_tap = NULL,
            .on_dance_finished = tap_dance_layer_finished,
            .on_reset = tap_dance_layer_reset,
        }, .user_data = &tdl_functions_numpad,
    },
    [TDL_NUMBERS_SYMBOLS] = {
        .fn = {
            .on_each_tap = NULL,
            .on_dance_finished = tap_dance_layer_finished,
            .on_reset = tap_dance_layer_reset,
        }, .user_data = &tdl_numbers_symbols,
    },
    [TDL_NAVIGATE] = {
        .fn = {
            .on_each_tap = NULL,
            .on_dance_finished = tap_dance_layer_finished,
            .on_reset = tap_dance_layer_reset,
        }, .user_data = &tdl_navigate,
    },
    [TDL_SPECIAL] = {
        .fn = {
            .on_each_tap = NULL,
            .on_dance_finished = tap_dance_layer_finished,
            .on_reset = tap_dance_layer_reset,
        }, .user_data = &tdl_special,
    },
    [TDL_MOUSE] = {
        .fn = {
            .on_each_tap = NULL,
            .on_dance_finished = tap_dance_layer_finished,
            .on_reset = tap_dance_layer_reset,
        }, .user_data = &tdl_mouse,
    },
};