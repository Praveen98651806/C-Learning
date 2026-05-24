#include <stdio.h>
#include "config.h"

void network_read(void) {
    // network.c reads the SAME whiteboard (no copy of its own)
    printf("  [network.c]  MAX_CONNECTIONS = %d\n", MAX_CONNECTIONS);
    printf("  [network.c]  timeout         = %.1f\n", timeout);
}
