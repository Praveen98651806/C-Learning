#include <stdio.h>

// ── static local variable demo ────────────────────────────────────────────────
//
//  SCOPE    = block only  (only visible inside the function)
//  LIFETIME = entire program (value survives between calls)
//  LINKAGE  = none
//  MEMORY   = Data/BSS segment (NOT stack)

void counter() {
    static int count = 0;   // initialized ONCE at program start
                            // lives in DATA segment — never destroyed
    count++;
    printf("  counter() called → count = %d\n", count);
}

void auto_counter() {
    int count = 0;          // initialized EVERY call
                            // lives on STACK — destroyed on return
    count++;
    printf("  auto_counter() called → count = %d\n", count);
}

// ── static local to track state ───────────────────────────────────────────────
void traffic_light() {
    static int state = 0;   // 0=RED, 1=GREEN, 2=YELLOW
    const char *colors[] = { "RED", "GREEN", "YELLOW" };

    printf("  traffic_light() → %s\n", colors[state]);

    state = (state + 1) % 3;    // advance to next state
                                // state persists for next call
}

// ── static local — scope proof ────────────────────────────────────────────────
void scope_proof() {
    static int x = 100;
    x += 10;
    printf("  inside scope_proof()  → x = %d\n", x);
    // x is accessible ONLY here — not in main, not anywhere else
}

int main() {

    // ── TEST 1: static vs auto ─────────────────────────────────
    printf("===== TEST 1: static local vs auto local =====\n");
    printf("\n  Calling counter() 5 times (static int count):\n");
    counter();   // count = 1
    counter();   // count = 2
    counter();   // count = 3
    counter();   // count = 4
    counter();   // count = 5

    printf("\n  Calling auto_counter() 5 times (auto int count):\n");
    auto_counter();  // always 1
    auto_counter();  // always 1
    auto_counter();  // always 1
    auto_counter();  // always 1
    auto_counter();  // always 1

    // ── TEST 2: static local for state machine ─────────────────
    printf("\n===== TEST 2: traffic light state (static local) =====\n");
    traffic_light();   // RED
    traffic_light();   // GREEN
    traffic_light();   // YELLOW
    traffic_light();   // RED again (wraps around)
    traffic_light();   // GREEN

    // ── TEST 3: scope proof ────────────────────────────────────
    printf("\n===== TEST 3: scope — x is hidden from main() =====\n");
    scope_proof();     // x = 110
    scope_proof();     // x = 120
    scope_proof();     // x = 130

    // printf("%d", x);  // ← COMPILE ERROR if uncommented
    //                       x is NOT visible here
    printf("  main() cannot see x — scope is block-only\n");

    return 0;
}
