# C Operator Precedence & Associativity

> Higher precedence = evaluated first. When precedence is equal, associativity decides the order.

---

## Full Precedence Table (Highest to Lowest)

| Level | Operators | Description | Associativity |
|-------|-----------|-------------|---------------|
| **1** | `()` `[]` `->` `.` | Function call, Array subscript, Member access | Left → Right |
| **2** | `++` `--` *(postfix)* | Postfix increment/decrement | Left → Right |
| **3** | `++` `--` *(prefix)* `+` `-` `!` `~` `*` `&` `sizeof` `(type)` | Prefix, Unary, Dereference, Address-of, Cast | Right → Left |
| **4** | `*` `/` `%` | Multiplication, Division, Modulo | Left → Right |
| **5** | `+` `-` | Addition, Subtraction | Left → Right |
| **6** | `<<` `>>` | Bitwise shift left/right | Left → Right |
| **7** | `<` `<=` `>` `>=` | Relational comparison | Left → Right |
| **8** | `==` `!=` | Equality / Inequality | Left → Right |
| **9** | `&` | Bitwise AND | Left → Right |
| **10** | `^` | Bitwise XOR | Left → Right |
| **11** | `\|` | Bitwise OR | Left → Right |
| **12** | `&&` | Logical AND | Left → Right |
| **13** | `\|\|` | Logical OR | Left → Right |
| **14** | `?:` | Ternary conditional | Right → Left |
| **15** | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | Assignment operators | Right → Left |
| **16** | `,` | Comma (sequence) | Left → Right |

---

## Quick Memory Aid

```
Please Excuse My Dear Aunt Sally... But Logically She Assigns Commas
  P  - Postfix      ()  []  ->  .   ++  --
  E  - (prefix)E    ++  --  +   -   !   ~   *   &   sizeof  (cast)
  M  - Multiplicative  *  /  %
  A  - Additive        +  -
  S  - Shift           <<  >>
  R  - Relational      <  <=  >  >=
  E  - Equality        ==  !=
  B  - Bitwise         &  ^  |
  L  - Logical         &&  ||
  T  - Ternary         ?:
  A  - Assignment      =  +=  -=  etc.
  C  - Comma           ,
```

---

## Common Examples

### Example 1: Arithmetic
```c
int x = 2 + 3 * 4;   // = 2 + 12 = 14  (* before +)
int y = (2 + 3) * 4; // = 5  * 4 = 20  (parentheses first)
```

### Example 2: Prefix vs Postfix
```c
int a = 5;
int b = a++;   // b = 5, a = 6  (postfix: use then increment)
int c = ++a;   // c = 7, a = 7  (prefix:  increment then use)
```

### Example 3: Logical Operators
```c
int result = 1 || 0 && 0;   // = 1 || (0 && 0) = 1 || 0 = 1
//                                      && before ||
```

### Example 4: Relational vs Equality
```c
int x = 5 > 3 == 1;   // = (5 > 3) == 1 = 1 == 1 = 1
//            > before ==
```

### Example 5: Assignment (Right to Left)
```c
int a, b, c;
a = b = c = 10;   // c=10, then b=10, then a=10
```

### Example 6: Bitwise
```c
int x = 5 & 3 | 2;   // = (5 & 3) | 2 = 1 | 2 = 3
//             & before |
```

### Example 7: Ternary
```c
int max = (a > b) ? a : b;   // if a > b then max=a, else max=b
```

---

## Tricky Cases to Watch Out For

### Mistake 1: Confusing `&` (bitwise) vs `&&` (logical)
```c
if (a & b)    // Bitwise AND — checks individual bits
if (a && b)   // Logical AND — checks if both are non-zero
```

### Mistake 2: Assignment inside condition
```c
if (x = 5)    // ASSIGNS 5 to x, always true! (probably a bug)
if (x == 5)   // COMPARES x with 5 (correct)
```

### Mistake 3: Sizeof with expression
```c
sizeof(int) * 2    // = (sizeof(int)) * 2  (sizeof has high precedence)
```

### Mistake 4: Postfix on pointer
```c
*p++    // = *(p++)  — dereference p, then increment pointer
(*p)++  // increment the value at p
```

---

## Rule of Thumb

> **When in doubt, use parentheses `()`.**  
> They always have the highest precedence and make code readable.

```c
// Instead of relying on precedence:
int result = a + b * c - d / e;

// Be explicit:
int result = a + (b * c) - (d / e);  // much clearer!
```

---

*Reference: ISO C Standard (C99/C11/C17)*
