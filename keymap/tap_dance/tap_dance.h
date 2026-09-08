#pragma once

#include QMK_KEYBOARD_H

// Internal imports
#include "tap_dance_layers.h"

enum tap_dance_events {
    
    // Tap Dance Key - TDK
    TDK_DQUO_QUOT,
    TDK_SLSH_QUES,
    TDK_LSFT_CAPS,
    
    // Tap Dance Layer - TDL
    TDL_TEXT,
    TDL_FUNCTIONS_NUMPAD,
    TDL_NUMBERS_SYMBOLS,
    TDL_NAVIGATE,
    TDL_SPECIAL,
    TDL_MOUSE,

    // Tap dance counter
    TD_COUNT
};

extern tap_dance_action_t tap_dance_actions[TD_COUNT];
