#include <stdio.h>

// Function Pointers and Callbacks

// Basic functions
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

// Function that uses function pointer (callback)
void perform_operation(int x, int y, int (*operation)(int, int)) {
    int result = operation(x, y);
    printf("Result: %d\n", result);
}

// Array of function pointers
int main() {
    printf("=== Basic Function Pointer ===\n");
    
    // Declare function pointer
    int (*fptr)(int, int);
    
    // Point to add function
    fptr = add;
    printf("5 + 3 = %d\n", fptr(5, 3));
    
    // Point to subtract function
    fptr = subtract;
    printf("5 - 3 = %d\n", fptr(5, 3));
    
    printf("\n=== Array of Function Pointers ===\n");
    
    // Array of function pointers
    int (*operations[3])(int, int) = {add, subtract, multiply};
    
    printf("add(10, 5) = %d\n", operations[0](10, 5));
    printf("subtract(10, 5) = %d\n", operations[1](10, 5));
    printf("multiply(10, 5) = %d\n", operations[2](10, 5));
    
    printf("\n=== Function Pointers as Callbacks ===\n");
    
    perform_operation(20, 10, add);
    perform_operation(20, 10, subtract);
    perform_operation(20, 10, multiply);
    
    return 0;
}
