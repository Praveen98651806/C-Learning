# Phase 1: Fundamentals - Exercises

## Easy Exercises (Start Here)

### Exercise 1.1: Simple Calculator
**Problem:** Create a program that takes two numbers and an operator (+, -, *, /) and outputs the result.

**Input:**
```
5 10 +
```

**Output:**
```
5 + 10 = 15
```

**Topics Covered:** Variables, Operators, Control Flow

**Hint:**
```c
#include <stdio.h>

int main() {
    int a, b;
    char op;
    scanf("%d %d %c", &a, &b, &op);
    
    if (op == '+') {
        printf("%d + %d = %d\n", a, b, a + b);
    }
    // ... handle other operators
    
    return 0;
}
```

---

### Exercise 1.2: Temperature Converter
**Problem:** Convert Celsius to Fahrenheit using formula: F = (C × 9/5) + 32

**Topics Covered:** Data Types, Arithmetic Operators

**Sample:**
```
Input: 0
Output: 32.00 F

Input: 100
Output: 212.00 F
```

---

### Exercise 1.3: Grade Calculator
**Problem:** Read marks and print the grade.
- 90-100: A
- 80-89: B
- 70-79: C
- 60-69: D
- Below 60: F

**Topics Covered:** if-else if, Control Flow

---

### Exercise 1.4: Number Classification
**Problem:** Check if a number is:
- Positive or Negative
- Even or Odd
- Prime or Not Prime (bonus)

**Topics Covered:** Logical Operators, Modulus Operator

---

### Exercise 1.5: Multiplication Table
**Problem:** Print the multiplication table of a given number up to 10.

**Input:** 5

**Output:**
```
5 * 1 = 5
5 * 2 = 10
5 * 3 = 15
...
5 * 10 = 50
```

**Topics Covered:** Loops (for), printf()

---

## Medium Exercises

### Exercise 1.6: Sum of Numbers
**Problem:** Read n numbers and print their sum and average.

**Input:**
```
5
10 20 30 40 50
```

**Output:**
```
Sum: 150
Average: 30.00
```

**Topics Covered:** Loops, Variables

---

### Exercise 1.7: Reverse Number
**Problem:** Read a number and print it in reverse order.

**Input:** 12345

**Output:** 54321

**Topics Covered:** Loops, Modulus, Integer Division

**Hint:** Use `num % 10` to get last digit, `num / 10` to remove last digit.

---

### Exercise 1.8: Factorial
**Problem:** Calculate factorial of a given number.

**Input:** 5

**Output:** 5! = 120 (5×4×3×2×1)

**Topics Covered:** Loops, Multiplication

---

### Exercise 1.9: Prime Number Checker
**Problem:** Check if a number is prime.

**Input:** 17

**Output:** 17 is a Prime Number

**Topics Covered:** Loops, If-else, Logical Operators

---

### Exercise 1.10: Fibonnaci Series
**Problem:** Print Fibonacci series up to n terms.

**Input:** 10

**Output:**
```
0 1 1 2 3 5 8 13 21 34
```

**Topics Covered:** Loops, Variables, Conditional Logic

---

## Hard Exercises

### Exercise 1.11: Pattern Printing - Triangle
**Problem:** Print a triangle pattern.

**Input:** 5

**Output:**
```
*
**
***
****
*****
```

**Topics Covered:** Nested Loops, Control Flow

---

### Exercise 1.12: Pattern Printing - Pyramid
**Problem:** Print a pyramid pattern.

**Input:** 5

**Output:**
```
    *
   * *
  * * *
 * * * *
* * * * *
```

**Topics Covered:** Nested Loops, Spaces

---

### Exercise 1.13: Digit Sum
**Problem:** Find the sum of all digits in a number repeatedly until you get a single digit.

**Input:** 9875

**Output:**
```
9 + 8 + 7 + 5 = 29
2 + 9 = 11
1 + 1 = 2
Result: 2
```

**Topics Covered:** Loops, Modulus

---

### Exercise 1.14: Bitwise Operations
**Problem:** Understand bitwise operations with examples.

**Task:** Create a program that:
1. Sets a specific bit
2. Clears a specific bit
3. Checks if a bit is set

```c
// Example:
// Set bit 3 in number 5 (0101)
// Result: 1101 (13)
```

**Topics Covered:** Bitwise Operators, Left/Right Shift

---

### Exercise 1.15: Day of Week
**Problem:** Given a number (1-7), print the day of the week using switch-case.

**Input:** 3

**Output:** Wednesday

**Topics Covered:** Switch-case, Control Flow

---

## ⚡ Operator Mastery Exercises (Semiconductor Edition)

**Why These Matter?**
- Semiconductor companies (Qualcomm, Intel, AMD) test operator knowledge heavily
- Bitwise operators are used in device drivers, firmware, hardware control
- Your Wi-Fi team uses these operators extensively in protocol implementation

---

### Exercise 1.16: Bitwise AND - Bit Masking ⭐
**Problem:** Create a program that checks if a specific bit is set in a number.

**Example:**
```
Number: 13 (Binary: 1101)
Check bit 2: Is bit at position 2 set?
Position:   3 2 1 0
Binary:     1 0 1 1 (wait, bit 2 is 0)
Actually:   1 1 0 1 (bit 2 is 1)
Output: YES
```

**Input Format:** `<number> <bit_position>`

**Sample Input:**
```
13 2
```

**Sample Output:**
```
Bit 2 in number 13 is SET (1)
```

**Topics Covered:** Bitwise AND, Bit Masking

**Hint:**
```c
// To check if bit at position 'pos' is set:
if ((number & (1 << pos)) != 0) {
    // Bit is set
}
```

**Why Semiconductor Companies Ask This:**
- Device drivers use bit masking to control registers
- Hardware status checking uses bit operations
- Wi-Fi protocol handling uses bit flags

---

### Exercise 1.17: Bitwise OR - Setting Bits ⭐
**Problem:** Create a program that sets a specific bit in a number to 1.

**Example:**
```
Number: 5 (Binary: 0101)
Set bit 3 to 1
Result: 1101 (13)
```

**Input Format:** `<number> <bit_position>`

**Sample Input:**
```
5 3
```

**Sample Output:**
```
Original: 5 (Binary: 0101)
After setting bit 3: 13 (Binary: 1101)
```

**Hint:**
```c
// To set bit at position 'pos':
number = number | (1 << pos);
```

**Real-World Use:**
- Setting control register bits in embedded systems
- Enabling hardware features via bit flags

---

### Exercise 1.18: Bitwise XOR - Toggling Bits ⭐
**Problem:** Create a program that toggles (flips) a specific bit in a number.

**Example:**
```
Number: 5 (Binary: 0101)
Toggle bit 1 (currently 0)
Result: 0111 (7)
```

**Input Format:** `<number> <bit_position>`

**Sample Input:**
```
5 1
```

**Sample Output:**
```
Original: 5 (Binary: 0101)
After toggling bit 1: 7 (Binary: 0111)

Input 2: 7 1
Original: 7 (Binary: 0111)
After toggling bit 1: 5 (Binary: 0101)
```

**Hint:**
```c
// To toggle bit at position 'pos':
number = number ^ (1 << pos);
```

---

### Exercise 1.19: Bitwise NOT and Complements ⭐
**Problem:** Understand bitwise NOT and create a program that:
1. Shows bitwise NOT of a number
2. Shows two's complement representation

**Sample Input:**
```
5
```

**Sample Output:**
```
Number: 5 (Binary: 0000 0101 in 8-bit)
Bitwise NOT (~5): -6 (Binary: 1111 1010)
Explanation: Flips all bits

Number: 5
Two's Complement (Negative): -5
```

**Topics Covered:** Bitwise NOT, Two's Complement

**Why Important:**
- Understanding negative number representation in binary
- Critical for embedded systems and hardware interaction

---

### Exercise 1.20: Left Shift - Multiplication by Powers of 2 ⭐
**Problem:** Use left shift to multiply numbers by powers of 2.

**Example:**
```
Number: 5 (Binary: 0101)
Left shift by 1: 10 (Binary: 1010) - equivalent to 5 * 2
Left shift by 2: 20 (Binary: 10100) - equivalent to 5 * 4
Left shift by 3: 40 (Binary: 101000) - equivalent to 5 * 8
```

**Input Format:** `<number> <shift_positions>`

**Sample Input:**
```
7 2
```

**Sample Output:**
```
Number: 7
Left shift by 2 positions: 28
Explanation: 7 << 2 = 7 * 2^2 = 7 * 4 = 28
```

**Why This Matters:**
- Faster than multiplication in embedded systems
- Used in device driver optimization
- Critical for real-time systems (Wi-Fi scheduling)

---

### Exercise 1.21: Right Shift - Division by Powers of 2 ⭐
**Problem:** Use right shift to divide numbers by powers of 2.

**Example:**
```
Number: 40 (Binary: 101000)
Right shift by 1: 20 (Binary: 10100) - equivalent to 40 / 2
Right shift by 2: 10 (Binary: 1010) - equivalent to 40 / 4
Right shift by 3: 5 (Binary: 101) - equivalent to 40 / 8
```

**Input Format:** `<number> <shift_positions>`

**Sample Input:**
```
64 2
```

**Sample Output:**
```
Number: 64
Right shift by 2 positions: 16
Explanation: 64 >> 2 = 64 / 2^2 = 64 / 4 = 16
```

---

### Exercise 1.22: Combined Bitwise Operations - Device Register Control ⭐
**Problem:** Simulate a hardware register control where you:
1. Clear all bits (reset)
2. Set specific bits (enable features)
3. Check if bits are set (read status)
4. Toggle bits (switch states)

**Context:** Wi-Fi hardware register with:
```
Bit 0: Transmit Enable
Bit 1: Receive Enable
Bit 2: Power Save Mode
Bit 3: Interrupt Enable
Bit 4-7: Channel Number
```

**Sample Program Flow:**
```
Register: 0 (all bits off)
Enable Transmit (set bit 0): Register = 1
Enable Receive (set bit 1): Register = 3
Enable Power Save (set bit 2): Register = 7
Check Transmit Status: YES
Check Receive Status: YES
Disable Transmit (clear bit 0): Register = 6
```

**Input Options:**
```
set <bit>       - Set bit to 1
clear <bit>     - Clear bit to 0
toggle <bit>    - Toggle bit
check <bit>     - Check if bit is set
print           - Print register binary and decimal
```

**Why This is Important:**
- Exactly what embedded systems and device drivers do
- Direct application to Wi-Fi hardware control
- Semiconductor companies test this heavily in interviews

---

### Exercise 1.23: Operator Precedence Challenge ⭐
**Problem:** Evaluate complex expressions with multiple operators. Predict output before running.

**Challenge 1:**
```c
int x = 5 + 3 * 2;
printf("%d\n", x);  // What's the output?
```

**Challenge 2:**
```c
int y = 10 - 5 - 2;
printf("%d\n", y);  // Left to right or right to left?
```

**Challenge 3:**
```c
int z = 2 * 3 + 4 * 5;
printf("%d\n", z);  // Multiplication first?
```

**Challenge 4:**
```c
int a = 5 > 3 && 2 < 4;
printf("%d\n", a);  // Comparison before logical AND?
```

**Challenge 5:**
```c
int b = 5 | 3 & 6;
printf("%d\n", b);  // Which operator has higher precedence?
```

**Challenge 6:**
```c
int c = 1 << 2 + 1;
printf("%d\n", c);  // Addition or shift first?
```

**Topics Covered:** Operator Precedence, Logical Operators

**Why Important:**
- Interview questions test understanding of operator order
- Critical for writing correct embedded code
- One wrong precedence = entire system fails

---

### Exercise 1.24: Real-World Scenario - Wi-Fi Status Register
**Problem:** Simulate reading and writing a Wi-Fi device status register (32-bit).

**Register Bit Layout:**
```
Bits 0-2:   Connection State (001=disconnected, 010=connecting, 011=connected)
Bit 3:      Error Flag
Bit 4:      Power Save Active
Bit 5:      Scanning Active
Bits 6-15:  Signal Strength (0-1024)
Bits 16-23: Channel Number
Bits 24-31: Reserved
```

**Example Program:**
```
1. Initialize register to 0
2. Set state to CONNECTING (2)
3. Set signal strength to 512
4. Set channel to 6
5. Print hex and binary representation
6. Read and parse each field
7. Check error flag
8. Toggle power save
9. Print final state
```

**Output:**
```
Register (Hex): 0x06204002
Register (Binary): 00000110 00100000 01000000 00000010

Parsing:
- Connection State: CONNECTING (2)
- Error Flag: NO
- Power Save: OFF
- Scanning: NO
- Signal Strength: 512
- Channel: 6

After toggling Power Save:
- Power Save: ON
Register (Hex): 0x06204012
```

**Why Semiconductor Companies Ask This:**
- This is EXACTLY what happens in real device drivers
- Qualcomm, Intel, Broadcom all do this in Wi-Fi drivers
- Tests deep understanding of bitwise operations
- Real-world embedded systems knowledge

---

### Exercise 1.25: Comparison and Logical Operators - System Decision Making
**Problem:** Create a program that makes decisions based on multiple conditions (like embedded system state machine).

**Scenario:** Wi-Fi Access Point decisioning

**Conditions to Check:**
```
1. Is RSSI (signal strength) strong enough?    (RSSI > -50)
2. Is bandwidth available?                      (Available_BW > 20)
3. Is client authenticated?                     (auth_flag == 1)
4. Is channel not congested?                    (CCA_busy < 50)
5. Is QoS requirement met?                      (priority == HIGH || priority == MEDIUM)
```

**Decision Logic:**
```
Allow connection IF:
  (RSSI > -50 AND bandwidth > 20 AND authenticated) 
  OR 
  (VIP_client AND CCA_busy < 80)

Deny if:
  NOT authenticated OR signal too weak
```

**Sample Input:**
```
RSSI: -45
Bandwidth: 50
Authenticated: 1
CCA_busy: 30
VIP_client: 0
Priority: HIGH
```

**Expected Output:**
```
Signal Strength: GOOD (-45 dBm)
Bandwidth: AVAILABLE (50 MHz)
Authentication: SUCCESS
Channel Congestion: LOW (30%)
VIP Status: NO
Priority: HIGH

=== DECISION ===
Condition 1: (RSSI > -50 AND BW > 20 AND auth) = (YES AND YES AND YES) = YES
Condition 2: (VIP AND CCA < 80) = (NO AND YES) = NO

FINAL DECISION: ALLOW CONNECTION ✓
Reason: All conditions met for standard clients
```

**Topics Covered:** Comparison operators, Logical AND/OR/NOT, Complex decision making

**Why Important:**
- Embedded systems make decisions based on multiple sensor inputs
- Your Wi-Fi system checks multiple parameters before accepting connections
- Interview question: Demonstrates logical thinking

---

## 🎯 Submission Checklist

Before moving to next phase, ensure:

### Basic Exercises
- [ ] Completed all Easy Exercises (1.1 - 1.5)
- [ ] Completed at least 5 Medium Exercises (1.6 - 1.10)
- [ ] Attempted at least 2 Hard Exercises (1.11 - 1.15)

### ⭐ Operator Mastery (CRITICAL FOR SEMICONDUCTORS)
- [ ] Exercise 1.16: Bitwise AND (Bit Masking)
- [ ] Exercise 1.17: Bitwise OR (Setting Bits)
- [ ] Exercise 1.18: Bitwise XOR (Toggling Bits)
- [ ] Exercise 1.19: Bitwise NOT (Complements)
- [ ] Exercise 1.20: Left Shift (Multiplication)
- [ ] Exercise 1.21: Right Shift (Division)
- [ ] Exercise 1.22: Device Register Control
- [ ] Exercise 1.23: Operator Precedence
- [ ] Exercise 1.24: Wi-Fi Status Register (Real-world)
- [ ] Exercise 1.25: Complex Logical Decisions

### Quality Checks
- [ ] All programs compile without errors
- [ ] All programs produce correct output
- [ ] Code is readable with comments
- [ ] Program didn't crash with invalid input
- [ ] Understand bitwise operations deeply
- [ ] Can explain operator precedence
- [ ] Can apply to real embedded systems scenarios

---

## 💡 Tips for Success

1. **Read the problem carefully** - Understand what's asked
2. **Break it down** - Divide into smaller parts
3. **Write pseudocode** - Plan before coding
4. **Test with examples** - Try different inputs
5. **Add comments** - Explain your logic
6. **Test edge cases** - Empty input, negative numbers, zero, etc.

---

## Next Steps

After completing these exercises:

✅ Review your solutions  
✅ Compare with others' code  
✅ Optimize for readability  
✅ Move to **Phase 2: Functions & Scope**  

