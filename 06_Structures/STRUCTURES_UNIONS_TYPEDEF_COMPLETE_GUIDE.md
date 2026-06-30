# Structures, Unions, and Typedef in C
## Complete Professional Training Material & Interview Handbook
### Beginner to Expert Level

---

## TABLE OF CONTENTS

1. [Introduction to Structures](#1-introduction-to-structures)
2. [Structure (struct) In Depth](#2-structure-struct-in-depth)
   - 2.1 Definition & Syntax
   - 2.2 Declaration & Initialization
   - 2.3 Accessing Members
   - 2.4 Arrays of Structures
   - 2.5 Nested Structures
   - 2.6 Structures and Functions
   - 2.7 Structures with Pointers
   - 2.8 Self-Referential Structures
   - 2.9 Dynamic Memory Allocation
   - 2.10 Real-World Applications
3. [Structure Memory Concepts](#3-structure-memory-concepts)
   - 3.1 Memory Layout
   - 3.2 Alignment & Padding
   - 3.3 Packing
   - 3.4 sizeof Operator
4. [Union (union) In Depth](#4-union-union-in-depth)
   - 4.1 Introduction & Syntax
   - 4.2 Memory Sharing
   - 4.3 Real-World Use Cases
   - 4.4 Embedded Systems Applications
5. [Structure vs Union Comparison](#5-structure-vs-union-comparison)
6. [Typedef In Depth](#6-typedef-in-depth)
7. [Advanced Topics](#7-advanced-topics)
   - 7.1 Bit-Fields
   - 7.2 Anonymous Structures & Unions
   - 7.3 Const & Volatile Structures
   - 7.4 Memory-Mapped Registers
   - 7.5 Embedded C & Linux Driver Applications
8. [Practical C Programs](#8-practical-c-programs)
   - 8.1 Beginner Level (10 Programs)
   - 8.2 Intermediate Level (10 Programs)
   - 8.3 Advanced Level (5 Programs)
9. [50+ Interview Questions & Answers](#9-50-interview-questions--answers)
10. [Tricky Interview Questions](#10-tricky-interview-questions)
11. [Common Mistakes & How to Avoid Them](#11-common-mistakes--how-to-avoid-them)
12. [Interview Preparation Roadmap](#12-interview-preparation-roadmap)

---

## 1. INTRODUCTION TO STRUCTURES

### What is a Structure?

In C, a **structure** is a user-defined data type that groups together variables of **different data types** under a single name. It allows you to model real-world entities (like a student, employee, or hardware register) in code.

### Why Do We Need Structures?

Consider storing data about a student:
```c
// Without structures — messy and unrelated variables
int student_id;
char student_name[50];
float student_gpa;

// With structures — clean, grouped, logical
struct Student {
    int id;
    char name[50];
    float gpa;
};
```

### Structures vs Arrays

| Feature        | Array                        | Structure                          |
|----------------|------------------------------|------------------------------------|
| Data types     | Same type only               | Different types allowed            |
| Access         | By index (`arr[0]`)          | By member name (`s.name`)          |
| Use case       | Collection of same items     | Entity with multiple attributes    |
| Memory         | Contiguous, same-size slots  | Contiguous, possibly with padding  |

---

## 2. STRUCTURE (struct) IN DEPTH

### 2.1 Definition & Syntax

```c
struct tag_name {
    data_type member1;
    data_type member2;
    // ...
};
```

**Example:**
```c
struct Point {
    int x;
    int y;
};
```

### 2.2 Declaration & Initialization

#### Method 1: Declare after definition
```c
struct Student {
    int id;
    char name[50];
    float gpa;
};

struct Student s1;   // Declaration
```

#### Method 2: Declare at definition time
```c
struct Student {
    int id;
    char name[50];
    float gpa;
} s1, s2;            // s1, s2 declared immediately
```

#### Method 3: Anonymous struct (no tag)
```c
struct {
    int x;
    int y;
} point1;
```

#### Initialization

```c
// Method 1: Positional
struct Student s1 = {101, "Alice", 3.9};

// Method 2: Designated initializer (C99+)
struct Student s2 = { .id = 102, .gpa = 3.7, .name = "Bob" };

// Method 3: After declaration
struct Student s3;
s3.id   = 103;
strcpy(s3.name, "Charlie");
s3.gpa  = 3.5;
```

### 2.3 Accessing Members

Use the **dot operator (`.`)** for direct struct variables, and **arrow operator (`->`)** for pointers.

```c
struct Student s1 = {101, "Alice", 3.9};
struct Student *ptr = &s1;

// Dot operator
printf("%d %s %.2f\n", s1.id, s1.name, s1.gpa);

// Arrow operator
printf("%d %s %.2f\n", ptr->id, ptr->name, ptr->gpa);

// Equivalent: (*ptr).id == ptr->id
```

### 2.4 Arrays of Structures

```c
struct Student class[30];    // Array of 30 Student structs

// Initialize
class[0].id = 1;
strcpy(class[0].name, "Alice");
class[0].gpa = 3.9;

// Iterate
for (int i = 0; i < 30; i++) {
    printf("%d: %s - %.2f\n", class[i].id, class[i].name, class[i].gpa);
}
```

### 2.5 Nested Structures

A structure can contain another structure as a member.

```c
struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    int id;
    char name[50];
    struct Date joining_date;    // Nested structure
    float salary;
};

// Access
struct Employee emp = {1, "John", {15, 6, 2020}, 55000.0};
printf("Joined: %d/%d/%d\n",
       emp.joining_date.day,
       emp.joining_date.month,
       emp.joining_date.year);
```

### 2.6 Structures and Functions

#### Passing Structure by Value

```c
void display(struct Student s) {     // Entire struct is copied
    printf("%d %s %.2f\n", s.id, s.name, s.gpa);
}
// Changes inside function do NOT affect original
```

#### Passing Structure by Reference (Pointer)

```c
void update_gpa(struct Student *s, float new_gpa) {
    s->gpa = new_gpa;    // Modifies original
}

// Call
struct Student s1 = {1, "Alice", 3.5};
update_gpa(&s1, 3.9);
```

#### Returning Structure from Function

```c
struct Point create_point(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;    // Returns a copy
}

struct Point origin = create_point(0, 0);
```

> **Best Practice:** Always pass large structures by pointer (`const struct T *`) to avoid expensive copies.

### 2.7 Structures with Pointers

```c
struct Node {
    int data;
    struct Node *next;    // Pointer to same type (for linked list)
};

// Dynamic allocation
struct Student *ptr = (struct Student *)malloc(sizeof(struct Student));
if (ptr == NULL) {
    // Handle allocation failure
    exit(EXIT_FAILURE);
}
ptr->id = 1;
strcpy(ptr->name, "Alice");
ptr->gpa = 3.9;

free(ptr);   // Always free!
```

### 2.8 Self-Referential Structures

A structure that contains a pointer to itself — the foundation of linked lists, trees, and graphs.

```c
struct Node {
    int data;
    struct Node *next;   // Self-referential pointer
};

// Build a linked list
struct Node *head = NULL;
struct Node *n1   = malloc(sizeof(struct Node));
struct Node *n2   = malloc(sizeof(struct Node));

n1->data = 10; n1->next = n2;
n2->data = 20; n2->next = NULL;
head = n1;
```

**Memory Diagram:**
```
head --> [ 10 | *next ] --> [ 20 | NULL ]
```

### 2.9 Dynamic Memory Allocation for Structures

```c
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char *name;     // Dynamic string
    float salary;
};

struct Employee *create_employee(int id, const char *name, float salary) {
    struct Employee *e = malloc(sizeof(struct Employee));
    if (!e) return NULL;

    e->id     = id;
    e->name   = malloc(strlen(name) + 1);
    if (!e->name) { free(e); return NULL; }
    strcpy(e->name, name);
    e->salary = salary;
    return e;
}

void free_employee(struct Employee *e) {
    if (e) {
        free(e->name);
        free(e);
    }
}
```

### 2.10 Real-World Applications

| Domain              | Example Use                             |
|---------------------|-----------------------------------------|
| Operating Systems   | `struct task_struct` (Linux process)    |
| Networking          | `struct sockaddr`, packet headers       |
| File Systems        | `struct inode`, `struct dirent`         |
| Embedded Systems    | Hardware register maps                  |
| Databases           | Table row representation                |
| Game Development    | Game entity (position, health, sprite)  |

---

## 3. STRUCTURE MEMORY CONCEPTS

### 3.1 Memory Layout

Structure members are stored **sequentially in memory**, but not always at consecutive byte addresses due to **alignment requirements**.

```c
struct Example {
    char  a;    // 1 byte
    int   b;    // 4 bytes
    char  c;    // 1 byte
};
```

**Memory Layout (without packing):**
```
Offset 0:  [a]  [pad][pad][pad]
Offset 4:  [b0] [b1] [b2] [b3]
Offset 8:  [c]  [pad][pad][pad]

Total size: 12 bytes
```

### 3.2 Alignment & Padding

**Alignment rule:** Each member must start at an address that is a multiple of its size.

| Type     | Typical Size | Alignment |
|----------|-------------|-----------|
| `char`   | 1 byte      | 1 byte    |
| `short`  | 2 bytes     | 2 bytes   |
| `int`    | 4 bytes     | 4 bytes   |
| `double` | 8 bytes     | 8 bytes   |
| pointer  | 4/8 bytes   | 4/8 bytes |

```c
struct Padded {
    char  a;     // offset 0
    // 3 bytes padding
    int   b;     // offset 4
    char  c;     // offset 8
    // 3 bytes padding (trailing, to make total multiple of 4)
};
// sizeof = 12

struct Optimized {
    int   b;     // offset 0
    char  a;     // offset 4
    char  c;     // offset 5
    // 2 bytes padding
};
// sizeof = 8
```

> **Tip:** Order members from **largest to smallest** to minimize padding.

### 3.3 Packing

Force the compiler to remove padding using `#pragma pack` or `__attribute__((packed))`:

```c
// GCC/Clang
struct __attribute__((packed)) Packed {
    char  a;    // offset 0
    int   b;    // offset 1 (unaligned!)
    char  c;    // offset 5
};
// sizeof = 6  (no padding)

// MSVC / Cross-platform
#pragma pack(push, 1)
struct Packed {
    char  a;
    int   b;
    char  c;
};
#pragma pack(pop)
```

> **Warning:** Packed structs cause **unaligned memory access** which can crash on ARM and be slow on x86. Use only when necessary (network packets, file formats).

### 3.4 sizeof Operator

```c
struct Student {
    int   id;       // 4 bytes
    char  name[20]; // 20 bytes
    float gpa;      // 4 bytes
};
// sizeof = 28 (no padding needed here — well aligned)

printf("Size: %zu\n", sizeof(struct Student));  // 28

struct Student arr[10];
printf("Array size: %zu\n", sizeof(arr));        // 280
printf("Count: %zu\n", sizeof(arr) / sizeof(arr[0])); // 10
```

**Interview Question — Size Calculation:**
```c
struct Q {
    char  a;     // 1 byte  + 3 pad
    int   b;     // 4 bytes
    short c;     // 2 bytes + 2 pad
    double d;    // 8 bytes
};
// Total = 1+3 + 4 + 2+2 + 8 = 20 bytes? 
// Wait — struct alignment = largest member = 8 (double)
// offset of d must be multiple of 8 → offset 8 is fine
// a(1)+pad(3)+b(4)+c(2)+pad(2)+d(8) = 20 bytes ✓
printf("%zu\n", sizeof(struct Q)); // 20
```

---

## 4. UNION (union) IN DEPTH

### 4.1 Introduction & Syntax

A **union** is a special data type where **all members share the same memory location**. The size of a union equals the size of its **largest member**.

```c
union Data {
    int    i;
    float  f;
    char   str[20];
};

// Usage
union Data d;
d.i = 10;
printf("%d\n", d.i);  // 10

d.f = 3.14;
printf("%f\n", d.f);  // 3.14
// Note: d.i is now garbage (memory overwritten)
```

### 4.2 Memory Sharing

**Memory Diagram:**
```
union Data {           Byte: 0  1  2  3  4  5 ... 19
    int    i;         [i0][i1][i2][i3]
    float  f;         [f0][f1][f2][f3]
    char   str[20];   [s0][s1][s2][s3][s4][s5]...[s19]
};

All members start at the SAME address!
sizeof(union Data) = 20  (largest member: char str[20])
```

### 4.3 Real-World Use Cases

#### 1. Protocol Parsing (Network / Serial)
```c
union Packet {
    uint8_t raw[4];
    struct {
        uint8_t  cmd;
        uint8_t  len;
        uint16_t checksum;
    } fields;
};

union Packet pkt;
pkt.raw[0] = 0x01;
pkt.raw[1] = 0x02;
// Access as fields
printf("CMD: 0x%02X\n", pkt.fields.cmd);
```

#### 2. Type Punning (Float to Bits)
```c
union FloatBits {
    float    f;
    uint32_t bits;
};

union FloatBits fb;
fb.f = 3.14f;
printf("Float bits: 0x%08X\n", fb.bits);
```

#### 3. Variant Type (Tagged Union)
```c
enum ValueType { INT_VAL, FLOAT_VAL, STRING_VAL };

struct Variant {
    enum ValueType type;
    union {
        int   i;
        float f;
        char  s[32];
    } value;
};
```

### 4.4 Embedded Systems Applications

```c
// Hardware register as union
union StatusRegister {
    uint8_t byte;
    struct {
        uint8_t tx_ready  : 1;
        uint8_t rx_ready  : 1;
        uint8_t overflow  : 1;
        uint8_t parity_err: 1;
        uint8_t reserved  : 4;
    } bits;
};

volatile union StatusRegister *UART_STATUS = (union StatusRegister *)0x40013800;

if (UART_STATUS->bits.tx_ready) {
    // Safe to transmit
}
```

---

## 5. STRUCTURE VS UNION COMPARISON

### Detailed Comparison Table

| Feature                | struct                                | union                                  |
|------------------------|---------------------------------------|----------------------------------------|
| Memory                 | Sum of all members (+ padding)        | Size of largest member                 |
| Member storage         | Each member has its own memory        | All members share same memory          |
| Simultaneous access    | All members accessible at any time    | Only one member valid at a time        |
| Initialization         | Can init all members                  | Only first member can be initialized   |
| sizeof                 | >= sum of all member sizes            | == size of largest member              |
| Use case               | Group related data (entity)           | Memory-efficient variant / overlay     |
| Safety                 | Safer — no overlap                    | Risky if wrong member accessed         |
| Padding                | Yes — between and after members       | Only trailing (to alignment boundary)  |

### Memory Usage Example

```c
struct S {
    int   a;    // 4
    float b;    // 4
    char  c;    // 1 + 3 pad
};
// sizeof(struct S) = 12

union U {
    int   a;    // 4
    float b;    // 4
    char  c;    // 1
};
// sizeof(union U) = 4
```

### When to Use Which

| Situation                                 | Use       |
|-------------------------------------------|-----------|
| Store all attributes of an entity         | struct    |
| Store one of several possible types       | union     |
| Hardware register mapping                 | union     |
| Network packet with multiple views        | union     |
| Student record with name, ID, GPA         | struct    |
| Save memory in embedded (limited RAM)     | union     |

---

## 6. TYPEDEF IN DEPTH

### 6.1 Introduction & Purpose

`typedef` creates an **alias** for an existing type. It improves readability, portability, and enables cleaner APIs.

```c
typedef existing_type new_name;
```

### 6.2 Typedef with Primitive Types

```c
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long long uint64_t;

// Now use cleaner names
uint8_t  reg_val = 0xFF;
uint32_t address = 0x40020000;
```

### 6.3 Typedef with Structures

```c
// Without typedef
struct Point {
    int x;
    int y;
};
struct Point p1;   // Must write 'struct' every time

// With typedef
typedef struct Point {
    int x;
    int y;
} Point;
Point p2;          // Clean!

// Or anonymous struct
typedef struct {
    int x;
    int y;
} Point;
Point p3;
```

### 6.4 Typedef with Unions

```c
typedef union {
    uint32_t word;
    uint16_t half[2];
    uint8_t  byte[4];
} Register32;

Register32 reg;
reg.word = 0xDEADBEEF;
printf("High byte: 0x%02X\n", reg.byte[3]);
```

### 6.5 Typedef with Pointers

```c
typedef int* IntPtr;
IntPtr p1, p2;    // Both are int pointers

// Warning: this is confusing — prefer explicit *
// typedef int* IntPtr;
// IntPtr p1, p2;   — both pointers, OK
// But: int* p1, p2; — p1 is pointer, p2 is int!

// Function pointer typedef
typedef int (*Comparator)(const void *, const void *);
Comparator cmp = strcmp;
```

### 6.6 Industry Coding Standards

```c
// Linux kernel style — lowercase with _t suffix
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// POSIX / stdint.h standard types
#include <stdint.h>
#include <stdbool.h>

// Embedded firmware style
typedef uint8_t  BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef bool     BOOL;
```

---

## 7. ADVANCED TOPICS

### 7.1 Bit-Fields

Bit-fields allow packing data at the **bit level** within a struct or union.

```c
struct Flags {
    unsigned int read    : 1;   // 1 bit
    unsigned int write   : 1;   // 1 bit
    unsigned int execute : 1;   // 1 bit
    unsigned int reserved: 29;  // 29 bits
};
// sizeof = 4 (fits in one int)

struct Flags f = {1, 1, 0, 0};
if (f.read) printf("Readable\n");
```

#### Hardware Register with Bit-Fields
```c
typedef struct {
    uint32_t enable     : 1;
    uint32_t mode       : 2;
    uint32_t prescaler  : 8;
    uint32_t reserved   : 21;
} TimerConfig;

volatile TimerConfig *TIMER0 = (TimerConfig *)0x40001000;
TIMER0->enable    = 1;
TIMER0->mode      = 2;
TIMER0->prescaler = 72;
```

#### Bit-Field Limitations
- Cannot take address of a bit-field member
- Bit-fields across bytes are implementation-defined
- Use `unsigned int` or `uint32_t` for portability

### 7.2 Anonymous Structures & Unions

```c
// Anonymous union inside struct
struct Variant {
    int type;
    union {         // No tag name — access members directly
        int   i_val;
        float f_val;
        char  s_val[32];
    };
};

struct Variant v;
v.type  = 0;
v.i_val = 42;   // Direct access — no union name needed
```

```c
// Anonymous struct inside union
union Register {
    uint32_t value;
    struct {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    };
};

union Register r;
r.value = 0x12345678;
printf("Byte0: 0x%02X\n", r.byte0);  // 0x78 (little-endian)
```

### 7.3 Const & Volatile Structures

```c
// const struct — members cannot be modified
const struct Point origin = {0, 0};
// origin.x = 5;  // ERROR!

// const pointer to struct
const struct Point *p = &origin;
// p->x = 5;  // ERROR — cannot modify through const pointer

// Pointer to const vs const pointer
struct Point pt = {1, 2};
struct Point *const fixed_ptr = &pt;  // Pointer cannot change, value can
const struct Point *read_ptr  = &pt;  // Value cannot change, pointer can

// volatile — tells compiler not to optimize accesses
// Used for memory-mapped hardware registers
volatile struct StatusReg *uart = (volatile struct StatusReg *)0x40013800;
```

### 7.4 Memory-Mapped Registers

```c
// STM32-style peripheral register struct
typedef struct {
    volatile uint32_t CR1;     // 0x00 - Control Register 1
    volatile uint32_t CR2;     // 0x04 - Control Register 2
    volatile uint32_t SR;      // 0x08 - Status Register
    volatile uint32_t DR;      // 0x0C - Data Register
    volatile uint32_t BRR;     // 0x10 - Baud Rate Register
} USART_TypeDef;

#define USART1_BASE  0x40013800
#define USART1       ((USART_TypeDef *)USART1_BASE)

// Usage
USART1->CR1  |= (1 << 13);  // Enable USART
USART1->BRR   = 0x0683;     // Set baud rate
```

### 7.5 Linux Driver Examples

```c
// Linux kernel — struct file_operations
#include <linux/fs.h>

static struct file_operations my_fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_release,
    .read    = my_read,
    .write   = my_write,
    .unlocked_ioctl = my_ioctl,
};

// Designated initializers — C99, used extensively in kernel
// Struct as device descriptor
struct my_device {
    struct cdev   cdev;
    dev_t         devno;
    struct mutex  lock;
    uint8_t      *buffer;
    size_t        buf_size;
};
```

---

## 8. PRACTICAL C PROGRAMS

### 8.1 Beginner Level

---

#### Program 1: Basic Student Record

**Problem:** Create a structure to store and display student information.

```c
#include <stdio.h>
#include <string.h>

struct Student {
    int   id;
    char  name[50];
    float gpa;
};

int main(void) {
    struct Student s1 = {1, "Alice Johnson", 3.9f};

    printf("=== Student Record ===\n");
    printf("ID   : %d\n",   s1.id);
    printf("Name : %s\n",   s1.name);
    printf("GPA  : %.2f\n", s1.gpa);

    return 0;
}
```

**Output:**
```
=== Student Record ===
ID   : 1
Name : Alice Johnson
GPA  : 3.90
```

**Interview Discussion:** Why use a struct instead of separate variables? Structs group related data logically, allow passing all related data in one function call, and make arrays of entities easy to manage.

---

#### Program 2: Array of Structures

**Problem:** Store and display 3 student records using an array of structures.

```c
#include <stdio.h>

struct Student {
    int   id;
    char  name[50];
    float gpa;
};

int main(void) {
    struct Student class[3] = {
        {1, "Alice", 3.9f},
        {2, "Bob",   3.5f},
        {3, "Carol", 3.7f}
    };

    printf("%-5s %-15s %-5s\n", "ID", "Name", "GPA");
    printf("-----------------------------\n");
    for (int i = 0; i < 3; i++) {
        printf("%-5d %-15s %.2f\n",
               class[i].id, class[i].name, class[i].gpa);
    }
    return 0;
}
```

**Output:**
```
ID    Name            GPA
-----------------------------
1     Alice           3.90
2     Bob             3.50
3     Carol           3.70
```

---

#### Program 3: Nested Structure — Employee with Date

**Problem:** Store employee data including joining date using nested structures.

```c
#include <stdio.h>

struct Date {
    int day, month, year;
};

struct Employee {
    int        id;
    char       name[50];
    float      salary;
    struct Date joined;
};

int main(void) {
    struct Employee e = {101, "John Smith", 75000.0f, {15, 3, 2019}};

    printf("ID      : %d\n", e.id);
    printf("Name    : %s\n", e.name);
    printf("Salary  : $%.2f\n", e.salary);
    printf("Joined  : %02d/%02d/%04d\n",
           e.joined.day, e.joined.month, e.joined.year);
    return 0;
}
```

**Output:**
```
ID      : 101
Name    : John Smith
Salary  : $75000.00
Joined  : 15/03/2019
```

---

#### Program 4: Passing Structure to Function

**Problem:** Pass a structure to a function to calculate GPA category.

```c
#include <stdio.h>

struct Student {
    int   id;
    char  name[50];
    float gpa;
};

const char* get_grade(struct Student s) {
    if (s.gpa >= 3.7f)  return "Distinction";
    if (s.gpa >= 3.0f)  return "Merit";
    if (s.gpa >= 2.0f)  return "Pass";
    return "Fail";
}

int main(void) {
    struct Student s = {1, "Alice", 3.85f};
    printf("%s: %s\n", s.name, get_grade(s));
    return 0;
}
```

**Output:**
```
Alice: Distinction
```

---

#### Program 5: Pointer to Structure

**Problem:** Use a pointer to modify structure members inside a function.

```c
#include <stdio.h>

struct Rectangle {
    float width;
    float height;
};

void scale(struct Rectangle *r, float factor) {
    r->width  *= factor;
    r->height *= factor;
}

float area(const struct Rectangle *r) {
    return r->width * r->height;
}

int main(void) {
    struct Rectangle rect = {5.0f, 3.0f};
    printf("Area before: %.2f\n", area(&rect));
    scale(&rect, 2.0f);
    printf("Area after : %.2f\n", area(&rect));
    return 0;
}
```

**Output:**
```
Area before: 15.00
Area after : 60.00
```

---

#### Program 6: Returning Structure from Function

**Problem:** Create a function that returns a structure.

```c
#include <stdio.h>
#include <math.h>

struct Point { float x, y; };

struct Point midpoint(struct Point a, struct Point b) {
    struct Point mid;
    mid.x = (a.x + b.x) / 2.0f;
    mid.y = (a.y + b.y) / 2.0f;
    return mid;
}

float distance(struct Point a, struct Point b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx*dx + dy*dy);
}

int main(void) {
    struct Point p1 = {0.0f, 0.0f};
    struct Point p2 = {4.0f, 3.0f};
    struct Point mid = midpoint(p1, p2);

    printf("Midpoint : (%.1f, %.1f)\n", mid.x, mid.y);
    printf("Distance : %.2f\n", distance(p1, p2));
    return 0;
}
```

**Output:**
```
Midpoint : (2.0, 1.5)
Distance : 5.00
```

---

#### Program 7: sizeof and Memory Inspection

**Problem:** Demonstrate sizeof behavior with structures.

```c
#include <stdio.h>

struct A { char c; int i; char d; };   // Padded
struct B { int i; char c; char d; };   // Optimized

int main(void) {
    printf("sizeof(struct A) = %zu\n", sizeof(struct A));
    printf("sizeof(struct B) = %zu\n", sizeof(struct B));

    struct A a;
    printf("\nAddresses in struct A:\n");
    printf("  &a.c = %p (offset %zu)\n", (void*)&a.c,   (size_t)((char*)&a.c   - (char*)&a));
    printf("  &a.i = %p (offset %zu)\n", (void*)&a.i,   (size_t)((char*)&a.i   - (char*)&a));
    printf("  &a.d = %p (offset %zu)\n", (void*)&a.d,   (size_t)((char*)&a.d   - (char*)&a));

    return 0;
}
```

**Output (typical):**
```
sizeof(struct A) = 12
sizeof(struct B) = 8

Addresses in struct A:
  &a.c = 0x... (offset 0)
  &a.i = 0x... (offset 4)
  &a.d = 0x... (offset 8)
```

---

#### Program 8: Basic Union Usage

**Problem:** Demonstrate union memory sharing.

```c
#include <stdio.h>

union Data {
    int    i;
    float  f;
    char   str[20];
};

int main(void) {
    union Data d;

    printf("sizeof(union Data) = %zu\n\n", sizeof(union Data));

    d.i = 100;
    printf("i = %d\n", d.i);

    d.f = 3.14f;
    printf("f = %.2f\n", d.f);
    printf("i after f assigned = %d (garbage!)\n", d.i);

    return 0;
}
```

**Output:**
```
sizeof(union Data) = 20

i = 100
f = 3.14
i after f assigned = 1078523331 (garbage!)
```

**Interview Discussion:** Only the **last assigned member** is valid in a union.

---

#### Program 9: Typedef with Struct

**Problem:** Simplify struct usage with typedef.

```c
#include <stdio.h>

typedef struct {
    int    x;
    int    y;
    int    z;
} Vector3D;

Vector3D add(Vector3D a, Vector3D b) {
    return (Vector3D){a.x+b.x, a.y+b.y, a.z+b.z};
}

float dot(Vector3D a, Vector3D b) {
    return (float)(a.x*b.x + a.y*b.y + a.z*b.z);
}

int main(void) {
    Vector3D v1 = {1, 2, 3};
    Vector3D v2 = {4, 5, 6};
    Vector3D sum = add(v1, v2);

    printf("Sum: (%d, %d, %d)\n", sum.x, sum.y, sum.z);
    printf("Dot: %.1f\n", dot(v1, v2));
    return 0;
}
```

**Output:**
```
Sum: (5, 7, 9)
Dot: 32.0
```

---

#### Program 10: Bit-Fields Basic

**Problem:** Use bit-fields to store file permission flags.

```c
#include <stdio.h>

typedef struct {
    unsigned int read    : 1;
    unsigned int write   : 1;
    unsigned int execute : 1;
    unsigned int sticky  : 1;
} Permissions;

void print_perms(Permissions p) {
    printf("%c%c%c%c\n",
           p.read    ? 'r' : '-',
           p.write   ? 'w' : '-',
           p.execute ? 'x' : '-',
           p.sticky  ? 't' : '-');
}

int main(void) {
    Permissions owner = {1, 1, 1, 0};  // rwx-
    Permissions group = {1, 0, 1, 0};  // r-x-
    Permissions other = {1, 0, 0, 0};  // r---

    printf("Owner: "); print_perms(owner);
    printf("Group: "); print_perms(group);
    printf("Other: "); print_perms(other);
    printf("sizeof(Permissions) = %zu\n", sizeof(Permissions));
    return 0;
}
```

**Output:**
```
Owner: rwx-
Group: r-x-
Other: r---
sizeof(Permissions) = 4
```

---

### 8.2 Intermediate Level

---

#### Program 11: Singly Linked List with Structures

**Problem:** Implement a singly linked list using self-referential structures.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int         data;
    struct Node *next;
} Node;

Node *create_node(int val) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->data = val;
    n->next = NULL;
    return n;
}

void push_front(Node **head, int val) {
    Node *n = create_node(val);
    n->next = *head;
    *head   = n;
}

void push_back(Node **head, int val) {
    Node *n = create_node(val);
    if (!*head) { *head = n; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

void print_list(const Node *head) {
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head) {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void) {
    Node *list = NULL;
    push_back(&list, 10);
    push_back(&list, 20);
    push_back(&list, 30);
    push_front(&list, 5);

    print_list(list);   // 5 -> 10 -> 20 -> 30
    free_list(list);
    return 0;
}
```

**Output:**
```
5 -> 10 -> 20 -> 30
```

---

#### Program 12: Binary Search Tree with Structures

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct BST {
    int        val;
    struct BST *left;
    struct BST *right;
} BST;

BST *insert(BST *root, int val) {
    if (!root) {
        BST *n = malloc(sizeof(BST));
        n->val = val; n->left = n->right = NULL;
        return n;
    }
    if (val < root->val) root->left  = insert(root->left,  val);
    else if (val > root->val) root->right = insert(root->right, val);
    return root;
}

void inorder(const BST *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void free_tree(BST *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    BST *root = NULL;
    int values[] = {5, 3, 7, 1, 4, 6, 8};
    for (int i = 0; i < 7; i++)
        root = insert(root, values[i]);
    inorder(root);   // 1 3 4 5 6 7 8
    printf("\n");
    free_tree(root);
    return 0;
}
```

---

#### Program 13: Dynamic Array of Structures

**Problem:** Dynamically allocate an array of student records.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   id;
    char  name[50];
    float gpa;
} Student;

Student *create_class(int n) {
    Student *arr = calloc(n, sizeof(Student));
    if (!arr) { perror("calloc"); exit(EXIT_FAILURE); }
    return arr;
}

void sort_by_gpa(Student *arr, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (arr[j].gpa < arr[j+1].gpa) {
                Student tmp = arr[j];
                arr[j]      = arr[j+1];
                arr[j+1]    = tmp;
            }
}

int main(void) {
    int n = 4;
    Student *class = create_class(n);

    Student data[] = {
        {1,"Alice",3.9f},{2,"Bob",3.2f},
        {3,"Carol",3.7f},{4,"Dave",2.8f}
    };
    memcpy(class, data, n * sizeof(Student));

    sort_by_gpa(class, n);

    printf("Ranked by GPA:\n");
    for (int i = 0; i < n; i++)
        printf("%d. %-10s %.2f\n", i+1, class[i].name, class[i].gpa);

    free(class);
    return 0;
}
```

**Output:**
```
Ranked by GPA:
1. Alice      3.90
2. Carol      3.70
3. Bob        3.20
4. Dave       2.80
```

---

#### Program 14: Struct with Function Pointers (OOP in C)

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// "Object" style programming
typedef struct Shape Shape;

struct Shape {
    const char *type;
    float       data[2];   // Stores dimensions
    float     (*area)  (const Shape *);
    float     (*perim) (const Shape *);
};

float circle_area (const Shape *s) { return 3.14159f * s->data[0] * s->data[0]; }
float circle_perim(const Shape *s) { return 2.0f * 3.14159f * s->data[0]; }

float rect_area   (const Shape *s) { return s->data[0] * s->data[1]; }
float rect_perim  (const Shape *s) { return 2.0f * (s->data[0] + s->data[1]); }

int main(void) {
    Shape shapes[] = {
        {"Circle",    {5.0f, 0.0f}, circle_area, circle_perim},
        {"Rectangle", {4.0f, 3.0f}, rect_area,   rect_perim  }
    };

    for (int i = 0; i < 2; i++) {
        printf("%s: Area=%.2f  Perimeter=%.2f\n",
               shapes[i].type,
               shapes[i].area(&shapes[i]),
               shapes[i].perim(&shapes[i]));
    }
    return 0;
}
```

**Output:**
```
Circle: Area=78.54  Perimeter=31.42
Rectangle: Area=12.00  Perimeter=14.00
```

---

#### Program 15: Union for Type-Safe Variant

```c
#include <stdio.h>
#include <string.h>

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } ValueType;

typedef struct {
    ValueType type;
    union {
        int   i;
        float f;
        char  s[32];
    };
} Value;

void print_value(const Value *v) {
    switch (v->type) {
        case TYPE_INT:    printf("int(%d)\n",   v->i); break;
        case TYPE_FLOAT:  printf("float(%.2f)\n", v->f); break;
        case TYPE_STRING: printf("string(\"%s\")\n", v->s); break;
    }
}

int main(void) {
    Value values[] = {
        {TYPE_INT,    .i = 42},
        {TYPE_FLOAT,  .f = 3.14f},
        {TYPE_STRING, .s = "hello"}
    };

    for (int i = 0; i < 3; i++)
        print_value(&values[i]);

    return 0;
}
```

**Output:**
```
int(42)
float(3.14)
string("hello")
```

---

#### Program 16: Packing for Network Packet

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t  version;
    uint8_t  type;
    uint16_t length;
    uint32_t src_ip;
    uint32_t dst_ip;
    uint8_t  payload[8];
} Packet;
#pragma pack(pop)

int main(void) {
    Packet pkt;
    pkt.version = 4;
    pkt.type    = 6;    // TCP
    pkt.length  = sizeof(Packet);
    pkt.src_ip  = 0xC0A80101; // 192.168.1.1
    pkt.dst_ip  = 0xC0A80102; // 192.168.1.2
    memset(pkt.payload, 0xAB, sizeof(pkt.payload));

    printf("Packet size: %zu bytes (no padding)\n", sizeof(Packet));
    printf("Source IP: %d.%d.%d.%d\n",
           (pkt.src_ip >> 24) & 0xFF, (pkt.src_ip >> 16) & 0xFF,
           (pkt.src_ip >>  8) & 0xFF, (pkt.src_ip      ) & 0xFF);
    return 0;
}
```

---

#### Program 17: Stack Using Struct

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK 100

typedef struct {
    int  data[MAX_STACK];
    int  top;
} Stack;

void     stack_init(Stack *s)       { s->top = -1; }
bool     stack_empty(const Stack *s){ return s->top == -1; }
bool     stack_full (const Stack *s){ return s->top == MAX_STACK - 1; }
bool     stack_push (Stack *s, int v) {
    if (stack_full(s)) return false;
    s->data[++s->top] = v;
    return true;
}
bool     stack_pop(Stack *s, int *v) {
    if (stack_empty(s)) return false;
    *v = s->data[s->top--];
    return true;
}

int main(void) {
    Stack s;
    stack_init(&s);
    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);

    int val;
    while (stack_pop(&s, &val))
        printf("Popped: %d\n", val);
    return 0;
}
```

**Output:**
```
Popped: 30
Popped: 20
Popped: 10
```

---

#### Program 18: Structure Serialization

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint32_t id;
    char     name[20];
    float    score;
} Record;

void serialize(const Record *r, uint8_t *buf) {
    memcpy(buf, r, sizeof(Record));
}

void deserialize(const uint8_t *buf, Record *r) {
    memcpy(r, buf, sizeof(Record));
}

int main(void) {
    Record original = {42, "TestRecord", 98.5f};
    uint8_t buffer[sizeof(Record)];

    serialize(&original, buffer);

    Record restored;
    deserialize(buffer, &restored);

    printf("ID: %u, Name: %s, Score: %.1f\n",
           restored.id, restored.name, restored.score);
    return 0;
}
```

---

#### Program 19: Struct with realloc (Dynamic Array Growth)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   id;
    char  name[30];
} Item;

typedef struct {
    Item  *data;
    size_t size;
    size_t capacity;
} ItemList;

void list_init(ItemList *l) {
    l->data     = NULL;
    l->size     = 0;
    l->capacity = 0;
}

void list_push(ItemList *l, Item item) {
    if (l->size == l->capacity) {
        size_t new_cap = l->capacity == 0 ? 4 : l->capacity * 2;
        Item  *tmp     = realloc(l->data, new_cap * sizeof(Item));
        if (!tmp) { perror("realloc"); exit(EXIT_FAILURE); }
        l->data     = tmp;
        l->capacity = new_cap;
    }
    l->data[l->size++] = item;
}

void list_free(ItemList *l) { free(l->data); }

int main(void) {
    ItemList list;
    list_init(&list);

    for (int i = 1; i <= 6; i++) {
        Item it;
        it.id = i;
        snprintf(it.name, sizeof(it.name), "Item_%d", i);
        list_push(&list, it);
    }

    for (size_t i = 0; i < list.size; i++)
        printf("[%d] %s\n", list.data[i].id, list.data[i].name);

    list_free(&list);
    return 0;
}
```

---

#### Program 20: Bit-Fields for Embedded GPIO Config

```c
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t mode      : 2;   // 00=input, 01=output, 10=AF, 11=analog
    uint32_t otype     : 1;   // 0=push-pull, 1=open-drain
    uint32_t ospeed    : 2;   // 00=low, 01=medium, 10=high, 11=vhigh
    uint32_t pupd      : 2;   // 00=none, 01=pullup, 10=pulldown
    uint32_t reserved  : 25;
} GPIOConfig;

const char *mode_str[]  = {"Input", "Output", "Alt Func", "Analog"};
const char *speed_str[] = {"Low", "Medium", "High", "Very High"};
const char *pupd_str[]  = {"None", "Pull-Up", "Pull-Down", "Reserved"};

int main(void) {
    GPIOConfig gpio = {
        .mode   = 1,    // Output
        .otype  = 0,    // Push-pull
        .ospeed = 2,    // High speed
        .pupd   = 0     // No pull
    };

    printf("GPIO Configuration:\n");
    printf("  Mode  : %s\n",  mode_str[gpio.mode]);
    printf("  OType : %s\n",  gpio.otype ? "Open-Drain" : "Push-Pull");
    printf("  Speed : %s\n",  speed_str[gpio.ospeed]);
    printf("  PUPD  : %s\n",  pupd_str[gpio.pupd]);
    printf("  Size  : %zu bytes\n", sizeof(gpio));
    return 0;
}
```

---

### 8.3 Advanced Level

---

#### Program 21: Generic Hash Map with Structs

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_SIZE 16

typedef struct Entry {
    char        *key;
    int          value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[HASHMAP_SIZE];
} HashMap;

static unsigned hash(const char *key) {
    unsigned h = 5381;
    while (*key) h = ((h << 5) + h) + (unsigned char)(*key++);
    return h % HASHMAP_SIZE;
}

void hm_put(HashMap *m, const char *key, int val) {
    unsigned idx = hash(key);
    for (Entry *e = m->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { e->value = val; return; }
    }
    Entry *e = malloc(sizeof(Entry));
    e->key   = strdup(key);
    e->value = val;
    e->next  = m->buckets[idx];
    m->buckets[idx] = e;
}

int hm_get(const HashMap *m, const char *key, int *out) {
    unsigned idx = hash(key);
    for (const Entry *e = m->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { *out = e->value; return 1; }
    }
    return 0;
}

void hm_free(HashMap *m) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        Entry *e = m->buckets[i];
        while (e) {
            Entry *tmp = e->next;
            free(e->key);
            free(e);
            e = tmp;
        }
    }
}

int main(void) {
    HashMap map = {0};
    hm_put(&map, "alice", 95);
    hm_put(&map, "bob",   82);
    hm_put(&map, "carol", 91);

    int v;
    if (hm_get(&map, "alice", &v)) printf("alice: %d\n", v);
    if (hm_get(&map, "bob",   &v)) printf("bob:   %d\n", v);

    hm_free(&map);
    return 0;
}
```

---

#### Program 22: Memory Pool Allocator

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define POOL_SIZE  1024
#define BLOCK_SIZE  64

typedef struct {
    uint8_t  memory[POOL_SIZE];
    uint8_t  used[POOL_SIZE / BLOCK_SIZE];
    size_t   block_size;
    int      total_blocks;
} MemPool;

void pool_init(MemPool *p) {
    memset(p->used, 0, sizeof(p->used));
    p->block_size   = BLOCK_SIZE;
    p->total_blocks = POOL_SIZE / BLOCK_SIZE;
}

void *pool_alloc(MemPool *p) {
    for (int i = 0; i < p->total_blocks; i++) {
        if (!p->used[i]) {
            p->used[i] = 1;
            return &p->memory[i * p->block_size];
        }
    }
    return NULL;  // Pool exhausted
}

void pool_free(MemPool *p, void *ptr) {
    uint8_t *base = p->memory;
    int      idx  = (int)(((uint8_t*)ptr - base) / p->block_size);
    if (idx >= 0 && idx < p->total_blocks)
        p->used[idx] = 0;
}

int main(void) {
    MemPool pool;
    pool_init(&pool);

    void *blk1 = pool_alloc(&pool);
    void *blk2 = pool_alloc(&pool);
    printf("Block 1: %p\n", blk1);
    printf("Block 2: %p\n", blk2);
    printf("Offset:  %td bytes\n", (uint8_t*)blk2 - (uint8_t*)blk1);

    pool_free(&pool, blk1);
    void *blk3 = pool_alloc(&pool);   // Should reuse blk1
    printf("Block 3 (reused): %p\n", blk3);
    return 0;
}
```

---

#### Program 23: State Machine with Struct

```c
#include <stdio.h>

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_PAUSED, STATE_STOPPED } State;
typedef enum { EVT_START, EVT_PAUSE, EVT_RESUME, EVT_STOP } Event;

typedef struct {
    State current;
    int   data;
} StateMachine;

typedef struct {
    State  from;
    Event  event;
    State  to;
    void (*action)(StateMachine *);
} Transition;

void on_start  (StateMachine *m) { printf("  ACTION: Started\n"); }
void on_pause  (StateMachine *m) { printf("  ACTION: Paused\n");  }
void on_resume (StateMachine *m) { printf("  ACTION: Resumed\n"); }
void on_stop   (StateMachine *m) { printf("  ACTION: Stopped\n"); }

static const Transition transitions[] = {
    {STATE_IDLE,    EVT_START,  STATE_RUNNING, on_start  },
    {STATE_RUNNING, EVT_PAUSE,  STATE_PAUSED,  on_pause  },
    {STATE_PAUSED,  EVT_RESUME, STATE_RUNNING, on_resume },
    {STATE_RUNNING, EVT_STOP,   STATE_STOPPED, on_stop   },
};
#define N_TRANS (sizeof(transitions)/sizeof(transitions[0]))

void sm_dispatch(StateMachine *m, Event ev) {
    for (size_t i = 0; i < N_TRANS; i++) {
        if (transitions[i].from == m->current && transitions[i].event == ev) {
            printf("State: %d -> %d\n", m->current, transitions[i].to);
            transitions[i].action(m);
            m->current = transitions[i].to;
            return;
        }
    }
    printf("  Invalid transition from state %d\n", m->current);
}

int main(void) {
    StateMachine sm = {STATE_IDLE, 0};
    sm_dispatch(&sm, EVT_START);
    sm_dispatch(&sm, EVT_PAUSE);
    sm_dispatch(&sm, EVT_RESUME);
    sm_dispatch(&sm, EVT_STOP);
    return 0;
}
```

---

#### Program 24: Ring Buffer (Circular Buffer) with Struct

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RING_SIZE 8

typedef struct {
    uint8_t buf[RING_SIZE];
    int     head;
    int     tail;
    int     count;
} RingBuffer;

void  rb_init (RingBuffer *r) { memset(r, 0, sizeof(*r)); }
bool  rb_full (const RingBuffer *r) { return r->count == RING_SIZE; }
bool  rb_empty(const RingBuffer *r) { return r->count == 0; }

bool rb_push(RingBuffer *r, uint8_t byte) {
    if (rb_full(r)) return false;
    r->buf[r->head] = byte;
    r->head = (r->head + 1) % RING_SIZE;
    r->count++;
    return true;
}

bool rb_pop(RingBuffer *r, uint8_t *byte) {
    if (rb_empty(r)) return false;
    *byte   = r->buf[r->tail];
    r->tail = (r->tail + 1) % RING_SIZE;
    r->count--;
    return true;
}

int main(void) {
    RingBuffer rb;
    rb_init(&rb);

    for (uint8_t i = 1; i <= 5; i++) rb_push(&rb, i * 10);

    printf("Ring Buffer contents (%d items):\n", rb.count);
    uint8_t val;
    while (rb_pop(&rb, &val))
        printf("  %d\n", val);
    return 0;
}
```

---

#### Program 25: Hardware Abstraction Layer (HAL) Simulation

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Simulated register
static uint32_t sim_gpio_reg = 0;

typedef struct {
    volatile uint32_t *ODR;   // Output Data Register
    volatile uint32_t *IDR;   // Input Data Register
    uint8_t            pin;
} GPIO_Handle;

typedef struct {
    void (*write)(GPIO_Handle *h, bool state);
    bool (*read) (GPIO_Handle *h);
    void (*toggle)(GPIO_Handle *h);
} GPIO_Ops;

static void gpio_write (GPIO_Handle *h, bool s) {
    if (s) *h->ODR |=  (1u << h->pin);
    else   *h->ODR &= ~(1u << h->pin);
}
static bool gpio_read  (GPIO_Handle *h) {
    return (*h->IDR >> h->pin) & 1;
}
static void gpio_toggle(GPIO_Handle *h) {
    *h->ODR ^= (1u << h->pin);
}

int main(void) {
    GPIO_Handle led = { &sim_gpio_reg, &sim_gpio_reg, 5 };
    GPIO_Ops ops = { gpio_write, gpio_read, gpio_toggle };

    ops.write(&led, true);
    printf("LED ON:  ODR=0x%08X\n", sim_gpio_reg);
    ops.toggle(&led);
    printf("LED OFF: ODR=0x%08X\n", sim_gpio_reg);
    ops.toggle(&led);
    printf("LED ON:  ODR=0x%08X\n", sim_gpio_reg);
    return 0;
}
```

**Output:**
```
LED ON:  ODR=0x00000020
LED OFF: ODR=0x00000000
LED ON:  ODR=0x00000020
```

---

## 9. 50+ INTERVIEW QUESTIONS & ANSWERS

### Basic Questions (1-10)

**Q1. What is a structure in C?**
> A structure is a user-defined data type that groups variables of different data types under a single name. Declared using the `struct` keyword.

**Q2. What is the difference between a structure and an array?**
> An array holds elements of the **same type**; a structure holds members of **different types**. Array members accessed by index; struct members by name.

**Q3. How do you access structure members?**
> Using the **dot operator (`.`)** for direct variables and **arrow operator (`->`)** for pointers to structures.

**Q4. Can a structure contain another structure?**
> Yes, this is called **nested structures**. Example: `struct Employee { struct Date joined; };`

**Q5. What is the `sizeof` operator's result for an empty struct?**
> In C, the behavior is implementation-defined. GCC returns 0; MSVC returns 1. An empty struct is unusual and rarely used.

**Q6. Can you have a pointer to a structure?**
> Yes. `struct S *ptr = &variable;` or `struct S *ptr = malloc(sizeof(struct S));`

**Q7. What is a self-referential structure?**
> A structure that contains a pointer to its own type. Used to build linked lists, trees, and graphs. `struct Node { int data; struct Node *next; };`

**Q8. What is the difference between passing a struct by value vs by pointer?**
> By value: the entire struct is **copied**. Expensive for large structs. Changes don't affect original. By pointer: only the address (8 bytes on 64-bit) is passed. Changes affect the original.

**Q9. Can you return a structure from a function?**
> Yes. The function returns a copy. With modern compilers, **Return Value Optimization (RVO)** may eliminate the copy.

**Q10. What is `typedef` and why is it used with structs?**
> `typedef` creates a type alias. With structs, it removes the need to write `struct` keyword every time. `typedef struct { int x; } Point;` allows `Point p;` instead of `struct Point p;`.

---

### Intermediate Questions (11-25)

**Q11. What is structure padding and why does it occur?**
> Padding is extra bytes inserted by the compiler between struct members to ensure each member starts at its natural alignment boundary (multiple of its size). This prevents **bus errors** and improves performance on most processors.

**Q12. How can you eliminate structure padding?**
> Use `#pragma pack(1)` or `__attribute__((packed))`. Caution: may cause unaligned access faults on ARM processors and reduced performance on x86.

**Q13. What is the result of `sizeof` for this struct?**
```c
struct { char a; int b; char c; };
```
> Typically **12 bytes**: `a`(1) + 3 pad + `b`(4) + `c`(1) + 3 trailing pad = 12. The struct size must be a multiple of the largest member's alignment (4).

**Q14. How do you find the offset of a member in a struct?**
> Use the `offsetof` macro from `<stddef.h>`: `offsetof(struct S, member)`. Returns the byte offset from the start of the struct.

**Q15. What is a bit-field?**
> A struct member with a specified number of bits. `unsigned int flag : 1;` Useful for hardware registers and compact flag storage.

**Q16. Can you take the address of a bit-field member?**
> **No.** Bit-fields don't necessarily start at byte boundaries, so they don't have addressable locations. `&struct_var.bit_member` is a compile error.

**Q17. What is a union? How does it differ from a struct?**
> A union allocates memory for **only its largest member**, and all members share that memory. Reading a member that wasn't last written gives undefined behavior. A struct allocates memory for **all** members separately.

**Q18. What is a tagged union?**
> A struct combining a `union` with an enum `type` field to indicate which union member is currently valid. Safe pattern for variant types.

**Q19. What is the size of a union?**
> The size of the **largest member**, rounded up to the alignment requirement of that member.
```c
union U { char c; int i; double d; }; // sizeof = 8
```

**Q20. What is `volatile` qualifier with structures?**
> `volatile` tells the compiler not to cache member values in registers and to perform actual memory reads/writes every time. Essential for hardware registers that can change outside the program's control.

**Q21. Can structures be assigned with `=`?**
> Yes. `struct S a = b;` copies all members. This is a **shallow copy** — pointer members are copied (address, not the pointed-to data).

**Q22. What is a shallow copy vs deep copy for structures?**
> **Shallow copy** (default `=`): copies member values, including raw pointer values (not the data they point to). **Deep copy**: manually duplicates heap data pointed to by pointer members.

**Q23. What is `#pragma pack`?**
> A compiler directive to change structure packing/alignment. `#pragma pack(1)` removes all padding. `#pragma pack(push, N)` / `#pragma pack(pop)` save/restore packing settings.

**Q24. How are structures stored in memory?**
> Sequentially, with possible padding between members and at the end (trailing padding). The struct's overall alignment equals the alignment of its largest member.

**Q25. Can you compare two structs with `==`?**
> **No** (directly). C does not support `==` for struct comparison. You must compare member by member or use `memcmp()` (only safe for packed structs without pointer members or padding).

---

### Advanced Questions (26-40)

**Q26. What is an anonymous struct/union?**
> A struct or union without a tag name, nested inside another struct/union. Members can be accessed directly without naming the inner struct/union. C11 standardized this. GCC supports it as an extension in earlier versions.

**Q27. What is the Flexible Array Member?**
```c
struct Packet {
    uint32_t len;
    uint8_t  data[];   // Flexible array member — C99
};
```
> The last member of a struct can be an incomplete array. Size is determined at allocation: `malloc(sizeof(struct Packet) + n)`. Access via `pkt->data[i]`.

**Q28. Explain structure layout in terms of cache lines.**
> A cache line is typically 64 bytes. "Hot" (frequently accessed) members should be placed together at the beginning of a struct to maximize cache hits. Separating frequently accessed data from rarely accessed data prevents **false sharing** in multi-threaded code.

**Q29. What is false sharing and how do structures help prevent it?**
> False sharing occurs when two threads access different variables that happen to reside on the same cache line, causing performance degradation. Padding struct members to cache-line size, or using `alignas(64)`, prevents this.

**Q30. How does `memcpy` work with structures?**
> `memcpy` copies raw bytes. For structs **without pointers**, this is equivalent to assignment. For structs **with pointers**, it's a shallow copy — both source and destination point to the same heap memory.

**Q31. What is `offsetof` and when is it used?**
> `offsetof(type, member)` returns the byte offset of `member` from the start of `type`. Used in container_of macro (Linux kernel), serialization, and struct inspection.

**Q32. What is the `container_of` macro?**
```c
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```
> Given a pointer to a member, derives a pointer to the containing struct. Widely used in Linux kernel for generic data structure implementations.

**Q33. Can a struct have const members?**
> Yes. `const` members cannot be modified after initialization. Useful for read-only configuration structs. Example: `struct Config { const int max_size; };`

**Q34. What is `__attribute__((aligned(N)))` in GCC?**
> Forces a variable or struct to be aligned to `N`-byte boundary. Example: `struct S { int x; } __attribute__((aligned(64)));` forces 64-byte alignment for cache-line optimization.

**Q35. How do you implement inheritance-like behavior using structures in C?**
> Place the "base" struct as the **first member** of the "derived" struct. A pointer to the derived struct can be safely cast to a pointer to the base. This is how Linux kernel implements polymorphism (e.g., `struct kobject` embedding).

**Q36. What is the difference between `struct *ptr = malloc(...)` vs stack allocation?**
> Stack: fast, automatic lifetime (destroyed at end of scope), limited size. Heap (`malloc`): slower, manual lifetime (must `free`), large allocations possible.

**Q37. What is union type punning and is it safe?**
> Type punning via union (reading from a member other than the last written) is **well-defined behavior in C** (C99 and later, per the C standard). It is **undefined behavior in C++**. Use memcpy for portable type punning in C++.

**Q38. How are function pointers used inside structures?**
> Function pointers as struct members enable **polymorphism** (virtual function table simulation) in C. Used extensively in Linux kernel (`struct file_operations`, `struct net_device_ops`).

**Q39. What is the Linux kernel `list_head` trick?**
> The kernel embeds `struct list_head { struct list_head *next, *prev; }` into other structs. Generic list operations work on `list_head` pointers, and `container_of` retrieves the outer struct. This enables type-safe generic linked lists.

**Q40. What happens if you access beyond a struct's memory?**
> Undefined behavior. Can cause data corruption, segmentation faults, or security vulnerabilities. Always ensure pointers are valid and within bounds.

---

### Expert & Embedded/Driver Questions (41-55)

**Q41. What is a memory-mapped register and how are structs used?**
> Hardware peripherals are controlled by writing to specific physical memory addresses. A struct with `volatile` members is cast to the peripheral's base address, allowing register access via struct member names.

**Q42. Why must hardware register structs be `volatile`?**
> Without `volatile`, the compiler may cache register reads in CPU registers or optimize away "redundant" writes (e.g., back-to-back writes to clear then set a flag). `volatile` ensures every access goes to actual memory.

**Q43. What is the difference between `volatile struct S *p` and `struct S * volatile p`?**
> `volatile struct S *p`: the **struct pointed to** is volatile (members accessed without caching). `struct S * volatile p`: the **pointer itself** is volatile (the pointer address may change unexpectedly). For hardware registers, you almost always want the first form.

**Q44. What is endianness and how does it affect union usage?**
> Endianness defines byte ordering: little-endian (LSB at lowest address) vs big-endian (MSB at lowest address). Union type punning results depend on endianness. Network protocols use big-endian; x86 is little-endian.

**Q45. How do you ensure a struct maps exactly to a hardware register layout?**
> Use `#pragma pack(1)` or `__attribute__((packed))`, place members in exact register order, use exact-width types (`uint32_t`), add `static_assert(sizeof(MyReg) == 4, "...")` to catch mismatches.

**Q46. What is `_Static_assert` and how does it help with structs?**
> `_Static_assert(condition, message)` (C11) causes a **compile-time error** if condition is false. Essential for verifying struct sizes match hardware expectations: `_Static_assert(sizeof(struct RegMap) == 0x100, "Reg map size mismatch");`

**Q47. What is the difference between structure and union in an embedded UART driver?**
> `struct UART_Regs` would hold all registers independently. `union` is used inside (e.g., for a status register byte that can be read as a whole byte or as individual bit-fields).

**Q48. How do you implement a callback in C using a struct?**
> Store function pointers in a struct. Client code fills in the pointers; driver code calls them. This is the **observer pattern** and used in Linux kernel's `struct file_operations`.

**Q49. What is `struct inode` in Linux?**
> `struct inode` represents a file system object (file, directory, etc.) in the Linux VFS (Virtual File System) layer. It contains metadata: permissions, timestamps, size, and a pointer to filesystem-specific operations (`struct inode_operations`).

**Q50. How does the Linux kernel use `container_of` with embedded structs?**
> The kernel embeds generic structures (`list_head`, `kobject`) inside driver-specific structs. When a callback receives a pointer to the embedded struct, `container_of` recovers the outer struct pointer without casting.

**Q51. What is the purpose of `__packed` vs `__attribute__((packed))` in device drivers?**
> Both eliminate padding. `__packed` is a GCC/Clang shorthand for `__attribute__((packed))`. Used when a struct must exactly match a wire protocol or hardware register layout with no padding.

**Q52. How does `#pragma pack` differ from `__attribute__((packed))`?**
> `#pragma pack` is a Microsoft-originated directive, widely supported (GCC, Clang, MSVC). `__attribute__((packed))` is GCC/Clang specific. `#pragma pack(push,1)/pop` is safer for scoping. Both achieve the same result but `#pragma pack` is more portable across compilers.

**Q53. What are the risks of packed structures in ARM Cortex-M?**
> ARM Cortex-M0/M0+ do **not support unaligned memory access** — accessing a packed 32-bit member at an unaligned address causes a HardFault. Cortex-M3/M4 support it but with a performance penalty. Always test packed structs on target hardware.

**Q54. How do you handle endianness-independent struct layouts?**
> Use byte arrays and manual bit manipulation instead of multi-byte fields in packed structs. Or use `htonl/ntohl` (host-to-network byte order) functions when transmitting.

**Q55. How do function pointer tables (vtables) work in C?**
> A struct of function pointers simulates C++ vtables. Each "class" (struct type) has a corresponding ops struct. `struct file_operations` in Linux is a vtable for file objects, allowing different filesystems to provide different implementations.

---

## 10. TRICKY INTERVIEW QUESTIONS

### Size Calculation Questions

**Q1. What is the output?**
```c
struct A { char a; short b; char c; int d; };
printf("%zu\n", sizeof(struct A));
```
> - `a`(1) + 1 pad + `b`(2) + `c`(1) + 3 pad + `d`(4) = **12**

**Q2. What is the output?**
```c
struct B { double d; char c; int i; };
printf("%zu\n", sizeof(struct B));
```
> - `d`(8) + `c`(1) + 3 pad + `i`(4) = **16**

**Q3. What is the output?**
```c
union U { int i; double d; char c[3]; };
printf("%zu\n", sizeof(union U));
```
> - Largest = `double`(8), alignment = 8 → **8**

**Q4. What is the output?**
```c
struct C { char a; char b; char c; char d; };
printf("%zu\n", sizeof(struct C));
```
> All chars, no padding needed → **4**

**Q5. What is the output?**
```c
struct D {
    int   a;
    char  b;
    int   c;
    char  d;
};
printf("%zu\n", sizeof(struct D));
```
> `a`(4) + `b`(1)+3pad + `c`(4) + `d`(1)+3pad = **16**

---

### Padding Questions

**Q6. How many padding bytes does this struct have?**
```c
struct P { char a; int b; short c; char d; double e; };
```
> - `a`(1)+3pad + `b`(4) + `c`(2)+1pad + `d`(1) → offset 11, but `double` needs 8-byte alignment → 4 more pad → `e`(8) = **24 bytes total**, 8 padding bytes

**Q7. Reorder this struct to minimize size:**
```c
struct Big { char a; double b; char c; int d; char e; short f; };
```
> Original size: likely 32. Optimized: `double b` first, then `int d`, `short f`, then chars.
```c
struct Small { double b; int d; short f; char a; char c; char e; char pad; };
// sizeof = 8 + 4 + 2 + 1 + 1 + 1 + 1(pad) = 18, rounds to 24? 
// Actually: 8+4+2+3chars = 17, round to 8-byte boundary = 24
```

---

### Pointer-to-Structure Questions

**Q8. What does `(*ptr).member` equal?**
> It is identical to `ptr->member`. The `->` operator is syntactic sugar.

**Q9. Is `ptr++` valid for a struct pointer?**
> Yes. `ptr++` advances the pointer by `sizeof(struct S)` bytes, moving to the next element in a struct array.

**Q10. What is the output?**
```c
struct Node { int val; struct Node *next; };
struct Node a = {1, NULL};
struct Node b = {2, &a};
struct Node *p = &b;
printf("%d\n", p->next->val);
```
> **1**

---

### Union Memory Questions

**Q11. What is the output? (Little-endian system)**
```c
union U { int i; char c[4]; };
union U u;
u.i = 0x12345678;
printf("%02X\n", u.c[0]);
```
> On little-endian: **78** (LSB stored first)

**Q12. After `u.f = 1.0f;`, what is `u.i`?**
```c
union { float f; int i; } u;
u.f = 1.0f;
printf("%d\n", u.i);
```
> IEEE 754: 1.0f = `0x3F800000` = **1065353216**

---

### Typedef Questions

**Q13. What is the difference?**
```c
typedef int* IntPtr;
IntPtr p, q;        // (A)
int*   r, s;        // (B)
```
> (A): both `p` and `q` are `int*`. (B): `r` is `int*`, `s` is `int` (not a pointer!). Typedef hides the pointer.

**Q14. Is this valid?**
```c
typedef struct Node { int val; struct Node *next; } Node;
```
> Yes. Inside the struct definition, you must use `struct Node` (the typedef `Node` is not yet defined). After the definition, `Node *` is valid.

---

### Bit-Field Questions

**Q15. What is the output?**
```c
struct BF { unsigned int x : 3; unsigned int y : 4; };
struct BF b = {7, 15};
printf("%u %u\n", b.x, b.y);
```
> 7 fits in 3 bits (max 7), 15 fits in 4 bits (max 15) → **7 15**

**Q16. What is `sizeof` for?**
```c
struct BF2 { unsigned int a : 1; unsigned int b : 1; unsigned int c : 30; };
```
> Total bits = 32 = 1 `unsigned int` → **4**

**Q17. Can you do `&b.x` if `b` is a struct with bit-fields?**
> **No.** The address-of operator on a bit-field is illegal. Bit-fields are not addressable.

---

## 11. COMMON MISTAKES & HOW TO AVOID THEM

### Mistake 1: Forgetting to use `->` with pointers

```c
// WRONG
struct Student *p = &s;
p.id = 1;     // Compile error!

// CORRECT
p->id = 1;
// OR
(*p).id = 1;
```

### Mistake 2: Incorrect `sizeof` assumptions

```c
// WRONG assumption
struct S { char a; int b; };
// Assuming sizeof = 5 — WRONG! It's likely 8.

// CORRECT approach
printf("%zu\n", sizeof(struct S));  // Always use sizeof!
```

### Mistake 3: Shallow copy of structs with pointers

```c
// WRONG — both s1 and s2 point to same name buffer
struct Student s1 = {1, strdup("Alice"), 3.9};
struct Student s2 = s1;  // Shallow copy!
free(s1.name);
// s2.name is now a dangling pointer!

// CORRECT — deep copy
struct Student s2;
s2.id   = s1.id;
s2.name = strdup(s1.name);  // Allocate separate copy
s2.gpa  = s1.gpa;
```

### Mistake 4: Not freeing all nested dynamic members

```c
// WRONG — memory leak
struct Employee *e = malloc(sizeof(*e));
e->name = malloc(50);
free(e);  // Leaks e->name!

// CORRECT
free(e->name);
free(e);
```

### Mistake 5: Accessing wrong union member

```c
// WRONG
union U { int i; float f; };
union U u;
u.f = 3.14f;
printf("%d\n", u.i);  // Garbage / undefined meaning
// Only the last-written member is valid!
```

### Mistake 6: Forgetting `volatile` for hardware registers

```c
// WRONG — compiler may optimize out the loop
while (!(UART->SR & 0x80));  // Wait for TX ready

// CORRECT — register must be volatile
volatile uint32_t *SR = (volatile uint32_t *)0x40013808;
while (!(*SR & 0x80));
```

### Mistake 7: Struct comparison with `==`

```c
struct S a = {1, 2};
struct S b = {1, 2};
if (a == b) { }   // COMPILE ERROR — no == for structs!

// CORRECT
if (a.x == b.x && a.y == b.y) { }
// Or for packed POD structs without padding:
// if (memcmp(&a, &b, sizeof(a)) == 0)
```

### Mistake 8: Modifying a const struct through a cast

```c
const struct Config cfg = {42};
struct Config *p = (struct Config *)&cfg;  // Casts away const
p->value = 100;  // Undefined behavior!
```

### Mistake 9: Returning pointer to local struct

```c
// WRONG — undefined behavior!
struct Point* get_point(void) {
    struct Point p = {1, 2};
    return &p;  // p is destroyed when function returns!
}

// CORRECT options:
// Option 1: Return by value
struct Point get_point(void) { return (struct Point){1, 2}; }
// Option 2: Pass output pointer
void get_point(struct Point *out) { out->x = 1; out->y = 2; }
// Option 3: Dynamic allocation
struct Point* get_point(void) { return malloc(sizeof(struct Point)); }
```

### Mistake 10: Integer overflow in bit-field assignment

```c
struct BF { unsigned int bits : 3; };
struct BF b;
b.bits = 10;  // 10 doesn't fit in 3 bits (max = 7)
// Result: b.bits = 10 & 0x7 = 2  — silently truncated!
```

---

## 12. INTERVIEW PREPARATION ROADMAP

### Beginner (0-1 Year Experience)

**Core Concepts to Master:**
- [ ] What is a struct and why use it
- [ ] Struct declaration, definition, initialization
- [ ] Accessing members with `.` and `->`
- [ ] Passing structs to functions (value vs pointer)
- [ ] Array of structs
- [ ] Nested structs
- [ ] Basic typedef usage
- [ ] What is a union and how memory is shared
- [ ] sizeof for structs and unions

**Interview Expectations:**
- Write a basic student/employee record program
- Explain why struct vs separate variables
- Understand that sizeof may not equal sum of member sizes

**Practice Programs:** Programs 1-5 from this guide

---

### Intermediate (1-3 Years Experience)

**Concepts to Master:**
- [ ] Padding, alignment, and `offsetof`
- [ ] `#pragma pack` and `__attribute__((packed))`
- [ ] Self-referential structures (linked lists, trees)
- [ ] Dynamic memory for structures
- [ ] Tagged unions (variant types)
- [ ] Bit-fields
- [ ] Typedef with pointers and function pointers
- [ ] Shallow vs deep copy
- [ ] Struct with function pointers (polymorphism)
- [ ] `memcpy` / `memset` with structs

**Interview Expectations:**
- Size calculation questions (padding)
- Implement linked list or stack using structs
- Explain shallow vs deep copy
- Union type punning
- Optimize struct layout for minimum size

**Practice Programs:** Programs 6-20 from this guide

---

### Experienced (3-5 Years Experience)

**Advanced Concepts:**
- [ ] `container_of` macro and its applications
- [ ] Flexible array members (C99)
- [ ] Anonymous structs and unions (C11)
- [ ] Cache line awareness and alignment
- [ ] `_Static_assert` for struct size verification
- [ ] Endianness impact on structs and unions
- [ ] Generic programming patterns with struct + function pointers
- [ ] Memory pool and slab allocators using structs
- [ ] State machine design using structs
- [ ] Ring buffer implementation

**Interview Expectations:**
- Design a memory allocator
- Implement generic data structures (hash map, queue)
- Explain false sharing and mitigation
- Complex size calculation questions
- Design HAL using structs and function pointers

**Practice Programs:** Programs 21-25 from this guide

---

### Embedded & Driver Development Roles

**Must-Know Topics:**
- [ ] `volatile` qualifier — when and why
- [ ] Memory-mapped register structs (MMIO)
- [ ] Bit-fields for hardware registers
- [ ] Packing requirements for protocol packets
- [ ] Endianness handling
- [ ] `static_assert` for layout verification
- [ ] Interrupt-safe struct access patterns
- [ ] DMA buffer alignment requirements
- [ ] Linux `file_operations`, `platform_driver`, `of_device_id`
- [ ] `container_of` in Linux kernel code
- [ ] `list_head` usage in kernel
- [ ] `kobject` and `ktype` usage
- [ ] IOCTL structures and `copy_to/from_user`

**Frequently Asked in Embedded Interviews:**
1. Declare a struct for a UART control register with bit-fields
2. Why must hardware register pointers be volatile?
3. What happens with unaligned access on ARM Cortex-M0?
4. How do you ensure a struct maps exactly to 32 bytes of hardware registers?
5. Difference between `volatile struct *` and `struct * volatile`
6. How does endianness affect your register struct on big-endian hardware?
7. How would you implement a circular buffer for UART DMA?
8. What is `#pragma pack` and when should you avoid it?

**Frequently Asked in Linux Driver Interviews:**
1. What is `file_operations` struct and how is it used?
2. How does `container_of` work? Write it from scratch.
3. Explain `struct platform_device` and `platform_driver`.
4. How do you pass data between user space and kernel space using structs?
5. What is a `kobject` and why is it embedded in driver structs?
6. How does the kernel use anonymous structs in `task_struct`?
7. Explain `struct sk_buff` — how is it used in networking?
8. What are `struct mutex`, `spinlock_t`, and how are they embedded in device structs?

---

## QUICK REFERENCE CHEAT SHEET

```c
// ===== STRUCT =====
struct Tag { type member; };          // Definition
struct Tag var;                       // Declaration
struct Tag var = { val1, val2 };      // Init
var.member                            // Access (value)
ptr->member                           // Access (pointer)

// ===== TYPEDEF =====
typedef struct { type m; } Name;     // Typedef struct
typedef type Alias;                   // Typedef type
typedef ret (*FnPtr)(params);         // Typedef fn pointer

// ===== UNION =====
union Tag { type m1; type m2; };      // Only last write is valid

// ===== BIT-FIELDS =====
struct Flags { unsigned int x : N; }; // N-bit field

// ===== MEMORY =====
sizeof(struct S)                      // Total size (with padding)
offsetof(struct S, member)            // Byte offset of member
__attribute__((packed))               // No padding (GCC)
#pragma pack(push, 1) ... pop         // No padding (portable)

// ===== DYNAMIC =====
struct S *p = malloc(sizeof(struct S));
free(p);

// ===== SELF-REFERENTIAL =====
struct Node { int d; struct Node *next; };

// ===== HARDWARE REGISTER =====
typedef struct { volatile uint32_t CR; } Periph;
#define PERIPH ((Periph *)BASE_ADDR)
```

---

*This document is a comprehensive training and interview preparation guide for C developers at all levels — from college students to senior embedded and Linux driver engineers.*

*Version 1.0 | June 2026*
