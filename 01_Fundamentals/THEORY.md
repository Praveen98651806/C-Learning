# Phase 1: C Fundamentals

## Overview
This is your starting point. Master these basics before moving forward.

---

## 1. What is C?

**C** is a procedural, general-purpose programming language created by **Dennis Ritchie** in 1972.

### Why C?
- ✅ Close to hardware (great for embedded systems & drivers)
- ✅ Efficient & fast
- ✅ Simple syntax
- ✅ Perfect for learning data structures & algorithms
- ✅ **Required for semiconductor companies**

### Where C is Used?
- Operating Systems (Unix, Linux kernels)
- Embedded Systems (IoT, microcontrollers)
- Databases (SQLite)
- System Software
- Wi-Fi drivers & firmware

---

## 2. Your First Program

```c
#include <stdio.h>  // Include standard input/output library

int main() {  // Program entry point
    printf("Hello, World!\n");  // Print text
    return 0;  // Program ends successfully
}
```

### How it works:
1. `#include <stdio.h>` - Includes library for printf()
2. `int main()` - Main function where program starts
3. `printf()` - Function to print text
4. `return 0` - Program ends (0 = success)

---

## 3. Data Types

### Primitive Data Types

| Type | Size | Range | Example |
|------|------|-------|---------|
| `char` | 1 byte | -128 to 127 | 'A', 'z' |
| `int` | 4 bytes | -2,147,483,648 to 2,147,483,647 | 42, -100 |
| `float` | 4 bytes | ~7 decimal digits | 3.14, -2.5 |
| `double` | 8 bytes | ~15 decimal digits | 3.14159265, 2.5 |
| `void` | - | No type | Functions without return |

### Check Size Using sizeof()

```c
#include <stdio.h>

int main() {
    printf("Size of int: %d bytes\n", sizeof(int));
    printf("Size of float: %d bytes\n", sizeof(float));
    printf("Size of double: %d bytes\n", sizeof(double));
    printf("Size of char: %d bytes\n", sizeof(char));
    return 0;
}
```

---

## 4. Variables & Constants

### Variables
```c
int age = 25;           // Integer variable
float height = 5.9f;    // Float variable (note the 'f')
double pi = 3.14159;    // Double variable
char initial = 'A';     // Character variable
```

### Constants
```c
const int MAX_USERS = 100;  // Constant (cannot change)
#define PI 3.14159          // Macro constant
```

### Rules for Variable Names
- Must start with letter or underscore
- Can contain letters, digits, underscores
- Case-sensitive (age ≠ AGE)
- No spaces or special characters

---

## 5. Operators

### 5.1 Arithmetic Operators
```c
int a = 10, b = 3;

int sum = a + b;        // Addition: 13
int difference = a - b; // Subtraction: 7
int product = a * b;    // Multiplication: 30
int quotient = a / b;   // Division: 3 (integer division)
int remainder = a % b;  // Modulus: 1
```

### 5.2 Comparison Operators
```c
5 == 5    // Equal: true (1)
5 != 3    // Not equal: true (1)
10 > 5    // Greater than: true (1)
3 < 8     // Less than: true (1)
10 >= 10  // Greater or equal: true (1)
3 <= 5    // Less or equal: true (1)
```

### 5.3 Logical Operators
```c
int a = 1, b = 0;

a && b    // AND: 0 (false) - both must be true
a || b    // OR: 1 (true) - at least one must be true
!a        // NOT: 0 (false) - negates the value
```

### 5.4 Bitwise Operators ⭐ (Important for embedded systems)
```c
int a = 5;      // Binary: 0101
int b = 3;      // Binary: 0011

a & b   // AND:           0001 (1)
a | b   // OR:            0111 (7)
a ^ b   // XOR:           0110 (6)
~a      // NOT:           1010 (-6 in two's complement)
a << 1  // Left shift:    1010 (10)
a >> 1  // Right shift:   0010 (2)
```

### 5.5 Assignment Operators
```c
int x = 10;
x += 5;   // Same as: x = x + 5  (x = 15)
x -= 3;   // Same as: x = x - 3  (x = 12)
x *= 2;   // Same as: x = x * 2  (x = 24)
x /= 4;   // Same as: x = x / 4  (x = 6)
x %= 5;   // Same as: x = x % 5  (x = 1)
```

---

## 6. Control Flow (if statements)

### 6.1 Simple if
```c
int age = 18;

if (age >= 18) {
    printf("You are an adult\n");
}
```

### 6.2 if-else
```c
int marks = 45;

if (marks >= 50) {
    printf("Pass\n");
} else {
    printf("Fail\n");
}
```

### 6.3 if-else if-else
```c
int marks = 75;

if (marks >= 90) {
    printf("Grade A\n");
} else if (marks >= 80) {
    printf("Grade B\n");
} else if (marks >= 70) {
    printf("Grade C\n");
} else {
    printf("Grade D\n");
}
```

### 6.4 switch case
```c
int day = 3;

switch (day) {
    case 1:
        printf("Monday\n");
        break;  // Important! Exit the switch
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    default:
        printf("Invalid day\n");
}
```

### 6.5 Ternary Operator
```c
int age = 20;
char *type = (age >= 18) ? "Adult" : "Child";
printf("%s\n", type);  // Output: Adult
```

---

## 7. Loops

### 7.1 for Loop
```c
// Print numbers 0 to 9
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
// Output: 0 1 2 3 4 5 6 7 8 9

// Backward loop
for (int i = 5; i >= 0; i--) {
    printf("%d ", i);
}
// Output: 5 4 3 2 1 0
```

### 7.2 while Loop
```c
int i = 0;
while (i < 5) {
    printf("%d ", i);
    i++;
}
// Output: 0 1 2 3 4
```

### 7.3 do-while Loop (executes at least once)
```c
int i = 0;
do {
    printf("%d ", i);
    i++;
} while (i < 5);
// Output: 0 1 2 3 4
```

### 7.4 Loop Control Statements
```c
// break - exits loop
for (int i = 0; i < 10; i++) {
    if (i == 5) break;  // Exit when i = 5
    printf("%d ", i);
}
// Output: 0 1 2 3 4

// continue - skip current iteration
for (int i = 0; i < 5; i++) {
    if (i == 2) continue;  // Skip when i = 2
    printf("%d ", i);
}
// Output: 0 1 3 4
```

---

## 8. Input/Output

### 8.1 printf() - Output
```c
printf("Simple text\n");
printf("Number: %d\n", 42);
printf("Float: %.2f\n", 3.14159);  // 2 decimal places
printf("Character: %c\n", 'A');
```

### 8.2 scanf() - Input
```c
int num;
printf("Enter a number: ");
scanf("%d", &num);  // % = memory address (more on this later)
printf("You entered: %d\n", num);
```

**Format Specifiers:**
- `%d` - Integer
- `%f` - Float
- `%lf` - Double
- `%c` - Character
- `%s` - String
- `%x` - Hexadecimal

---

## 9. Comments

```c
// Single line comment - ignored by compiler

/*
    Multi-line comment
    Can span multiple lines
    Ignored by compiler
*/
```

---

## 10. Quick Reference Card

```c
#include <stdio.h>

int main() {
    // Variables
    int age = 25;
    float weight = 65.5f;
    
    // Input
    scanf("%d", &age);
    
    // Conditional
    if (age > 18) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }
    
    // Loop
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
    }
    
    return 0;
}
```

---

## Key Takeaways

✅ Understand data types and variable declaration  
✅ Master all operators (arithmetic, logical, bitwise)  
✅ Use if-else and switch statements appropriately  
✅ Write efficient loops  
✅ Handle input/output with scanf() and printf()  

---

**Next:** Move to `EXERCISES.md` to practice!

