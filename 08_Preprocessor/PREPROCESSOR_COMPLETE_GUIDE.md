# C Preprocessor Directives — Complete Training Manual, Reference Guide & Interview Handbook

> **Audience:** College Students · Software Engineers · Embedded Engineers · Firmware Developers · Linux System Programmers · Device Driver Developers · Automotive Engineers  
> **Level:** Beginner → Expert  
> **Author:** Senior C Programming Trainer

---

## Table of Contents

1. [Introduction to C Preprocessor](#1-introduction-to-c-preprocessor)
2. [C Compilation Stages](#2-c-compilation-stages)
3. [Preprocessor Directives Overview](#3-preprocessor-directives-overview)
4. [File Inclusion Directives](#4-file-inclusion-directives)
5. [Macro Definitions](#5-macro-definitions)
6. [Macros In Depth](#6-macros-in-depth)
7. [Conditional Compilation](#7-conditional-compilation)
8. [Header File Protection](#8-header-file-protection)
9. [Special Predefined Macros](#9-special-predefined-macros)
10. [Operator Macros — # and ##](#10-operator-macros----and-)
11. [Undefining Macros — #undef](#11-undefining-macros---undef)
12. [Error and Warning Directives](#12-error-and-warning-directives)
13. [Pragmas](#13-pragmas)
14. [Advanced Preprocessor Concepts](#14-advanced-preprocessor-concepts)
15. [Header Files In Depth](#15-header-files-in-depth)
16. [Embedded C Applications](#16-embedded-c-applications)
17. [Linux and System Programming Applications](#17-linux-and-system-programming-applications)
18. [Common Macro Problems](#18-common-macro-problems)
19. [Macros vs Functions](#19-macros-vs-functions)
20. [#define vs const](#20-define-vs-const)
21. [30 Practical C Programs](#21-30-practical-c-programs)
    - [Beginner Programs (1–10)](#beginner-programs-110)
    - [Intermediate Programs (11–20)](#intermediate-programs-1120)
    - [Advanced Programs (21–30)](#advanced-programs-2130)
22. [50+ Interview Questions & Answers](#22-50-interview-questions--answers)
23. [Tricky Interview Questions](#23-tricky-interview-questions)
24. [Real-World Case Studies](#24-real-world-case-studies)
25. [Common Mistakes](#25-common-mistakes)
26. [Best Practices](#26-best-practices)
27. [Memory Diagrams & Flowcharts](#27-memory-diagrams--flowcharts)
28. [Learning & Interview Preparation Roadmap](#28-learning--interview-preparation-roadmap)

---

## 1. Introduction to C Preprocessor

### What is a Preprocessor?

The **C Preprocessor (cpp)** is a text-substitution tool that runs **before** the actual C compiler. It processes special directives (lines beginning with `#`) and transforms the source code before any compilation occurs.

The preprocessor does **not** understand C syntax or types — it operates purely on text tokens.

```
Source file (.c) → [Preprocessor] → Expanded source → [Compiler] → Object code
```

### Role of the Preprocessor

| Role | Example |
|------|---------|
| File inclusion | `#include <stdio.h>` → pastes the entire header |
| Macro substitution | `MAX(a,b)` → `((a)>(b)?(a):(b))` |
| Conditional compilation | `#ifdef DEBUG` → include/exclude blocks |
| Error generation | `#error "Unsupported platform"` |
| Pragma instructions | `#pragma pack(1)` — pack structures |

### Importance in Software Development

- Eliminates code duplication through reusable macros.
- Enables **platform-specific** code within a single source file.
- Provides **compile-time configuration** — no runtime overhead.
- Foundation of **header-based API design** in C.
- Critical in **embedded systems** for register maps and HAL layers.
- Powers **Linux kernel** macros that generate code automatically.

### Real-World Applications

| Domain | Use |
|--------|-----|
| Embedded firmware | Register address macros, bit-field manipulation |
| Linux kernel | `container_of()`, `EXPORT_SYMBOL()`, module macros |
| Automotive (AUTOSAR) | Feature flags, memory section macros |
| Cross-platform libs | `#ifdef _WIN32` / `#elif __linux__` |
| RTOS (FreeRTOS) | `configUSE_PREEMPTION`, task configuration macros |
| Game engines | Debug/release build toggles |

---

## 2. C Compilation Stages

### Complete Flow

```
Source File (.c)
      │
      ▼  Stage 1: Preprocessing  (cpp)
Expanded Source (.i)
      │
      ▼  Stage 2: Compilation    (cc1)
Assembly File (.s)
      │
      ▼  Stage 3: Assembly       (as)
Object File (.o)
      │
      ▼  Stage 4: Linking        (ld)
Executable (.out / .exe)
```

### Stage Details

#### Stage 1 — Preprocessing
- Handled by `cpp` (C Preprocessor).
- Processes all `#` directives.
- Expands macros, pastes included files, evaluates conditions.
- Produces a `.i` file (intermediate).
- **Inspect it:** `gcc -E main.c -o main.i`

```c
// Before preprocessing:
#define PI 3.14159
float area = PI * r * r;

// After preprocessing (in main.i):
float area = 3.14159 * r * r;
```

#### Stage 2 — Compilation
- Converts C code to architecture-specific assembly.
- Performs syntax checking, type checking, optimization.
- Produces a `.s` file.
- **Inspect it:** `gcc -S main.c -o main.s`

#### Stage 3 — Assembly
- Converts assembly text to machine code (binary).
- Produces a `.o` (object) file with relocatable binary.
- **Inspect it:** `gcc -c main.c -o main.o`

#### Stage 4 — Linking
- Combines multiple `.o` files.
- Resolves external symbol references.
- Links with standard/system libraries (`libc.a`, `libm.so`).
- Produces the final executable.
- **Command:** `gcc main.o utils.o -o myapp`

### Compilation Flowchart

```
┌─────────────────────────────────────────────────┐
│                  main.c                         │
│  #include <stdio.h>                             │
│  #define MAX 100                                │
│  int main() { ... }                             │
└──────────────────┬──────────────────────────────┘
                   │  gcc -E
                   ▼
┌─────────────────────────────────────────────────┐
│  main.i  (preprocessed)                         │
│  [full stdio.h contents pasted here]            │
│  int main() { ... /* MAX replaced with 100 */ } │
└──────────────────┬──────────────────────────────┘
                   │  gcc -S
                   ▼
┌────────────────────────┐
│  main.s  (assembly)    │
│  movl $100, %eax       │
│  ...                   │
└──────────┬─────────────┘
           │  gcc -c
           ▼
┌────────────────────────┐
│  main.o  (object)      │
│  [binary machine code] │
└──────────┬─────────────┘
           │  gcc (linker)
           ▼
┌────────────────────────┐
│  a.out / myapp         │
│  [final executable]    │
└────────────────────────┘
```

---

## 3. Preprocessor Directives Overview

### What are Directives?

Preprocessor directives are instructions to the preprocessor. They:
- Begin with `#` as the **first non-whitespace character** on a line.
- Do **not** end with a semicolon `;`.
- Are processed **before** compilation.
- Are **not** C statements.

### Complete Directive Reference

| Directive | Purpose |
|-----------|---------|
| `#include` | Include another file |
| `#define` | Define a macro |
| `#undef` | Remove a macro |
| `#if` | Conditional compilation (expression) |
| `#ifdef` | Conditional if macro defined |
| `#ifndef` | Conditional if macro not defined |
| `#elif` | Else-if in conditional |
| `#else` | Else in conditional |
| `#endif` | End conditional block |
| `#error` | Emit a compile-time error |
| `#warning` | Emit a compile-time warning (GCC) |
| `#pragma` | Compiler-specific instructions |
| `#line` | Override line number and filename in errors |

### Syntax Rules

```c
#define PI 3.14159       // No semicolon
#include <stdio.h>       // No semicolon
#define SQUARE(x) ((x)*(x))   // No semicolon

// Multi-line macro uses backslash continuation:
#define PRINT_INFO(name) \
    printf("Name: %s\n", (name))

// Directives can be indented (C99+):
#ifdef DEBUG
    #define LOG(x) printf(x)
#else
    #define LOG(x)
#endif
```

---

## 4. File Inclusion Directives

### #include

Pastes the **entire contents** of the specified file at the point of the directive before compilation.

```c
#include <stdio.h>    // System header — searches system include paths
#include "mylib.h"    // User header  — searches current directory first
```

### Difference: Angle Brackets vs Quotes

| Form | Search Order |
|------|-------------|
| `#include <file.h>` | System paths only (`/usr/include`, compiler dirs) |
| `#include "file.h"` | Current directory first, then system paths |

**Rule of thumb:**
- `<...>` for standard library and third-party installed headers.
- `"..."` for your own project headers.

### Header Search Path

```bash
# View default include paths (GCC):
gcc -v -x c /dev/null -fsyntax-only

# Add custom include path:
gcc -I./include -I../common main.c

# On Linux, system paths typically include:
# /usr/include
# /usr/local/include
# /usr/lib/gcc/x86_64-linux-gnu/XX/include
```

### Nested Includes

Header A can include Header B which includes Header C:
```
main.c
  └── #include "app.h"
        └── #include "config.h"
              └── #include "platform.h"
```
This is valid but can cause **multiple inclusion** problems — solved by include guards (see Section 8).

### Interview Questions on #include

**Q1:** Can you include the same header twice?  
**A:** Without include guards, yes — you'll get "redefinition" errors. With `#ifndef` guards or `#pragma once`, the second inclusion is ignored.

**Q2:** What does the preprocessor do with `#include`?  
**A:** It literally copies and pastes the entire file content at that line in the source file.

**Q3:** What happens if an included file is not found?  
**A:** Fatal compile error: `fatal error: myheader.h: No such file or directory`.

---

## 5. Macro Definitions

### #define — Object-Like Macros

A simple text replacement:

```c
#define PI          3.14159265358979
#define MAX_SIZE    100
#define TRUE        1
#define FALSE       0
#define NEWLINE     '\n'
#define MSG         "Hello, World!"

// Usage:
float area = PI * r * r;           // → float area = 3.14159265358979 * r * r;
int arr[MAX_SIZE];                  // → int arr[100];
```

### #define — Function-Like Macros

Take parameters — expanded inline:

```c
#define SQUARE(x)       ((x) * (x))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define ABS(x)          ((x) < 0 ? -(x) : (x))
#define SWAP(a, b, T)   do { T _t = (a); (a) = (b); (b) = _t; } while(0)

// Usage:
int s = SQUARE(5);       // → int s = ((5) * (5));
int m = MAX(3, 7);       // → int m = ((3) > (7) ? (3) : (7));
```

**Critical: Always wrap parameters AND the whole expression in parentheses!**

```c
// WRONG — operator precedence bug:
#define SQUARE_WRONG(x)  x * x
int r = SQUARE_WRONG(2 + 3);  // → 2 + 3 * 2 + 3 = 11 (not 25!)

// CORRECT:
#define SQUARE(x)  ((x) * (x))
int r = SQUARE(2 + 3);        // → ((2+3) * (2+3)) = 25
```

### Multi-Line Macros

Use `\` at end of each line (no space after `\`):

```c
#define PRINT_HEADER() \
    printf("======================\n"); \
    printf("  My Application v1.0 \n"); \
    printf("======================\n")

// Better — use do-while(0) to make it a single statement:
#define INIT_ARRAY(arr, size, val) \
    do { \
        for (int _i = 0; _i < (size); _i++) \
            (arr)[_i] = (val); \
    } while(0)
```

### Macro Expansion Process

The preprocessor replaces each occurrence before compilation. No type checking, no scope, no function call overhead.

```c
#define ADD(a, b)  ((a) + (b))

// Source:
int result = ADD(x * 2, y + 1);

// After expansion:
int result = ((x * 2) + (y + 1));
```

### Advantages and Disadvantages of Macros

| Advantage | Disadvantage |
|-----------|-------------|
| Zero runtime overhead (inlined) | No type checking |
| Works across all types (generic) | Hard to debug (no line info after expansion) |
| Can generate code | Side effects from multiple evaluation |
| Enables conditional compilation | Can conflict with variable names |
| No function call overhead | Poor readability for complex macros |

---

## 6. Macros In Depth

### Parameterized Macros — Safety Rules

```c
// Rule 1: Parenthesize every parameter
#define CUBE(x)  ((x) * (x) * (x))   // Correct

// Rule 2: Parenthesize entire expression
#define HALF(x)  ((x) / 2)            // Correct
// Without outer parens:  HALF(a + b) * 2 → a + b / 2 * 2  WRONG!

// Rule 3: Use do-while(0) for multi-statement macros
#define ASSERT_POS(x) \
    do { \
        if ((x) <= 0) { \
            fprintf(stderr, "ASSERT: " #x " not positive\n"); \
            abort(); \
        } \
    } while(0)
```

### Nested Macros

Macros can reference other macros:

```c
#define PI      3.14159
#define TWO_PI  (2 * PI)          // Uses PI
#define RAD(d)  ((d) * PI / 180)  // Degrees to radians

double circumference = TWO_PI * r;
double rad = RAD(90);   // → ((90) * 3.14159 / 180)
```

### Recursive Macro Limitations

The C preprocessor **does not support recursion**. A macro that references itself is NOT re-expanded:

```c
#define MACRO  MACRO + 1   // MACRO expands to "MACRO + 1", stops there
// Not infinite — preprocessor marks macro as being-expanded
```

### Side Effects in Macros — Multiple Evaluation Problem

```c
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

int x = 5;
int result = MAX(x++, 3);
// Expands to: ((x++) > (3) ? (x++) : (3))
// x is incremented TWICE if x > 3 — undefined behavior!

// SOLUTION: Use inline functions or temporary variables:
static inline int max_int(int a, int b) { return a > b ? a : b; }
```

### Expression Evaluation Issues

```c
// Problem: without outer parens, used in multiplication
#define DOUBLE(x)  (x) + (x)     // MISSING outer parens!
int result = DOUBLE(3) * 2;
// Expands to: (3) + (3) * 2 = 3 + 6 = 9   (expected 12!)

// Fix:
#define DOUBLE(x)  ((x) + (x))
int result = DOUBLE(3) * 2;      // ((3) + (3)) * 2 = 12  Correct
```

### Best Practices

```c
// 1. Use ALL_CAPS for macro names
#define BUFFER_SIZE  1024

// 2. Wrap params and expression in parens
#define MUL(a, b)  ((a) * (b))

// 3. Use do-while(0) for multi-statement macros
#define SWAP(a, b)  do { int _t = (a); (a) = (b); (b) = _t; } while(0)

// 4. Prefer inline functions for type safety (C99+)
static inline int square(int x) { return x * x; }

// 5. Document complex macros
/* CLAMP(val, lo, hi): Returns val clamped to [lo, hi] */
#define CLAMP(val, lo, hi)  ((val) < (lo) ? (lo) : (val) > (hi) ? (hi) : (val))
```

---

## 7. Conditional Compilation

### Directives

```c
#if    <constant-expression>   // If expression is non-zero
#ifdef <macro>                 // If macro IS defined
#ifndef <macro>                // If macro is NOT defined
#elif  <constant-expression>   // Else-if
#else                          // Else
#endif                         // End of conditional block
```

### Platform-Specific Code

```c
#include <stdio.h>

void platform_init(void) {
#if defined(_WIN32) || defined(_WIN64)
    printf("Initializing Windows platform\n");
    // Windows-specific initialization
#elif defined(__linux__)
    printf("Initializing Linux platform\n");
    // Linux-specific initialization
#elif defined(__APPLE__)
    printf("Initializing macOS platform\n");
#else
    #error "Unsupported platform!"
#endif
}
```

### Debug vs Release Builds

```c
// Compile with: gcc -DDEBUG main.c  (debug build)
// Compile with: gcc main.c          (release build)

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DBG_PRINT(fmt, ...)   // Empty — optimized out in release
#endif

int main(void) {
    int x = 42;
    DBG_PRINT("x = %d", x);   // Only prints in debug build
    return 0;
}
```

### Architecture-Based Compilation

```c
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH "x86-64"
    #define WORD_SIZE 64
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH "x86-32"
    #define WORD_SIZE 32
#elif defined(__arm__)
    #define ARCH "ARM"
    #define WORD_SIZE 32
#elif defined(__aarch64__)
    #define ARCH "ARM64"
    #define WORD_SIZE 64
#else
    #define ARCH "Unknown"
    #define WORD_SIZE 0
#endif
```

### Feature Flags

```c
// In config.h:
#define FEATURE_BLUETOOTH   1
#define FEATURE_WIFI        0
#define FEATURE_DISPLAY     1

// In main.c:
#if FEATURE_BLUETOOTH
    bluetooth_init();
#endif

#if FEATURE_WIFI
    wifi_init();
#endif
```

---

## 8. Header File Protection

### The Multiple Inclusion Problem

Without protection, including a header twice causes redefinition errors:

```c
// header.h (no protection):
typedef struct { int x; } Point;
int global_count;

// main.c:
#include "header.h"
#include "header.h"   // ERROR: 'Point' redefined, 'global_count' redefined
```

### Include Guards (#ifndef / #define / #endif)

```c
// header.h — with include guard:
#ifndef HEADER_H
#define HEADER_H

typedef struct { int x; int y; } Point;
void point_init(Point *p, int x, int y);

#endif  /* HEADER_H */
```

**How it works:**
1. First inclusion: `HEADER_H` not defined → defines it → processes contents.
2. Second inclusion: `HEADER_H` already defined → `#ifndef` is false → entire block skipped.

### Naming Convention for Include Guards

```c
// Convention: <PROJECT>_<PATH>_<FILENAME>_H
// For:  include/drivers/uart.h
#ifndef MYPROJECT_DRIVERS_UART_H
#define MYPROJECT_DRIVERS_UART_H
// ...
#endif
```

### #pragma once

Simpler alternative supported by all modern compilers (GCC, Clang, MSVC):

```c
#pragma once

typedef struct { int x; int y; } Point;
void point_init(Point *p, int x, int y);
```

### Comparison: Include Guards vs #pragma once

| Factor | `#ifndef` Guards | `#pragma once` |
|--------|-----------------|----------------|
| Standard | C Standard (portable) | Non-standard (but universally supported) |
| Syntax | Verbose (3 lines) | One line |
| Hard links | Works correctly | May fail with filesystem hard links |
| Reliability | Always correct | Compiler-dependent |
| Industry use | Kernel, embedded | Application code, game engines |

**Industry practice:** Linux kernel uses `#ifndef`; most application code uses `#pragma once`.

---

## 9. Special Predefined Macros

### Standard Predefined Macros

| Macro | Type | Value / Meaning |
|-------|------|----------------|
| `__FILE__` | `char *` | Name of current source file as a string |
| `__LINE__` | `int` | Current line number |
| `__DATE__` | `char *` | Compilation date: `"Jun 30 2026"` |
| `__TIME__` | `char *` | Compilation time: `"14:30:00"` |
| `__func__` | `char *` | Current function name (C99) |
| `__STDC__` | `int` | `1` if compiler conforms to ISO C |
| `__STDC_VERSION__` | `long` | C standard version: `199901L`, `201112L`, `201710L` |

### Usage Examples

```c
#include <stdio.h>

// Logging macro using predefined macros:
#define LOG(level, msg) \
    printf("[%s] %s:%d in %s(): %s\n", (level), __FILE__, __LINE__, __func__, (msg))

void compute(void) {
    LOG("INFO", "Starting computation");
    // ...
    LOG("INFO", "Computation done");
}

int main(void) {
    printf("Built on: %s at %s\n", __DATE__, __TIME__);
    printf("C Standard: %ld\n", __STDC_VERSION__);
    compute();
    return 0;
}
```

**Output:**
```
Built on: Jun 30 2026 at 14:30:00
C Standard: 201710
[INFO] main.c:8 in compute(): Starting computation
[INFO] main.c:10 in compute(): Computation done
```

### Compiler-Specific Predefined Macros

| Macro | Compiler | Meaning |
|-------|----------|---------|
| `__GNUC__` | GCC | GCC major version |
| `__clang__` | Clang | Defined if using Clang |
| `_MSC_VER` | MSVC | MSVC version number |
| `__COUNTER__` | GCC/Clang/MSVC | Unique integer, increments each use |
| `__PRETTY_FUNCTION__` | GCC | Full function signature |
| `__TIMESTAMP__` | GCC/MSVC | Last modification time of source file |

---

## 10. Operator Macros — # and ##

### Stringizing Operator (#)

Converts a macro argument to a **string literal**:

```c
#define TO_STRING(x)   #x

printf("%s\n", TO_STRING(Hello World));   // Output: Hello World
printf("%s\n", TO_STRING(3 + 4));         // Output: 3 + 4
printf("%s\n", TO_STRING(int));           // Output: int
```

**Practical use — print variable name and value:**
```c
#define PRINT_VAR(var)  printf(#var " = %d\n", (var))

int temperature = 42;
PRINT_VAR(temperature);   // Output: temperature = 42
```

### Token Pasting Operator (##)

Concatenates two tokens into one:

```c
#define CONCAT(a, b)   a##b

int CONCAT(my, Var) = 10;   // → int myVar = 10;
CONCAT(pri, ntf)("Hello\n"); // → printf("Hello\n");
```

**Dynamic variable naming:**
```c
#define MAKE_VAR(type, name, num)   type name##num

MAKE_VAR(int, sensor, 1) = 100;   // → int sensor1 = 100;
MAKE_VAR(int, sensor, 2) = 200;   // → int sensor2 = 200;
```

**Embedded register generation:**
```c
#define GPIO_PORT(n)   GPIO##n

#define GPIO_SET(port, pin)  (GPIO_PORT(port)->ODR |= (1U << (pin)))

GPIO_SET(A, 5);   // → (GPIOA->ODR |= (1U << (5)));
GPIO_SET(B, 3);   // → (GPIOB->ODR |= (1U << (3)));
```

### Combining # and ##

```c
#define REGISTER_HANDLER(event) \
    void handle_##event(void); \
    static const char *event##_name = #event

REGISTER_HANDLER(click);
// Expands to:
// void handle_click(void);
// static const char *click_name = "click";
```

---

## 11. Undefining Macros — #undef

### Syntax and Usage

```c
#undef MACRO_NAME
```

Removes a previously defined macro so it is no longer recognized.

### When and Why to Use #undef

```c
// 1. Override a library definition:
#include <some_lib.h>    // defines MAX as 100
#undef MAX
#define MAX 256          // Override with our value

// 2. Limit scope of a macro:
#define TEMP_BUFFER_SIZE  512
char buf[TEMP_BUFFER_SIZE];
// ... use buffer ...
#undef TEMP_BUFFER_SIZE  // Prevent accidental use below

// 3. Redefine for different sections:
#define SECTION  "header"
// ... process header ...
#undef SECTION
#define SECTION  "body"
// ... process body ...
#undef SECTION
```

### Practical Example — Configuration Override

```c
// default_config.h:
#define BAUD_RATE   9600
#define TIMEOUT_MS  1000

// custom_config.h:
#include "default_config.h"
#undef BAUD_RATE
#define BAUD_RATE   115200   // Override for high-speed UART
```

---

## 12. Error and Warning Directives

### #error — Compile-Time Fatal Error

```c
#error "message"
// Stops compilation immediately with the given message
```

**Version checking:**
```c
#if __STDC_VERSION__ < 199901L
    #error "This code requires C99 or later. Compile with -std=c99"
#endif
```

**Platform validation:**
```c
#if !defined(__linux__) && !defined(_WIN32) && !defined(__APPLE__)
    #error "Unsupported platform. Only Linux, Windows, and macOS are supported."
#endif
```

**Configuration validation:**
```c
#if BUFFER_SIZE < 64
    #error "BUFFER_SIZE must be at least 64 bytes"
#endif

#if (SAMPLE_RATE != 8000) && (SAMPLE_RATE != 16000) && (SAMPLE_RATE != 44100)
    #error "SAMPLE_RATE must be 8000, 16000, or 44100 Hz"
#endif
```

### #warning — Compile-Time Warning (GCC/Clang)

```c
#warning "message"
// Prints warning but continues compilation
```

```c
#ifndef SECURITY_KEY
    #warning "SECURITY_KEY not defined — using default insecure key!"
    #define SECURITY_KEY  0xDEADBEEF
#endif

#if FEATURE_DEPRECATED_API
    #warning "FEATURE_DEPRECATED_API is deprecated and will be removed in v3.0"
#endif
```

---

## 13. Pragmas

### #pragma — Compiler Instructions

`#pragma` passes non-portable instructions to the compiler. Unknown pragmas are **ignored** (not an error), making it safe to use portably.

### #pragma once

Already covered in Section 8. Prevents multiple inclusion.

### #pragma pack — Structure Packing

Controls alignment/padding of struct members:

```c
#include <stdio.h>

// Default alignment (with padding):
typedef struct {
    char  a;    // 1 byte + 3 padding
    int   b;    // 4 bytes
    char  c;    // 1 byte + 3 padding
} Normal;       // Total: 12 bytes

// Packed (no padding):
#pragma pack(push, 1)
typedef struct {
    char  a;    // 1 byte
    int   b;    // 4 bytes
    char  c;    // 1 byte
} Packed;       // Total: 6 bytes
#pragma pack(pop)

int main(void) {
    printf("Normal size: %zu\n", sizeof(Normal));  // 12
    printf("Packed size: %zu\n", sizeof(Packed));  // 6
    return 0;
}
```

**Critical in embedded:** Packed structs are used for protocol frames, register maps, binary file headers.

```c
// Ethernet frame header (must match exact byte layout):
#pragma pack(push, 1)
typedef struct {
    uint8_t  dst_mac[6];
    uint8_t  src_mac[6];
    uint16_t ethertype;
} EthernetHeader;   // Exactly 14 bytes — no padding allowed
#pragma pack(pop)
```

### Other Common Pragmas

```c
#pragma GCC optimize("O3")          // Force O3 optimization for next function
#pragma GCC poison malloc free       // Error if malloc/free used (safety check)
#pragma comment(lib, "ws2_32.lib")  // MSVC: Link with winsock (Windows)
#pragma warning(disable: 4996)      // MSVC: Disable specific warning
#pragma clang diagnostic push       // Clang: Save diagnostic state
#pragma clang diagnostic ignored "-Wunused-variable"
```

---

## 14. Advanced Preprocessor Concepts

### Variadic Macros (__VA_ARGS__)

```c
// C99: Macros with variable arguments
#define LOG(fmt, ...)    printf("[LOG] " fmt "\n", ##__VA_ARGS__)
#define ERROR(fmt, ...)  fprintf(stderr, "[ERROR] %s:%d: " fmt "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)

LOG("Server started on port %d", 8080);
ERROR("Connection failed: %s", strerror(errno));
```

### Compile-Time Assertions

```c
// C11: _Static_assert (built-in)
_Static_assert(sizeof(int) == 4, "int must be 4 bytes");
_Static_assert(sizeof(void*) == 8, "Must be 64-bit system");

// Pre-C11 macro implementation:
#define STATIC_ASSERT(cond, msg) \
    typedef char static_assert_##msg[(cond) ? 1 : -1]

STATIC_ASSERT(sizeof(long) == 8, long_must_be_8_bytes);
```

### X-Macro Pattern (Macro Metaprogramming)

Generate multiple pieces of code from a single list:

```c
// Define data in one place:
#define ERROR_LIST \
    X(ERR_OK,      0,  "Success")          \
    X(ERR_NOMEM,   1,  "Out of memory")    \
    X(ERR_IO,      2,  "I/O error")        \
    X(ERR_TIMEOUT, 3,  "Timeout")

// Generate enum:
#define X(name, val, str)  name = val,
typedef enum { ERROR_LIST } ErrorCode;
#undef X

// Generate string table:
#define X(name, val, str)  [val] = str,
static const char *error_strings[] = { ERROR_LIST };
#undef X

// Usage:
ErrorCode err = ERR_TIMEOUT;
printf("Error: %s\n", error_strings[err]);  // "Timeout"
```

### Feature Flags and Build Configuration

```c
// Compile with: gcc -DFEATURE_LEVEL=2 -DENABLE_LOGGING main.c

#ifndef FEATURE_LEVEL
    #define FEATURE_LEVEL 1   // Default
#endif

#if FEATURE_LEVEL >= 1
    #define BASIC_FEATURES
#endif
#if FEATURE_LEVEL >= 2
    #define ADVANCED_FEATURES
#endif
#if FEATURE_LEVEL >= 3
    #define EXPERT_FEATURES
#endif
```

### Macro-Based Generic Programming

```c
// Generic min/max that works for any type:
#define GENERIC_MIN(type, a, b) \
    ({ type _a = (a); type _b = (b); _a < _b ? _a : _b; })  // GCC extension

// Or using C11 _Generic:
#define MIN(a, b) \
    _Generic((a), \
        int:    min_int, \
        float:  min_float, \
        double: min_double \
    )((a), (b))
```

---

## 15. Header Files In Depth

### Structure of a Professional Header File

```c
// uart.h — Professional header file template
#ifndef MYPROJECT_DRIVERS_UART_H
#define MYPROJECT_DRIVERS_UART_H

/*============================================================
 *  uart.h — UART Driver Interface
 *  Project: MyEmbeddedProject
 *  Version: 1.2.0
 *============================================================*/

#include <stdint.h>
#include <stdbool.h>

/* ── Constants ─────────────────────────────────────────── */
#define UART_MAX_BAUD       115200U
#define UART_BUFFER_SIZE    256U
#define UART_TIMEOUT_MS     1000U

/* ── Type Definitions ───────────────────────────────────── */
typedef enum {
    UART_OK      = 0,
    UART_ERROR   = 1,
    UART_TIMEOUT = 2,
    UART_BUSY    = 3
} UartStatus;

typedef struct {
    uint32_t baud_rate;
    uint8_t  data_bits;
    uint8_t  stop_bits;
    bool     parity_enable;
} UartConfig;

/* ── Function Declarations ──────────────────────────────── */
UartStatus uart_init(uint8_t port, const UartConfig *cfg);
UartStatus uart_send(uint8_t port, const uint8_t *data, uint16_t len);
UartStatus uart_recv(uint8_t port, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
void       uart_deinit(uint8_t port);

#endif /* MYPROJECT_DRIVERS_UART_H */
```

### Multi-File Project Organization

```
project/
├── main.c
├── include/
│   ├── config.h          ← Build-time configuration
│   ├── common.h          ← Shared types, macros
│   └── drivers/
│       ├── uart.h
│       ├── spi.h
│       └── gpio.h
├── src/
│   └── drivers/
│       ├── uart.c
│       ├── spi.c
│       └── gpio.c
└── Makefile
```

```c
// config.h — Central configuration header
#ifndef CONFIG_H
#define CONFIG_H

#define FW_VERSION_MAJOR    1
#define FW_VERSION_MINOR    2
#define FW_VERSION_PATCH    3

#define ENABLE_UART         1
#define ENABLE_SPI          1
#define ENABLE_WIFI         0

#define LOG_LEVEL           2   // 0=off, 1=error, 2=info, 3=debug

#endif /* CONFIG_H */
```

### Inline Functions in Headers (C99+)

```c
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdint.h>

static inline uint32_t clamp_u32(uint32_t val, uint32_t lo, uint32_t hi) {
    return val < lo ? lo : val > hi ? hi : val;
}

static inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

#endif
```

---

## 16. Embedded C Applications

### Register Address Macros

```c
// stm32f4_regs.h — STM32F4 peripheral register definitions

#define PERIPH_BASE         0x40000000UL
#define AHB1_BASE           (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE          (AHB1_BASE   + 0x00000000UL)
#define GPIOB_BASE          (AHB1_BASE   + 0x00000400UL)

// Register structure for GPIO:
typedef struct {
    volatile uint32_t MODER;    // Mode register
    volatile uint32_t OTYPER;   // Output type register
    volatile uint32_t OSPEEDR;  // Output speed register
    volatile uint32_t PUPDR;    // Pull-up/pull-down register
    volatile uint32_t IDR;      // Input data register
    volatile uint32_t ODR;      // Output data register
    volatile uint32_t BSRR;     // Bit set/reset register
    volatile uint32_t LCKR;     // Configuration lock register
    volatile uint32_t AFR[2];   // Alternate function registers
} GPIO_TypeDef;

#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)

// Usage:
// GPIOA->MODER |= (0x01U << (5 * 2));   // PA5 as output
// GPIOA->BSRR   = (1U << 5);            // PA5 HIGH
```

### Bit Manipulation Macros

```c
// bit_ops.h — Portable bit manipulation macros

#define BIT(n)              (1UL << (n))
#define SET_BIT(reg, bit)   ((reg) |=  BIT(bit))
#define CLR_BIT(reg, bit)   ((reg) &= ~BIT(bit))
#define TOG_BIT(reg, bit)   ((reg) ^=  BIT(bit))
#define GET_BIT(reg, bit)   (((reg) >> (bit)) & 1UL)

#define SET_MASK(reg, mask) ((reg) |=  (mask))
#define CLR_MASK(reg, mask) ((reg) &= ~(mask))

// Usage:
uint32_t status_reg = 0;
SET_BIT(status_reg, 3);      // Set bit 3
CLR_BIT(status_reg, 3);      // Clear bit 3
if (GET_BIT(status_reg, 5))  // Test bit 5
    handle_event();
```

### Hardware Abstraction Layer (HAL)

```c
// hal_gpio.h — Abstract GPIO interface

#ifdef TARGET_STM32F4
    #include "stm32f4_gpio.h"
    #define HAL_GPIO_WRITE(port, pin, val)  stm32_gpio_write(port, pin, val)
    #define HAL_GPIO_READ(port, pin)        stm32_gpio_read(port, pin)
#elif defined(TARGET_ARDUINO)
    #include "arduino_gpio.h"
    #define HAL_GPIO_WRITE(port, pin, val)  digitalWrite(pin, val)
    #define HAL_GPIO_READ(port, pin)        digitalRead(pin)
#elif defined(TARGET_LINUX)
    #include "linux_gpio.h"
    #define HAL_GPIO_WRITE(port, pin, val)  linux_gpio_write(pin, val)
    #define HAL_GPIO_READ(port, pin)        linux_gpio_read(pin)
#else
    #error "Unknown target platform — define TARGET_STM32F4, TARGET_ARDUINO, or TARGET_LINUX"
#endif

// Usage (platform-independent):
HAL_GPIO_WRITE(A, 5, 1);   // Drive GPIO high
int state = HAL_GPIO_READ(B, 3);
```

### RTOS Configuration (FreeRTOS Style)

```c
// FreeRTOSConfig.h
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              168000000UL
#define configTICK_RATE_HZ              1000U
#define configMAX_PRIORITIES            5
#define configMINIMAL_STACK_SIZE        128
#define configTOTAL_HEAP_SIZE           (50 * 1024)
#define configMAX_TASK_NAME_LEN         16
#define configUSE_TRACE_FACILITY        0
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1

#endif /* FREERTOS_CONFIG_H */
```

---

## 17. Linux and System Programming Applications

### Linux Kernel Macros

```c
// container_of — get struct from member pointer (kernel idiom):
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

// Usage:
struct list_node { struct list_node *next; };
struct my_data   { int value; struct list_node node; };

struct list_node *n = get_from_list();
struct my_data *d = container_of(n, struct my_data, node);
printf("Value: %d\n", d->value);
```

```c
// ARRAY_SIZE — number of elements in a stack array:
#define ARRAY_SIZE(arr)  (sizeof(arr) / sizeof((arr)[0]))

int data[] = {1, 2, 3, 4, 5};
for (int i = 0; i < ARRAY_SIZE(data); i++)
    printf("%d\n", data[i]);
```

### Kernel Module Macros

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Example kernel module");
MODULE_VERSION("1.0");

static int __init my_module_init(void) {
    printk(KERN_INFO "Module loaded\n");
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
```

### Build Configuration Systems

```makefile
# Makefile with preprocessor flags:
CFLAGS = -Wall -Wextra -std=c11

ifdef DEBUG
    CFLAGS += -DDEBUG -g -O0
else
    CFLAGS += -DNDEBUG -O2
endif

ifdef TARGET
    CFLAGS += -DTARGET_$(TARGET)
endif

build:
    gcc $(CFLAGS) main.c -o app
```

```bash
# Usage:
make DEBUG=1 TARGET=STM32F4
```

---

## 18. Common Macro Problems

### 1. Side Effects — Multiple Evaluation

```c
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

// Problem:
int x = 5, y = 3;
int m = MAX(x++, y++);
// Expands: ((x++) > (y++) ? (x++) : (y++))
// x or y gets incremented twice — undefined behavior!

// Fix: Use inline function:
static inline int max_int(int a, int b) { return a > b ? a : b; }
```

### 2. Missing Parentheses

```c
// Problem:
#define AREA(r)    3.14 * r * r         // Missing parens around r
double a = AREA(2 + 1);
// Expands: 3.14 * 2 + 1 * 2 + 1 = 9.28  (expected: 3.14 * 9 = 28.26!)

// Fix:
#define AREA(r)    (3.14 * (r) * (r))   // Correct
```

### 3. Multi-Statement Macro Without do-while(0)

```c
// Problem:
#define SWAP(a, b)  int t = a; a = b; b = t;

if (x > y)
    SWAP(x, y);
// Expands to:
// if (x > y)
//     int t = x;    ← only this is in the if
// x = y;            ← always executed!
// y = t;            ← always executed!

// Fix:
#define SWAP(a, b)  do { int _t = (a); (a) = (b); (b) = _t; } while(0)
```

### 4. Debugging Difficulty

Macros don't show up in debuggers as function names. The compiler shows the expanded line, not the macro call. **Mitigation:**
- Use `-E` flag to see expanded code: `gcc -E main.c`
- Name internal variables with `_` prefix to avoid conflicts.
- Prefer `static inline` functions where possible.

### 5. Naming Conflicts

```c
#define max(a, b)   ((a) > (b) ? (a) : (b))   // Lowercase — bad!

// Now this code breaks:
#include <algorithm>  // C++ max function
int result = max(3, 7);  // Macro replaces function call!
```

**Fix:** Use `ALL_CAPS` for all macro names. Never use lowercase macro names.

---

## 19. Macros vs Functions

### Comparison Table

| Feature | Macro | Function |
|---------|-------|----------|
| **Speed** | Faster (inline expansion, no call overhead) | Call/return overhead |
| **Type checking** | None (text substitution) | Full type checking |
| **Debugging** | Difficult (no stack frame) | Easy (debugger shows function) |
| **Side effects** | Dangerous (multiple evaluation) | Safe (single evaluation) |
| **Code size** | Larger (expanded everywhere) | Smaller (one copy) |
| **Recursion** | Not supported | Supported |
| **Scope** | File-wide / global | Function-local |
| **Generic** | Yes (works any type) | No (type-specific) |
| **Inline keyword** | N/A | `static inline` (C99) |

### Practical Comparison

```c
// Macro approach:
#define SQUARE_M(x)   ((x) * (x))

// Function approach:
static inline int square_f(int x) { return x * x; }

// For type safety and debugging: prefer inline function
// For truly generic (works on int, float, double): macro or _Generic
```

### Recommendation

| Situation | Use |
|-----------|-----|
| Simple constant | `const` or `enum` over `#define` |
| Platform detection | `#ifdef` (macros only option) |
| Simple type-generic operation | Macro with caution |
| Numeric operation with arguments | `static inline` function |
| Logging with `__FILE__`/`__LINE__` | Macro (inline functions can't do this) |
| Register addresses in embedded | `#define` (raw address, no type) |

---

## 20. #define vs const

### Comparison Table

| Property | `#define PI 3.14` | `const float PI = 3.14;` |
|----------|-------------------|--------------------------|
| Memory allocation | None (text substitution) | Variable in memory (may be optimized away) |
| Type safety | None | Has type (`float`) |
| Scope | File-wide (no scope) | Respects C scoping rules |
| Debugging | Shows as `3.14` in debugger | Shows as `PI = 3.14` |
| Address | Cannot take `&PI` | Can take `&PI` |
| Compiler errors | Preprocessor errors | Meaningful type errors |
| C++ compatibility | Works | Preferred in C++ |
| Embedded use | Common for register addresses | Preferred for numeric constants |

### When to Use Each

```c
// Use #define for:
#define GPIO_BASE_ADDR  0x40020000UL   // Raw address — no type
#define MAX_RETRY_MASK  0xFFU          // Bit mask
#ifdef DEBUG ...                        // Conditional compilation

// Use const for:
const int MAX_CONNECTIONS = 100;       // Has type, scope, debuggable
const float GRAVITY = 9.81f;          // Floating point constant
const char *VERSION = "1.0.0";        // String constant
```

### Interview Discussion

**Q:** Why prefer `const int MAX = 100` over `#define MAX 100`?  
**A:** `const int` has type (caught by compiler if misused), has scope (can be local), appears in debugger with its name, can have its address taken, and participates in type checking. `#define` is just text substitution with none of these benefits.

---

## 21. 30 Practical C Programs

---

### Beginner Programs (1–10)

---

#### Program 1: Simple Macro Definition

**Problem:** Define and use basic object-like macros.

```c
#include <stdio.h>

#define APP_NAME    "MyApp"
#define VERSION     "1.0.0"
#define MAX_USERS   50
#define PI          3.14159265

int main(void) {
    printf("Application: %s v%s\n", APP_NAME, VERSION);
    printf("Max users  : %d\n", MAX_USERS);
    printf("Pi value   : %.5f\n", PI);
    return 0;
}
```

**Output:**
```
Application: MyApp v1.0.0
Max users  : 50
Pi value   : 3.14159
```
**Interview Point:** `#define` creates no variable — just text substitution. No memory used.

---

#### Program 2: PI and Circle Calculations

**Problem:** Use macros for mathematical constants and formulas.

```c
#include <stdio.h>

#define PI              3.14159265358979
#define CIRCUMFERENCE(r) (2.0 * PI * (r))
#define AREA_CIRCLE(r)   (PI * (r) * (r))

int main(void) {
    double r;
    printf("Enter radius: ");
    scanf("%lf", &r);
    printf("Circumference : %.4f\n", CIRCUMFERENCE(r));
    printf("Area          : %.4f\n", AREA_CIRCLE(r));
    return 0;
}
```

**Sample Input:** `5`  
**Sample Output:**
```
Circumference : 31.4159
Area          : 78.5398
```
**Interview Point:** Function-like macros have no type — they work for `int`, `float`, `double` alike.

---

#### Program 3: SQUARE and CUBE Macros

**Problem:** Demonstrate correctly parenthesized function-like macros.

```c
#include <stdio.h>

#define SQUARE(x)  ((x) * (x))
#define CUBE(x)    ((x) * (x) * (x))
#define POW4(x)    (SQUARE(x) * SQUARE(x))

int main(void) {
    int n = 4;
    printf("SQUARE(%d)  = %d\n", n, SQUARE(n));
    printf("CUBE(%d)    = %d\n", n, CUBE(n));
    printf("POW4(%d)    = %d\n", n, POW4(n));

    // Demonstrate importance of parentheses:
    printf("SQUARE(2+1) = %d\n", SQUARE(2 + 1));  // Correct: 9
    return 0;
}
```

**Output:**
```
SQUARE(4)  = 16
CUBE(4)    = 64
POW4(4)    = 256
SQUARE(2+1) = 9
```

---

#### Program 4: MAX and MIN Macros

```c
#include <stdio.h>

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#define CLAMP(v, lo, hi)  (MAX((lo), MIN((v), (hi))))

int main(void) {
    int x = 15, y = 28;
    printf("MAX(%d, %d) = %d\n", x, y, MAX(x, y));
    printf("MIN(%d, %d) = %d\n", x, y, MIN(x, y));
    printf("CLAMP(150, 0, 100) = %d\n", CLAMP(150, 0, 100));
    printf("CLAMP(-5, 0, 100)  = %d\n", CLAMP(-5, 0, 100));
    return 0;
}
```

**Output:**
```
MAX(15, 28) = 28
MIN(15, 28) = 15
CLAMP(150, 0, 100) = 100
CLAMP(-5, 0, 100)  = 0
```

---

#### Program 5: Area Calculations Using Macros

```c
#include <stdio.h>
#define PI 3.14159265

#define AREA_RECT(w, h)    ((w) * (h))
#define AREA_TRIANGLE(b,h) (0.5 * (b) * (h))
#define AREA_CIRCLE(r)     (PI * (r) * (r))
#define AREA_SQUARE(s)     ((s) * (s))

int main(void) {
    printf("Rectangle  (6x4)   : %.2f\n", AREA_RECT(6, 4));
    printf("Triangle   (base=5, h=8): %.2f\n", AREA_TRIANGLE(5, 8));
    printf("Circle     (r=7)   : %.4f\n", AREA_CIRCLE(7));
    printf("Square     (side=9): %.2f\n", AREA_SQUARE(9));
    return 0;
}
```

**Output:**
```
Rectangle  (6x4)        : 24.00
Triangle   (base=5, h=8): 20.00
Circle     (r=7)        : 153.9380
Square     (side=9)     : 81.00
```

---

#### Program 6: Conditional Compilation — Debug Build

```c
#include <stdio.h>

// Simulate: gcc -DDEBUG_MODE prog6.c

#ifdef DEBUG_MODE
    #define LOG(msg)  printf("[DEBUG] %s\n", (msg))
#else
    #define LOG(msg)  /* nothing */
#endif

int add(int a, int b) {
    LOG("Entering add()");
    int result = a + b;
    LOG("Exiting add()");
    return result;
}

int main(void) {
    int r = add(3, 4);
    printf("Result: %d\n", r);
    return 0;
}
```

**Output (with -DDEBUG_MODE):**
```
[DEBUG] Entering add()
[DEBUG] Exiting add()
Result: 7
```
**Output (without -DDEBUG_MODE):**
```
Result: 7
```

---

#### Program 7: Include Guard Demonstration

```c
// ---- mymath.h ----
#ifndef MYMATH_H
#define MYMATH_H

#define MYMATH_PI  3.14159
double circle_area(double r);

#endif /* MYMATH_H */
```

```c
// ---- mymath.c ----
#include "mymath.h"
double circle_area(double r) { return MYMATH_PI * r * r; }
```

```c
// ---- main.c ----
#include <stdio.h>
#include "mymath.h"
#include "mymath.h"   // Second inclusion — safely ignored due to guard

int main(void) {
    printf("Area = %.4f\n", circle_area(5.0));
    return 0;
}
```

**Output:** `Area = 78.5398`

---

#### Program 8: Debug Messages with __FILE__ and __LINE__

```c
#include <stdio.h>

#define DEBUG_MSG(msg) \
    printf("[DBG] File: %-15s | Line: %3d | %s\n", __FILE__, __LINE__, (msg))

#define TRACE_FUNC()  \
    printf("[TRACE] Entered: %s\n", __func__)

void compute(int x) {
    TRACE_FUNC();
    DEBUG_MSG("Starting computation");
    int result = x * x;
    DEBUG_MSG("Computation done");
    printf("Result = %d\n", result);
}

int main(void) {
    DEBUG_MSG("Program started");
    compute(7);
    DEBUG_MSG("Program ending");
    return 0;
}
```

**Output:**
```
[DBG] File: prog8.c        | Line:  16 | Program started
[TRACE] Entered: compute
[DBG] File: prog8.c        | Line:   9 | Starting computation
[DBG] File: prog8.c        | Line:  11 | Computation done
Result = 49
[DBG] File: prog8.c        | Line:  19 | Program ending
```

---

#### Program 9: File Information Display

```c
#include <stdio.h>

int main(void) {
    printf("Source file : %s\n", __FILE__);
    printf("Line number : %d\n", __LINE__);
    printf("Compiled on : %s\n", __DATE__);
    printf("Compiled at : %s\n", __TIME__);
    printf("Function    : %s\n", __func__);
#ifdef __STDC_VERSION__
    printf("C Standard  : %ldL\n", __STDC_VERSION__);
#endif
    return 0;
}
```

**Output:**
```
Source file : prog9.c
Line number : 5
Compiled on : Jun 30 2026
Compiled at : 14:30:00
Function    : main
C Standard  : 201710L
```

---

#### Program 10: Compile Date and Time Banner

```c
#include <stdio.h>

#define BANNER \
    "========================================\n" \
    " App: DataProcessor\n"                      \
    " Version: 2.0\n"                            \
    " Built: " __DATE__ " " __TIME__ "\n"        \
    "========================================\n"

int main(void) {
    printf(BANNER);
    printf("Running application...\n");
    return 0;
}
```

**Output:**
```
========================================
 App: DataProcessor
 Version: 2.0
 Built: Jun 30 2026 14:30:00
========================================
Running application...
```

---

### Intermediate Programs (11–20)

---

#### Program 11: Feature Enabling/Disabling

```c
#include <stdio.h>

// Feature configuration — change 1/0 to enable/disable:
#define FEATURE_LOGGING     1
#define FEATURE_ENCRYPTION  0
#define FEATURE_COMPRESSION 1

void run_pipeline(void) {
#if FEATURE_LOGGING
    printf("[LOG] Pipeline started\n");
#endif

#if FEATURE_ENCRYPTION
    printf("[ENC] Encrypting data...\n");
#else
    printf("[ENC] Encryption disabled — plain text\n");
#endif

#if FEATURE_COMPRESSION
    printf("[ZIP] Compressing data...\n");
#endif

#if FEATURE_LOGGING
    printf("[LOG] Pipeline finished\n");
#endif
}

int main(void) { run_pipeline(); return 0; }
```

**Output:**
```
[LOG] Pipeline started
[ENC] Encryption disabled — plain text
[ZIP] Compressing data...
[LOG] Pipeline finished
```

---

#### Program 12: Token Pasting (##)

```c
#include <stdio.h>

#define DECLARE_SENSOR(n)    int sensor_##n##_value = 0
#define READ_SENSOR(n)       sensor_##n##_value
#define WRITE_SENSOR(n, v)   sensor_##n##_value = (v)

DECLARE_SENSOR(1);
DECLARE_SENSOR(2);
DECLARE_SENSOR(3);

int main(void) {
    WRITE_SENSOR(1, 100);
    WRITE_SENSOR(2, 250);
    WRITE_SENSOR(3, 175);

    printf("Sensor 1: %d\n", READ_SENSOR(1));
    printf("Sensor 2: %d\n", READ_SENSOR(2));
    printf("Sensor 3: %d\n", READ_SENSOR(3));
    return 0;
}
```

**Output:**
```
Sensor 1: 100
Sensor 2: 250
Sensor 3: 175
```

---

#### Program 13: Stringizing (#)

```c
#include <stdio.h>

#define PRINT_VAR(var)        printf(#var " = %d\n", (var))
#define PRINT_FLOAT(var)      printf(#var " = %.4f\n", (var))
#define STRINGIFY(x)          #x
#define STR(x)                STRINGIFY(x)

#define VERSION_MAJOR   2
#define VERSION_MINOR   5
#define VERSION_STRING  STR(VERSION_MAJOR) "." STR(VERSION_MINOR)

int main(void) {
    int temperature = 37;
    float voltage   = 3.3f;
    int  counter    = 1024;

    PRINT_VAR(temperature);
    PRINT_VAR(counter);
    PRINT_FLOAT(voltage);

    printf("Version: %s\n", VERSION_STRING);
    printf("Code: " STRINGIFY(if(x > 0) x++) "\n");
    return 0;
}
```

**Output:**
```
temperature = 37
counter = 1024
voltage = 3.3000
Version: 2.5
Code: if(x > 0) x++
```

---

#### Program 14: Conditional Log System

```c
#include <stdio.h>
#include <stdarg.h>

// Log levels
#define LOG_LEVEL_ERROR  1
#define LOG_LEVEL_WARN   2
#define LOG_LEVEL_INFO   3
#define LOG_LEVEL_DEBUG  4

#ifndef CURRENT_LOG_LEVEL
    #define CURRENT_LOG_LEVEL  LOG_LEVEL_INFO
#endif

#define LOG(level, label, fmt, ...) \
    do { \
        if ((level) <= CURRENT_LOG_LEVEL) \
            printf("[" label "] %s:%d: " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    } while(0)

#define LOG_ERROR(fmt, ...)  LOG(LOG_LEVEL_ERROR, "ERROR", fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)   LOG(LOG_LEVEL_WARN,  "WARN ", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)   LOG(LOG_LEVEL_INFO,  "INFO ", fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)  LOG(LOG_LEVEL_DEBUG, "DEBUG", fmt, ##__VA_ARGS__)

void connect(const char *host, int port) {
    LOG_DEBUG("Attempting connection to %s:%d", host, port);
    LOG_INFO("Connecting to %s:%d", host, port);
    // Simulate error:
    LOG_ERROR("Connection refused on port %d", port);
    LOG_WARN("Retrying in 5 seconds");
}

int main(void) {
    connect("192.168.1.100", 8080);
    return 0;
}
```

**Output (CURRENT_LOG_LEVEL=3):**
```
[INFO ] connect:24: Connecting to 192.168.1.100:8080
[ERROR] connect:26: Connection refused on port 8080
[WARN ] connect:27: Retrying in 5 seconds
```

---

#### Program 15: Version Management

```c
#include <stdio.h>

#define FW_VER_MAJOR    2
#define FW_VER_MINOR    4
#define FW_VER_PATCH    1

#define MAKE_VERSION(maj, min, pat)  (((maj) << 16) | ((min) << 8) | (pat))
#define FW_VERSION      MAKE_VERSION(FW_VER_MAJOR, FW_VER_MINOR, FW_VER_PATCH)

#define VER_MAJOR(v)    (((v) >> 16) & 0xFF)
#define VER_MINOR(v)    (((v) >>  8) & 0xFF)
#define VER_PATCH(v)    ( (v)        & 0xFF)

// Compile-time version check:
#if FW_VERSION < MAKE_VERSION(2, 0, 0)
    #error "Firmware version 2.0.0 or later required"
#endif

int main(void) {
    printf("Firmware version: %d.%d.%d\n",
           FW_VER_MAJOR, FW_VER_MINOR, FW_VER_PATCH);
    printf("Version integer: 0x%06X\n", FW_VERSION);
    printf("Decoded: %d.%d.%d\n",
           VER_MAJOR(FW_VERSION),
           VER_MINOR(FW_VERSION),
           VER_PATCH(FW_VERSION));
    return 0;
}
```

**Output:**
```
Firmware version: 2.4.1
Version integer: 0x020401
Decoded: 2.4.1
```

---

#### Program 16: Custom Assertions

```c
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
    #define ASSERT(cond)      ((void)0)
    #define ASSERT_MSG(c, m)  ((void)0)
#else
    #define ASSERT(cond) \
        do { \
            if (!(cond)) { \
                fprintf(stderr, "ASSERTION FAILED: (%s)\n" \
                        "  File: %s\n  Line: %d\n  Func: %s\n", \
                        #cond, __FILE__, __LINE__, __func__); \
                abort(); \
            } \
        } while(0)

    #define ASSERT_MSG(cond, msg) \
        do { \
            if (!(cond)) { \
                fprintf(stderr, "ASSERTION FAILED: %s\n" \
                        "  Condition: (%s)\n  File: %s:%d\n", \
                        (msg), #cond, __FILE__, __LINE__); \
                abort(); \
            } \
        } while(0)
#endif

int divide(int a, int b) {
    ASSERT_MSG(b != 0, "Division by zero!");
    return a / b;
}

int main(void) {
    printf("10 / 2 = %d\n", divide(10, 2));
    printf("8  / 4 = %d\n", divide(8, 4));
    // divide(5, 0);  // This would trigger assertion
    return 0;
}
```

**Output:**
```
10 / 2 = 5
8  / 4 = 2
```

---

#### Program 17: Platform-Specific Code

```c
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
    #define OS_NAME       "Windows"
    #define PATH_SEP      '\\'
    #define SLEEP_MS(ms)  Sleep(ms)
    #include <windows.h>
#elif defined(__linux__)
    #define OS_NAME       "Linux"
    #define PATH_SEP      '/'
    #define SLEEP_MS(ms)  usleep((ms) * 1000)
    #include <unistd.h>
#elif defined(__APPLE__)
    #define OS_NAME       "macOS"
    #define PATH_SEP      '/'
    #define SLEEP_MS(ms)  usleep((ms) * 1000)
    #include <unistd.h>
#else
    #define OS_NAME       "Unknown"
    #define PATH_SEP      '/'
    #define SLEEP_MS(ms)  ((void)(ms))
#endif

void build_path(char *buf, const char *dir, const char *file) {
    sprintf(buf, "%s%c%s", dir, PATH_SEP, file);
}

int main(void) {
    char path[256];
    build_path(path, "data", "config.txt");
    printf("OS     : %s\n", OS_NAME);
    printf("Path   : %s\n", path);
    printf("Separator: '%c'\n", PATH_SEP);
    return 0;
}
```

---

#### Program 18: Multi-File Project Organization

```c
// ---- config.h ----
#ifndef CONFIG_H
#define CONFIG_H
#define APP_VERSION   "3.0"
#define MAX_ENTRIES   1000
#define ENABLE_CACHE  1
#endif
```

```c
// ---- utils.h ----
#ifndef UTILS_H
#define UTILS_H
#include "config.h"
void print_version(void);
int  clamp(int val, int lo, int hi);
#endif
```

```c
// ---- utils.c ----
#include <stdio.h>
#include "utils.h"
void print_version(void) { printf("Version: %s\n", APP_VERSION); }
int  clamp(int v, int lo, int hi) { return v<lo?lo:v>hi?hi:v; }
```

```c
// ---- main.c ----
#include <stdio.h>
#include "utils.h"
int main(void) {
    print_version();
    printf("Max entries: %d\n", MAX_ENTRIES);
    printf("Clamped: %d\n", clamp(150, 0, 100));
    return 0;
}
```

---

#### Program 19: Macro-Based Calculations

```c
#include <stdio.h>
#include <math.h>

#define DEG_TO_RAD(d)   ((d) * 3.14159265358979 / 180.0)
#define RAD_TO_DEG(r)   ((r) * 180.0 / 3.14159265358979)
#define HYPOTENUSE(a,b) (sqrt((double)(a)*(a) + (double)(b)*(b)))
#define PERCENT(part,total) (100.0 * (part) / (total))

int main(void) {
    printf("45 degrees in radians : %.6f\n", DEG_TO_RAD(45));
    printf("PI/4 in degrees       : %.4f\n", RAD_TO_DEG(3.14159265/4.0));
    printf("Hypotenuse (3,4)      : %.4f\n", HYPOTENUSE(3, 4));
    printf("75 out of 120         : %.2f%%\n", PERCENT(75, 120));
    return 0;
}
```

**Output:**
```
45 degrees in radians : 0.785398
PI/4 in degrees       : 45.0000
Hypotenuse (3,4)      : 5.0000
75 out of 120         : 62.50%
```

---

#### Program 20: Header File with All Elements

```c
// ---- sensor.h ----
#ifndef SENSOR_H
#define SENSOR_H
#pragma once   // Double protection

#include <stdint.h>
#include <stdbool.h>

#define SENSOR_VERSION   0x0102U   // v1.2
#define SENSOR_MAX_COUNT 16U
#define SENSOR_TIMEOUT   500U      // ms

typedef enum {
    SENSOR_TEMP     = 0,
    SENSOR_HUMIDITY = 1,
    SENSOR_PRESSURE = 2
} SensorType;

typedef struct {
    uint8_t    id;
    SensorType type;
    float      value;
    bool       valid;
} SensorData;

bool sensor_read(uint8_t id, SensorData *out);
void sensor_print(const SensorData *s);

#endif /* SENSOR_H */
```

---

### Advanced Programs (21–30)

---

#### Program 21: Embedded Register Definitions

```c
#include <stdio.h>
#include <stdint.h>

// Simulated MCU registers (embedded: these would be volatile hardware addresses)
static uint32_t GPIOA_ODR = 0;
static uint32_t GPIOA_IDR = 0;
static uint32_t RCC_AHB1  = 0;

// Register bit macros:
#define RCC_AHB1EN_GPIOA    BIT(0)
#define GPIOA_PIN5          5U
#define GPIOA_PIN13         13U

#define BIT(n)              (1UL << (n))
#define REG_SET(reg, mask)  ((reg) |=  (mask))
#define REG_CLR(reg, mask)  ((reg) &= ~(mask))
#define REG_GET(reg, bit)   (((reg) >> (bit)) & 1U)

// GPIO abstraction macros:
#define GPIO_ENABLE_CLOCK()         REG_SET(RCC_AHB1, RCC_AHB1EN_GPIOA)
#define LED_ON()                    REG_SET(GPIOA_ODR, BIT(GPIOA_PIN5))
#define LED_OFF()                   REG_CLR(GPIOA_ODR, BIT(GPIOA_PIN5))
#define BUTTON_PRESSED()            REG_GET(GPIOA_IDR, GPIOA_PIN13)

int main(void) {
    GPIO_ENABLE_CLOCK();
    printf("Clock enabled. RCC_AHB1 = 0x%08X\n", RCC_AHB1);

    LED_ON();
    printf("LED ON.  GPIOA_ODR = 0x%08X\n", GPIOA_ODR);

    LED_OFF();
    printf("LED OFF. GPIOA_ODR = 0x%08X\n", GPIOA_ODR);

    // Simulate button press:
    REG_SET(GPIOA_IDR, BIT(GPIOA_PIN13));
    printf("Button pressed: %d\n", BUTTON_PRESSED());
    return 0;
}
```

---

#### Program 22: Bit Manipulation Library

```c
#include <stdio.h>
#include <stdint.h>

#define BIT(n)                   (1UL << (n))
#define BITMASK(hi, lo)          (((1UL << ((hi)-(lo)+1)) - 1UL) << (lo))

#define SET_BIT(reg, bit)        ((reg) |=  BIT(bit))
#define CLR_BIT(reg, bit)        ((reg) &= ~BIT(bit))
#define TOG_BIT(reg, bit)        ((reg) ^=  BIT(bit))
#define GET_BIT(reg, bit)        (((reg) >> (bit)) & 1UL)

#define GET_FIELD(reg, hi, lo)   (((reg) & BITMASK(hi,lo)) >> (lo))
#define SET_FIELD(reg, hi, lo, val) \
    ((reg) = ((reg) & ~BITMASK(hi,lo)) | (((val) << (lo)) & BITMASK(hi,lo)))

void print_bits(uint32_t v) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (int)GET_BIT(v, i));
        if (i % 4 == 0 && i > 0) printf(" ");
    }
    printf("\n");
}

int main(void) {
    uint32_t reg = 0;
    printf("Initial  : "); print_bits(reg);

    SET_BIT(reg, 3);
    SET_BIT(reg, 7);
    printf("Set 3,7  : "); print_bits(reg);

    CLR_BIT(reg, 3);
    printf("Clr 3    : "); print_bits(reg);

    SET_FIELD(reg, 11, 8, 0xA);
    printf("Set[11:8]: "); print_bits(reg);
    printf("Get[11:8]: 0x%X\n", GET_FIELD(reg, 11, 8));

    return 0;
}
```

---

#### Program 23: Hardware Abstraction Layer

```c
#include <stdio.h>
#include <stdint.h>

// Target selection (compile with -DTARGET_SIM or -DTARGET_HW)
#ifndef TARGET_SIM
    #define TARGET_SIM   // Default to simulation
#endif

#ifdef TARGET_SIM
    // Simulation stubs:
    static uint8_t sim_uart_buf[256];
    static int     sim_uart_pos = 0;

    #define HAL_UART_INIT(baud)    printf("[HAL-SIM] UART init @ %d baud\n", (baud))
    #define HAL_UART_SEND(c)       do { sim_uart_buf[sim_uart_pos++] = (c); \
                                   printf("[HAL-SIM] UART TX: 0x%02X ('%c')\n", \
                                   (uint8_t)(c), (char)(c)); } while(0)
    #define HAL_LED_ON()           printf("[HAL-SIM] LED ON\n")
    #define HAL_LED_OFF()          printf("[HAL-SIM] LED OFF\n")
    #define HAL_DELAY_MS(ms)       printf("[HAL-SIM] Delay %d ms\n", (ms))
#else
    // Real hardware (STM32 example):
    #include "stm32f4xx_hal.h"
    #define HAL_UART_INIT(baud)    MX_USART2_UART_Init(baud)
    #define HAL_UART_SEND(c)       HAL_UART_Transmit(&huart2, (uint8_t*)&(c), 1, 100)
    #define HAL_LED_ON()           HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
    #define HAL_LED_OFF()          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
    #define HAL_DELAY_MS(ms)       HAL_Delay(ms)
#endif

void blink_and_send(void) {
    HAL_UART_INIT(115200);
    for (int i = 0; i < 3; i++) {
        HAL_LED_ON();
        HAL_DELAY_MS(500);
        HAL_LED_OFF();
        HAL_DELAY_MS(500);
        HAL_UART_SEND('A' + i);
    }
}

int main(void) { blink_and_send(); return 0; }
```

---

#### Program 24: Compile-Time Configuration System

```c
#include <stdio.h>
#include <stdint.h>

// ---- build_config.h (simulated) ----
#define HW_PLATFORM_V2
#define COMM_PROTOCOL_UART
#define BAUD_RATE           115200
#define LOG_LEVEL           3
#define MAX_PACKET_SIZE     256

// ---- Validation ----
#if !defined(HW_PLATFORM_V1) && !defined(HW_PLATFORM_V2)
    #error "Define HW_PLATFORM_V1 or HW_PLATFORM_V2"
#endif

#if MAX_PACKET_SIZE > 1024
    #error "MAX_PACKET_SIZE exceeds hardware buffer limit of 1024"
#endif

// ---- Platform-specific ----
#ifdef HW_PLATFORM_V1
    #define FLASH_SIZE_KB   128
    #define RAM_SIZE_KB     16
#else
    #define FLASH_SIZE_KB   512
    #define RAM_SIZE_KB     128
#endif

int main(void) {
    printf("=== Build Configuration ===\n");
#ifdef HW_PLATFORM_V1
    printf("Platform    : V1\n");
#else
    printf("Platform    : V2\n");
#endif
    printf("Flash       : %d KB\n", FLASH_SIZE_KB);
    printf("RAM         : %d KB\n", RAM_SIZE_KB);
    printf("Baud rate   : %d\n", BAUD_RATE);
    printf("Log level   : %d\n", LOG_LEVEL);
    printf("Packet size : %d\n", MAX_PACKET_SIZE);
    return 0;
}
```

---

#### Program 25: Full Logging Framework

```c
#include <stdio.h>
#include <time.h>

#define LOG_NONE   0
#define LOG_FATAL  1
#define LOG_ERROR  2
#define LOG_WARN   3
#define LOG_INFO   4
#define LOG_DEBUG  5
#define LOG_TRACE  6

#ifndef LOG_LEVEL
    #define LOG_LEVEL  LOG_INFO
#endif

#define _LOG(lvl, tag, fmt, ...) \
    do { \
        if ((lvl) <= LOG_LEVEL) { \
            time_t _t = time(NULL); \
            struct tm *_tm = localtime(&_t); \
            printf("[%02d:%02d:%02d][%s] %s:%d: " fmt "\n", \
                   _tm->tm_hour, _tm->tm_min, _tm->tm_sec, \
                   (tag), __func__, __LINE__, ##__VA_ARGS__); \
        } \
    } while(0)

#define LOGF(fmt, ...)  _LOG(LOG_FATAL, "FATAL", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...)  _LOG(LOG_ERROR, "ERROR", fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...)  _LOG(LOG_WARN,  "WARN ", fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...)  _LOG(LOG_INFO,  "INFO ", fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...)  _LOG(LOG_DEBUG, "DEBUG", fmt, ##__VA_ARGS__)
#define LOGT(fmt, ...)  _LOG(LOG_TRACE, "TRACE", fmt, ##__VA_ARGS__)

void process_data(int count) {
    LOGI("Processing %d items", count);
    for (int i = 0; i < count; i++) {
        LOGD("Processing item %d", i);
        if (i == 2) LOGW("Item %d flagged for review", i);
    }
    LOGI("Processing complete");
}

int main(void) {
    LOGI("Application started");
    process_data(5);
    LOGE("Simulated error condition");
    LOGI("Application exiting");
    return 0;
}
```

---

#### Program 26: Diagnostic Framework

```c
#include <stdio.h>
#include <stdlib.h>

// Compile with -DENABLE_DIAGNOSTICS to activate
#ifdef ENABLE_DIAGNOSTICS
    #define DIAG_ENTER(fn)     printf(">>> ENTER: %s\n", fn)
    #define DIAG_EXIT(fn, ret) printf("<<< EXIT : %s (ret=%d)\n", fn, (int)(ret))
    #define DIAG_VAR(v)        printf("    VAR: " #v " = %d\n", (int)(v))
    #define DIAG_PTR(p)        printf("    PTR: " #p " = %p\n", (void*)(p))
#else
    #define DIAG_ENTER(fn)
    #define DIAG_EXIT(fn, ret)
    #define DIAG_VAR(v)
    #define DIAG_PTR(p)
#endif

int *allocate_array(int size) {
    DIAG_ENTER(__func__);
    DIAG_VAR(size);
    int *arr = malloc(size * sizeof(int));
    DIAG_PTR(arr);
    DIAG_EXIT(__func__, arr ? 0 : -1);
    return arr;
}

int main(void) {
    int *arr = allocate_array(10);
    if (!arr) { fprintf(stderr, "Allocation failed\n"); return 1; }
    for (int i = 0; i < 10; i++) arr[i] = i * i;
    printf("arr[5] = %d\n", arr[5]);
    free(arr);
    return 0;
}
```

---

#### Program 27: Build Configuration Manager

```c
#include <stdio.h>

// ---- Selectable build profiles ----
// Compile: gcc -DBUILD_RELEASE prog27.c
// Default: development

#if defined(BUILD_RELEASE)
    #define BUILD_PROFILE       "RELEASE"
    #define OPTIMIZE_LEVEL      3
    #define ENABLE_ASSERTIONS   0
    #define LOG_LEVEL           1    // Errors only
    #define ENABLE_PROFILING    0
#elif defined(BUILD_TESTING)
    #define BUILD_PROFILE       "TESTING"
    #define OPTIMIZE_LEVEL      0
    #define ENABLE_ASSERTIONS   1
    #define LOG_LEVEL           4
    #define ENABLE_PROFILING    1
#else
    #define BUILD_PROFILE       "DEVELOPMENT"
    #define OPTIMIZE_LEVEL      0
    #define ENABLE_ASSERTIONS   1
    #define LOG_LEVEL           5
    #define ENABLE_PROFILING    0
#endif

#if ENABLE_ASSERTIONS
    #define ASSERT(x)  do { if(!(x)) { printf("ASSERT FAIL: " #x "\n"); } } while(0)
#else
    #define ASSERT(x)  ((void)0)
#endif

int main(void) {
    printf("Build Profile    : %s\n", BUILD_PROFILE);
    printf("Optimization     : O%d\n", OPTIMIZE_LEVEL);
    printf("Assertions       : %s\n", ENABLE_ASSERTIONS ? "ON" : "OFF");
    printf("Log Level        : %d\n", LOG_LEVEL);
    printf("Profiling        : %s\n", ENABLE_PROFILING ? "ON" : "OFF");

    int x = -1;
    ASSERT(x >= 0);
    return 0;
}
```

---

#### Program 28: X-Macro Generic Programming

```c
#include <stdio.h>

// Single source of truth: status code list
#define STATUS_LIST \
    X(STATUS_OK,           0,   "Success")                \
    X(STATUS_ERROR,        1,   "General error")          \
    X(STATUS_TIMEOUT,      2,   "Operation timed out")    \
    X(STATUS_INVALID_ARG,  3,   "Invalid argument")       \
    X(STATUS_NO_MEMORY,    4,   "Out of memory")          \
    X(STATUS_IO_ERROR,     5,   "I/O error")

// Auto-generate enum:
#define X(name, val, str)  name = val,
typedef enum { STATUS_LIST } Status;
#undef X

// Auto-generate string array:
#define X(name, val, str)  [val] = str,
static const char *status_strings[] = { STATUS_LIST };
#undef X

// Auto-generate name array:
#define X(name, val, str)  [val] = #name,
static const char *status_names[] = { STATUS_LIST };
#undef X

const char *status_to_string(Status s) {
    if (s < (int)(sizeof(status_strings)/sizeof(*status_strings)))
        return status_strings[s];
    return "Unknown";
}

int main(void) {
    printf("%-25s %-5s %s\n", "Name", "Val", "Description");
    printf("--------------------------------------------\n");
#define X(name, val, str)  printf("%-25s %-5d %s\n", #name, val, str);
    STATUS_LIST
#undef X

    printf("\nTest lookup:\n");
    printf("Status 2: %s (%s)\n", status_names[2], status_to_string(STATUS_TIMEOUT));
    return 0;
}
```

---

#### Program 29: Packed Structures for Protocol Frames

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Network packet header — must match exact wire format
#pragma pack(push, 1)
typedef struct {
    uint8_t  start_byte;    // 0xAA
    uint8_t  version;       // Protocol version
    uint16_t length;        // Payload length (big-endian)
    uint8_t  msg_type;      // Message type
    uint8_t  flags;         // Control flags
    uint16_t checksum;      // CRC16
} PacketHeader;             // Must be exactly 8 bytes

typedef struct {
    PacketHeader header;
    uint8_t      payload[256];
} Packet;
#pragma pack(pop)

// Flag bits:
#define FLAG_ENCRYPTED  BIT(0)
#define FLAG_COMPRESSED BIT(1)
#define FLAG_PRIORITY   BIT(7)
#define BIT(n)          (1U << (n))

uint16_t simple_checksum(const uint8_t *data, int len) {
    uint16_t sum = 0;
    for (int i = 0; i < len; i++) sum += data[i];
    return sum;
}

int main(void) {
    printf("PacketHeader size: %zu bytes (should be 8)\n", sizeof(PacketHeader));

    Packet pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.header.start_byte = 0xAA;
    pkt.header.version    = 1;
    pkt.header.length     = 5;
    pkt.header.msg_type   = 0x10;
    pkt.header.flags      = FLAG_PRIORITY;
    memcpy(pkt.payload, "Hello", 5);
    pkt.header.checksum = simple_checksum(pkt.payload, 5);

    printf("Packet assembled:\n");
    printf("  Start  : 0x%02X\n", pkt.header.start_byte);
    printf("  Version: %d\n",     pkt.header.version);
    printf("  Length : %d\n",     pkt.header.length);
    printf("  Flags  : 0x%02X\n", pkt.header.flags);
    printf("  CRC    : 0x%04X\n", pkt.header.checksum);
    printf("  Payload: %.*s\n",   pkt.header.length, pkt.payload);
    return 0;
}
```

---

#### Program 30: Driver Configuration Framework

```c
#include <stdio.h>
#include <stdint.h>

// ---- Driver registration using X-Macros and ## ----
#define DRIVER_LIST \
    D(uart,  "UART Driver",  1) \
    D(spi,   "SPI Driver",   1) \
    D(i2c,   "I2C Driver",   0) \
    D(can,   "CAN Driver",   0) \
    D(usb,   "USB Driver",   1)

// Auto-generate init prototypes:
#define D(name, desc, en)  void name##_driver_init(void);
DRIVER_LIST
#undef D

// Auto-generate stub implementations:
#define D(name, desc, en) \
    void name##_driver_init(void) { \
        printf("[DRIVER] %s initialized\n", desc); \
    }
DRIVER_LIST
#undef D

// Auto-generate driver table:
typedef struct { const char *name; void (*init)(void); int enabled; } Driver;

#define D(name, desc, en)  { desc, name##_driver_init, en },
static Driver drivers[] = { DRIVER_LIST };
#undef D

void init_all_drivers(void) {
    int n = sizeof(drivers) / sizeof(drivers[0]);
    printf("Initializing %d drivers...\n", n);
    for (int i = 0; i < n; i++) {
        if (drivers[i].enabled) {
            drivers[i].init();
        } else {
            printf("[DRIVER] %s DISABLED\n", drivers[i].name);
        }
    }
}

int main(void) {
    init_all_drivers();
    return 0;
}
```

**Output:**
```
Initializing 5 drivers...
[DRIVER] UART Driver initialized
[DRIVER] SPI Driver initialized
[DRIVER] I2C Driver DISABLED
[DRIVER] CAN Driver DISABLED
[DRIVER] USB Driver initialized
```

---

## 22. 50+ Interview Questions & Answers

### Basic Level

**Q1: What is the C Preprocessor?**  
A: A text-processing tool that runs before the compiler, handling `#` directives — file inclusion, macro expansion, and conditional compilation. It outputs a `.i` file that the compiler then compiles.

**Q2: What is a macro in C?**  
A: A macro is a symbolic name defined with `#define` that is replaced by its definition (text substitution) before compilation. It can be object-like (constant) or function-like (takes parameters).

**Q3: What is `#include`?**  
A: A directive that copies the entire contents of the specified file into the current source file at that point during preprocessing.

**Q4: Why are header files used?**  
A: Header files declare functions, types, macros, and constants that are shared across multiple `.c` files. They provide the interface contract between modules without duplicating definitions.

**Q5: What is the difference between `#include <file>` and `#include "file"`?**  
A: `<file>` searches system/compiler include directories first. `"file"` searches the current directory first, then falls back to system paths.

**Q6: Does `#define` allocate memory?**  
A: No. `#define` is purely textual substitution. The preprocessor replaces the macro name with its value — no memory is allocated.

**Q7: What is the difference between `#define MAX 100` and `const int MAX = 100`?**  
A: `#define` is textual substitution with no type, no scope, no memory. `const int` has a type, respects scope, can be debugged, and may occupy memory.

**Q8: What is a predefined macro? Name 4.**  
A: Macros automatically defined by the compiler: `__FILE__` (filename), `__LINE__` (line number), `__DATE__` (compile date), `__TIME__` (compile time).

**Q9: What is `#undef`?**  
A: Removes a previously defined macro so it is no longer recognized by the preprocessor from that point forward.

**Q10: How do you see the preprocessed output of a C file?**  
A: `gcc -E main.c -o main.i` or `gcc -E main.c` (outputs to stdout).

---

### Intermediate Level

**Q11: Explain macro expansion with an example.**  
A: When the preprocessor encounters a macro name in source code, it replaces it with the macro's definition. Example: `SQUARE(x+1)` with `#define SQUARE(x) ((x)*(x))` expands to `((x+1)*(x+1))`.

**Q12: What are include guards? Why are they needed?**  
A: A `#ifndef / #define / #endif` block that prevents a header from being processed more than once. Without them, double inclusion causes redefinition errors.

**Q13: What is `#pragma once` and how does it compare to include guards?**  
A: A non-standard but universally supported single-line alternative to include guards. Simpler but may not work with hard links to the same file.

**Q14: What is conditional compilation?**  
A: Using `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif` to include or exclude sections of code at compile time based on macros or expressions.

**Q15: What is the `__func__` predefined identifier?**  
A: A C99 identifier (not strictly a macro) that expands to the name of the enclosing function as a string. Used in logging and debugging.

**Q16: Why wrap multi-statement macros in `do { ... } while(0)`?**  
A: To make the macro behave as a single statement that works correctly with `if`/`else` without braces, and to allow a trailing semicolon naturally.

**Q17: What does `#if defined(X)` do compared to `#ifdef X`?**  
A: Both test if `X` is defined. `#if defined(X)` allows complex boolean expressions: `#if defined(A) && defined(B)`. `#ifdef` only checks one macro.

**Q18: What is the stringizing operator?**  
A: The `#` operator before a macro parameter converts the argument to a string literal: `#define STR(x) #x` → `STR(hello)` becomes `"hello"`.

**Q19: What is the token pasting operator?**  
A: The `##` operator concatenates two tokens: `#define CONCAT(a,b) a##b` → `CONCAT(var, 1)` becomes `var1`.

**Q20: How do you pass a compiler-defined macro from the command line?**  
A: Use `-D` flag: `gcc -DDEBUG -DVERSION=2 main.c`. Equivalent to `#define DEBUG` and `#define VERSION 2` at the top of the file.

---

### Advanced Level

**Q21: What is the `##__VA_ARGS__` trick?**  
A: `##__VA_ARGS__` removes the preceding comma if `__VA_ARGS__` is empty. Useful in variadic macros: `#define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)` works when called as `LOG("hello")` (no extra args).

**Q22: What is `#pragma pack` and when do you use it?**  
A: It controls struct member alignment, eliminating compiler-inserted padding. Used for binary protocol frames, register maps, or any struct that must match an exact byte layout.

**Q23: What is the X-Macro pattern?**  
A: A technique where a list-defining macro is used multiple times with different `X` definitions to generate parallel code structures (enums, string arrays, function tables) from a single source list.

**Q24: What is a compile-time assertion?**  
A: A check evaluated at compile time. `_Static_assert(sizeof(int)==4, "int must be 4 bytes")` causes a compile error if the condition is false — useful to catch platform incompatibilities early.

**Q25: Explain the `container_of` macro from the Linux kernel.**  
A: `container_of(ptr, type, member)` takes a pointer to a struct member and returns a pointer to the enclosing struct. It uses `offsetof()` to calculate the struct's base address.

---

### Expert Level

**Q26: Why doesn't the C preprocessor support recursion?**  
A: The standard prohibits re-expansion of a macro currently being expanded. When `MACRO` expands and encounters `MACRO` in the expansion, it is left unexpanded — preventing infinite loops.

**Q27: How does compiler-dependent behavior affect macros?**  
A: Predefined macros like `__GNUC__`, `_MSC_VER`, `__clang__` differ per compiler. Extensions like `__attribute__((packed))` (GCC) vs `#pragma pack` (MSVC) require `#ifdef` guards for portability.

**Q28: How do you create a type-safe generic macro in C11?**  
A: Use `_Generic`: `#define ABS(x) _Generic((x), int: abs_int, float: abs_float, double: abs_double)(x)` — dispatches to the correct function based on argument type.

**Q29: What is `NDEBUG` and how is it related to `assert()`?**  
A: `NDEBUG` is a standard macro. When defined (e.g., `-DNDEBUG` for release builds), the `assert()` macro expands to `((void)0)` — completely removed, no overhead.

**Q30: How does the Linux kernel use macros to generate module metadata?**  
A: Macros like `MODULE_LICENSE("GPL")`, `module_init()`, `module_exit()` expand to declarations of special ELF section data that the kernel reads when loading the module — no runtime code is generated.

---

### Embedded / Linux Additional Q&A

**Q31–Q50 (Key topics with answers):**

| Q# | Question | Answer Summary |
|----|----------|---------------|
| 31 | What is `volatile` in embedded macros? | `volatile uint32_t *` prevents compiler from caching register reads |
| 32 | Why use `UL` suffix in bit macros? | `BIT(31)` on 32-bit int would overflow; `1UL << 31` is safe |
| 33 | What is HAL in embedded C? | Hardware Abstraction Layer — macros map portable API to hardware-specific code |
| 34 | How is FreeRTOS configured? | Entirely through `#define` in `FreeRTOSConfig.h` |
| 35 | What is AUTOSAR preprocessor use? | Feature activation, memory section placement (`SECTION_CODE_FAST`) |
| 36 | What does `__attribute__((packed))` do? | GCC-specific struct packing — equivalent to `#pragma pack(1)` |
| 37 | What is `offsetof()`? | Macro returning byte offset of struct member — used in `container_of` |
| 38 | How detect 32 vs 64 bit at compile time? | `#if UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF` (64-bit) |
| 39 | What is `__builtin_expect`? | GCC hint for branch prediction: `if (__builtin_expect(err, 0))` |
| 40 | Why not use `#define` for function-like things in C++? | Macros bypass namespaces, templates, RAII; use `inline` and `constexpr` instead |
| 41 | What is a sentinel macro? | A macro (e.g., `END_OF_LIST`) used as a terminator in X-macro lists |
| 42 | How do you conditionally include a library? | `#ifdef USE_LIBSSL` / `#include <openssl/ssl.h>` / `#endif` |
| 43 | What is `#line`? | Overrides `__FILE__` and `__LINE__` — used by code generators |
| 44 | What is `__COUNTER__`? | GCC/Clang macro that gives a unique integer per expansion — useful for unique names |
| 45 | What does `#pragma GCC poison` do? | Makes use of specified identifiers a compile error — prevents use of banned functions |
| 46 | How implement compile-time max without C++? | `#define CT_MAX(a,b) ((a)>(b)?(a):(b))` — works at compile time for constants |
| 47 | What is an anonymous struct in a macro? | `#define DECLARE_NODE struct { int val; struct Node *next; }` |
| 48 | What is `EXPORT_SYMBOL` in Linux kernel? | Macro that exposes a kernel symbol for use by loadable modules |
| 49 | How to prevent a macro from expanding? | Put it in a string `"MACRO"` or use `\` to break tokenization |
| 50 | What is `BUILD_BUG_ON` in Linux kernel? | Compile-time assertion: `#define BUILD_BUG_ON(cond) ((void)sizeof(char[1 - 2*!!(cond)]))` |

---

## 23. Tricky Interview Questions

**Q: What is the output of `SQUARE(2+3)` for `#define SQUARE(x) x*x`?**  
A: `2+3*2+3 = 11` — NOT 25! Missing parentheses. The fix: `#define SQUARE(x) ((x)*(x))`.

---

**Q: What is wrong with this code?**
```c
#define DOUBLE(x)  x + x
int r = DOUBLE(5) * 3;  // Expected: 30
```
A: Expands to `5 + 5 * 3 = 5 + 15 = 20`. Missing outer parentheses. Fix: `#define DOUBLE(x) ((x) + (x))`.

---

**Q: How many times is `x` incremented here?**
```c
#define MAX(a,b)  ((a)>(b)?(a):(b))
int x=5, y=3;
int m = MAX(x++, y++);
```
A: `x` is incremented **twice** — once in the comparison `(x++)>(y++)`, and once again in `(x++)` since the condition is true. This is undefined behavior.

---

**Q: Will this compile? Why or why not?**
```c
#define SWAP(a,b)   int t=a; a=b; b=t;
if (x > y)
    SWAP(x, y);
printf("%d\n", x);
```
A: It compiles but behaves incorrectly. The `if` only captures `int t=x;`. The remaining two statements `x=y; y=t;` execute unconditionally. Fix: use `do { ... } while(0)`.

---

**Q: What does this expand to?**
```c
#define A  "Hello"
#define B  " World"
printf(A B "\n");
```
A: Adjacent string literals are concatenated by the compiler: `printf("Hello" " World" "\n")` → `printf("Hello World\n")`. This works because the preprocessor/compiler concatenates adjacent string literals.

---

**Q: Can you have the same include guard in two different header files?**  
A: Technically no — if two headers share the same guard name, the second one to be included will be completely skipped. Always use unique, descriptive guard names based on the file path.

---

**Q: What is the difference between `#if 0` and `/* comment */`?**  
A: `#if 0 ... #endif` disables code blocks correctly even if they contain `*/` characters that would break a C comment. It's the standard way to comment out large code blocks.

---

**Q: What is the output of:**
```c
#define CAT(a,b)   a##b
printf("%d\n", CAT(1, 2));
```
A: Outputs `12` — the tokens `1` and `2` are pasted into the integer literal `12`.

---

**Q: Why can't you put a `#define` inside a function?**  
A: You can, but the macro is still global — it is visible after the function definition. Macros have no scope. This can cause hard-to-find bugs. Use `#undef` after the function to limit "scope".

---

**Q: What happens when `#pragma pack` is not restored with `pop`?**  
A: The packing setting remains active for all subsequent structs in the translation unit, causing them to be packed unexpectedly. Always use `#pragma pack(push, n)` / `#pragma pack(pop)`.

---

## 24. Real-World Case Studies

### Case Study 1: Embedded Firmware Project (STM32)

**Scenario:** Blinking LED + UART data logger for an IoT sensor device.

```
project/
├── include/
│   ├── config.h        ← #define MCU_FREQ, UART_BAUD, LOG_LEVEL
│   ├── hal_gpio.h      ← HAL_GPIO_SET/CLR macros → maps to hardware
│   └── hal_uart.h      ← HAL_UART_SEND macro
├── src/
│   ├── main.c
│   ├── sensor.c
│   └── hal/
│       ├── gpio.c
│       └── uart.c
└── Makefile
    ← make TARGET=STM32F4 BUILD=RELEASE
    ← CFLAGS += -DTARGET_STM32F4 -DBUILD_RELEASE
```

**Key preprocessor techniques used:**
- `#define GPIOA ((GPIO_TypeDef *)0x40020000UL)` for hardware registers.
- `#pragma pack(1)` for sensor data structures in binary flash logs.
- `#ifdef BUILD_DEBUG` for conditional logging.
- Feature flags `FEATURE_GPS`, `FEATURE_BLUETOOTH` in `config.h`.

---

### Case Study 2: Device Driver Development (Linux)

A Linux kernel character device driver uses:
```c
#include <linux/module.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Engineer Name");

// Kernel-provided macros:
#define DRIVER_NAME     "mychardev"
#define pr_fmt(fmt)     DRIVER_NAME ": " fmt
// pr_info, pr_err now auto-prefix "mychardev: "

pr_info("Device registered at major %d\n", major);
```

---

### Case Study 3: Cross-Platform Library (libnetwork)

```c
// network.h
#if defined(_WIN32)
    #include <winsock2.h>
    typedef SOCKET  net_socket_t;
    #define NET_CLOSE(s)    closesocket(s)
    #define NET_INIT()      do { WSADATA wd; WSAStartup(MAKEWORD(2,2), &wd); } while(0)
#elif defined(__linux__) || defined(__APPLE__)
    #include <sys/socket.h>
    #include <unistd.h>
    typedef int     net_socket_t;
    #define NET_CLOSE(s)    close(s)
    #define NET_INIT()      ((void)0)
#endif
// Same application code works on Windows, Linux, macOS
```

---

### Case Study 4: Automotive Software (AUTOSAR)

AUTOSAR Standard uses macros for:
```c
// Memory section placement:
#define OS_START_SEC_CODE
#include "MemMap.h"
FUNC(void, OS_CODE) OsTask_10ms(void);
#define OS_STOP_SEC_CODE
#include "MemMap.h"

// MemMap.h switches #pragma section based on macro → places code in specific ROM region
```

---

### Case Study 5: RTOS Configuration (FreeRTOS)

All of FreeRTOS behavior is controlled via preprocessor:
```c
// FreeRTOSConfig.h
#define configUSE_PREEMPTION            1
#define configUSE_TIME_SLICING          1
#define configCPU_CLOCK_HZ              216000000UL
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            7
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 75 * 1024 ) )
// 50+ such macros control the entire RTOS configuration
```

---

## 25. Common Mistakes

### 1. Missing Parentheses in Macros
```c
// WRONG:
#define AREA(r)  3.14 * r * r
AREA(2+1) → 3.14 * 2+1 * 2+1 = wrong!

// CORRECT:
#define AREA(r)  (3.14 * (r) * (r))
```

### 2. Multiple Inclusion Without Guards
```c
// WRONG: header.h included twice → redefinition errors
// CORRECT: add #ifndef / #define / #endif or #pragma once
```

### 3. Macro Naming Conflicts
```c
// WRONG: lowercase macros conflict with functions
#define max(a,b) ...   // Conflicts with C++ std::max, POSIX max()

// CORRECT: ALL_CAPS always
#define MAX(a,b) ...
```

### 4. Forgetting do-while(0)
```c
// WRONG:
#define LOG_AND_RETURN(v)  printf("val=%d\n",(v)); return (v);

if (err)
    LOG_AND_RETURN(-1);  // Only printf is in the if!

// CORRECT:
#define LOG_AND_RETURN(v)  do { printf("val=%d\n",(v)); return (v); } while(0)
```

### 5. Side Effects from Multiple Evaluation
```c
// WRONG: MAX(x++, y++) increments twice
// CORRECT: Use inline function or assign to temp first
int _a = x++; int _b = y++;
int m = MAX(_a, _b);
```

### 6. Not Restoring #pragma pack
```c
// WRONG:
#pragma pack(1)
typedef struct { ... } MyPacked;
// Forgot #pragma pack(pop) — next struct is also packed!

// CORRECT:
#pragma pack(push, 1)
typedef struct { ... } MyPacked;
#pragma pack(pop)
```

---

## 26. Best Practices

### Macro Naming Conventions
```c
// Constants and object macros: ALL_CAPS
#define MAX_SIZE    1024
#define BUFFER_LEN  256

// Function-like macros: ALL_CAPS
#define SQUARE(x)   ((x)*(x))

// Internal macro helpers: leading underscore + ALL_CAPS
#define _LOG_IMPL(lvl, fmt, ...) ...

// Avoid: lowercase macros (conflict with functions/variables)
```

### Safe Macro Design Checklist
- [ ] Wrap every parameter in `()`
- [ ] Wrap entire expression in `()`
- [ ] Use `do { } while(0)` for multi-statement macros
- [ ] Avoid evaluating arguments more than once
- [ ] Add a comment explaining complex macros
- [ ] Use `static inline` instead of function-like macros when type safety matters

### Include Guard Standards
```c
// Recommended format: <PROJECT>_<MODULE>_<FILENAME>_H
#ifndef MYFW_DRIVERS_UART_H   // unique project prefix
#define MYFW_DRIVERS_UART_H
// ...
#endif /* MYFW_DRIVERS_UART_H */
```

### Portability Guidelines
```c
// Check for C standard version:
#if __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(c, m)  _Static_assert(c, m)
#else
    #define STATIC_ASSERT(c, m)  typedef char sa_[(c)?1:-1]
#endif

// Use standard integer types:
#include <stdint.h>   // uint32_t, int16_t etc. — not int, long
```

---

## 27. Memory Diagrams & Flowcharts

### Compilation Process Flow

```
Source (.c)
    │
    ▼
┌─────────────────────────────────┐
│         PREPROCESSOR (cpp)      │
│  1. Process #include → paste    │
│  2. Expand #define macros       │
│  3. Evaluate #if/#ifdef         │
│  4. Output: expanded .i file    │
└──────────────┬──────────────────┘
               │
               ▼
┌─────────────────────────────────┐
│    COMPILER (cc1 / clang)       │
│  1. Lexing → tokens             │
│  2. Parsing → AST               │
│  3. Semantic analysis           │
│  4. Code generation             │
│  5. Output: assembly .s         │
└──────────────┬──────────────────┘
               │
               ▼
┌─────────────────────────────────┐
│       ASSEMBLER (as)            │
│  Converts assembly to binary    │
│  Output: relocatable .o         │
└──────────────┬──────────────────┘
               │
               ▼
┌─────────────────────────────────┐
│         LINKER (ld)             │
│  Resolves symbol references     │
│  Combines .o + libraries        │
│  Output: executable             │
└─────────────────────────────────┘
```

### Macro Expansion Flow

```
Source code:
   int r = SQUARE(x + 1);

Preprocessor scan:
   1. Find token: SQUARE
   2. Is it a macro? YES → function-like
   3. Collect argument: "x + 1"
   4. Replace each (x) in body with (x + 1):
         ((x + 1) * (x + 1))
   5. Substitute in source:
         int r = ((x + 1) * (x + 1));

Output to .i:
   int r = ((x + 1) * (x + 1));
```

### Header Inclusion Flow

```
main.c
  │
  ├── #include "app.h"
  │     ├── #ifndef APP_H → not defined → process
  │     ├── #define APP_H
  │     ├── #include "config.h"
  │     │     ├── #ifndef CONFIG_H → process
  │     │     ├── #define CONFIG_H
  │     │     └── ... config macros ...
  │     └── ... app declarations ...
  │
  └── #include "app.h"  (second time)
        ├── #ifndef APP_H → ALREADY DEFINED
        └── Entire block SKIPPED ✓
```

### Conditional Compilation Flow

```
Source has:
  #ifdef DEBUG
    [block A]
  #elif RELEASE
    [block B]
  #else
    [block C]
  #endif

Preprocessor evaluation:
  ┌─────────────────────────┐
  │  Is DEBUG defined?       │
  │  YES → include block A   │──→ Compiled code: [block A]
  │  NO  ──────────────┐     │
  └────────────────────┼─────┘
                       ▼
  ┌─────────────────────────┐
  │  Is RELEASE defined?    │
  │  YES → include block B  │──→ Compiled code: [block B]
  │  NO  ──────────────┐    │
  └────────────────────┼────┘
                       ▼
                 Include block C  ──→ Compiled code: [block C]
```

---

## 28. Learning & Interview Preparation Roadmap

### Beginner (0–1 Year)

**Master these topics:**
- [ ] What is a preprocessor and where it fits in compilation
- [ ] `#define` — object-like macros (constants)
- [ ] `#include` — system vs user headers
- [ ] Include guards (`#ifndef / #define / #endif`)
- [ ] `#ifdef / #ifndef / #endif` — basic conditional compilation
- [ ] `__FILE__`, `__LINE__`, `__DATE__`, `__TIME__`

**Practice programs:** 1–10 from this guide  
**Tools:** `gcc -E` to inspect expanded output

---

### Intermediate (1–3 Years)

**Master these topics:**
- [ ] Function-like macros with parenthesization rules
- [ ] `do { } while(0)` multi-statement macros
- [ ] Variadic macros (`__VA_ARGS__`, `##__VA_ARGS__`)
- [ ] `#pragma once` and include guard conventions
- [ ] `#error` and `#warning` for compile-time validation
- [ ] `#undef` and macro scoping strategies
- [ ] Logging frameworks using predefined macros
- [ ] Feature flags and build configuration
- [ ] `#pragma pack` and structure packing

**Practice programs:** 11–20 from this guide

---

### Experienced (3–5 Years)

**Master these topics:**
- [ ] Stringizing (`#`) and token pasting (`##`) operators
- [ ] X-Macro metaprogramming pattern
- [ ] `_Static_assert` and compile-time assertions
- [ ] `_Generic` and type-generic macros (C11)
- [ ] Complex multi-layer macro systems
- [ ] HAL design using macros
- [ ] `container_of`, `ARRAY_SIZE` and kernel-style macros
- [ ] Performance: macro vs `static inline` trade-offs

**Practice programs:** 21–30 from this guide

---

### Embedded Engineers

**Focus:**
- [ ] Register address macros with correct `volatile` and `UL` suffixes
- [ ] Bit manipulation macro libraries (`BIT()`, `SET_BIT()`, `GET_FIELD()`)
- [ ] HAL macros for GPIO, UART, SPI, I2C abstraction
- [ ] `#pragma pack(1)` for protocol frames and register maps
- [ ] FreeRTOS/CMSIS configuration macros
- [ ] Feature flags for product variant management
- [ ] AUTOSAR section placement macros

---

### Linux Developers

**Focus:**
- [ ] `container_of`, `offsetof`, `ARRAY_SIZE`
- [ ] `module_init`, `module_exit`, `MODULE_LICENSE`
- [ ] `pr_info`, `pr_err` and `pr_fmt` customization
- [ ] `BUILD_BUG_ON`, `BUILD_BUG_ON_ZERO`
- [ ] `__attribute__((packed))`, `__attribute__((aligned(n)))`
- [ ] `EXPORT_SYMBOL`, `EXPORT_SYMBOL_GPL`
- [ ] Conditional feature inclusion via Kconfig (`CONFIG_*` macros)

---

### Summary Quick Reference

| Topic | Key Directives | Key Programs |
|-------|---------------|--------------|
| File inclusion | `#include <> ""` | 7, 18, 20 |
| Constants | `#define`, `const` | 1, 2, 3 |
| Function macros | `#define F(x)` | 4, 5, 19 |
| Conditional | `#if #ifdef #elif #else` | 6, 11, 17 |
| Guards | `#ifndef / #pragma once` | 7, 8 |
| Predefined | `__FILE__ __LINE__` | 8, 9, 10 |
| Operators | `# ##` | 12, 13 |
| Logging | `#define LOG` | 14, 25 |
| Versioning | `MAKE_VERSION` | 15 |
| Assertions | `#define ASSERT` | 16, 26 |
| Pragma pack | `#pragma pack(1)` | 29 |
| Embedded | Registers, HAL | 21, 22, 23 |
| Advanced | X-Macro, Generic | 28, 30 |

---

*End of C Preprocessor Directives — Complete Training Manual*  
*Cover: Theory · 30 Programs · 50+ Interview Q&A · Embedded · Linux · Best Practices · Roadmap*
