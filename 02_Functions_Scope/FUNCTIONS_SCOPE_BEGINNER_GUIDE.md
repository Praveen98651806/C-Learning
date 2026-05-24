# C Functions & Scope — Study Guide

> **Who is this for?** Anyone with basic C knowledge wanting to deeply understand functions and scope.  
> **Style:** Step-by-step, practical, beginner-friendly  
> **Path:** Beginner → Intermediate → Advanced → Expert

---

## Table of Contents

1. [BEGINNER — What is a Function?](#1-beginner--what-is-a-function)
2. [BEGINNER — Function Syntax & Types](#2-beginner--function-syntax--types)
3. [BEGINNER — Parameters & Return Values](#3-beginner--parameters--return-values)
4. [BEGINNER — Scope: Where Variables Live](#4-beginner--scope-where-variables-live)
5. [INTERMEDIATE — Storage Classes](#5-intermediate--storage-classes)
6. [INTERMEDIATE — Memory: Stack vs Global](#6-intermediate--memory-stack-vs-global)
7. [INTERMEDIATE — Call by Value vs Reference](#7-intermediate--call-by-value-vs-reference)
8. [ADVANCED — Function Pointers](#8-advanced--function-pointers)
9. [ADVANCED — Inline Functions](#9-advanced--inline-functions)
10. [Common Mistakes & Best Practices](#10-common-mistakes--best-practices)

---

## 1. BEGINNER — What is a Function?

### Simple Idea

Think of a function as a **recipe**. You write the recipe once and use it whenever you need it — without rewriting it.

```
Without functions:               With functions:
─────────────────                ──────────────
add a + b                        int add(int a, int b) { return a+b; }
print result
                                 add(2, 3);   ← use it anywhere
add c + d
print result                     add(7, 9);   ← use it again
```

### Why Use Functions?

- **Avoid repeating code** — write once, call many times
- **Easier to read** — code tells a story
- **Easier to test** — test each part separately
- **Easier to fix** — fix in one place, fixed everywhere

### First Example

```c
#include <stdio.h>

/* Function definition */
void say_hello(void) {
    printf("Hello, World!\n");
}

int main(void) {
    say_hello();   /* Function call */
    say_hello();   /* Call it again! */
    return 0;
}
```

Output:
```
Hello, World!
Hello, World!
```

---

## 2. BEGINNER — Function Syntax & Types

### Basic Structure

```c
return_type  function_name ( parameters ) {
    /* body */
    return value;
}
```

### 4 Common Types

#### Type 1: No input, no output
```c
void print_line(void) {
    printf("-------------------\n");
}
```

#### Type 2: No input, returns something
```c
int get_max_score(void) {
    return 100;
}
```

#### Type 3: Takes input, no output
```c
void print_square(int n) {
    printf("%d x %d = %d\n", n, n, n * n);
}
```

#### Type 4: Takes input, returns something (most common)
```c
int add(int a, int b) {
    return a + b;
}
```

### Function Declaration (Prototype)

Always declare a function **before** you use it. Put declarations at the top or in a `.h` file.

```c
#include <stdio.h>

int add(int a, int b);    /* Declaration — tells compiler it exists */

int main(void) {
    int result = add(5, 3);   /* Can now use it */
    printf("Result: %d\n", result);
    return 0;
}

int add(int a, int b) {   /* Definition — actual code */
    return a + b;
}
```

> **Rule:** Declaration tells the compiler WHAT exists. Definition tells it HOW it works.

---

## 3. BEGINNER — Parameters & Return Values

### Parameters — Sending Data In

```c
/* 'name' and 'age' are parameters */
void introduce(char *name, int age) {
    printf("Hi, I am %s and I am %d years old.\n", name, age);
}

int main(void) {
    introduce("Alice", 25);
    introduce("Bob", 30);
    return 0;
}
```

### Return Values — Getting Data Out

```c
/* Calculate area of a rectangle */
float area(float length, float width) {
    return length * width;
}

int main(void) {
    float room = area(5.0, 3.5);
    printf("Area: %.1f sq meters\n", room);   /* 17.5 */
    return 0;
}
```

### Returning an Error Code (Very Common Pattern)

```c
/* Returns 0 = success, -1 = error */
int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;          /* Error: division by zero */
    }
    *result = a / b;
    return 0;               /* Success */
}

int main(void) {
    int answer;
    if (divide(10, 2, &answer) == 0) {
        printf("Answer: %d\n", answer);   /* 5 */
    } else {
        printf("Error!\n");
    }
    return 0;
}
```

> **Why this pattern?** In hardware drivers, a function often needs to return a value AND tell you if something went wrong. This pattern handles both.

---

## 4. BEGINNER — Scope: Where Variables Live

### What is Scope?

Scope answers the question: **"Where can I use this variable?"**

Think of it like rooms in a house:
- A variable in the kitchen is **only available in the kitchen**
- A variable in the hallway is **available to all rooms**

### Local Variables (Block Scope)

Created inside a function. Only visible inside that function.

```c
void calculate(void) {
    int x = 10;        /* Local to calculate() */
    int y = 20;
    printf("%d\n", x + y);
}

void another_function(void) {
    /* printf("%d\n", x);  ERROR! x doesn't exist here */
}
```

### Global Variables

Declared outside all functions. Visible everywhere.

```c
#include <stdio.h>

int score = 0;    /* Global — visible to all functions below */

void add_points(int pts) {
    score += pts;   /* Can access global */
}

void show_score(void) {
    printf("Score: %d\n", score);   /* Can access global */
}

int main(void) {
    add_points(10);
    add_points(5);
    show_score();    /* Output: Score: 15 */
    return 0;
}
```

### Block Scope (Inside `{}`)

Even inside a function, `{}` braces create a smaller scope.

```c
int main(void) {
    int a = 5;

    {
        int b = 10;          /* Only exists inside these braces */
        printf("%d\n", a);   /* OK — a is visible */
        printf("%d\n", b);   /* OK — b is visible */
    }

    /* printf("%d\n", b);    ERROR — b is gone! */

    return 0;
}
```

### Scope in `if`, `for`, `while`

```c
for (int i = 0; i < 5; i++) {   /* i exists only inside the for loop */
    printf("%d ", i);
}
/* printf("%d", i);   ERROR — i is gone */
```

### Variable Shadowing (Common Trap!)

```c
int value = 100;   /* Global */

void show(void) {
    int value = 50;          /* Local — HIDES the global! */
    printf("%d\n", value);   /* Prints 50, not 100 */
}
```

> **Best Practice:** Avoid naming local variables the same as globals. It causes confusion.

---

## 5. INTERMEDIATE — Storage Classes

Storage classes control **where** and **how long** a variable lives.

### `auto` — Default (You never need to write it)

Every local variable is `auto` by default. Lives on the stack, gone after the function returns.

```c
void counter(void) {
    auto int count = 0;   /* Same as: int count = 0; */
    count++;
    printf("%d\n", count);   /* Always prints 1 — resets every call */
}
```

---

### `static` — Remembers Its Value Between Calls ⭐

A `static` local variable is initialized **once** and **keeps its value** between function calls.

```c
void counter(void) {
    static int count = 0;   /* Initialized only once! */
    count++;
    printf("Called %d times\n", count);
}

int main(void) {
    counter();   /* Called 1 times */
    counter();   /* Called 2 times */
    counter();   /* Called 3 times */
    return 0;
}
```

#### Real-world use: Debounce button press
```c
int is_button_pressed(void) {
    static int last_state = 0;
    int current = read_button_pin();     /* Read hardware pin */

    if (current != last_state) {
        last_state = current;
        return 1;   /* State changed */
    }
    return 0;   /* No change */
}
```

#### `static` on a global/function — limits visibility to one file

```c
/* helper.c */
static int private_counter = 0;     /* Only this file can use it */
static void reset_counter(void) {   /* Private function */
    private_counter = 0;
}
```

---

### `extern` — Share a Variable Across Files

When your program has multiple `.c` files, use `extern` to share variables.

```c
/* config.c — defines the variable */
int max_retries = 5;

/* main.c — uses it */
extern int max_retries;   /* Tells compiler: "it's defined elsewhere" */

int main(void) {
    printf("Max retries: %d\n", max_retries);   /* 5 */
    return 0;
}
```

---

### `register` — Speed Hint (Rarely Used Today)

Asks the compiler to store the variable in a CPU register for faster access. Modern compilers usually do this automatically and ignore this hint.

```c
void sum_array(int *arr, int n) {
    register int i;        /* Ask compiler to keep i in a register */
    register int sum = 0;
    for (i = 0; i < n; i++)
        sum += arr[i];
    printf("Sum: %d\n", sum);
}
```

### Quick Summary Table

| Class | Where stored | Lifetime | Default value | Scope |
|-------|-------------|----------|---------------|-------|
| `auto` | Stack | Function call | Garbage (undefined) | Block |
| `static` (local) | Data segment | Whole program | 0 | Block |
| `static` (global) | Data segment | Whole program | 0 | File only |
| `extern` | Data segment | Whole program | From definition | All files |
| `register` | CPU register | Function call | Garbage | Block |

---

## 6. INTERMEDIATE — Memory: Stack vs Global

### The Big Picture

```
Your program's memory looks like this:

┌──────────────────────────────┐  High address
│          STACK               │  ← Local variables live here
│       (grows down ↓)         │    Created/destroyed on each call
├──────────────────────────────┤
│          HEAP                │  ← malloc/free (not covered here)
├──────────────────────────────┤
│       DATA SEGMENT           │  ← Initialized globals and statics
│  int x = 5;                  │    e.g., static int count = 0;
├──────────────────────────────┤
│       BSS SEGMENT            │  ← Uninitialized globals (auto-zeroed)
│  int y;  (global)            │    e.g., int total;
├──────────────────────────────┤
│       CODE (TEXT)            │  ← Your function code lives here
└──────────────────────────────┘  Low address
```

### What Goes Where?

```c
int global_a = 10;        /* DATA segment — initialized global */
int global_b;             /* BSS segment  — uninitialized global (= 0) */

void my_function(void) {
    int local_x = 5;      /* STACK — local variable */
    static int count = 0; /* DATA segment — static local */

    local_x += 1;   /* Lives on stack, gone after return */
    count++;        /* Persists in data segment */
}
```

### Why This Matters

```c
/* PROBLEM: Big array on stack can crash your program! */
void bad_example(void) {
    int big_array[100000];   /* ~400KB on stack — CRASH! Stack overflow! */
}

/* SOLUTION: Make it static or global */
static int big_array[100000];   /* In data segment — safe */

void good_example(void) {
    /* Use big_array safely */
}
```

### Function Call Stack — Step by Step

```c
int add(int a, int b) {
    int result = a + b;    /* 'result', 'a', 'b' pushed on stack */
    return result;
}                          /* All popped off — stack cleaned up */

int main(void) {
    int x = add(3, 4);    /* Stack grows during call, shrinks after */
    return 0;
}
```

---

## 7. INTERMEDIATE — Call by Value vs Reference

### Call by Value — Passes a Copy

The function gets a **copy** of the value. The original is **not changed**.

```c
void double_it(int n) {
    n = n * 2;             /* Only changes the copy */
    printf("Inside: %d\n", n);
}

int main(void) {
    int num = 5;
    double_it(num);
    printf("Outside: %d\n", num);   /* Still 5 — original unchanged */
    return 0;
}
```

Output:
```
Inside: 10
Outside: 5
```

### Call by Reference — Passes the Address

The function gets a **pointer** to the original. It **can** change the original.

```c
void double_it(int *n) {
    *n = *n * 2;           /* Changes the original via pointer */
}

int main(void) {
    int num = 5;
    double_it(&num);       /* Pass address with & */
    printf("Outside: %d\n", num);   /* Now 10! */
    return 0;
}
```

Output:
```
Outside: 10
```

### Side-by-Side Comparison

```c
/* Call by Value — swap doesn't work */
void swap_val(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}   /* Only swapped local copies */

/* Call by Reference — swap works */
void swap_ref(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}   /* Swapped the actual variables */

int main(void) {
    int x = 3, y = 7;

    swap_val(x, y);
    printf("%d %d\n", x, y);   /* 3 7 — unchanged */

    swap_ref(&x, &y);
    printf("%d %d\n", x, y);   /* 7 3 — swapped! */

    return 0;
}
```

### When to Use Each

| Use Case | Method |
|----------|--------|
| Just read a value | Call by value |
| Need to change the original | Call by reference (pointer) |
| Pass a large struct (avoid copying) | Call by reference (`const *`) |
| Return multiple values | Pointers as out-parameters |

### Example: Return Two Values

```c
/* Two outputs via pointers */
void min_max(int *arr, int n, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main(void) {
    int data[] = {3, 1, 9, 5, 2};
    int lo, hi;
    min_max(data, 5, &lo, &hi);
    printf("Min: %d, Max: %d\n", lo, hi);   /* Min: 1, Max: 9 */
    return 0;
}
```

---

## 8. ADVANCED — Function Pointers

### What is a Function Pointer?

Just like a pointer stores the **address of a variable**, a function pointer stores the **address of a function**.

### Basic Syntax

```c
/* Normal function */
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main(void) {
    /* Declare a function pointer */
    int (*operation)(int, int);

    /* Point it to add */
    operation = add;
    printf("%d\n", operation(5, 3));   /* 8 */

    /* Point it to sub */
    operation = sub;
    printf("%d\n", operation(5, 3));   /* 2 */

    return 0;
}
```

### Simpler with `typedef`

```c
typedef int (*math_fn_t)(int, int);   /* Name the type */

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

void apply(math_fn_t fn, int x, int y) {
    printf("Result: %d\n", fn(x, y));
}

int main(void) {
    apply(add, 4, 5);   /* Result: 9  */
    apply(mul, 4, 5);   /* Result: 20 */
    return 0;
}
```

### Real Use: Menu / Dispatch Table

```c
typedef void (*menu_fn_t)(void);

void new_game(void)  { printf("Starting new game...\n"); }
void load_game(void) { printf("Loading game...\n"); }
void quit_game(void) { printf("Quitting...\n"); }

/* Table of function pointers — indexed by menu choice */
menu_fn_t menu[] = { new_game, load_game, quit_game };

int main(void) {
    int choice = 1;            /* User picks option 1 */
    menu[choice]();            /* Calls load_game() */
    return 0;
}
```

### Light Embedded Example: Callback

```c
typedef void (*event_cb_t)(void);

static event_cb_t button_callback = NULL;

void register_button_handler(event_cb_t cb) {
    button_callback = cb;
}

void on_button_press(void) {   /* Called when button is pressed */
    if (button_callback != NULL)
        button_callback();
}

/* In your application */
void my_action(void) {
    printf("Button was pressed!\n");
}

int main(void) {
    register_button_handler(my_action);
    on_button_press();   /* Triggers my_action */
    return 0;
}
```

---

## 9. ADVANCED — Inline Functions

### What is Inline?

When you call a normal function, the CPU has to:
1. Jump to the function
2. Set up a stack frame
3. Execute the code
4. Jump back

For **tiny, frequently called functions**, this overhead can matter.

`inline` tells the compiler: *"paste the function body directly here, no jump needed."*

### Example

```c
/* Normal call — jumps to function */
int square(int x) {
    return x * x;
}

/* Inline — code pasted in place */
static inline int square_fast(int x) {
    return x * x;
}

int main(void) {
    int a = square(5);       /* CPU jumps to function */
    int b = square_fast(5);  /* Compiler pastes: b = 5 * 5; */
    return 0;
}
```

### When to Use Inline

```c
/* Good candidates for inline — tiny, called often */
static inline int max(int a, int b) { return a > b ? a : b; }
static inline int min(int a, int b) { return a < b ? a : b; }
static inline int clamp(int v, int lo, int hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

/* Usage */
int volume = clamp(user_input, 0, 100);
```

### Inline vs Macro

```c
/* Macro — no type checking, can have side effects */
#define SQUARE(x)  ((x) * (x))
int r = SQUARE(a++);  /* BUG: a++ evaluated twice! */

/* Inline — type safe, no side effects */
static inline int square(int x) { return x * x; }
int r = square(a++);  /* Safe: a++ called once */
```

> **Rule:** Prefer `static inline` over macros for small utility functions.

---

## 10. Common Mistakes & Best Practices

### Common Mistakes

#### Mistake 1: Using a local variable after function returns
```c
/* WRONG — local array disappears after return */
int* make_array(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;   /* BUG: arr is on stack, gone! */
}

/* CORRECT — use static */
int* make_array(void) {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;   /* Safe — lives in data segment */
}
```

---

#### Mistake 2: Forgetting `&` in call by reference
```c
void reset(int *counter) { *counter = 0; }

int main(void) {
    int c = 10;
    reset(c);    /* WRONG — passing value, not address */
    reset(&c);   /* CORRECT — passing address */
    return 0;
}
```

---

#### Mistake 3: Assuming uninitialized local variables are zero
```c
void bad(void) {
    int x;            /* Garbage value on stack — could be anything! */
    printf("%d\n", x);   /* Unpredictable output */
}

void good(void) {
    int x = 0;        /* Always initialize */
    printf("%d\n", x);
}
```

---

#### Mistake 4: Too many global variables
```c
/* BAD — everything global makes code hard to track */
int a, b, c, temp, result, flag, count;  /* Anyone can change these! */

/* GOOD — only share what's necessary, keep others local */
static int internal_count = 0;  /* Only this file needs it */
```

---

#### Mistake 5: Not checking return values
```c
/* BAD */
divide(10, 0, &result);   /* Ignoring error — result is garbage! */

/* GOOD */
if (divide(10, 0, &result) != 0) {
    printf("Error: division by zero\n");
}
```

---

#### Mistake 6: Forgetting NULL check on function pointer
```c
typedef void (*callback_t)(void);
callback_t cb = NULL;

/* BAD — crashes if cb is NULL */
cb();

/* GOOD */
if (cb != NULL)
    cb();
```

---

### Best Practices

| Practice | Reason |
|----------|--------|
| One function = one job | Easier to test and understand |
| Keep functions short (< 50 lines) | Easier to read |
| Always initialize variables | Avoid garbage values |
| Use `const` for read-only parameters | Prevents accidental changes |
| Prefer `static` for private helpers | Hide implementation details |
| Return error codes from functions | Caller knows if something went wrong |
| Use meaningful names | `calc_area()` beats `func1()` |
| Avoid too many globals | Use parameters and return values instead |
| NULL-check before calling function pointers | Prevents crashes |
| Use `static inline` instead of macros | Type-safe, debuggable |

---

### Clean Code Example — Before & After

**Before (messy):**
```c
int x;
void f(int a, int b) {
    x = a+b;
    printf("%d\n",x);
}
```

**After (clean):**
```c
/* Calculate and display the sum of two integers */
void print_sum(int first, int second) {
    int sum = first + second;
    printf("Sum: %d\n", sum);
}
```

---

## Quick Revision Card

```
FUNCTIONS
─────────
Syntax:    return_type name(params) { ... return val; }
Declare:   int add(int a, int b);         ← prototype
Define:    int add(int a, int b) { return a+b; }

SCOPE
─────
Local:     Only inside { } where declared
Global:    Outside all functions — visible everywhere
static:    Persists across calls (local) or file-only (global)
Block:     Limited to { } braces

STORAGE CLASSES
───────────────
auto:      Default. Stack. Gone after function.
static:    Data segment. Persists. Zero-initialized.
extern:    Defined elsewhere. Shared across files.
register:  Hint for CPU register. Rarely used.

CALL BY VALUE vs REFERENCE
──────────────────────────
Value:     Copy passed. Original unchanged. Use for read-only input.
Reference: Address passed. Original can change. Use &var and *param.

FUNCTION POINTERS
─────────────────
typedef void (*fn_t)(void);
fn_t ptr = my_function;
ptr();   ← calls my_function()

INLINE
──────
static inline int sq(int x) { return x*x; }
Use for: tiny, frequently-called utility functions
```

---

*Happy coding! Master these concepts and you're ready for driver-level and embedded C development.*
