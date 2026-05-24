#include <stdio.h>

// Understanding Pointers - Basic Example

int main() {
    // Declare an integer variable
    int age = 25;
    
    // Declare a pointer to int
    int *ptr;
    
    // Initialize pointer with address of age
    ptr = &age;
    
    // Different ways to access
    printf("=== Pointer Basics ===\n");
    printf("Value of age: %d\n", age);
    printf("Address of age: %p\n", (void*)&age);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Dereferencing ptr: %d\n", *ptr);
    printf("\n");
    
    // Modifying through pointer
    printf("=== Modifying Through Pointer ===\n");
    printf("Before: age = %d\n", age);
    *ptr = 30;                      // Change age through pointer
    printf("After: age = %d\n", age);
    printf("\n");
    
    // Array and pointer relationship
    printf("=== Array and Pointer ===\n");
    int arr[5] = {10, 20, 30, 40, 50};
    int *arr_ptr = arr;             // arr decays to pointer
    
    printf("arr[0] = %d\n", arr[0]);
    printf("*arr = %d\n", *arr);
    printf("*(arr + 2) = %d\n", *(arr + 2)); // Pointer arithmetic
    printf("arr_ptr[1] = %d\n", arr_ptr[1]);
    printf("\n");
    
    // Pointer increment
    printf("=== Pointer Arithmetic ===\n");
    printf("arr_ptr points to: %d\n", *arr_ptr);
    arr_ptr++;
    printf("After arr_ptr++: %d\n", *arr_ptr);
    arr_ptr += 2;
    printf("After arr_ptr += 2: %d\n", *arr_ptr);
    
    return 0;
}
