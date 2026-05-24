#include <stdio.h>
#include "config.h"

void network_read(void);  // tell main.c that network_read exists

int main() {

    // ── BEFORE calling update_config() ────────────────────────
    printf("===== BEFORE update_config() =====\n");
    printf("  [main.c]     MAX_CONNECTIONS = %d\n", MAX_CONNECTIONS);
    printf("  [main.c]     timeout         = %.1f\n", timeout);
    network_read();   // network.c also reads — sees same values

    // ── CALL update_config() ──────────────────────────────────
    printf("\n  >>> update_config() called <<<\n\n");
    update_config();  // writes 101 and 60.0 onto the whiteboard

    // ── AFTER calling update_config() ─────────────────────────
    printf("===== AFTER update_config() =====\n");
    printf("  [main.c]     MAX_CONNECTIONS = %d\n", MAX_CONNECTIONS);
    printf("  [main.c]     timeout         = %.1f\n", timeout);
    network_read();   // network.c also reads — sees updated values

    // ── CALL reset_config() ───────────────────────────────────
    printf("\n  >>> reset_config() called <<<\n\n");
    reset_config();   // writes 100 and 30.5 back

    // ── AFTER reset_config() ──────────────────────────────────
    printf("===== AFTER reset_config() =====\n");
    printf("  [main.c]     MAX_CONNECTIONS = %d\n", MAX_CONNECTIONS);
    printf("  [main.c]     timeout         = %.1f\n", timeout);
    network_read();   // back to original

    return 0;
}
