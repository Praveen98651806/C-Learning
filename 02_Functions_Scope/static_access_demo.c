#include <stdio.h>

// ─────────────────────────────────────────────────────────────
// Q1: Can func2() access static int count from func1()?
//     Answer: NO directly. But YES via pointer.
// ─────────────────────────────────────────────────────────────

// APPROACH 1 — func1() returns a pointer to its static variable
int* func1_get_count() {
    static int count = 10;       // lives in Data segment
    return &count;               // share the address
}

void func2_via_pointer() {
    int *ptr = func1_get_count();        // get the address of count

    printf("func2 reads  count = %d\n", *ptr);   // read it

    // Q2: change count from func2 — will it reflect everywhere?
    *ptr = 200;
    printf("func2 writes count = %d\n", *ptr);   // now 200
}

// ─────────────────────────────────────────────────────────────
// APPROACH 2 — func1() takes a pointer and writes into it
// ─────────────────────────────────────────────────────────────
void func1_export(int **out) {
    static int count = 10;
    *out = &count;               // give caller direct access
}

// ─────────────────────────────────────────────────────────────
// PROOF: After func2 changes count to 200,
//        func1 also sees 200 (same memory address)
// ─────────────────────────────────────────────────────────────
void func1_print() {
    // same static count — func1 reads its own variable
    int *ptr = func1_get_count();
    printf("func1 reads  count = %d\n", *ptr);
}

int main() {

    printf("===== Q1: Can func2 access func1's static var? =====\n");
    printf("  Direct access → NOT possible (compile error)\n");
    printf("  Via pointer   → YES possible\n\n");

    printf("===== Q2: Does change in func2 reflect everywhere? =====\n\n");

    printf("BEFORE func2 changes it:\n");
    func1_print();                  // func1 reads  count = 10

    func2_via_pointer();            // func2 reads 10, writes 200

    printf("\nAFTER func2 changed it to 200:\n");
    func1_print();                  // func1 reads  count = 200 ✅

    printf("\nConclusion:\n");
    printf("  count lives in Data segment (ONE memory location)\n");
    printf("  func2 changed the actual memory → func1 sees 200\n");
    printf("  The change is permanent for the entire program\n");

    return 0;
}
