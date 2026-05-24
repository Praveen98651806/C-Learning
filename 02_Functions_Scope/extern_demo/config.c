#include "config.h"

// DEFINITIONS — actual memory allocated here (the whiteboard)
int   MAX_CONNECTIONS = 100;
float timeout         = 30.5f;

void update_config(void) {
    MAX_CONNECTIONS = 101;       // writes 101 onto the whiteboard
    timeout         = 60.0f;
}

void reset_config(void) {
    MAX_CONNECTIONS = 100;       // resets back to 100
    timeout         = 30.5f;
}
