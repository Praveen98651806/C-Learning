# C Functions & Scope — Complete Guide for Embedded/Semiconductor Engineers

> **Target Audience:** Firmware developers, embedded engineers, driver developers, semiconductor professionals  
> **Progression:** Beginner → Intermediate → Advanced → Expert  
> **Focus:** Practical, real-world patterns used in MCU firmware, RTOS, Linux kernel drivers

---

## Table of Contents

1. [BEGINNER — Function Basics](#1-beginner--function-basics)
2. [BEGINNER — Scope Types](#2-beginner--scope-types)
3. [INTERMEDIATE — Storage Classes](#3-intermediate--storage-classes)
4. [INTERMEDIATE — Memory Perspective](#4-intermediate--memory-perspective)
5. [INTERMEDIATE — Call by Value vs Reference](#5-intermediate--call-by-value-vs-reference)
6. [ADVANCED — Function Pointers](#6-advanced--function-pointers)
7. [ADVANCED — Static Functions & Modular Design](#7-advanced--static-functions--modular-design)
8. [ADVANCED — Inline Functions & Performance](#8-advanced--inline-functions--performance)
9. [ADVANCED — Recursion in Embedded Systems](#9-advanced--recursion-in-embedded-systems)
10. [EXPERT — Mini Projects: GPIO & ADC Drivers](#10-expert--mini-projects-gpio--adc-drivers)
11. [EXPERT — Multi-file Firmware Architecture](#11-expert--multi-file-firmware-architecture)
12. [Interview Questions & Tricky Answers](#12-interview-questions--tricky-answers)
13. [Common Mistakes & Debugging Insights](#13-common-mistakes--debugging-insights)

---

## 1. BEGINNER — Function Basics

### Theory

A function is a named block of code that performs a specific task. In embedded systems, functions map directly to:
- Hardware abstraction layers (HAL)
- Peripheral driver routines
- Interrupt handlers
- State machine transitions

### Syntax

```c
return_type function_name(parameter_type param1, parameter_type param2) {
    // body
    return value;
}
```

### Function Types

| Type | Syntax | Use in Embedded |
|------|--------|-----------------|
| No return, no param | `void init(void)` | Hardware init routines |
| Returns value | `uint32_t read_reg(void)` | Register reads |
| Takes params | `void write_reg(uint32_t val)` | Register writes |
| Both | `int8_t send_uart(uint8_t *buf, uint16_t len)` | UART TX |

### Examples — Progression

#### Simple: LED Toggle
```c
void led_toggle(void) {
    GPIOA->ODR ^= (1 << 5);   /* Toggle PA5 */
}
```

#### With Return Value: Read ADC
```c
uint16_t adc_read(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;           /* Start conversion */
    while (!(ADC1->SR & ADC_SR_EOC));        /* Wait for End Of Conversion */
    return (uint16_t)(ADC1->DR & 0x0FFF);   /* Return 12-bit result */
}
```

#### With Parameters: UART Send Byte
```c
void uart_send_byte(USART_TypeDef *uart, uint8_t data) {
    while (!(uart->SR & USART_SR_TXE));   /* Wait TX buffer empty */
    uart->DR = data;
}
```

#### With Return + Error Code: I2C Write
```c
/* Returns 0 on success, negative on error */
int8_t i2c_write(uint8_t addr, uint8_t *data, uint16_t len) {
    if (data == NULL || len == 0)
        return -1;   /* Invalid argument */

    i2c_start();

    if (!i2c_send_addr(addr | I2C_WRITE))
        return -2;   /* No ACK */

    for (uint16_t i = 0; i < len; i++) {
        if (!i2c_send_byte(data[i]))
            return -3;   /* Data NACK */
    }

    i2c_stop();
    return 0;   /* Success */
}
```

### Function Declaration vs Definition

```c
/* Declaration (prototype) — goes in .h file */
uint16_t adc_read(void);
void uart_send_byte(USART_TypeDef *uart, uint8_t data);

/* Definition — goes in .c file */
uint16_t adc_read(void) {
    /* ... implementation ... */
}
```

> **Rule:** Always declare before use. In multi-file firmware, prototypes go in header files.

---

## 2. BEGINNER — Scope Types

### What is Scope?

Scope defines **where a variable or function is visible and accessible** in your code.

### 4 Types of Scope

#### 1. Block Scope (Most Restricted)

Variable exists only within `{ }` braces.

```c
void gpio_init(void) {
    uint32_t temp;              /* Only visible inside this function */
    temp = GPIOA->CRL;
    temp &= ~(0xF << 20);
    temp |= (0x3 << 20);        /* Output push-pull 50MHz */
    GPIOA->CRL = temp;
}   /* temp is destroyed here */
```

#### 2. Function Scope

Only applies to `goto` labels — visible anywhere within the function.

```c
void spi_transfer(void) {
retry:
    if (SPI1->SR & SPI_SR_MODF) {   /* Mode fault */
        SPI1->CR1 |= SPI_CR1_SPE;   /* Re-enable */
        goto retry;
    }
    /* ... proceed ... */
}
```

#### 3. File Scope (Static Global)

Variable declared outside all functions, only visible within that `.c` file.

```c
/* uart.c */
static uint32_t baud_rate = 115200;    /* Only uart.c can access this */
static uint8_t tx_buffer[256];

void uart_init(uint32_t baud) {
    baud_rate = baud;   /* Accessible here */
}
```

#### 4. Global Scope

Visible across ALL files (with `extern` declaration).

```c
/* system.c */
uint32_t system_clock_hz = 168000000;   /* 168 MHz */

/* gpio.c */
extern uint32_t system_clock_hz;   /* Declare to use it */

void gpio_set_speed(uint8_t speed) {
    if (system_clock_hz > 100000000)
        /* use high-speed settings */;
}
```

### Scope Summary Table

| Scope | Location | Visible In | Lifetime |
|-------|----------|------------|----------|
| Block | Inside `{}` | That block only | Duration of block |
| Function | Function body | Whole function | Duration of call |
| File (static) | Outside functions, `static` | That `.c` file only | Entire program |
| Global | Outside functions | All files (with `extern`) | Entire program |

---

## 3. INTERMEDIATE — Storage Classes

### `auto` (Default)

Every local variable is `auto` by default. Created on stack, destroyed on return.

```c
void read_sensor(void) {
    auto int raw;       /* Same as: int raw; */
    raw = ADC1->DR;
    process(raw);
}   /* raw destroyed here */
```

> **In embedded:** Never use `auto` explicitly — it's the default and `auto` has a different meaning in C++.

---

### `static` (Most Important in Embedded!)

**For local variables:** Persists across function calls (stored in data segment, not stack).

```c
uint8_t debounce_button(void) {
    static uint8_t prev_state = 0;    /* Initialized ONCE at startup */
    static uint32_t last_time = 0;

    uint8_t curr = (GPIOA->IDR >> 0) & 0x1;

    if (curr != prev_state) {
        uint32_t now = systick_get_ms();
        if ((now - last_time) > 50) {   /* 50ms debounce */
            prev_state = curr;
            last_time = now;
            return curr;   /* State changed */
        }
    }
    return 0xFF;   /* No change */
}
```

**For global variables/functions:** Restricts visibility to the current `.c` file only.

```c
/* uart.c — internal state, hidden from other files */
static uint8_t  rx_buf[512];
static uint16_t rx_head = 0;
static uint16_t rx_tail = 0;

static void rx_buffer_push(uint8_t byte) {   /* Private helper */
    rx_buf[rx_head] = byte;
    rx_head = (rx_head + 1) % sizeof(rx_buf);
}
```

---

### `extern`

Declares a variable/function defined in **another file**.

```c
/* clocks.c */
uint32_t ahb_clock_hz  = 168000000;
uint32_t apb1_clock_hz =  42000000;
uint32_t apb2_clock_hz =  84000000;

/* uart.c */
extern uint32_t apb1_clock_hz;   /* UART clocks from APB1 */

void uart_set_baud(uint32_t baud) {
    uint32_t div = apb1_clock_hz / (16 * baud);
    USART2->BRR = div;
}
```

---

### `register`

Hint to compiler to store in CPU register for speed. Mostly ignored by modern compilers.

```c
void fast_memcpy(uint8_t *dst, const uint8_t *src, register uint32_t len) {
    while (len--)
        *dst++ = *src++;
}
```

> **In embedded:** Rarely used today — compilers optimize better on their own. Useful hint for critical ISR loops.

---

### Storage Class Summary

| Class | Where Stored | Lifetime | Default Value | Visibility |
|-------|-------------|----------|---------------|------------|
| `auto` | Stack | Function call | Garbage | Block |
| `static` (local) | Data/BSS | Whole program | 0 | Block |
| `static` (global) | Data/BSS | Whole program | 0 | File |
| `extern` | Data/BSS | Whole program | (from definition) | All files |
| `register` | CPU register | Function call | Garbage | Block |

---

## 4. INTERMEDIATE — Memory Perspective

### Memory Layout of an Embedded Program

```
High Address  ┌─────────────────────────────┐
              │         STACK               │ ← Local vars, function frames
              │    (grows downward ↓)        │
              ├─────────────────────────────┤
              │           ↑                 │
              │         HEAP                │ ← malloc/free (avoid in bare-metal)
              │    (grows upward ↑)          │
              ├─────────────────────────────┤
              │    BSS Segment              │ ← Uninitialized globals/statics (zeroed)
              ├─────────────────────────────┤
              │    Data Segment             │ ← Initialized globals/statics
              ├─────────────────────────────┤
              │    Text/Code Segment        │ ← Function code, constants
Low Address   └─────────────────────────────┘
```

### Where Variables Live

```c
uint32_t g_clock = 48000000;       /* Data segment  — initialized global */
uint8_t  g_buffer[1024];           /* BSS segment   — uninitialized global (zeroed) */

void uart_isr(void) {
    static uint8_t count = 0;      /* Data/BSS      — static local */
    uint8_t byte = USART1->DR;     /* Stack         — local auto */
    count++;
}

void* ptr = malloc(64);            /* Heap          — dynamic (avoid in bare-metal!) */
```

### Stack in Embedded Systems — Critical!

```c
/* DANGEROUS: Large array on stack can overflow in MCU (e.g., 4KB stack) */
void bad_function(void) {
    uint8_t big_buffer[4096];   /* 4KB on stack — may cause stack overflow! */
    process(big_buffer);
}

/* CORRECT: Use static or global for large buffers */
static uint8_t big_buffer[4096];   /* Data/BSS — safe */

void good_function(void) {
    process(big_buffer);
}
```

### Stack Frame — What Happens on Function Call

```
Before call:                After call to foo(x, y):
┌────────────┐              ┌────────────┐
│  main vars │              │  main vars │
├────────────┤              ├────────────┤
│            │              │  ret addr  │ ← pushed by CALL
│            │              │  param y   │ ← argument
│            │              │  param x   │ ← argument
│            │              │  local a   │ ← local var of foo
│            │              │  local b   │ ← local var of foo
└────────────┘              └────────────┘
     SP →                        SP →
```

> **Key insight:** Every function call costs stack space. Deep call chains in ISRs with limited stack = crash!

---

## 5. INTERMEDIATE — Call by Value vs Reference

### Call by Value

A **copy** of the argument is passed. Original is unaffected.

```c
/* Value copy — original unchanged */
void set_frequency(uint32_t freq) {
    freq = freq * 1000;   /* Only modifies local copy */
}

int main(void) {
    uint32_t hz = 8;
    set_frequency(hz);
    /* hz is still 8 here! */
}
```

### Call by Reference (via Pointer)

A **pointer** to the argument is passed. Original can be modified.

```c
/* Pointer — modifies original */
void set_frequency(uint32_t *freq) {
    *freq = *freq * 1000;   /* Modifies the actual variable */
}

int main(void) {
    uint32_t hz = 8;
    set_frequency(&hz);
    /* hz is now 8000 */
}
```

### Embedded Patterns Using Pointers

#### Pattern 1: Return multiple values (status + data)
```c
/* Returns error code, fills data via pointer */
int8_t adc_read_channel(uint8_t channel, uint16_t *result) {
    if (channel > 15)
        return -1;   /* Error */

    ADC1->SQR3 = channel;
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    *result = ADC1->DR;   /* Write result through pointer */
    return 0;             /* Success */
}

/* Usage */
uint16_t adc_val;
if (adc_read_channel(3, &adc_val) == 0) {
    process(adc_val);
}
```

#### Pattern 2: Config struct by pointer
```c
typedef struct {
    uint32_t baud_rate;
    uint8_t  data_bits;
    uint8_t  stop_bits;
    uint8_t  parity;
} uart_config_t;

/* Pass large structs by pointer — avoids copying on stack */
void uart_init(const uart_config_t *cfg) {
    uint32_t brr = apb1_clock / (16 * cfg->baud_rate);
    USART2->BRR = brr;
    /* ... apply data bits, parity etc ... */
}

/* Usage */
uart_config_t cfg = { .baud_rate = 115200, .data_bits = 8,
                      .stop_bits = 1,      .parity = 0 };
uart_init(&cfg);   /* Pass address, no data copy */
```

#### Pattern 3: `const` pointer — read-only input
```c
/* const = caller's data won't be modified */
void spi_write(const uint8_t *data, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        while (!(SPI1->SR & SPI_SR_TXE));
        SPI1->DR = data[i];
    }
}
```

---

## 6. ADVANCED — Function Pointers

### Theory

A function pointer stores the **address of a function**. Used for:
- Callbacks (ISR hooks)
- Driver abstraction layers (HAL)
- State machines
- Event dispatch tables

### Syntax

```c
/* Declare a function pointer type */
typedef void (*isr_handler_t)(void);
typedef int  (*read_fn_t)(uint8_t *buf, uint16_t len);

/* Or without typedef */
void (*handler)(void);
```

### Example 1: ISR Callback Registration

```c
/* isr_manager.c */
typedef void (*isr_callback_t)(void);

static isr_callback_t uart1_rx_cb = NULL;
static isr_callback_t timer2_cb   = NULL;

void uart1_register_rx_callback(isr_callback_t cb) {
    uart1_rx_cb = cb;
}

/* ISR — calls registered callback */
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        if (uart1_rx_cb != NULL)
            uart1_rx_cb();   /* Call the registered handler */
    }
}

/* application.c */
void my_uart_handler(void) {
    uint8_t rx = USART1->DR;
    process_byte(rx);
}

int main(void) {
    uart1_register_rx_callback(my_uart_handler);
    /* ... */
}
```

### Example 2: Driver Abstraction (HAL-style)

```c
/* Abstraction — any communication bus can be plugged in */
typedef struct {
    int8_t  (*init)(uint32_t speed);
    int8_t  (*write)(uint8_t addr, const uint8_t *data, uint16_t len);
    int8_t  (*read)(uint8_t addr, uint8_t *data,  uint16_t len);
    void    (*deinit)(void);
} bus_ops_t;

/* SPI implementation */
static int8_t spi_init_impl(uint32_t speed)  { /* ... */ return 0; }
static int8_t spi_write_impl(uint8_t a, const uint8_t *d, uint16_t l) { /* ... */ return 0; }
static int8_t spi_read_impl (uint8_t a, uint8_t *d, uint16_t l) { /* ... */ return 0; }
static void   spi_deinit_impl(void) { /* ... */ }

const bus_ops_t spi_ops = {
    .init   = spi_init_impl,
    .write  = spi_write_impl,
    .read   = spi_read_impl,
    .deinit = spi_deinit_impl,
};

/* Sensor driver — doesn't care if SPI or I2C */
void sensor_read(const bus_ops_t *bus, uint8_t reg, uint8_t *val) {
    bus->write(SENSOR_ADDR, &reg, 1);
    bus->read(SENSOR_ADDR, val, 1);
}

/* Usage: swap bus without changing sensor code */
sensor_read(&spi_ops, REG_TEMP, &temp);
sensor_read(&i2c_ops, REG_TEMP, &temp);
```

### Example 3: State Machine with Function Pointers

```c
typedef void (*state_fn_t)(void);

void state_idle(void);
void state_tx(void);
void state_rx(void);
void state_error(void);

static state_fn_t current_state = state_idle;

void state_idle(void) {
    if (tx_request)   current_state = state_tx;
    if (rx_available) current_state = state_rx;
}

void state_tx(void) {
    send_packet();
    if (tx_done)   current_state = state_idle;
    if (tx_error)  current_state = state_error;
}

/* Main loop */
while (1) {
    current_state();   /* Call whichever state is active */
}
```

### Example 4: Interrupt Vector Table (Bare-Metal)

```c
/* Cortex-M vector table — array of function pointers */
typedef void (*vector_fn_t)(void);

extern uint32_t _estack;    /* Linker symbol: top of stack */

__attribute__((section(".isr_vector")))
const vector_fn_t vector_table[] = {
    (vector_fn_t)&_estack,   /* Initial stack pointer */
    Reset_Handler,            /* Reset */
    NMI_Handler,              /* NMI */
    HardFault_Handler,        /* Hard Fault */
    /* ... */
    USART1_IRQHandler,        /* USART1 */
    SPI1_IRQHandler,          /* SPI1 */
};
```

---

## 7. ADVANCED — Static Functions & Modular Design

### Why `static` Functions Matter

`static` on a function = **private to the `.c` file**. This is the foundation of firmware modularity.

```
gpio.c                    uart.c                   main.c
┌─────────────────┐       ┌──────────────────┐     ┌──────────────┐
│ gpio_init()     │◄──────│                  │     │              │
│ gpio_set()      │◄──────│                  │◄────│ gpio_init()  │
│ gpio_get()      │◄──────│                  │◄────│ uart_init()  │
│                 │       │ uart_init()       │◄────│ adc_read()   │
│ ► set_mode()   │       │ uart_send()       │◄────│              │
│   [private]     │       │                  │
│ ► calc_speed() │       │ ► format_byte()  │
│   [private]     │       │   [private]       │
└─────────────────┘       └──────────────────┘
```

### Example: GPIO Driver with Private Helpers

**gpio.h** — Public interface only:
```c
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum { GPIO_INPUT = 0, GPIO_OUTPUT } gpio_dir_t;
typedef enum { GPIO_LOW   = 0, GPIO_HIGH   } gpio_state_t;

void       gpio_init(uint8_t pin, gpio_dir_t dir);
void       gpio_write(uint8_t pin, gpio_state_t state);
gpio_state_t gpio_read(uint8_t pin);

#endif
```

**gpio.c** — Private helpers hidden:
```c
#include "gpio.h"

/* Private — not visible outside this file */
static GPIO_TypeDef* get_port(uint8_t pin) {
    if (pin < 16) return GPIOA;
    if (pin < 32) return GPIOB;
    return GPIOC;
}

static uint8_t get_pin_num(uint8_t pin) {
    return pin % 16;
}

static void enable_clock(GPIO_TypeDef *port) {
    if (port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    if (port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    if (port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}

/* Public — exposed via gpio.h */
void gpio_init(uint8_t pin, gpio_dir_t dir) {
    GPIO_TypeDef *port = get_port(pin);      /* Private call */
    uint8_t p          = get_pin_num(pin);   /* Private call */
    enable_clock(port);                       /* Private call */

    port->MODER &= ~(0x3 << (p * 2));
    if (dir == GPIO_OUTPUT)
        port->MODER |= (0x1 << (p * 2));
}
```

### Benefits of `static` Functions

1. **Encapsulation** — implementation details stay hidden
2. **Name clash prevention** — two files can both have `static void reset()` without conflict
3. **Compiler optimization** — compiler can inline and optimize `static` functions more aggressively
4. **Unit testability** — clear public API

---

## 8. ADVANCED — Inline Functions & Performance

### Theory

`inline` suggests the compiler to **replace the function call with the function body** — eliminates call overhead (push/pop stack frame).

```c
/* Without inline: each call = PUSH, JUMP, POP = 3+ cycles */
uint32_t read_reg(volatile uint32_t *addr) {
    return *addr;
}

/* With inline: compiler pastes the code directly = 1 cycle */
static inline uint32_t read_reg(volatile uint32_t *addr) {
    return *addr;
}
```

### When to Use in Embedded

```c
/* Perfect for inline: tiny, called very frequently */
static inline uint8_t gpio_read_pin(GPIO_TypeDef *port, uint8_t pin) {
    return (port->IDR >> pin) & 0x1;
}

static inline void gpio_set_pin(GPIO_TypeDef *port, uint8_t pin) {
    port->BSRR = (1 << pin);   /* Atomic set */
}

static inline void gpio_clear_pin(GPIO_TypeDef *port, uint8_t pin) {
    port->BSRR = (1 << (pin + 16));   /* Atomic clear */
}

/* Used in tight loop — no function call overhead */
while (1) {
    if (gpio_read_pin(GPIOA, 0))
        gpio_set_pin(GPIOB, 5);
    else
        gpio_clear_pin(GPIOB, 5);
}
```

### Inline vs Macro

```c
/* Macro — no type safety, no debuggability */
#define READ_REG(addr)  (*(volatile uint32_t *)(addr))
#define BIT_SET(r, b)   ((r) |= (1 << (b)))   /* Danger: b evaluated twice! */

/* Inline function — type safe, debuggable, no side effects */
static inline void bit_set(volatile uint32_t *reg, uint8_t bit) {
    *reg |= (1U << bit);
}

/* Always prefer inline over macros for functions */
```

### `__attribute__((always_inline))` — Force Inline

```c
/* Critical ISR path — compiler MUST inline regardless of optimization level */
__attribute__((always_inline))
static inline void clear_pending_irq(uint8_t irq) {
    NVIC->ICPR[irq >> 5] = (1 << (irq & 0x1F));
}
```

---

## 9. ADVANCED — Recursion in Embedded Systems

### Theory

Recursion = function calling itself. Each call adds a **stack frame**.

### Simple Example: Factorial

```c
uint32_t factorial(uint32_t n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);   /* Stack grows with each call */
}
```

### Embedded Use Case: Traverse Linked List / Tree

```c
/* Walk a singly linked list (e.g., command queue) */
typedef struct node_t {
    uint8_t cmd;
    struct node_t *next;
} node_t;

void execute_all(node_t *node) {
    if (node == NULL) return;   /* Base case */
    execute_command(node->cmd);
    execute_all(node->next);   /* Recursive: ~3 words of stack per call */
}
```

### Recursion in Embedded — RISKS

```c
/* DANGEROUS: Unbounded recursion can easily overflow a 1-4KB stack */
void parse_packet(packet_t *pkt) {
    if (pkt->has_extension)
        parse_packet(pkt->extension);   /* Depth unknown = STACK OVERFLOW! */
}
```

### When to Avoid / Use

| Situation | Recommendation |
|-----------|----------------|
| Bare-metal MCU (< 8KB stack) | **AVOID** — use iterative instead |
| Deep recursion (unknown depth) | **AVOID** — use loop or explicit stack |
| RTOS tasks (each has own stack) | **Careful** — know your max depth |
| Fixed-depth recursion (e.g., depth ≤ 4) | **OK** — stack usage is bounded and known |
| Linux kernel driver | **AVOID** — kernel stack is small (8KB) |

### Iterative Alternative (Preferred in Embedded)

```c
/* Iterative version — O(1) stack usage */
void execute_all_iter(node_t *node) {
    while (node != NULL) {
        execute_command(node->cmd);
        node = node->next;
    }
}
```

---

## 10. EXPERT — Mini Projects: GPIO & ADC Drivers

### Mini Project 1: Complete GPIO Driver

**gpio.h**
```c
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Pin definitions: port*16 + pin_num */
#define PA0   0    /* GPIOA pin 0 */
#define PA5   5
#define PB8   24   /* GPIOB pin 8 */
#define PC13  45   /* GPIOC pin 13 */

typedef enum { GPIO_MODE_INPUT=0, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG } gpio_mode_t;
typedef enum { GPIO_PULL_NONE=0, GPIO_PULL_UP, GPIO_PULL_DOWN } gpio_pull_t;
typedef enum { GPIO_SPEED_LOW=0, GPIO_SPEED_MED, GPIO_SPEED_HIGH, GPIO_SPEED_VHIGH } gpio_speed_t;

typedef struct {
    uint8_t      pin;
    gpio_mode_t  mode;
    gpio_pull_t  pull;
    gpio_speed_t speed;
    uint8_t      af;   /* Alternate function number (0-15) */
} gpio_config_t;

void gpio_configure(const gpio_config_t *cfg);
void gpio_write(uint8_t pin, uint8_t state);
uint8_t gpio_read(uint8_t pin);
void gpio_toggle(uint8_t pin);

#endif
```

**gpio.c**
```c
#include "gpio.h"
#include "stm32f4xx.h"

/* Private helpers */
static GPIO_TypeDef* get_port(uint8_t pin) {
    switch (pin / 16) {
        case 0: return GPIOA;
        case 1: return GPIOB;
        case 2: return GPIOC;
        case 3: return GPIOD;
        default: return NULL;
    }
}

static void enable_gpio_clock(uint8_t port_idx) {
    RCC->AHB1ENR |= (1 << port_idx);
    (void)RCC->AHB1ENR;   /* Read-back to ensure clock is enabled */
}

/* Public API */
void gpio_configure(const gpio_config_t *cfg) {
    if (!cfg) return;

    uint8_t pn       = cfg->pin % 16;
    uint8_t port_idx = cfg->pin / 16;
    GPIO_TypeDef *port = get_port(cfg->pin);

    if (!port) return;

    enable_gpio_clock(port_idx);

    /* Mode */
    port->MODER &= ~(0x3 << (pn * 2));
    port->MODER |=  (cfg->mode << (pn * 2));

    /* Pull-up/down */
    port->PUPDR &= ~(0x3 << (pn * 2));
    port->PUPDR |=  (cfg->pull << (pn * 2));

    /* Speed */
    port->OSPEEDR &= ~(0x3 << (pn * 2));
    port->OSPEEDR |=  (cfg->speed << (pn * 2));

    /* Alternate function */
    if (cfg->mode == GPIO_MODE_AF) {
        if (pn < 8) {
            port->AFR[0] &= ~(0xF << (pn * 4));
            port->AFR[0] |=  (cfg->af << (pn * 4));
        } else {
            port->AFR[1] &= ~(0xF << ((pn-8) * 4));
            port->AFR[1] |=  (cfg->af << ((pn-8) * 4));
        }
    }
}

void gpio_write(uint8_t pin, uint8_t state) {
    GPIO_TypeDef *port = get_port(pin);
    uint8_t pn = pin % 16;
    if (!port) return;
    if (state)
        port->BSRR = (1 << pn);         /* Atomic set */
    else
        port->BSRR = (1 << (pn + 16));  /* Atomic clear */
}

uint8_t gpio_read(uint8_t pin) {
    GPIO_TypeDef *port = get_port(pin);
    if (!port) return 0;
    return (port->IDR >> (pin % 16)) & 0x1;
}

void gpio_toggle(uint8_t pin) {
    GPIO_TypeDef *port = get_port(pin);
    if (!port) return;
    port->ODR ^= (1 << (pin % 16));
}
```

---

### Mini Project 2: ADC Driver with Callback

**adc.h**
```c
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

typedef void (*adc_complete_cb_t)(uint8_t channel, uint16_t value);

void    adc_init(void);
void    adc_register_callback(adc_complete_cb_t cb);
void    adc_start(uint8_t channel);
uint16_t adc_read_blocking(uint8_t channel);

#endif
```

**adc.c**
```c
#include "adc.h"
#include "stm32f4xx.h"

/* Private state */
static adc_complete_cb_t adc_cb      = NULL;
static uint8_t           active_chan = 0;

/* Private helper */
static void select_channel(uint8_t ch) {
    ADC1->SQR3 = (ch & 0x1F);   /* Single conversion, sequence length = 1 */
}

/* Public API */
void adc_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC1->CR2  = 0;
    ADC1->CR1  = 0;
    ADC1->SMPR2 = (7 << 0);   /* Max sample time for ch0-9 */
    ADC1->CR2 |= ADC_CR2_ADON;   /* Power up ADC */
    /* Wait stabilization */
    for (volatile int i = 0; i < 1000; i++);
}

void adc_register_callback(adc_complete_cb_t cb) {
    adc_cb = cb;
}

uint16_t adc_read_blocking(uint8_t channel) {
    select_channel(channel);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return (uint16_t)(ADC1->DR & 0x0FFF);
}

void adc_start(uint8_t channel) {
    active_chan = channel;
    select_channel(channel);
    ADC1->CR1 |= ADC_CR1_EOCIE;     /* Enable end-of-conversion interrupt */
    ADC1->CR2  |= ADC_CR2_SWSTART;  /* Start conversion */
}

/* ISR — called by hardware */
void ADC_IRQHandler(void) {
    if (ADC1->SR & ADC_SR_EOC) {
        uint16_t val = (uint16_t)(ADC1->DR & 0x0FFF);
        if (adc_cb != NULL)
            adc_cb(active_chan, val);   /* Fire callback */
    }
}
```

**main.c usage:**
```c
#include "gpio.h"
#include "adc.h"

static void on_adc_done(uint8_t ch, uint16_t val) {
    /* Called from ISR — keep SHORT */
    if (val > 2048)
        gpio_write(PA5, 1);   /* LED on if voltage > ~1.65V */
    else
        gpio_write(PA5, 0);
}

int main(void) {
    gpio_configure(&(gpio_config_t){ PA5, GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_SPEED_LOW, 0 });

    adc_init();
    adc_register_callback(on_adc_done);

    while (1) {
        adc_start(0);        /* Start channel 0 */
        delay_ms(100);       /* Do other work while conversion happens */
    }
}
```

---

## 11. EXPERT — Multi-file Firmware Architecture

### Typical Firmware Layout

```
firmware/
├── main.c              ← Application entry
├── app/
│   ├── app.c           ← Application logic
│   └── app.h
├── drivers/
│   ├── gpio.c / gpio.h
│   ├── uart.c / uart.h
│   ├── spi.c  / spi.h
│   └── adc.c  / adc.h
├── hal/
│   ├── clocks.c / clocks.h
│   └── nvic.c   / nvic.h
└── utils/
    ├── ring_buffer.c / ring_buffer.h
    └── crc.c         / crc.h
```

### Scope Rules Across Files

```c
/* clocks.h — extern declarations for shared variables */
#ifndef CLOCKS_H
#define CLOCKS_H
extern uint32_t sys_clock_hz;
extern uint32_t apb1_clock_hz;
void clocks_init(uint32_t target_mhz);
#endif

/* clocks.c — actual definitions */
uint32_t sys_clock_hz  = 16000000;   /* Default: HSI 16MHz */
uint32_t apb1_clock_hz =  8000000;

/* uart.c — uses shared clock */
#include "clocks.h"
extern uint32_t apb1_clock_hz;   /* From clocks.c */

void uart_set_baud(uint32_t baud) {
    USART2->BRR = apb1_clock_hz / baud;
}
```

### Guard Headers — Prevent Double Include

```c
/* Always use include guards in every .h file */
#ifndef UART_H
#define UART_H

/* ... declarations ... */

#endif /* UART_H */
```

---

## 12. Interview Questions & Tricky Answers

### Q1: What is the difference between `static` local and `static` global?

**Answer:**
- `static` local: variable persists across calls but visible only in that function
- `static` global/function: visible only within the `.c` file — used for encapsulation

---

### Q2: Can a local variable be `extern`?

**Answer:** No. `extern` is for global (file-scope) variables/functions. Local variables cannot be `extern`.

---

### Q3: What happens if you don't initialize a `static` variable?

**Answer:** It is automatically initialized to **zero** by the C runtime startup code (`_startup`). This is guaranteed by the C standard.

```c
static uint8_t count;    /* = 0, guaranteed */
uint8_t local;           /* = garbage! */
```

---

### Q4: Why is `volatile` important with pointers to hardware registers?

**Answer:** Without `volatile`, the compiler may optimize away repeated reads/writes (cache the value in a register). Hardware registers can change outside the program's control (by hardware), so each access must go to actual memory.

```c
/* WRONG — compiler may optimize the while loop away */
while (!(USART1->SR & USART_SR_TXE));

/* CORRECT — volatile pointer forces actual register read each time */
volatile uint32_t *sr = &USART1->SR;
while (!(*sr & USART_SR_TXE));
```

---

### Q5: What is a re-entrant function?

**Answer:** A function that can be safely called while already executing (e.g., from an ISR while also running in main loop). A re-entrant function:
- Uses only local variables (no `static` locals)
- Does not access shared global state without protection
- Does not call non-reentrant functions

```c
/* NOT re-entrant — static variable shared */
uint8_t checksum(uint8_t *data, uint16_t len) {
    static uint8_t sum;   /* Danger if called from ISR and main! */
    sum = 0;
    for (uint16_t i = 0; i < len; i++) sum += data[i];
    return sum;
}

/* Re-entrant — all on stack */
uint8_t checksum(const uint8_t *data, uint16_t len) {
    uint8_t sum = 0;   /* Local — each call has own copy */
    for (uint16_t i = 0; i < len; i++) sum += data[i];
    return sum;
}
```

---

### Q6: When would you use `inline` vs a macro vs a regular function?

| Situation | Use |
|-----------|-----|
| Simple, small, performance-critical | `static inline` |
| Needs type safety + debugging | `static inline` |
| Needs to work on any type (generics) | Macro |
| Complex logic, called infrequently | Regular function |
| ISR hot path, tiny operation | `__attribute__((always_inline))` |

---

### Q7: What is the danger of recursion in ISRs?

**Answer:** Each recursive call adds a stack frame. ISRs share the main stack (or a separate ISR stack). Deep or unbounded recursion inside an ISR will overflow the stack, causing a HardFault on Cortex-M and system crash. Always use iterative solutions inside ISRs.

---

### Q8: What does `const` in a function parameter mean?

```c
void process(const uint8_t *data, uint16_t len);
```

**Answer:** The function promises **not to modify** what `data` points to. This:
1. Prevents accidental modification
2. Allows passing literals/const arrays
3. Documents intent clearly — important in driver APIs

---

## 13. Common Mistakes & Debugging Insights

### Mistake 1: Returning pointer to local variable

```c
/* WRONG — returns dangling pointer! local destroyed on return */
uint8_t* get_buffer(void) {
    uint8_t buf[64];
    return buf;   /* BUG: buf is on stack, gone after return */
}

/* CORRECT — static persists */
uint8_t* get_buffer(void) {
    static uint8_t buf[64];
    return buf;
}
```

---

### Mistake 2: Missing `volatile` on shared ISR variable

```c
/* WRONG — compiler may cache flag and never see ISR update */
uint8_t rx_done = 0;
void USART1_IRQHandler(void) { rx_done = 1; }
void main_loop(void) {
    while (!rx_done);   /* May loop forever! */
}

/* CORRECT */
volatile uint8_t rx_done = 0;
```

---

### Mistake 3: Global name collision across files

```c
/* file1.c and file2.c both define: */
int counter = 0;   /* LINKER ERROR: multiple definition! */

/* Fix: use static to limit scope */
static int counter = 0;   /* Each file has its own 'counter' */
```

---

### Mistake 4: Stack overflow from large local arrays

```c
/* MCU has 8KB stack, this alone = 4KB */
void process(void) {
    uint8_t workspace[4096];   /* DANGEROUS */
    /* ... */
}

/* Fix: use static or global */
static uint8_t workspace[4096];   /* Safe — in data segment */
```

---

### Mistake 5: Forgetting to check NULL function pointer

```c
/* CRASH if callback not registered */
void USART1_IRQHandler(void) {
    rx_callback(USART1->DR);   /* Fault if NULL! */
}

/* CORRECT */
void USART1_IRQHandler(void) {
    if (rx_callback)
        rx_callback(USART1->DR);
}
```

---

### Mistake 6: Doing too much in an ISR

```c
/* WRONG — ISR should be minimal */
void USART1_IRQHandler(void) {
    uint8_t byte = USART1->DR;
    parse_full_packet(&byte);   /* Heavy processing in ISR! */
    update_display();           /* Very wrong! */
}

/* CORRECT — ISR just buffers, main loop processes */
void USART1_IRQHandler(void) {
    rx_ring_buf_push(USART1->DR);  /* Fast, minimal */
    rx_pending = 1;                 /* Signal main loop */
}
```

---

## Design Best Practices Summary

| Practice | Rule |
|----------|------|
| Encapsulation | Use `static` for all private functions and variables |
| Interfaces | Expose only public API in `.h` files |
| ISR design | Keep ISRs minimal — set flag, push to buffer, return |
| Large buffers | Use `static` or global, never on stack |
| Shared state | Protect with `volatile` if accessed from ISR |
| Function size | Each function should do ONE thing |
| Error handling | Always return error codes from driver functions |
| Callbacks | Always NULL-check before calling function pointer |
| Parameters | Pass large structs by `const` pointer, not value |
| Naming | `module_action_object()` e.g., `uart_send_byte()` |

---

*References: ARM Cortex-M Architecture Reference, MISRA C:2012, Linux Kernel Coding Style, STM32 HAL Source*
