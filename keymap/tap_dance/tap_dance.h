#pragma once

#include QMK_KEYBOARD_H

// Internal imports
#include "tap_dance_layers.h"

enum tap_dance_events {
    
    // Simple tap dance
    TD_DQUO_QUOT,
    TD_SLSH_QUES,
    TD_LSFT_CAPS,
    
    // Tap Dance Layer - TDL
    TDL_FUNCTIONS_NUMPAD,
    TDL_NUMBERS_SYMBOLS,
    TDL_NAVIGATE,

    // Tap dance counter
    TD_COUNT
};

extern tap_dance_action_t tap_dance_actions[TD_COUNT];
