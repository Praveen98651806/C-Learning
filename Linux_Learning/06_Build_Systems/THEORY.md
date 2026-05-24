# Phase 6: Build Systems — Theory & Practice
> Time: Week 6 | Prerequisite: Phase 1-5 + C basics

---

## 6.1 GCC Compilation Stages

```
Source code (.c)
    │
    ▼ Preprocessor (cpp) — expands #include, #define, #ifdef
Preprocessed code (.i)
    │
    ▼ Compiler (cc1) — generates assembly
Assembly code (.s)
    │
    ▼ Assembler (as) — generates machine code
Object file (.o)
    │
    ▼ Linker (ld) — combines objects + libraries
Executable / Shared Library
```

```bash
# See each stage explicitly:
gcc -E program.c -o program.i    # Preprocessor only
gcc -S program.c -o program.s    # Compile to assembly
gcc -c program.c -o program.o    # Compile to object file
gcc program.o -o program         # Link only

# Normal build (all stages):
gcc program.c -o program
```

---

## 6.2 GCC Flags — Essential for Semiconductor Work

```bash
# Warnings and errors (ALWAYS use in development):
gcc -Wall -Wextra -Werror -o program program.c
# -Wall    : enable common warnings
# -Wextra  : extra warnings
# -Werror  : treat warnings as errors

# Debugging:
gcc -g program.c -o program      # Include debug symbols (for GDB)
gcc -g3 -ggdb program.c -o prog  # Maximum debug info

# Optimization:
gcc -O0 program.c -o prog        # No optimization (best for debugging)
gcc -O2 program.c -o prog        # Production optimization
gcc -Os program.c -o prog        # Optimize for size (embedded systems!)
gcc -O3 program.c -o prog        # Maximum speed (may increase size)

# Architecture targeting (CRITICAL for cross-compilation):
gcc -march=armv8-a program.c     # Target ARMv8-A (NXP Cortex-A)
gcc -mcpu=cortex-a53 program.c   # Specific CPU (NXP i.MX8)
gcc -mfpu=neon-vfpv4             # Enable NEON SIMD instructions

# Include paths:
gcc -I/path/to/headers program.c
gcc -I/opt/nxp_sdk/include program.c

# Library linking:
gcc program.c -lm              # Link math library (libm)
gcc program.c -lpthread        # Link pthread library
gcc program.c -L/opt/lib -lmychip  # Link custom library

# Define macros:
gcc -DDEBUG program.c          # Same as #define DEBUG
gcc -DCHIP_TYPE=QCA6490 program.c

# Output shared library:
gcc -shared -fPIC -o libmychip.so chip.c

# Output static library:
ar rcs libmychip.a chip.o
```

---

## 6.3 Makefile — The Build Script for C/Linux

### Basic Makefile:
```makefile
# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = my_program
SRCS = main.c utils.c chip_driver.c
OBJS = $(SRCS:.c=.o)         # Replace .c with .o

# Default target (first one is default)
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
#   $@ = target name (my_program)
#   $^ = all prerequisites (all .o files)
#   $< = first prerequisite

# Compile step (pattern rule)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not real files)
.PHONY: all clean
```

### Advanced Makefile (like real driver Makefiles):
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
LDFLAGS = -lpthread -lm
INCDIR = include/
SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

# Find all source files
SRCS = $(wildcard $(SRCDIR)*.c)
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
TARGET = $(BINDIR)my_program

all: directories $(TARGET)

directories:
	mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Print source files (debugging your Makefile)
print-%:
	@echo $* = $($*)

.PHONY: all clean directories
```

---

## 6.4 CMake — Used in Many NXP SDKs

```cmake
# CMakeLists.txt — minimum example
cmake_minimum_required(VERSION 3.10)
project(ChipDriver VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Compiler flags
add_compile_options(-Wall -Wextra -g)

# Add executable
add_executable(chip_tool
    src/main.c
    src/chip_init.c
    src/chip_comms.c
)

# Include directories
target_include_directories(chip_tool PRIVATE include/)

# Link libraries
target_link_libraries(chip_tool pthread m)

# Add a library
add_library(chiplib STATIC src/chip_lib.c)
target_link_libraries(chip_tool chiplib)
```

```bash
# Build with CMake:
mkdir build && cd build
cmake ..                           # Configure
cmake --build . -j4               # Build (4 parallel jobs)
# or: make -j4

# Cross-compile for ARM with CMake:
cmake -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake ..
```

```cmake
# arm-toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

---

## 6.5 Cross-Compilation (Daily Work in Semiconductor)

You build code on your **x86 host PC** but it runs on an **ARM board** (NXP i.MX, etc.).

```bash
# Install cross-compiler toolchain:
sudo apt install gcc-aarch64-linux-gnu   # For ARM64 (NXP i.MX8)
sudo apt install gcc-arm-linux-gnueabihf # For ARM32 (NXP i.MX6)

# Cross-compile a C program:
aarch64-linux-gnu-gcc -o my_program my_program.c

# Verify it's ARM binary:
file my_program
# Output: ELF 64-bit LSB executable, ARM aarch64...

# Transfer to board and run:
scp my_program root@192.168.1.100:/tmp/
ssh root@192.168.1.100 "/tmp/my_program"

# Cross-compile with Make:
make CC=aarch64-linux-gnu-gcc

# Cross-compile kernel module:
make -C /path/to/arm-kernel \
     M=$PWD \
     ARCH=arm64 \
     CROSS_COMPILE=aarch64-linux-gnu- \
     modules
```

---

## 6.6 Linux Kernel Build System (Kbuild)

When you modify the kernel or build drivers:

```bash
# Configure kernel (shows menu):
make menuconfig

# Build kernel:
make -j$(nproc)          # Use all CPU cores

# Build specific driver only:
make drivers/net/wireless/ath/ath11k/ -j4

# Build kernel modules:
make modules -j4

# Install modules to /lib/modules/$(uname -r)/:
sudo make modules_install

# Build for ARM:
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j8

# Enable/disable a driver in config:
# In menuconfig: Networking → Wireless → Atheros → ath11k
# Or directly edit .config:
# CONFIG_ATH11K=m    (m = module, y = built-in, n = disabled)
```

---

## 6.7 Static vs Shared Libraries

```bash
# Create object file:
gcc -c chip_utils.c -o chip_utils.o

# Static library (.a) — code is copied into executable:
ar rcs libchiputils.a chip_utils.o
gcc main.c -L. -lchiputils -o main_static
# Executable is self-contained, bigger size

# Shared library (.so) — loaded at runtime, smaller executables:
gcc -shared -fPIC -o libchiputils.so chip_utils.o
gcc main.c -L. -lchiputils -o main_shared
# Need libchiputils.so present at runtime:
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./main_shared

# Check what libraries an executable needs:
ldd my_program
# Output: libchiputils.so => ./libchiputils.so
```

---

## 6.8 Binary Analysis Tools

```bash
# nm — list symbols in object/library
nm my_program | grep "chip_init"
nm -D libmychip.so | grep " T "   # Exported functions

# objdump — disassemble binary
objdump -d my_program | head -50   # Disassembly
objdump -h my_program              # Section headers
objdump -t my_program              # Symbol table
objdump -S my_program              # Source + assembly (needs -g)

# readelf — ELF file analysis
readelf -h my_program              # ELF header
readelf -S my_program              # Section headers
readelf -d my_program              # Dynamic section (shared lib deps)

# strings — find human-readable strings in binary
strings firmware.bin | grep "version"
strings firmware.bin | grep "QCA"

# ldd — shared library dependencies
ldd my_program
ldd /usr/sbin/wpa_supplicant      # See what wpa_supplicant needs

# size — section sizes
size my_program
# text + data + bss = total program size
```

---

## Practice Exercises

1. Create a Makefile that compiles 3 C files and links them into one executable
2. Write a CMakeLists.txt for the same 3 files
3. Install ARM cross-compiler and cross-compile one of your C programs
4. Verify with `file` command that it's ARM ELF
5. Use `nm` on a compiled program to list its symbols
6. Use `readelf -h` to check architecture of a cross-compiled binary
7. Build a shared library from one of your utility functions

---

*Next: `07_Kernel_Drivers/THEORY.md`*
