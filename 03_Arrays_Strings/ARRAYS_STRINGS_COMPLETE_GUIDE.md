# 📚 Complete Guide: Arrays & Strings in C

> **From Beginner to Interview-Ready** — Covers ALL concepts, edge cases, and interview questions

---

## 📋 Table of Contents

1. [Arrays - Fundamentals](#1-arrays---fundamentals)
2. [Arrays - Memory Layout](#2-arrays---memory-layout)
3. [2D & Multi-dimensional Arrays](#3-2d--multi-dimensional-arrays)
4. [Arrays & Pointers Relationship](#4-arrays--pointers-relationship)
5. [Passing Arrays to Functions](#5-passing-arrays-to-functions)
6. [Strings in C](#6-strings-in-c)
7. [String Library Functions](#7-string-library-functions)
8. [String Manipulation Techniques](#8-string-manipulation-techniques)
9. [Common Pitfalls & Edge Cases](#9-common-pitfalls--edge-cases)
10. [Interview Questions - Theory](#10-interview-questions---theory)
11. [Interview Questions - Coding](#11-interview-questions---coding)
12. [Tricky Interview Questions](#12-tricky-interview-questions)

---

# 1. Arrays - Fundamentals

## What is an Array?
An array is a **contiguous block of memory** storing elements of the **same data type**.

```
Memory Layout of int arr[5] = {10, 20, 30, 40, 50};

Address:    1000    1004    1008    1012    1016
          +-------+-------+-------+-------+-------+
Value:    |  10   |  20   |  30   |  40   |  50   |
          +-------+-------+-------+-------+-------+
Index:       [0]     [1]     [2]     [3]     [4]
```

## Declaration & Initialization

### Method 1: Declaration then Initialization
```c
int arr[5];           // Declaration (contains garbage values!)
arr[0] = 10;          // Individual assignment
arr[1] = 20;
```

### Method 2: Declaration with Initialization
```c
int arr[5] = {10, 20, 30, 40, 50};    // Full initialization
int arr[5] = {10, 20};                 // Partial: {10, 20, 0, 0, 0}
int arr[5] = {0};                      // All zeros: {0, 0, 0, 0, 0}
int arr[] = {10, 20, 30};              // Size inferred: 3 elements
```

### Method 3: Designated Initializers (C99)
```c
int arr[5] = {[2] = 100, [4] = 200};   // {0, 0, 100, 0, 200}
int arr[5] = {[1 ... 3] = 5};          // GCC extension: {0, 5, 5, 5, 0}
```

## ⚠️ CRITICAL: Uninitialized Arrays

```c
// LOCAL arrays have GARBAGE values
void foo() {
    int arr[5];        // Contains random garbage!
    printf("%d", arr[0]);  // Undefined behavior
}

// GLOBAL/STATIC arrays are initialized to 0
int global_arr[5];     // All zeros

void bar() {
    static int arr[5]; // All zeros
}
```

## Array Size Calculation

```c
int arr[10];
size_t size = sizeof(arr) / sizeof(arr[0]);  // = 10

// IMPORTANT: This only works in the SAME scope as declaration
// After passing to function, array decays to pointer!
```

## Array Bounds - NO CHECKING!

```c
int arr[5] = {1, 2, 3, 4, 5};

// C does NOT check bounds - these compile but are DANGEROUS:
arr[5] = 100;    // Buffer overflow! Writing beyond array
arr[-1] = 50;    // Negative index! Undefined behavior
arr[100] = 1;    // Far out of bounds - may crash or corrupt memory

// This is a MAJOR source of security vulnerabilities!
```

---

# 2. Arrays - Memory Layout

## Contiguous Memory Allocation

```c
int arr[4] = {10, 20, 30, 40};

printf("Address of arr[0]: %p\n", &arr[0]);  // e.g., 0x1000
printf("Address of arr[1]: %p\n", &arr[1]);  // 0x1004 (1000 + 4)
printf("Address of arr[2]: %p\n", &arr[2]);  // 0x1008 (1004 + 4)
printf("Address of arr[3]: %p\n", &arr[3]);  // 0x100C (1008 + 4)

// Formula: &arr[i] = &arr[0] + i * sizeof(element)
```

## Stack vs Heap Arrays

```c
// STACK allocation (automatic)
void stack_array() {
    int arr[100];      // Allocated on stack
    // Fast allocation
    // Limited size (stack is ~1-8 MB typically)
    // Automatically freed when function returns
}

// HEAP allocation (dynamic) - covered in Phase 5
void heap_array() {
    int *arr = malloc(100 * sizeof(int));  // On heap
    // Slower allocation
    // Much larger sizes possible
    // Must manually free()
    free(arr);
}
```

## Variable Length Arrays (VLAs) - C99

```c
void vla_example(int n) {
    int arr[n];        // Size determined at runtime!
    
    // VLA limitations:
    // - Cannot be initialized
    // - Cannot be static or global
    // - Size must be > 0
    // - Some compilers don't support (MSVC)
}

// Safer alternative: alloca() or malloc()
```

---

# 3. 2D & Multi-dimensional Arrays

## 2D Array Declaration

```c
int matrix[3][4];  // 3 rows, 4 columns

// Visual representation:
//        Col 0   Col 1   Col 2   Col 3
// Row 0:  [0][0]  [0][1]  [0][2]  [0][3]
// Row 1:  [1][0]  [1][1]  [1][2]  [1][3]
// Row 2:  [2][0]  [2][1]  [2][2]  [2][3]
```

## 2D Array Initialization

```c
// Method 1: Nested braces (recommended)
int matrix[2][3] = {
    {1, 2, 3},     // Row 0
    {4, 5, 6}      // Row 1
};

// Method 2: Flat initialization (not recommended)
int matrix[2][3] = {1, 2, 3, 4, 5, 6};  // Same result

// Method 3: Partial initialization
int matrix[2][3] = {
    {1},           // {1, 0, 0}
    {4, 5}         // {4, 5, 0}
};

// Method 4: All zeros
int matrix[2][3] = {0};
```

## Row-Major Memory Layout (CRITICAL for Interviews!)

```c
int matrix[2][3] = {{1,2,3}, {4,5,6}};

// Memory layout is ROW-MAJOR in C:
// Address: 1000  1004  1008  1012  1016  1020
// Value:   [1]   [2]   [3]   [4]   [5]   [6]
//          ----Row 0----   ----Row 1----

// This means:
// matrix[0][0] is at address base
// matrix[0][1] is at address base + 4
// matrix[1][0] is at address base + 12 (not base + 4!)

// Formula: Address of matrix[i][j] = base + (i * num_cols + j) * sizeof(element)
```

## Cache Performance (Interview Topic!)

```c
// GOOD: Row-wise traversal (cache-friendly)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = value;  // Sequential memory access
    }
}

// BAD: Column-wise traversal (cache-unfriendly)
for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
        matrix[i][j] = value;  // Jumping around in memory
    }
}
// The "bad" version can be 10-100x slower for large arrays!
```

## 3D and Higher Dimensional Arrays

```c
int cube[2][3][4];  // 2 layers, 3 rows, 4 columns

// Initialization
int cube[2][2][2] = {
    {{1, 2}, {3, 4}},     // Layer 0
    {{5, 6}, {7, 8}}      // Layer 1
};

// Memory: Still contiguous, row-major extended
// [1][2][3][4][5][6][7][8]
```

---

# 4. Arrays & Pointers Relationship

## Array Decay (MUST KNOW for Interviews!)

```c
int arr[5] = {10, 20, 30, 40, 50};

// Array name "decays" to pointer to first element
printf("%p\n", arr);      // Address of arr[0]
printf("%p\n", &arr[0]);  // Same address

// BUT they are NOT the same type!
printf("%zu\n", sizeof(arr));      // 20 (5 * 4 bytes)
printf("%zu\n", sizeof(&arr[0]));  // 8 (pointer size on 64-bit)
```

## Array Indexing is Pointer Arithmetic!

```c
int arr[5] = {10, 20, 30, 40, 50};

// These are ALL equivalent:
arr[3]      // Traditional indexing
*(arr + 3)  // Pointer arithmetic
*(3 + arr)  // Addition is commutative
3[arr]      // Yes, this works! (interview trick question)

// Why 3[arr] works:
// arr[3] = *(arr + 3) = *(3 + arr) = 3[arr]
```

## Array of Pointers vs Pointer to Array

```c
// Array of 5 pointers to int
int *arr[5];
// Each element is a pointer: arr[0], arr[1], etc. are int*

// Pointer to an array of 5 ints
int (*ptr)[5];
// ptr points to the entire array as a unit

// Example:
int data[5] = {1, 2, 3, 4, 5};
int (*p)[5] = &data;      // p points to the whole array
printf("%d\n", (*p)[2]);  // Access element: 3
```

## Difference: &arr vs arr

```c
int arr[5];

// arr decays to: int* (pointer to first element)
// &arr is: int (*)[5] (pointer to entire array)

// Same address, DIFFERENT types and arithmetic:
int *p1 = arr;
int (*p2)[5] = &arr;

printf("%p %p\n", p1, p2);      // Same address
printf("%p %p\n", p1+1, p2+1);  // DIFFERENT!
// p1+1: moves 4 bytes (one int)
// p2+1: moves 20 bytes (entire array of 5 ints)
```

---

# 5. Passing Arrays to Functions

## Arrays Always Pass as Pointers!

```c
// All three declarations are EQUIVALENT for parameters:
void func1(int arr[100]);   // Looks like array, but it's a pointer!
void func2(int arr[]);      // Same - size is ignored
void func3(int *arr);       // Explicit pointer - most honest

// Inside all three, sizeof(arr) = sizeof(int*) = 8 bytes
```

## You Must Pass Size Separately!

```c
// WRONG - size info is lost
void print_array(int arr[]) {
    int size = sizeof(arr) / sizeof(arr[0]);  // WRONG! Always gives pointer size
}

// CORRECT - pass size explicitly
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    print_array(arr, 5);  // Or use sizeof(arr)/sizeof(arr[0]) here
}
```

## Passing 2D Arrays

```c
// Method 1: Fixed column size (most common)
void print_matrix(int matrix[][4], int rows) {
    // Column size MUST be specified
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", matrix[i][j]);
        }
    }
}

// Method 2: Pointer to array
void print_matrix2(int (*matrix)[4], int rows) {
    // Same as above, more explicit
}

// Method 3: VLA (C99) - most flexible
void print_matrix3(int rows, int cols, int matrix[rows][cols]) {
    // Both dimensions can be variable
    // NOTE: rows and cols must come BEFORE matrix in parameters
}

// Method 4: Flatten to 1D pointer
void print_matrix4(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);  // Manual indexing
        }
    }
}
```

## Returning Arrays from Functions

```c
// WRONG - returning local array (dangling pointer!)
int* get_array() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // WARNING: arr will be destroyed!
}

// Option 1: Static array (not thread-safe)
int* get_array_static() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // OK, but all calls share same memory
}

// Option 2: Caller provides buffer (recommended)
void fill_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

// Option 3: Dynamic allocation (caller must free)
int* get_array_dynamic(int size) {
    int *arr = malloc(size * sizeof(int));
    // fill array...
    return arr;  // Caller must free!
}
```

---

# 6. Strings in C

## What is a String in C?

A string in C is a **null-terminated character array**.

```c
// String literal
char *str = "Hello";

// Memory representation:
// Index:   [0]  [1]  [2]  [3]  [4]  [5]
// Value:   'H'  'e'  'l'  'l'  'o'  '\0'
//                                    ↑
//                             Null terminator (ASCII 0)
```

## String Declaration Methods

```c
// Method 1: Character array with initialization
char str1[] = "Hello";        // Size = 6 (includes '\0')
char str2[10] = "Hello";      // Size = 10, extra chars are '\0'
char str3[5] = "Hello";       // DANGER! No room for '\0'

// Method 2: Character array explicit
char str4[] = {'H', 'e', 'l', 'l', 'o', '\0'};  // Must add '\0'
char str5[] = {'H', 'e', 'l', 'l', 'o'};        // NOT a string! No '\0'

// Method 3: Pointer to string literal
char *str6 = "Hello";         // Points to read-only memory!

// Method 4: Empty string
char str7[] = "";             // Contains only '\0', size = 1
char *str8 = "";              // Same
```

## ⚠️ CRITICAL: Array vs Pointer String Declaration

```c
// ARRAY - stored in modifiable memory (stack/heap)
char arr[] = "Hello";
arr[0] = 'J';          // OK! Now "Jello"

// POINTER - points to string literal (read-only memory)
char *ptr = "Hello";
ptr[0] = 'J';          // UNDEFINED BEHAVIOR! May crash

// Pointer can be reassigned, array cannot
ptr = "World";         // OK
// arr = "World";      // ERROR! Array name is not assignable
```

## String Input/Output

```c
#include <stdio.h>

char name[50];

// scanf - stops at whitespace
scanf("%s", name);              // "John Doe" → only reads "John"
scanf("%49s", name);            // Safe: limit input length

// gets - NEVER USE! (deprecated, removed in C11)
// gets(name);                   // Buffer overflow vulnerability

// fgets - SAFE way to read strings
fgets(name, 50, stdin);         // Reads up to 49 chars + '\0'
// Note: fgets includes newline '\n' if there's room

// Remove newline from fgets
name[strcspn(name, "\n")] = '\0';  // Clean way

// printf for strings
printf("%s\n", name);           // Print string
printf("%.5s\n", name);         // Print first 5 chars
printf("%10s\n", name);         // Right-align in 10-char field
printf("%-10s\n", name);        // Left-align in 10-char field
```

## String Length vs Array Size

```c
char str[20] = "Hello";

printf("%zu\n", sizeof(str));   // 20 (array size in bytes)
printf("%zu\n", strlen(str));   // 5 (string length, excludes '\0')

// IMPORTANT: strlen() scans until '\0'
// If no '\0', undefined behavior (may crash or return garbage)
```

---

# 7. String Library Functions

Include `<string.h>` for these functions.

## Length Functions

```c
// strlen - returns length (not including '\0')
size_t len = strlen("Hello");  // 5

// strnlen - bounded strlen (safer)
size_t len = strnlen(str, 100);  // Max 100, prevents infinite loop
```

## Copy Functions

```c
char dest[20];
char src[] = "Hello";

// strcpy - UNSAFE (no bounds checking)
strcpy(dest, src);             // dest = "Hello"

// strncpy - SAFER but tricky
strncpy(dest, src, 19);        // Copy max 19 chars
dest[19] = '\0';               // MUST manually null-terminate!

// strncpy quirks:
// - Does NOT null-terminate if src >= n chars
// - Pads with '\0' if src < n chars

// strlcpy - BEST (BSD/glibc) - returns src length
// size_t len = strlcpy(dest, src, sizeof(dest));  // Always null-terminates
```

## Concatenation Functions

```c
char dest[20] = "Hello";

// strcat - UNSAFE
strcat(dest, " World");        // dest = "Hello World"

// strncat - SAFER
strncat(dest, " World", 10);   // Append max 10 chars
// Note: strncat ALWAYS null-terminates (unlike strncpy)

// Buffer overflow example:
char small[6] = "Hello";
strcat(small, " World");       // BUFFER OVERFLOW! Undefined behavior
```

## Comparison Functions

```c
char s1[] = "apple";
char s2[] = "banana";

// strcmp - compare entire strings
int result = strcmp(s1, s2);
// result < 0: s1 comes before s2 (alphabetically)
// result == 0: strings are equal
// result > 0: s1 comes after s2

// strncmp - compare first n characters
int result = strncmp(s1, s2, 3);  // Compare first 3 chars

// Case-insensitive (non-standard, but common)
int result = strcasecmp(s1, s2);     // POSIX
int result = _stricmp(s1, s2);       // Windows
```

## Search Functions

```c
char str[] = "Hello World";

// strchr - find first occurrence of character
char *pos = strchr(str, 'o');   // Points to first 'o'
if (pos != NULL) {
    printf("Found at index: %ld\n", pos - str);  // 4
}

// strrchr - find LAST occurrence of character
char *pos = strrchr(str, 'o');  // Points to second 'o'

// strstr - find substring
char *pos = strstr(str, "World");  // Points to "World"
if (pos != NULL) {
    printf("Found at index: %ld\n", pos - str);  // 6
}

// strpbrk - find first char from a set
char *pos = strpbrk(str, "aeiou");  // First vowel: 'e'

// strcspn - length before any char from set
size_t len = strcspn(str, "aeiou");  // 1 (position of 'e')

// strspn - length of initial chars FROM set
size_t len = strspn("aaabbbccc", "ab");  // 6
```

## Tokenization

```c
char str[] = "Hello,World,How,Are,You";

// strtok - splits string by delimiters
char *token = strtok(str, ",");
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");  // NULL continues previous string
}
// Output: Hello World How Are You

// WARNING: strtok modifies original string!
// WARNING: strtok is NOT thread-safe!

// strtok_r - thread-safe version (POSIX)
char *saveptr;
char *token = strtok_r(str, ",", &saveptr);
```

## Memory Functions (work on any data, not just strings)

```c
#include <string.h>

// memset - fill memory with a value
char buffer[100];
memset(buffer, 0, 100);         // Zero out buffer
memset(buffer, 'A', 50);        // Fill first 50 bytes with 'A'

// memcpy - copy memory (non-overlapping)
int src[5] = {1, 2, 3, 4, 5};
int dest[5];
memcpy(dest, src, 5 * sizeof(int));

// memmove - copy memory (handles overlapping)
char str[] = "Hello World";
memmove(str + 2, str, 5);       // Safe even if regions overlap

// memcmp - compare memory blocks
int result = memcmp(buf1, buf2, 10);  // Compare 10 bytes

// memchr - find byte in memory
void *pos = memchr(buffer, 'X', 100);  // Find 'X' in first 100 bytes
```

---

# 8. String Manipulation Techniques

## Reverse a String (In-Place)

```c
void reverse_string(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
```

## Check Palindrome

```c
int is_palindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return 0;  // Not palindrome
        }
        left++;
        right--;
    }
    return 1;  // Is palindrome
}
```

## Count Character Occurrences

```c
int count_char(const char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) count++;
        str++;
    }
    return count;
}
```

## Remove Spaces

```c
void remove_spaces(char *str) {
    char *write = str;
    char *read = str;
    
    while (*read) {
        if (*read != ' ') {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}
```

## Convert Case

```c
#include <ctype.h>

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}
```

## Count Words

```c
int count_words(const char *str) {
    int count = 0;
    int in_word = 0;
    
    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}
```

## Reverse Words in a String

```c
// "Hello World" → "World Hello"
void reverse_words(char *str) {
    // Step 1: Reverse entire string
    reverse_string(str);
    
    // Step 2: Reverse each word
    char *word_start = str;
    char *ptr = str;
    
    while (*ptr) {
        if (*ptr == ' ') {
            *ptr = '\0';
            reverse_string(word_start);
            *ptr = ' ';
            word_start = ptr + 1;
        }
        ptr++;
    }
    reverse_string(word_start);  // Reverse last word
}
```

---

# 9. Common Pitfalls & Edge Cases

## Pitfall 1: Buffer Overflow

```c
// WRONG
char name[5];
scanf("%s", name);        // User enters "Hello" → overflow!

// CORRECT
char name[5];
scanf("%4s", name);       // Read max 4 chars + '\0'

// WRONG
char dest[10];
strcpy(dest, "This is a very long string");  // Overflow!

// CORRECT
char dest[10];
strncpy(dest, "This is a very long string", 9);
dest[9] = '\0';
```

## Pitfall 2: Missing Null Terminator

```c
// WRONG
char str[5] = {'H', 'e', 'l', 'l', 'o'};  // No '\0'!
printf("%s\n", str);       // Undefined behavior - keeps reading

// WRONG
char dest[5];
strncpy(dest, "Hello", 5);  // dest is NOT null-terminated!
printf("%s\n", dest);       // Undefined behavior

// CORRECT
char dest[6];
strncpy(dest, "Hello", 5);
dest[5] = '\0';
```

## Pitfall 3: Modifying String Literals

```c
// WRONG
char *str = "Hello";
str[0] = 'J';              // Crash or undefined behavior!

// CORRECT
char str[] = "Hello";      // Array copy
str[0] = 'J';              // OK
```

## Pitfall 4: Array Decay in sizeof

```c
void func(int arr[]) {
    // WRONG - sizeof(arr) returns pointer size
    int size = sizeof(arr) / sizeof(arr[0]);  // Always 2 on 64-bit!
}

// CORRECT - pass size separately
void func(int arr[], int size) {
    // Use size parameter
}
```

## Pitfall 5: Off-by-One Errors

```c
char str[10] = "Hello";

// WRONG - index starts at 0
for (int i = 0; i <= strlen(str); i++) {  // Should be <, not <=
    // Processing including '\0' might cause issues
}

// WRONG - array of 10, valid indices are 0-9
str[10] = 'X';  // Out of bounds!

// Correct
for (int i = 0; i < strlen(str); i++) {
    // Process characters only
}
```

## Pitfall 6: Comparing Strings with ==

```c
// WRONG - compares addresses, not content
char str1[] = "Hello";
char str2[] = "Hello";
if (str1 == str2) { }      // Always false! Different addresses

// CORRECT
if (strcmp(str1, str2) == 0) { }  // Compare content
```

## Pitfall 7: Empty String vs NULL Pointer

```c
char *str1 = "";        // Valid empty string - points to '\0'
char *str2 = NULL;      // NULL pointer - points to nothing

strlen(str1);           // Returns 0 - valid
strlen(str2);           // CRASH! Dereferencing NULL

// Always check for NULL before string operations
if (str != NULL && strlen(str) > 0) {
    // Safe to process
}
```

## Pitfall 8: scanf() Leaves Newline

```c
int num;
char name[50];

scanf("%d", &num);       // User enters "42\n"
fgets(name, 50, stdin);  // Reads the leftover '\n' immediately!

// SOLUTION 1: Consume newline
scanf("%d", &num);
getchar();               // Consume '\n'
fgets(name, 50, stdin);

// SOLUTION 2: Use space in format
scanf(" %s", name);      // Leading space skips whitespace
```

## Pitfall 9: VLA Stack Overflow

```c
// DANGEROUS
void process(int n) {
    int arr[n];          // If n is huge, stack overflow!
}

process(10000000);       // Likely crash

// SAFER - use heap for large arrays
void process_safe(int n) {
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) return;  // Handle allocation failure
    // ... use arr ...
    free(arr);
}
```

## Pitfall 10: strtok() Modifies Original

```c
char original[] = "a,b,c,d";
char *copy = original;         // Just copies pointer!

strtok(copy, ",");             // Modifies original too!

// CORRECT - make actual copy
char original[] = "a,b,c,d";
char copy[20];
strcpy(copy, original);
strtok(copy, ",");             // original is preserved
```

---

# 10. Interview Questions - Theory

## Q1: Difference between char arr[] and char *ptr?

**Answer:**
| Aspect | `char arr[] = "Hello"` | `char *ptr = "Hello"` |
|--------|------------------------|------------------------|
| Storage | Stack (or data segment if global) | Pointer on stack, string in read-only section |
| Modifiable | Yes | No (undefined behavior) |
| sizeof | Returns array size (6) | Returns pointer size (8) |
| Reassignable | No | Yes |
| Memory | Copies the string | Just stores address |

## Q2: What is array decay?

**Answer:**
Array decay is when an array name is implicitly converted to a pointer to its first element. This happens in most contexts except:
1. `sizeof(array)` - returns actual array size
2. `&array` - gives pointer to entire array
3. String literal initializing char array

## Q3: Why is strcpy() unsafe?

**Answer:**
- No bounds checking - copies until '\0' found in source
- Can overflow destination buffer
- Attacker can exploit for buffer overflow attacks
- Use strncpy() or strlcpy() instead

## Q4: Difference between memcpy() and memmove()?

**Answer:**
- `memcpy()`: Faster but undefined for overlapping regions
- `memmove()`: Handles overlapping regions safely (slightly slower)

```c
char str[] = "Hello World";
memcpy(str + 2, str, 5);   // UNDEFINED if overlap
memmove(str + 2, str, 5);  // SAFE
```

## Q5: What is Row-Major order?

**Answer:**
In C, 2D arrays are stored in row-major order - all elements of row 0 first, then row 1, etc.

`int a[2][3] = {{1,2,3}, {4,5,6}}`

Memory: [1][2][3][4][5][6]

Address of `a[i][j]` = base + (i * num_cols + j) * sizeof(element)

## Q6: Can array size be zero?

**Answer:**
- Standard C: No, undefined behavior
- GCC extension: Allows zero-size arrays at end of structs (flexible array member)

```c
struct packet {
    int length;
    char data[];  // Flexible array member
};
```

## Q7: What's wrong with returning local array?

**Answer:**
```c
int* foo() {
    int arr[5] = {1,2,3,4,5};
    return arr;  // WRONG - arr destroyed when function returns
}
```
The array is on the stack and gets deallocated. Returning its address gives a dangling pointer.

## Q8: Difference between strlen() and sizeof() for strings?

**Answer:**
```c
char str[] = "Hello";
strlen(str);    // 5 - counts characters until '\0'
sizeof(str);    // 6 - total bytes allocated including '\0'
```

## Q9: What is a string literal's type?

**Answer:**
In C: `char *` (but modifying is undefined behavior)
In C++: `const char *`

String literals are stored in read-only memory section.

## Q10: What happens with negative array index?

**Answer:**
C allows it syntactically: `arr[-1]` = `*(arr - 1)`

It's valid IF there's allocated memory at that address:
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = &arr[2];
printf("%d", ptr[-1]);  // Prints 2 (arr[1]) - valid!
```

But `arr[-1]` directly is undefined behavior (accessing before array).

---

# 11. Interview Questions - Coding

## Easy Level

### 1. Find Maximum and Minimum in Array
```c
void find_min_max(int arr[], int n, int *min, int *max) {
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}
```

### 2. Reverse an Array
```c
void reverse_array(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}
```

### 3. Check if String is Palindrome
```c
int is_palindrome(char *str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        if (str[left++] != str[right--]) return 0;
    }
    return 1;
}
```

### 4. Count Vowels and Consonants
```c
void count_vowels_consonants(char *str, int *v, int *c) {
    *v = *c = 0;
    while (*str) {
        char ch = tolower(*str);
        if (ch >= 'a' && ch <= 'z') {
            if (ch == 'a' || ch == 'e' || ch == 'i' || 
                ch == 'o' || ch == 'u')
                (*v)++;
            else
                (*c)++;
        }
        str++;
    }
}
```

### 5. Remove Duplicates from Sorted Array
```c
int remove_duplicates(int arr[], int n) {
    if (n == 0) return 0;
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[j]) {
            arr[++j] = arr[i];
        }
    }
    return j + 1;  // New length
}
```

## Medium Level

### 6. Rotate Array by K Positions
```c
// Method: Reverse approach - O(n) time, O(1) space
void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start++] = arr[end];
        arr[end--] = temp;
    }
}

void rotate_right(int arr[], int n, int k) {
    k = k % n;  // Handle k > n
    reverse(arr, 0, n - 1);     // Reverse entire array
    reverse(arr, 0, k - 1);     // Reverse first k elements
    reverse(arr, k, n - 1);     // Reverse remaining elements
}
```

### 7. Find First Non-Repeating Character
```c
char first_non_repeating(char *str) {
    int count[256] = {0};
    
    // Count occurrences
    for (char *p = str; *p; p++) {
        count[(unsigned char)*p]++;
    }
    
    // Find first with count 1
    for (char *p = str; *p; p++) {
        if (count[(unsigned char)*p] == 1) {
            return *p;
        }
    }
    return '\0';  // All repeating
}
```

### 8. Check if Two Strings are Anagrams
```c
int are_anagrams(char *s1, char *s2) {
    int count[256] = {0};
    
    // Increment for s1, decrement for s2
    while (*s1) count[(unsigned char)*s1++]++;
    while (*s2) count[(unsigned char)*s2++]--;
    
    // Check all counts are zero
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) return 0;
    }
    return 1;
}
```

### 9. Find Missing Number (1 to n)
```c
int find_missing(int arr[], int n) {
    // Array has n-1 elements, one missing from 1 to n
    int expected_sum = n * (n + 1) / 2;
    int actual_sum = 0;
    
    for (int i = 0; i < n - 1; i++) {
        actual_sum += arr[i];
    }
    
    return expected_sum - actual_sum;
}

// XOR method (avoids overflow)
int find_missing_xor(int arr[], int n) {
    int xor_all = 0, xor_arr = 0;
    
    for (int i = 1; i <= n; i++) xor_all ^= i;
    for (int i = 0; i < n - 1; i++) xor_arr ^= arr[i];
    
    return xor_all ^ xor_arr;
}
```

### 10. Longest Substring Without Repeating Characters
```c
int longest_unique_substring(char *str) {
    int last_seen[256];
    memset(last_seen, -1, sizeof(last_seen));
    
    int max_len = 0, start = 0;
    
    for (int i = 0; str[i]; i++) {
        unsigned char c = str[i];
        
        // If char seen and within current window
        if (last_seen[c] >= start) {
            start = last_seen[c] + 1;
        }
        
        last_seen[c] = i;
        int current_len = i - start + 1;
        if (current_len > max_len) max_len = current_len;
    }
    
    return max_len;
}
```

### 11. Move All Zeros to End
```c
void move_zeros_to_end(int arr[], int n) {
    int non_zero_index = 0;
    
    // Move all non-zero elements forward
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[non_zero_index++] = arr[i];
        }
    }
    
    // Fill remaining with zeros
    while (non_zero_index < n) {
        arr[non_zero_index++] = 0;
    }
}
```

### 12. Find Pair with Given Sum (Two Sum)
```c
// Brute force O(n²)
int find_pair_brute(int arr[], int n, int sum, int *i1, int *i2) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == sum) {
                *i1 = i; *i2 = j;
                return 1;
            }
        }
    }
    return 0;
}

// Two-pointer approach for SORTED array - O(n)
int find_pair_sorted(int arr[], int n, int sum, int *i1, int *i2) {
    int left = 0, right = n - 1;
    
    while (left < right) {
        int current_sum = arr[left] + arr[right];
        if (current_sum == sum) {
            *i1 = left; *i2 = right;
            return 1;
        } else if (current_sum < sum) {
            left++;
        } else {
            right--;
        }
    }
    return 0;
}
```

## Hard Level

### 13. Find Kth Largest Element (QuickSelect)
```c
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) {  // Descending order
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int quickselect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pivot_index = partition(arr, low, high);
        
        if (pivot_index == k - 1)
            return arr[pivot_index];
        else if (pivot_index > k - 1)
            return quickselect(arr, low, pivot_index - 1, k);
        else
            return quickselect(arr, pivot_index + 1, high, k);
    }
    return -1;
}
```

### 14. Maximum Subarray Sum (Kadane's Algorithm)
```c
int max_subarray_sum(int arr[], int n) {
    int max_so_far = arr[0];
    int max_ending_here = arr[0];
    
    for (int i = 1; i < n; i++) {
        max_ending_here = (arr[i] > max_ending_here + arr[i]) 
                          ? arr[i] : max_ending_here + arr[i];
        
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
        }
    }
    
    return max_so_far;
}
```

### 15. Longest Common Prefix
```c
char* longest_common_prefix(char *strs[], int n) {
    if (n == 0) return "";
    
    static char result[1000];
    strcpy(result, strs[0]);
    
    for (int i = 1; i < n; i++) {
        int j = 0;
        while (result[j] && strs[i][j] && result[j] == strs[i][j]) {
            j++;
        }
        result[j] = '\0';
        
        if (result[0] == '\0') return result;
    }
    
    return result;
}
```

### 16. String Compression (Run-Length Encoding)
```c
void compress_string(char *str, char *result) {
    if (*str == '\0') {
        *result = '\0';
        return;
    }
    
    char *write = result;
    int count = 1;
    
    for (int i = 1; ; i++) {
        if (str[i] == str[i-1]) {
            count++;
        } else {
            *write++ = str[i-1];
            if (count > 1) {
                write += sprintf(write, "%d", count);
            }
            if (str[i] == '\0') break;
            count = 1;
        }
    }
    *write = '\0';
}
// "aaabbbccc" → "a3b3c3"
```

### 17. Spiral Matrix Traversal
```c
void spiral_traverse(int rows, int cols, int matrix[rows][cols]) {
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    
    while (top <= bottom && left <= right) {
        // Right
        for (int i = left; i <= right; i++)
            printf("%d ", matrix[top][i]);
        top++;
        
        // Down
        for (int i = top; i <= bottom; i++)
            printf("%d ", matrix[i][right]);
        right--;
        
        // Left
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                printf("%d ", matrix[bottom][i]);
            bottom--;
        }
        
        // Up
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                printf("%d ", matrix[i][left]);
            left++;
        }
    }
}
```

### 18. Next Permutation
```c
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void reverse_arr(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start++], &arr[end--]);
    }
}

void next_permutation(int arr[], int n) {
    // Find first decreasing element from right
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    
    if (i >= 0) {
        // Find element just larger than arr[i]
        int j = n - 1;
        while (arr[j] <= arr[i]) {
            j--;
        }
        swap(&arr[i], &arr[j]);
    }
    
    // Reverse the suffix
    reverse_arr(arr, i + 1, n - 1);
}
```

---

# 12. Tricky Interview Questions

## Q1: What does this print?

```c
int arr[] = {10, 20, 30};
printf("%d %d %d", 0[arr], 1[arr], 2[arr]);
```

**Answer:** `10 20 30`

Because `i[arr]` = `*(i + arr)` = `*(arr + i)` = `arr[i]`

---

## Q2: What's the output?

```c
char str[] = "Hello";
printf("%c %c", *str, *(str+4));
```

**Answer:** `H o`

`*str` is `str[0]` = 'H'  
`*(str+4)` is `str[4]` = 'o'

---

## Q3: Find the bug

```c
char *getString() {
    char str[] = "Hello";
    return str;
}
```

**Answer:** Returns address of local array - dangling pointer! `str` is destroyed when function returns.

---

## Q4: What's the output?

```c
char *p = "Hello";
printf("%c", *p++);
printf("%c", *p);
```

**Answer:** `H e`

First prints 'H' then increments p. Second prints 'e'.

---

## Q5: What's wrong?

```c
char str1[5] = "Hello";
```

**Answer:** Array size 5 but "Hello" needs 6 bytes (including '\0'). No null terminator stored!

---

## Q6: What's the sizeof?

```c
char *str = "Hello";
char arr[] = "Hello";

printf("%zu %zu", sizeof(str), sizeof(arr));
```

**Answer:** `8 6` (on 64-bit)

`sizeof(str)` = pointer size = 8  
`sizeof(arr)` = array size = 6 (including '\0')

---

## Q7: What happens?

```c
char *str = "Hello";
str[0] = 'J';
```

**Answer:** Undefined behavior (likely crash). String literal is in read-only memory.

---

## Q8: What's the output?

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;
printf("%d", *(p + 3));
printf("%d", p[3]);
printf("%d", 3[p]);
```

**Answer:** `4 4 4` - All three are equivalent!

---

## Q9: True or False?

```c
int a[5];
int *p = a;

// a and p are the same
```

**Answer:** False! 
- `a` is an array - has fixed address, sizeof gives array size
- `p` is a pointer - can be reassigned, sizeof gives pointer size

---

## Q10: What's printed?

```c
int a[5] = {1, 2, 3, 4, 5};
printf("%p\n", a);
printf("%p\n", a + 1);
printf("%p\n", &a);
printf("%p\n", &a + 1);
```

**Answer:** (assuming base = 1000)
- `a` → 1000 (address of first element)
- `a + 1` → 1004 (moves by sizeof(int))
- `&a` → 1000 (address of entire array)
- `&a + 1` → 1020 (moves by sizeof(entire array) = 20 bytes)

---

## Q11: What does this do?

```c
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void foo(int arr[]) {
    printf("%zu", ARRAY_SIZE(arr));
}
```

**Answer:** Wrong! Always prints 2 (64-bit) or 1 (32-bit) because inside function, `arr` is pointer.

---

## Q12: Find the error

```c
char buffer[10];
sprintf(buffer, "Number is: %d", 123456789);
```

**Answer:** Buffer overflow! "Number is: 123456789" is 21 chars but buffer is only 10.

Use `snprintf(buffer, sizeof(buffer), ...)` instead.

---

## Q13: What's special about this?

```c
struct {
    int count;
    char data[];
} packet;
```

**Answer:** Flexible array member (C99). `data` has no size in struct, but memory can be allocated for it:
```c
struct packet *p = malloc(sizeof(*p) + 100);  // 100 bytes for data
```

---

## Quick Reference Card

### Array Declaration Cheat Sheet
```c
int arr[5];                    // Uninitialized (garbage values if local)
int arr[5] = {0};              // All zeros
int arr[5] = {1, 2};           // {1, 2, 0, 0, 0}
int arr[] = {1, 2, 3};         // Size = 3
int arr[5] = {[2]=5, [4]=7};   // {0, 0, 5, 0, 7}
```

### String Declaration Cheat Sheet
```c
char str[] = "Hello";          // Modifiable, size = 6
char *str = "Hello";           // Read-only, just pointer
char str[10] = "Hello";        // Modifiable, size = 10
char str[10] = {0};            // Empty string, all zeros
```

### Common Patterns
```c
// Array length (only works in same scope)
size_t len = sizeof(arr) / sizeof(arr[0]);

// String length
size_t len = strlen(str);

// Iterate array
for (int i = 0; i < n; i++) { ... }

// Iterate string
for (char *p = str; *p; p++) { ... }  // or
for (int i = 0; str[i]; i++) { ... }

// Safe string copy
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';

// Remove newline from fgets
str[strcspn(str, "\n")] = '\0';
```

---

**🎯 Practice these concepts thoroughly. Arrays and strings are the FOUNDATION of most interview coding problems!**
