# Dynamic Memory Allocation in C
## A Complete Guide — Beginner to Expert

---

## TABLE OF CONTENTS

1. [What is Memory in C?](#1-what-is-memory-in-c)
2. [Static vs Dynamic Memory Allocation](#2-static-vs-dynamic-memory-allocation)
3. [Stack vs Heap Memory](#3-stack-vs-heap-memory)
4. [Why Dynamic Memory Allocation is Needed](#4-why-dynamic-memory-allocation-is-needed)
5. [The Four Core Functions](#5-the-four-core-functions)
   - [malloc()](#51-malloc)
   - [calloc()](#52-calloc)
   - [realloc()](#53-realloc)
   - [free()](#54-free)
6. [Practical Examples](#6-practical-examples)
7. [Intermediate Concepts](#7-intermediate-concepts)
8. [Advanced Topics](#8-advanced-topics)
9. [Comparison Table](#9-comparison-table)
10. [Debugging and Tools](#10-debugging-and-tools)
11. [Common Mistakes](#11-common-mistakes)
12. [Summary and Quick Revision](#12-summary-and-quick-revision)
13. [Interview Questions](#13-interview-questions)

---

## 1. What is Memory in C?

When a C program runs, the operating system provides it a block of memory. This memory is divided into multiple regions, each serving a specific purpose.

```
Memory Layout of a Running C Program:

┌────────────────────────┐  High Address
│    Command-line args   │
│    Environment vars    │
├────────────────────────┤
│         Stack          │  ← function calls, local variables (grows downward ↓)
│           ↓            │
│                        │
│       [free space]     │
│                        │
│           ↑            │
│          Heap          │  ← dynamic memory (grows upward ↑)
├────────────────────────┤
│    BSS Segment         │  ← uninitialized global/static variables (zeroed)
├────────────────────────┤
│    Data Segment        │  ← initialized global/static variables
├────────────────────────┤
│    Text Segment        │  ← compiled machine code (read-only)
└────────────────────────┘  Low Address
```

| Segment     | Stored What                          | Managed By    |
|-------------|--------------------------------------|---------------|
| Text        | Compiled code                        | OS / Loader   |
| Data / BSS  | Global and static variables          | OS            |
| Stack       | Local variables, function frames     | Compiler      |
| Heap        | Dynamic allocations (`malloc` etc.)  | Programmer    |

> **Key takeaway**: As a programmer, you directly control only the **Heap** — through `malloc`, `calloc`, `realloc`, and `free`.

---

## 2. Static vs Dynamic Memory Allocation

### Static Memory Allocation

Memory is allocated **at compile time**. The size must be known before the program runs.

```c
int arr[10];           // 10 integers, size fixed forever
char name[50];         // 50 characters, fixed
int x = 5;            // single integer
```

**Limitations:**
- Size cannot change at runtime
- Wastes memory if you allocate too much
- Crashes (stack overflow) if you allocate too little

---

### Dynamic Memory Allocation

Memory is allocated **at runtime** from the heap. Size can be determined while the program is running.

```c
int n;
printf("How many elements? ");
scanf("%d", &n);

int *arr = malloc(n * sizeof(int));  // n decided at runtime!
```

**Advantages:**
- Size decided at runtime
- Can grow and shrink as needed
- Only uses as much memory as required

**Disadvantages:**
- You must manually free memory (risk of leaks)
- Slightly slower than stack allocation
- Risk of fragmentation

---

## 3. Stack vs Heap Memory

### Stack Memory

```
void foo() {
    int x = 10;       ← pushed onto stack
    int y = 20;       ← pushed onto stack
    // ... function ends
}                     ← x and y automatically popped off

Stack (grows downward):
┌──────────────┐
│   main()     │
│   x = 10     │
│   y = 20     │  ← top of stack (current frame)
└──────────────┘
```

- **Automatic**: allocated when function is called, freed when it returns
- **Fast**: just moves a stack pointer
- **Limited**: typically 1–8 MB total
- **Short-lived**: data dies when function exits

---

### Heap Memory

```
int *p = malloc(4);   ← allocates 4 bytes on the heap
*p = 42;
free(p);              ← you must free it manually

Heap (grows upward):
┌──────────────────────────────────┐
│  [4 bytes: value 42]   ← p points here
│  [free space]
│  ...
└──────────────────────────────────┘
```

- **Manual**: you allocate and free it yourself
- **Slower** than stack (managed by allocator)
- **Large**: can use most of available RAM
- **Long-lived**: persists until you call `free()`

---

### Side-by-Side Comparison

```
Stack                        Heap
┌────────────────────┐       ┌─────────────────────┐
│ int x = 10;        │       │ int *p = malloc(4); │
│ Allocated on entry │       │ Allocated on demand │
│ Freed on exit      │       │ Freed by free(p)    │
│ Fast               │       │ Slower              │
│ Small (1–8 MB)     │       │ Large (GBs)         │
│ Automatic          │       │ Manual              │
└────────────────────┘       └─────────────────────┘
```

| Feature        | Stack           | Heap                   |
|----------------|-----------------|------------------------|
| Allocation     | Compile time    | Runtime                |
| Management     | Automatic       | Manual (you)           |
| Size limit     | ~1–8 MB         | Limited by RAM         |
| Speed          | Very fast       | Slower                 |
| Scope          | Within function | Until `free()` called  |
| Overflow risk  | Stack overflow  | Memory leak            |

---

## 4. Why Dynamic Memory Allocation is Needed

### Problem 1: Unknown Size at Compile Time

```c
// BAD — size must be a constant
int arr[10];    // what if the user has 500 elements?

// GOOD — size known only at runtime
int n;
scanf("%d", &n);
int *arr = malloc(n * sizeof(int));
```

### Problem 2: Data Must Outlive a Function

```c
// BAD — local array destroyed when function returns
int* create_array() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;   // DANGER: returns pointer to dead stack memory!
}

// GOOD — heap memory outlives the function
int* create_array() {
    int *arr = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) arr[i] = i + 1;
    return arr;   // safe — heap memory is alive until free() is called
}
```

### Problem 3: Resizable Data Structures

```c
// A dynamic list that grows as needed
int capacity = 4;
int *list = malloc(capacity * sizeof(int));

// list is full? double its size
capacity *= 2;
list = realloc(list, capacity * sizeof(int));
```

---

## 5. The Four Core Functions

> **Header required:** `#include <stdlib.h>`

---

### 5.1 malloc()

**malloc** = **M**emory **alloc**ation

```c
void *malloc(size_t size);
```

- Allocates `size` bytes on the heap
- Returns a `void *` pointer to the start of the block
- The memory is **uninitialized** (contains garbage values)
- Returns `NULL` if allocation fails

```
Before malloc(12):
Heap: [......free......]

After malloc(12):
Heap: [####][....free...]
       ^
       returned pointer (12 bytes, uninitialized — garbage inside)
```

**Example:**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));    // allocate space for 1 integer

    if (p == NULL) {                 // ALWAYS check for NULL
        printf("Allocation failed!\n");
        return 1;
    }

    *p = 42;
    printf("Value: %d\n", *p);      // Output: 42

    free(p);                         // release memory
    p = NULL;                        // good practice

    return 0;
}
```

**Allocating an array with malloc:**
```c
int n = 5;
int *arr = malloc(n * sizeof(int));  // 5 * 4 = 20 bytes

if (arr == NULL) { /* handle error */ }

for (int i = 0; i < n; i++)
    arr[i] = i * 10;                 // arr[0]=0, arr[1]=10, ...

for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);

free(arr);
arr = NULL;
```

---

### 5.2 calloc()

**calloc** = **C**ontiguous **alloc**ation

```c
void *calloc(size_t num_elements, size_t element_size);
```

- Allocates memory for `num_elements`, each of `element_size` bytes
- Total bytes = `num_elements × element_size`
- **Zero-initializes** all allocated memory (unlike `malloc`)
- Returns `NULL` if allocation fails

```
calloc(5, sizeof(int))  allocates 20 bytes, all set to 0:

Heap: [ 0 ][ 0 ][ 0 ][ 0 ][ 0 ]
        ^    ^    ^    ^    ^
        arr[0]   arr[2]   arr[4]
```

**Example:**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int *arr = calloc(n, sizeof(int));   // 5 integers, all zeroed

    if (arr == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }

    // No need to initialize — already all zeros
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);           // Output: 0 0 0 0 0

    free(arr);
    arr = NULL;
    return 0;
}
```

**malloc vs calloc — Key difference:**
```c
// malloc: garbage values inside
int *a = malloc(5 * sizeof(int));
// a[0], a[1]... contain unknown garbage!

// calloc: guaranteed zeros
int *b = calloc(5, sizeof(int));
// b[0] = 0, b[1] = 0, b[2] = 0 ...

// malloc + memset = equivalent to calloc
int *c = malloc(5 * sizeof(int));
memset(c, 0, 5 * sizeof(int));
// now c[0..4] = 0
```

---

### 5.3 realloc()

**realloc** = **Re**size **alloc**ation

```c
void *realloc(void *ptr, size_t new_size);
```

- Resizes a previously allocated block to `new_size` bytes
- May move the block to a new location if needed
- If `ptr` is `NULL`, behaves like `malloc(new_size)`
- If `new_size` is 0, behaves like `free(ptr)`
- **Existing data is preserved** (up to the minimum of old and new sizes)

```
Before realloc — 3 elements:
Heap: [10][20][30][....free....]
       ^
       ptr (12 bytes)

After realloc(ptr, 5 * sizeof(int)) — expanded to 5:
Heap: [10][20][30][ ? ][ ? ][...free...]
       ^
       new_ptr (20 bytes — old data preserved, new bytes uninitialized)
```

**Example — Growing a dynamic array:**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 10; arr[1] = 20; arr[2] = 30;

    // Need to store 2 more elements — resize!
    int *temp = realloc(arr, 5 * sizeof(int));

    if (temp == NULL) {
        printf("Realloc failed!\n");
        free(arr);   // original still valid on failure
        return 1;
    }

    arr = temp;      // update pointer only after NULL check
    arr[3] = 40;
    arr[4] = 50;

    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);   // 10 20 30 40 50

    free(arr);
    arr = NULL;
    return 0;
}
```

> **Important**: Never do `arr = realloc(arr, new_size)` directly!  
> If `realloc` fails it returns `NULL` — you lose the original pointer and cause a memory leak.  
> **Always use a temp pointer first.**

---

### 5.4 free()

```c
void free(void *ptr);
```

- Releases a heap-allocated block back to the OS/allocator
- `ptr` must point to the **start** of a previously allocated block
- After `free()`, the memory is no longer yours — do not use it
- Calling `free(NULL)` is safe (does nothing)

```
After free(arr):

Heap: [........freed space........]
       ^
       arr still holds the old address (dangling pointer!)
       Setting arr = NULL prevents accidental use
```

**Example:**
```c
int *p = malloc(sizeof(int));
*p = 100;
free(p);          // memory returned to heap
p = NULL;         // prevents dangling pointer

// free(p) again would be undefined behaviour — avoid double-free!
```

---

## 6. Practical Examples

### 6.1 Dynamic Integer Array

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter size: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    if (!arr) { perror("malloc"); return 1; }

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("You entered: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    arr = NULL;
    return 0;
}
```

---

### 6.2 malloc vs calloc — Garbage Demo

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = malloc(5 * sizeof(int));
    int *b = calloc(5, sizeof(int));

    printf("malloc (uninitialized):\n");
    for (int i = 0; i < 5; i++)
        printf("a[%d] = %d\n", i, a[i]);    // random garbage!

    printf("\ncalloc (zero-initialized):\n");
    for (int i = 0; i < 5; i++)
        printf("b[%d] = %d\n", i, b[i]);    // always 0

    free(a);
    free(b);
    return 0;
}
```

**Sample Output:**
```
malloc (uninitialized):
a[0] = -842150451     ← garbage
a[1] = 32765          ← garbage
a[2] = 0
a[3] = 1073741824     ← garbage
a[4] = -1             ← garbage

calloc (zero-initialized):
b[0] = 0
b[1] = 0
b[2] = 0
b[3] = 0
b[4] = 0
```

---

### 6.3 Dynamic Array with realloc

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int capacity = 2;
    int size = 0;
    int *arr = malloc(capacity * sizeof(int));

    int val;
    printf("Enter integers (-1 to stop):\n");

    while (1) {
        scanf("%d", &val);
        if (val == -1) break;

        if (size == capacity) {           // array full — double capacity
            capacity *= 2;
            int *temp = realloc(arr, capacity * sizeof(int));
            if (!temp) { free(arr); return 1; }
            arr = temp;
            printf("[Resized to %d]\n", capacity);
        }

        arr[size++] = val;
    }

    printf("Stored: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
```

---

### 6.4 Dynamic String

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str = malloc(50 * sizeof(char));
    if (!str) return 1;

    strcpy(str, "Hello, World!");
    printf("%s\n", str);         // Hello, World!

    // Resize to fit a longer string
    str = realloc(str, 100 * sizeof(char));
    strcat(str, " Welcome to C!");
    printf("%s\n", str);         // Hello, World! Welcome to C!

    free(str);
    return 0;
}
```

---

## 7. Intermediate Concepts

### 7.1 Memory Leaks

A **memory leak** happens when allocated memory is never freed. The program keeps consuming RAM without releasing it.

```c
// Memory leak example
void leaky_function() {
    int *p = malloc(100 * sizeof(int));
    // ... do some work ...
    return;    // BUG: forgot to free(p)!
               // 400 bytes lost forever (until program exits)
}

int main() {
    for (int i = 0; i < 1000; i++)
        leaky_function();    // leaks 400 KB total!
    return 0;
}
```

**Visual:**
```
Call 1: Heap [####][....free....]  ← 400 bytes, no pointer to free it
Call 2: Heap [####][####][..free.]
...
Call N: Heap [####][####][####]..  ← RAM exhausted!
```

**How to Avoid Leaks:**
```c
// GOOD: always free before returning
void safe_function() {
    int *p = malloc(100 * sizeof(int));
    if (!p) return;

    // ... do work ...

    free(p);   // ← always free
    p = NULL;
}
```

**Rules:**
- Every `malloc`/`calloc` must have exactly one matching `free`
- Use tools like **Valgrind** to detect leaks automatically
- In functions that return early (error paths), ensure memory is freed on each path

---

### 7.2 Dangling Pointers

A **dangling pointer** is a pointer that still holds an address after the memory at that address has been freed.

```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);          // memory is released

// p still contains the old address — it is now DANGLING
*p = 100;         // UNDEFINED BEHAVIOUR — memory no longer belongs to us!
printf("%d", *p); // unpredictable result, possible crash
```

**Fix: Always set pointer to NULL after free**
```c
free(p);
p = NULL;         // now p is a null pointer — safe, predictable

if (p != NULL)    // this check now works correctly
    *p = 100;     // won't execute
```

**Types of dangling pointers:**

| Cause                           | Example                                       |
|---------------------------------|-----------------------------------------------|
| Freed heap memory               | `free(p);` then using `p`                     |
| Out-of-scope local variable     | Returning pointer to local variable           |
| Accessing array out of bounds   | `arr[n]` where valid range is `arr[0..n-1]`   |

---

### 7.3 NULL Pointer Handling

`malloc` and `calloc` return `NULL` when allocation fails (e.g., not enough memory).

```c
int *arr = malloc(1000000000 * sizeof(int));   // requesting ~4 GB

if (arr == NULL) {                             // ALWAYS check!
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}
```

**Never skip the NULL check:**
```c
// BAD — no NULL check
int *p = malloc(sizeof(int));
*p = 5;                  // if malloc failed, this crashes with segfault!

// GOOD — always check
int *p = malloc(sizeof(int));
if (p == NULL) {
    perror("malloc failed");
    return -1;
}
*p = 5;
```

Using `perror()` prints the system error message — helpful for debugging.

---

### 7.4 Best Practices for Safe Memory Usage

```c
// 1. Always check return value of malloc/calloc/realloc
int *p = malloc(size);
if (!p) { /* handle error */ }

// 2. Use sizeof with the type or the variable (safer)
int *arr = malloc(n * sizeof(*arr));   // sizeof(*arr) = sizeof(int)
// If type changes, sizeof(*arr) updates automatically

// 3. Set pointer to NULL after free
free(ptr);
ptr = NULL;

// 4. Never double-free
free(ptr);
free(ptr);   // WRONG — undefined behaviour

// 5. Use a temp pointer for realloc
int *temp = realloc(arr, new_size);
if (!temp) { free(arr); return -1; }
arr = temp;

// 6. Free all memory before program exits (good habit)
free(arr);
free(str);
// etc.

// 7. Avoid pointer arithmetic beyond allocated bounds
int *arr = malloc(5 * sizeof(int));
arr[5] = 10;   // WRONG — out of bounds!
```

---

## 8. Advanced Topics

### 8.1 Dynamic Memory for Structures

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int  age;
    float gpa;
} Student;

int main() {
    // Allocate a single struct
    Student *s = malloc(sizeof(Student));
    if (!s) return 1;

    strcpy(s->name, "Alice");
    s->age = 20;
    s->gpa = 3.8f;

    printf("Name: %s, Age: %d, GPA: %.1f\n", s->name, s->age, s->gpa);
    free(s);

    // Allocate an array of structs
    int n = 3;
    Student *class = malloc(n * sizeof(Student));
    if (!class) return 1;

    strcpy(class[0].name, "Alice");  class[0].age = 20;
    strcpy(class[1].name, "Bob");    class[1].age = 21;
    strcpy(class[2].name, "Carol");  class[2].age = 19;

    for (int i = 0; i < n; i++)
        printf("%s is %d years old\n", class[i].name, class[i].age);

    free(class);
    return 0;
}
```

---

### 8.2 Dynamic Structures with Pointer Members

When a struct has pointer members, you must allocate them separately:

```c
typedef struct {
    char *name;      // pointer — needs its own allocation
    int   age;
} Person;

Person *create_person(const char *name, int age) {
    Person *p = malloc(sizeof(Person));
    if (!p) return NULL;

    p->name = malloc(strlen(name) + 1);   // +1 for null terminator
    if (!p->name) { free(p); return NULL; }

    strcpy(p->name, name);
    p->age = age;
    return p;
}

void destroy_person(Person *p) {
    if (p) {
        free(p->name);   // free inner pointer FIRST
        free(p);         // then free struct
        // free outer last — freeing outer first loses inner pointer!
    }
}

int main() {
    Person *alice = create_person("Alice", 25);
    printf("%s, age %d\n", alice->name, alice->age);
    destroy_person(alice);
    return 0;
}
```

> **Rule**: Free in **reverse order** of allocation. Inner members first, outer struct last.

---

### 8.3 Double Pointers and Dynamic 2D Arrays

**Method 1: Array of Pointers (most common)**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;

    // Step 1: allocate array of row pointers
    int **matrix = malloc(rows * sizeof(int *));

    // Step 2: allocate each row
    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(cols * sizeof(int));

    // Fill matrix
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = i * cols + j;

    // Print matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }

    // Free: rows first, then pointer array
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}
```

**Memory layout:**
```
matrix (double pointer)
   │
   ▼
[ *row0 | *row1 | *row2 ]    ← malloc(rows * sizeof(int*))
     │        │        │
     ▼        ▼        ▼
  [0][1][2][3]  [4][5][6][7]  [8][9][10][11]
   ← each row is a separate malloc ─────────►
```

**Method 2: Single contiguous block (better cache performance)**

```c
int rows = 3, cols = 4;

// Allocate one flat block
int *data = malloc(rows * cols * sizeof(int));

// Access as 2D: data[i * cols + j]
for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
        data[i * cols + j] = i * cols + j;

printf("Element [1][2] = %d\n", data[1 * cols + 2]);   // 6

free(data);   // single free
```

---

### 8.4 Fragmentation

#### Internal Fragmentation

Wasted space **inside** an allocated block because the allocator rounds up sizes.

```
Request: malloc(3)  — ask for 3 bytes
Allocator gives:    4 bytes (rounds up to alignment boundary)

Allocated block: [B][B][B][waste]
                  ^used^  ^1 byte wasted internally^
```

#### External Fragmentation

Free memory exists in **many small scattered blocks** rather than one large contiguous block.

```
After many malloc/free cycles:

[USED][free][USED][free][USED][free][USED]

Total free: 12 bytes. But malloc(12) FAILS — no contiguous 12-byte block!
```

**Minimising fragmentation:**
- Allocate similar-sized objects together
- Use memory pools for fixed-size objects
- Prefer `calloc` or contiguous 2D arrays where possible
- Use allocators like `jemalloc` or `tcmalloc` in production systems

---

### 8.5 Alignment and Padding Basics

The CPU accesses memory most efficiently when data is **aligned** to its natural boundary.

```
int (4 bytes) → best stored at address divisible by 4
double (8 bytes) → best stored at address divisible by 8
```

`malloc` always returns memory aligned for any basic type (at least 8-byte or 16-byte aligned on most platforms).

**Struct padding example:**
```c
struct Example {
    char  a;    // 1 byte
    // 3 bytes padding added by compiler
    int   b;    // 4 bytes (needs 4-byte alignment)
    char  c;    // 1 byte
    // 7 bytes padding added
    double d;   // 8 bytes (needs 8-byte alignment)
};
// sizeof(struct Example) = 24, not 14!
```

**Visualised:**
```
Offset: 0    1    2    3    4    5    6    7    8    9   10  ...  16  17  18  19  20  21  22  23
        [a] [pad][pad][pad][ b — 4 bytes  ] [c] [p] [p] [p] [p] [p] [p] [p] [ d — 8 bytes    ]
```

Use `__attribute__((packed))` (GCC) to eliminate padding — but this may cause performance penalties or crashes on strict-alignment architectures.

---

### 8.6 Real-World Usage in Systems Programming

**Linked List Node (dynamic allocation):**
```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int val) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = val;
    n->next = NULL;
    return n;
}

void free_list(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);        // free each node
    }
}
```

**String builder (dynamic string):**
```c
char *build_greeting(const char *name) {
    // "Hello, " + name + "!" + null terminator
    size_t len = 8 + strlen(name) + 1 + 1;
    char *result = malloc(len);
    if (!result) return NULL;
    snprintf(result, len, "Hello, %s!", name);
    return result;   // caller must free()
}
```

---

## 9. Comparison Table

| Feature                | `malloc`            | `calloc`               | `realloc`                | Static Allocation   |
|------------------------|---------------------|------------------------|--------------------------|---------------------|
| When allocated         | Runtime             | Runtime                | Runtime                  | Compile time        |
| Initialization         | Uninitialized (garbage) | Zero-initialized   | Preserves old data       | Default init        |
| Syntax                 | `malloc(size)`      | `calloc(n, size)`      | `realloc(ptr, new_size)` | `int arr[10];`      |
| Can resize?            | No                  | No                     | Yes                       | No                  |
| Returns                | `void *`            | `void *`               | `void *`                  | N/A                 |
| On failure             | Returns `NULL`      | Returns `NULL`         | Returns `NULL`            | Compile error       |
| Must free?             | Yes                 | Yes                    | Yes                       | No                  |
| Speed                  | Fast                | Slightly slower (zeros) | Depends on move needed   | Fastest             |
| Stored in              | Heap                | Heap                   | Heap                     | Stack / Data seg    |
| Use case               | General allocation  | Arrays needing zeros   | Resizing existing block  | Known fixed size    |

---

## 10. Debugging and Tools

### 10.1 Valgrind — Memory Error Detector

Valgrind is the industry-standard tool for detecting memory errors in C programs on Linux.

**Install:**
```bash
sudo apt install valgrind    # Ubuntu/Debian
sudo yum install valgrind    # CentOS/RHEL
```

**Run:**
```bash
gcc -g -o myapp myapp.c     # compile with debug symbols
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./myapp
```

**Example Valgrind output:**
```
==12345== Memcheck, a memory error detector
==12345== Invalid write of size 4
==12345==    at 0x4005A8: main (myapp.c:12)
==12345==  Address 0x5204080 is 0 bytes after a block of size 20
==12345==
==12345== LEAK SUMMARY:
==12345==    definitely lost: 40 bytes in 1 blocks
==12345==    indirectly lost:  0 bytes in 0 blocks
==12345==      possibly lost:  0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345== ERROR SUMMARY: 1 errors from 1 contexts
```

**What Valgrind detects:**

| Error Type            | Description                                    |
|-----------------------|------------------------------------------------|
| Invalid read/write    | Accessing memory out of bounds                 |
| Use of uninitialized  | Using uninitialised malloc'd memory            |
| Definitely lost       | Memory allocated but never freed (leak)        |
| Double free           | Calling `free()` twice on same pointer         |
| Invalid free          | Calling `free()` on non-heap or middle address |

---

### 10.2 AddressSanitizer (ASan) — Compile-Time Tool

Faster than Valgrind; works on Linux, macOS, and Windows (MSVC/Clang).

```bash
gcc -fsanitize=address -fsanitize=leak -g -o myapp myapp.c
./myapp
```

**Output example:**
```
==12345==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x...
WRITE of size 4 at 0x... thread T0
    #0 0x4005c8 in main myapp.c:15

==12345==ERROR: LeakSanitizer: detected memory leaks
Direct leak of 40 byte(s) in 1 object(s) allocated from:
    #0 0x... in malloc
    #1 0x4005a4 in main myapp.c:8
```

---

### 10.3 Common Errors and Detection

| Error                   | Symptom                           | Detection Method          |
|-------------------------|-----------------------------------|---------------------------|
| Memory leak             | RSS grows unboundedly             | Valgrind, ASan/LSan       |
| Buffer overflow         | Crash, corrupted data             | ASan, Valgrind             |
| Use-after-free          | Crash / wrong data                | ASan, Valgrind             |
| Double free             | Crash / assertion failure         | ASan, Valgrind             |
| Uninitialized memory    | Unpredictable results             | Valgrind (`--track-origins=yes`) |
| NULL dereference        | Segmentation fault                | Code review + NULL checks |
| Stack overflow          | Segfault in deep recursion        | Reduce recursion depth    |

**Quick runtime check with `assert`:**
```c
#include <assert.h>

int *arr = malloc(10 * sizeof(int));
assert(arr != NULL);    // terminates program if NULL during development
```

---

## 11. Common Mistakes

### Mistake 1: Forgetting to check NULL
```c
// WRONG
int *p = malloc(1000000 * sizeof(int));
p[0] = 5;              // crash if malloc returned NULL

// RIGHT
int *p = malloc(1000000 * sizeof(int));
if (!p) { perror("malloc"); exit(1); }
p[0] = 5;
```

### Mistake 2: Freeing the wrong pointer
```c
int *arr = malloc(5 * sizeof(int));
arr++;                  // moved pointer forward!
free(arr);              // WRONG — must free original pointer!

// RIGHT: keep original pointer, use index notation
int *arr = malloc(5 * sizeof(int));
arr[0] = 1;             // don't move the pointer
free(arr);              // correct
```

### Mistake 3: Using memory after free
```c
int *p = malloc(sizeof(int));
*p = 10;
free(p);
printf("%d\n", *p);    // WRONG — undefined behaviour

// RIGHT
free(p);
p = NULL;              // now any accidental dereference causes predictable crash
```

### Mistake 4: Losing the pointer (memory leak)
```c
int *p = malloc(100);
p = malloc(200);       // WRONG — original 100-byte block is leaked!

// RIGHT
free(p);               // free first block before reassigning
p = malloc(200);
```

### Mistake 5: Incorrect realloc usage
```c
// WRONG — potential null-pointer leak
arr = realloc(arr, new_size);   // if realloc fails, arr = NULL, original lost!

// RIGHT
int *temp = realloc(arr, new_size);
if (!temp) { free(arr); return -1; }
arr = temp;
```

### Mistake 6: Off-by-one in string allocation
```c
const char *msg = "Hello";

// WRONG — no space for null terminator '\0'
char *copy = malloc(strlen(msg));
strcpy(copy, msg);    // writes 6 bytes into 5-byte buffer!

// RIGHT
char *copy = malloc(strlen(msg) + 1);    // +1 for '\0'
strcpy(copy, msg);
```

### Mistake 7: sizeof(pointer) instead of sizeof(type)
```c
int *arr = malloc(10 * sizeof(int *));   // WRONG! allocates 80 bytes (10 × 8-byte pointers)
int *arr = malloc(10 * sizeof(int));     // RIGHT!  allocates 40 bytes (10 × 4-byte ints)

// Best practice: use sizeof(*arr) — always correct regardless of type
int *arr = malloc(10 * sizeof(*arr));
```

---

## 12. Summary and Quick Revision

### Core Functions Recap

```
malloc(n)          → allocate n bytes, uninitialized, return void*
calloc(count, n)   → allocate count×n bytes, zero-initialized, return void*
realloc(ptr, n)    → resize ptr to n bytes, preserve data, return void*
free(ptr)          → release allocated memory, set ptr=NULL after
```

### Memory Model Recap

```
┌───────────────────────────────────────────────────────────┐
│                   Program Memory                           │
│                                                           │
│  Text ─ your code (read-only)                            │
│  Data ─ global/static vars (initialized)                  │
│  BSS  ─ global/static vars (uninitialized, zeroed)       │
│                                                           │
│  Heap ─ malloc/calloc/realloc ─ YOU manage this ↑        │
│                                                           │
│  Stack ─ local vars, function calls ─ auto managed ↓     │
└───────────────────────────────────────────────────────────┘
```

### Golden Rules

1. **Every `malloc` needs a `free`** — one-to-one correspondence
2. **Always check for `NULL`** after every allocation
3. **Set pointer to `NULL` after `free`** — prevents dangling pointers
4. **Use a temp pointer with `realloc`** — never assign directly to source
5. **Free inner members before outer struct** — avoid memory leaks in structs
6. **Free in reverse order** of allocation
7. **Never access freed memory** — undefined behaviour

---

## 13. Interview Questions

**Q1: What is the difference between malloc and calloc?**
> `malloc` allocates uninitialized memory. `calloc` allocates and zero-initializes. `calloc(n, size)` is safer when you need zeroed arrays; `malloc` is slightly faster when you'll initialize the memory yourself.

**Q2: What happens if you call free() twice on the same pointer?**
> This is **undefined behaviour** — typically causes a crash or heap corruption. Always set the pointer to `NULL` after freeing: `free(p); p = NULL;`. Calling `free(NULL)` is safe and does nothing.

**Q3: What is a memory leak and how do you prevent it?**
> A memory leak occurs when allocated memory is never freed. Prevent it by: matching every `malloc` with a `free`, freeing on all code paths (including error paths), using tools like Valgrind or ASan.

**Q4: What is a dangling pointer?**
> A pointer that references memory that has been freed or gone out of scope. Accessing it is undefined behaviour. Prevent by setting pointers to `NULL` after `free`.

**Q5: Can you use realloc with NULL as the first argument?**
> Yes. `realloc(NULL, size)` is equivalent to `malloc(size)`.

**Q6: What is the difference between stack and heap?**
> Stack: automatic, fast, limited size, function-scoped. Heap: manual (`malloc`/`free`), larger, slower, lives as long as you need.

**Q7: Why should you not write `arr = realloc(arr, new_size)` directly?**
> If `realloc` fails it returns `NULL` but the original block is still allocated. Assigning `NULL` to `arr` loses the only pointer to the original block, causing a memory leak. Always use a temporary pointer.

**Q8: What is the purpose of setting a pointer to NULL after free()?**
> It turns the dangling pointer into a null pointer. Any accidental subsequent access will cause a predictable NULL-dereference crash (or can be guarded with an `if (p != NULL)` check) instead of silent memory corruption.

**Q9: How do you allocate a 2D array dynamically?**
> Two methods: (1) array of pointers — each row is a separate `malloc`, access as `arr[i][j]`; (2) single contiguous block — `malloc(rows * cols * sizeof(int))`, access as `data[i * cols + j]`. Method 2 has better cache performance.

**Q10: What does Valgrind's "definitely lost" mean?**
> Memory was allocated but there is no pointer left that points to it — it cannot be freed. This is a definitive memory leak.

**Q11: What is the difference between internal and external fragmentation?**
> Internal fragmentation: wasted space inside an allocated block (due to alignment padding). External fragmentation: many small free blocks exist but no single contiguous block large enough to satisfy a request.

**Q12: What is the correct way to free a struct that contains a pointer member?**
> Free the inner pointer member first, then free the struct itself. Freeing the struct first loses the inner pointer, causing a memory leak.

---

*Guide covers C89/C90 through C11/C17. All examples compile with `gcc -Wall -Wextra -g`.*
*Practice every example — memory management is learned by doing, not just reading.*
