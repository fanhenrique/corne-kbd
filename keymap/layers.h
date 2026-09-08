#ifndef LAYER_H
#define LAYER_H

#define LAYER_LIST(X) \
    X(BASE) \
    X(OS) \
    X(OPERATIONS) \
    X(NAVIGATE) \
    X(NUMBERS_SYMBOLS) \
    X(FUNCTIONS_NUMPAD) \
    X(SPECIAL) \
    X(MOUSE)

#define DEFINE_LAYER(name) name,

enum {
    LAYER_LIST(DEFINE_LAYER)
};

#undef DEFINE_LAYER

#endif