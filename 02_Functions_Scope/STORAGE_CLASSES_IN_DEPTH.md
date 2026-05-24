# Storage Classes in C — In-Depth Guide

## Table of Contents
1. [What is a Storage Class?](#1-what-is-a-storage-class)
2. [Memory Architecture Overview](#2-memory-architecture-overview)
3. [auto](#3-auto)
4. [register](#4-register)
5. [static](#5-static)
6. [extern](#6-extern)
7. [Storage Class Comparison Table](#7-storage-class-comparison-table)
8. [Scope vs Lifetime vs Linkage Diagram](#8-scope-vs-lifetime-vs-linkage-diagram)
9. [Multi-File Architecture (extern in action)](#9-multi-file-architecture-extern-in-action)
10. [Common Pitfalls](#10-common-pitfalls)
11. [Quick Reference Card](#11-quick-reference-card)

---

## 1. What is a Storage Class?

A **storage class** defines **three properties** of a variable or function:

```
┌──────────────────────────────────────────────────────────────┐
│                     STORAGE CLASS                            │
│                                                              │
│   ┌─────────────┐   ┌─────────────┐   ┌─────────────────┐  │
│   │   SCOPE     │   │  LIFETIME   │   │    LINKAGE      │  │
│   │             │   │             │   │                 │  │
│   │ Where can   │   │ How long    │   │ Visible across  │  │
│   │ the var be  │   │ does it     │   │ translation     │  │
│   │ accessed?   │   │ live in     │   │ units (.c files)?│  │
│   │             │   │ memory?     │   │                 │  │
│   └─────────────┘   └─────────────┘   └─────────────────┘  │
└──────────────────────────────────────────────────────────────┘
```

**Syntax:**
```c
storage_class  data_type  variable_name;
// Example:
static         int        counter;
extern         float      temperature;
```

---

## 2. Memory Architecture Overview

When a C program runs, the OS gives it a virtual address space split into regions:

```
HIGH ADDRESS
┌──────────────────────────────────────┐
│           KERNEL SPACE               │  ← OS, not accessible
├──────────────────────────────────────┤
│                                      │
│             STACK                    │  ← auto variables, function frames
│         (grows DOWN ↓)               │
│                                      │
│  [frame: main()]                     │
│    int x = 5;    ← auto int x        │
│    char c = 'A'; ← auto char c       │
│  [frame: foo()]                      │
│    int y = 10;   ← auto int y        │
│                                      │
├──────────────────────────────────────┤
│              ↕ free space ↕           │
├──────────────────────────────────────┤
│                                      │
│              HEAP                    │  ← dynamic memory (malloc/free)
│          (grows UP ↑)                │
│                                      │
├──────────────────────────────────────┤
│           BSS SEGMENT                │  ← uninitialized global/static vars
│   static int count;   → 0            │    (zero-initialized by OS)
│   int global_b;       → 0            │
├──────────────────────────────────────┤
│           DATA SEGMENT               │  ← initialized global/static vars
│   static int flag = 1; → 1           │
│   int global_a = 5;    → 5           │
├──────────────────────────────────────┤
│           TEXT SEGMENT               │  ← compiled machine code (read-only)
│   main() { ... }                     │
│   foo()  { ... }                     │
├──────────────────────────────────────┤
│       CONSTANTS / RODATA             │  ← string literals, const globals
│   "Hello World"                      │
│   const int MAX = 100;               │
└──────────────────────────────────────┘
LOW ADDRESS

  ┌──────────────────────────────────────────────────┐
  │ REGISTER STORAGE CLASS → CPU Registers (NOT RAM) │
  │                                                  │
  │  ┌──────────┐  ┌──────────┐  ┌──────────┐       │
  │  │  EAX/RAX │  │  EBX/RBX │  │  ECX/RCX │  ...  │
  │  └──────────┘  └──────────┘  └──────────┘       │
  └──────────────────────────────────────────────────┘
```

---

## 3. `auto`

### Definition
`auto` is the **default** storage class for all local variables. You almost never write the keyword explicitly.

```c
void foo() {
    auto int x = 10;   // explicitly auto — rarely written
    int y = 20;        // implicitly auto — same thing
}
```

### Memory Location
```
STACK
┌─────────────────────────────┐
│  [foo() stack frame]        │
│  ┌────────────────────┐     │
│  │  int x = 10  [4B]  │ ←── auto variable lives here
│  │  int y = 20  [4B]  │ ←── auto variable lives here
│  └────────────────────┘     │
│       ↑ created on call     │
│       ↓ destroyed on return │
└─────────────────────────────┘
```

### Lifetime Diagram
```
Time ───────────────────────────────────────────────────────►

  foo() called         foo() returns
       │                    │
       ▼                    ▼
───────┬────────────────────┬───────────────────────────────
       │  x and y EXIST     │  x and y ARE GONE (memory freed)
       └────────────────────┘
```

### Key Properties
| Property  | Value                        |
|-----------|------------------------------|
| Scope     | Block (inside `{}`)          |
| Lifetime  | Duration of the block        |
| Linkage   | None                         |
| Default   | Garbage value (uninitialized)|
| Memory    | Stack                        |

### Code Example
```c
#include <stdio.h>

void demo_auto() {
    auto int x = 10;    // born here
    printf("x = %d\n", x);
}                       // x dies here — stack frame destroyed

int main() {
    demo_auto();
    // x is inaccessible here
    return 0;
}
```

---

## 4. `register`

### Definition
Hints to the compiler to store the variable in a **CPU register** instead of RAM for faster access. Modern compilers mostly **ignore** this hint and decide themselves.

```c
void loop_example() {
    register int i;        // suggest: keep i in a CPU register
    for (i = 0; i < 1000000; i++) {
        // fast inner loop
    }
}
```

### Memory Location
```
  CPU
  ┌─────────────────────────────────────────┐
  │                                         │
  │  ┌────────┐  ┌────────┐  ┌────────┐    │
  │  │  RAX   │  │  RBX   │  │  RCX   │... │
  │  │ i=0→1  │  │        │  │        │    │
  │  └────────┘  └────────┘  └────────┘    │
  │         Register File                   │
  │         (EXTREMELY fast ~1 cycle)       │
  └─────────────────────────────────────────┘
        vs
  RAM (Stack)  ~100-300 cycles for cache miss
```

### Important Restrictions
```
  ┌──────────────────────────────────────────────────────┐
  │  register int i = 5;                                 │
  │                                                      │
  │  int *ptr = &i;  ← ILLEGAL! Cannot take address      │
  │                    of a register variable            │
  │                    (registers have no memory address)│
  └──────────────────────────────────────────────────────┘
```

### Key Properties
| Property  | Value                              |
|-----------|------------------------------------|
| Scope     | Block (inside `{}`)                |
| Lifetime  | Duration of the block              |
| Linkage   | None                               |
| Default   | Garbage value (uninitialized)      |
| Memory    | CPU Register (or Stack if no reg available) |
| `&` op    | NOT allowed                        |

### Code Example
```c
#include <stdio.h>

long long sum_register(int n) {
    register int i;         // hint: use register for loop counter
    register long long sum = 0;
    for (i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    printf("Sum = %lld\n", sum_register(1000000));
    return 0;
}
```

---

## 5. `static`

`static` has **two different behaviors** depending on where it is used:

### 5a. static Local Variable

```c
void counter() {
    static int count = 0;   // initialized ONCE, persists between calls
    count++;
    printf("Called %d times\n", count);
}
```

#### Memory Layout
```
DATA SEGMENT (permanent storage)
┌────────────────────────────────────────┐
│  static int count = 0                  │ ← initialized once at program start
│  Address: 0x601020  (fixed address)    │ ← stays here for entire program life
└────────────────────────────────────────┘

STACK (per call — temporary)
┌────────────────────────────────────────┐
│  [counter() stack frame]               │
│  (no space for count — it's in data)   │
└────────────────────────────────────────┘
```

#### Lifetime Diagram
```
Program Start                              Program End
     │                                         │
     ▼                                         ▼
─────┬─────────────────────────────────────────┬─────
     │  static count EXISTS in DATA segment    │
     └─────────────────────────────────────────┘
              │          │          │
          call 1      call 2      call 3
          count=1     count=2     count=3
          (scope: only inside counter())
```

### 5b. static Global Variable / Function

Restricts the visibility to the **current file only** (internal linkage).

```c
// file: utils.c
static int helper_flag = 0;    // ONLY visible in utils.c
static void internal_func() {  // ONLY callable from utils.c
    // ...
}
```

#### File Visibility Diagram
```
  file1.c                        file2.c
┌──────────────────────┐       ┌──────────────────────┐
│ static int x = 5;    │       │ extern int x;  ← ERROR│
│                      │       │ // cannot see x!      │
│ int pub_var = 10;    │       │ extern int pub_var; ← OK│
│                      │       │                      │
│ static void helper(){│       │ helper();  ← ERROR   │
│   ...                │       │ // cannot call it!   │
│ }                    │       │                      │
│ void pub_func() {    │       │ pub_func();  ← OK    │
│   ...                │       │                      │
│ }                    │       │                      │
└──────────────────────┘       └──────────────────────┘
        │                               │
        └──────────── linker ───────────┘
             static = NOT exported to linker
```

### Key Properties
| Property              | static Local          | static Global/Function  |
|-----------------------|-----------------------|-------------------------|
| Scope                 | Block only            | File only               |
| Lifetime              | Entire program        | Entire program          |
| Linkage               | None                  | Internal (file-only)    |
| Default value         | Zero-initialized      | Zero-initialized        |
| Memory                | Data / BSS segment    | Data / BSS segment      |

### Code Example — static Local
```c
#include <stdio.h>

void counter() {
    static int count = 0;   // initialized only once
    count++;
    printf("count = %d\n", count);
}

int main() {
    counter();  // count = 1
    counter();  // count = 2
    counter();  // count = 3
    return 0;
}
// Output:
// count = 1
// count = 2
// count = 3
```

### Code Example — static Global
```c
// math_utils.c
#include <stdio.h>

static int internal_state = 0;   // hidden from other files

static int square(int x) {       // private helper
    return x * x;
}

int public_compute(int n) {      // exposed to other files
    internal_state++;
    return square(n) + internal_state;
}
```

---

## 6. `extern`

### Definition
`extern` declares that a variable or function is **defined elsewhere** (in another file or later in the same file). It does **not allocate memory** — it's just a declaration telling the compiler "this exists somewhere."

```c
extern int global_counter;   // declaration — no memory allocated
                             // actual definition is in another .c file
```

### How extern Works — Compilation and Linking
```
SOURCE FILES                   OBJECT FILES            EXECUTABLE
─────────────────────────────────────────────────────────────────

  main.c                         main.o
┌──────────────────┐   compile  ┌──────────────────┐
│ extern int x;    │ ─────────► │ UNDEFINED REF: x │ ─────┐
│ int main() {     │            │ UNDEFINED REF:   │      │
│   printf("%d",x);│            │   print_value    │      │  LINKER
│   print_value(); │            └──────────────────┘      │  resolves
└──────────────────┘                                       │  symbols
                                                           ▼
  globals.c                      globals.o           ┌──────────────┐
┌──────────────────┐   compile  ┌──────────────────┐ │  program.exe │
│ int x = 42;      │ ─────────► │ DEFINES: x       │ │              │
│                  │            │                  │ │ x → 42       │
│ void print_value │            │ DEFINES:         │ │              │
│ () {             │            │   print_value    │ │ works!       │
│   printf("%d",x);│            └──────────────────┘ └──────────────┘
│ }                │
└──────────────────┘
```

### Declaration vs Definition
```
  extern int x;          // DECLARATION — "x exists somewhere, trust me"
                         //   No memory allocated
                         //   Can appear many times

  int x = 10;            // DEFINITION — "x is HERE, allocate memory"
                         //   Memory allocated
                         //   Must appear exactly ONCE across all files
```

### extern in the Same File (forward declaration)
```c
#include <stdio.h>

extern int value;        // forward declaration — defined below main()

int main() {
    printf("%d\n", value);   // works because of extern declaration
    return 0;
}

int value = 100;         // actual definition
```

### Key Properties
| Property  | Value                                    |
|-----------|------------------------------------------|
| Scope     | From declaration to end of file          |
| Lifetime  | Entire program                           |
| Linkage   | External (visible across files)          |
| Memory    | Data / BSS segment (at definition site)  |
| Allocation| NO — extern only declares, not defines   |

### Code Example — Multi-file
```c
// ── config.c ──────────────────────────────
int MAX_CONNECTIONS = 100;      // DEFINED here
float timeout = 30.5f;          // DEFINED here

void reset_config() {
    MAX_CONNECTIONS = 100;
    timeout = 30.5f;
}

// ── network.c ─────────────────────────────
extern int MAX_CONNECTIONS;     // DECLARED — uses config.c's definition
extern float timeout;           // DECLARED — uses config.c's definition

void connect() {
    if (MAX_CONNECTIONS > 0) {
        // use the shared global
    }
}

// ── main.c ────────────────────────────────
extern int MAX_CONNECTIONS;     // same declaration in main.c too
extern void reset_config();     // extern on function (optional but valid)

int main() {
    reset_config();
    printf("Max: %d\n", MAX_CONNECTIONS);
    return 0;
}
```

---

## 7. Storage Class Comparison Table

```
┌──────────────┬──────────────┬──────────────────┬──────────────────┬──────────────┬───────────────┐
│   Storage    │   Keyword    │     Scope        │    Lifetime      │   Linkage    │ Memory Region │
│   Class      │              │                  │                  │              │               │
├──────────────┼──────────────┼──────────────────┼──────────────────┼──────────────┼───────────────┤
│  Automatic   │  auto        │  Block           │  Block duration  │  None        │  Stack        │
│              │  (default)   │                  │                  │              │               │
├──────────────┼──────────────┼──────────────────┼──────────────────┼──────────────┼───────────────┤
│  Register    │  register    │  Block           │  Block duration  │  None        │  CPU Register │
│              │              │                  │                  │              │  (or Stack)   │
├──────────────┼──────────────┼──────────────────┼──────────────────┼──────────────┼───────────────┤
│  Static      │  static      │  Block           │  Entire program  │  None        │  Data/BSS     │
│  (local)     │  (local var) │  (local only)    │                  │              │               │
├──────────────┼──────────────┼──────────────────┼──────────────────┼──────────────┼───────────────┤
│  Static      │  static      │  File            │  Entire program  │  Internal    │  Data/BSS     │
│  (global)    │  (global var)│  (current file)  │                  │  (file-only) │               │
├──────────────┼──────────────┼──────────────────┼──────────────────┼──────────────┼───────────────┤
│  External    │  extern      │  File & beyond   │  Entire program  │  External    │  Data/BSS     │
│              │              │  (all files)     │                  │  (all files) │  (at def site)│
└──────────────┴──────────────┴──────────────────┴──────────────────┴──────────────┴───────────────┘

Default initialization:
  auto / register  →  GARBAGE (undefined behavior if read before write)
  static / extern  →  ZERO   (0 for int, 0.0 for float, NULL for pointers)
```

---

## 8. Scope vs Lifetime vs Linkage Diagram

```
SCOPE — "Where in source code can this name be used?"
──────────────────────────────────────────────────────

int g = 1;          ◄── file scope (global)
                    │
┌── main() {        │
│   int a = 2;  ◄── block scope (local to main)
│                   │
│   ┌── if (...) {  │
│   │   int b = 3;  ◄── inner block scope
│   │               │   (b not visible outside {})
│   └── }           │
│                   │
└── }               │


LIFETIME — "When in RUNTIME does the memory exist?"
──────────────────────────────────────────────────────

Program Execution Timeline:
────────────────────────────────────────────────────────►
 │                                                       │
 │← static/extern ──────────────────────────────────────►│
 │         (entire program duration)                      │
 │                                                        │
 │    │← auto/register ──►│    │← auto/register ──►│     │
 │       (per function call)       (per function call)    │
 │                                                        │
start                                                    end


LINKAGE — "Which translation units (files) can see this name?"
──────────────────────────────────────────────────────────────

  No Linkage    →  Only this scope (local vars)
  Internal      →  Only this file (static globals)
  External      →  Any file (globals, extern)

  file_a.c          file_b.c          file_c.c
  ─────────         ─────────         ─────────
  int x=1;  ←────────────────────────────────── external linkage
  static    ←── only file_a.c can see this       internal linkage
  int y=2;
  void f(){
    int z;    ←── only inside f()                no linkage
  }
```

---

## 9. Multi-File Architecture (extern in action)

A realistic embedded/driver-style multi-file project:

```
PROJECT STRUCTURE
──────────────────────────────────────────────────────────────
  main.c          →  entry point, calls init and run
  config.c        →  global configuration values (DEFINED here)
  config.h        →  extern declarations for other files to include
  driver.c        →  hardware driver using config values
──────────────────────────────────────────────────────────────


config.h  (HEADER — only declarations)
┌──────────────────────────────────────┐
│  #ifndef CONFIG_H                    │
│  #define CONFIG_H                    │
│                                      │
│  extern int   BAUD_RATE;             │ ← tells compiler: "exists somewhere"
│  extern float CLOCK_MHZ;             │
│  extern char  DEVICE_NAME[32];       │
│                                      │
│  #endif                              │
└──────────────────────────────────────┘
                 │
    ┌────────────┼────────────┐
    ▼            ▼            ▼
 config.c      main.c      driver.c
 (DEFINES)    (uses)       (uses)

config.c  (DEFINITIONS — memory allocated here)
┌──────────────────────────────────────┐
│  #include "config.h"                 │
│                                      │
│  int   BAUD_RATE = 115200;           │ ← actual memory allocated
│  float CLOCK_MHZ = 48.0f;           │
│  char  DEVICE_NAME[32] = "STM32";   │
└──────────────────────────────────────┘

main.c
┌──────────────────────────────────────┐
│  #include "config.h"                 │ ← gets extern declarations
│                                      │
│  int main() {                        │
│    printf("%d\n", BAUD_RATE);        │ ← linker resolves to config.c
│    return 0;                         │
│  }                                   │
└──────────────────────────────────────┘

driver.c
┌──────────────────────────────────────┐
│  #include "config.h"                 │ ← gets extern declarations
│  static int driver_state = 0;        │ ← private to driver.c only
│                                      │
│  void init_driver() {                │
│    driver_state = BAUD_RATE / 100;   │ ← uses shared extern
│  }                                   │
└──────────────────────────────────────┘

LINKER VIEW:
┌─────────────────────────────────────────────────────┐
│                                                     │
│  config.o  → exports: BAUD_RATE, CLOCK_MHZ,        │
│                        DEVICE_NAME                  │
│                                                     │
│  main.o    → imports: BAUD_RATE                     │
│                                                     │
│  driver.o  → imports: BAUD_RATE                     │
│              does NOT export: driver_state (static) │
│                                                     │
│  Linker connects imports → exports → program.exe    │
└─────────────────────────────────────────────────────┘
```

---

## 10. Common Pitfalls

### Pitfall 1 — Forgetting static loses state
```c
// WRONG — count resets every call
int broken_counter() {
    int count = 0;      // reinitialized every time!
    return ++count;     // always returns 1
}

// CORRECT — count persists
int working_counter() {
    static int count = 0;
    return ++count;     // 1, 2, 3, 4...
}
```

### Pitfall 2 — Multiple definitions with extern
```c
// BAD — defining the same variable in two files causes linker error
// file_a.c:  int x = 5;
// file_b.c:  int x = 10;   ← LINKER ERROR: multiple definition of x

// GOOD — define once, declare with extern in others
// file_a.c:  int x = 5;          ← one definition
// file_b.c:  extern int x;       ← declaration only
```

### Pitfall 3 — Taking address of register variable
```c
register int speed = 100;
int *ptr = &speed;      // COMPILE ERROR — no address for register vars
printf("%d", *ptr);     // would crash anyway
```

### Pitfall 4 — Global vs static global naming conflict
```c
// file_a.c
int result = 0;         // external linkage — visible everywhere

// file_b.c
static int result = 0;  // internal linkage — different variable, same name
                        // Both exist independently — can cause confusion!
```

### Pitfall 5 — Assuming auto variables are zero
```c
void risky() {
    int x;              // auto — GARBAGE VALUE on stack
    if (x > 0) {        // UNDEFINED BEHAVIOR — x is uninitialized
        // ...
    }
}

void safe() {
    int x = 0;          // always initialize auto variables
    if (x > 0) {
        // ...
    }
}
```

---

## 11. Quick Reference Card

```
┌──────────────────────────────────────────────────────────────────┐
│                   STORAGE CLASSES QUICK CARD                     │
├───────────┬──────────┬───────────────────────────────────────────┤
│  Keyword  │ Where?   │ Use it when...                            │
├───────────┼──────────┼───────────────────────────────────────────┤
│  auto     │ local    │ Default local variable (rarely written    │
│           │          │ explicitly)                               │
├───────────┼──────────┼───────────────────────────────────────────┤
│  register │ local    │ Performance-critical loop counters        │
│           │          │ (modern compilers mostly ignore this)     │
├───────────┼──────────┼───────────────────────────────────────────┤
│  static   │ local    │ Need to retain value between calls        │
│           │          │ (e.g., counters, state machines)          │
├───────────┼──────────┼───────────────────────────────────────────┤
│  static   │ global   │ Want to hide variable/function from       │
│           │ or func  │ other files (encapsulation in C)          │
├───────────┼──────────┼───────────────────────────────────────────┤
│  extern   │ global   │ Share a variable/function defined in      │
│           │          │ another .c file (multi-file projects)     │
└───────────┴──────────┴───────────────────────────────────────────┘

MEMORY REGION CHEAT SHEET:
  Stack   → fast, temporary, auto-managed   (auto, register)
  Data    → permanent, initialized          (static with init, extern with init)
  BSS     → permanent, zero-filled          (static no init, extern no init)
  Register→ fastest, no address, tiny       (register hint)

INITIALIZATION DEFAULT:
  auto / register  →  ❌ GARBAGE (always initialize manually!)
  static / extern  →  ✅ ZERO    (0, 0.0, NULL automatically)
```

---

*Document created for C-Learning curriculum — 02_Functions_Scope*
