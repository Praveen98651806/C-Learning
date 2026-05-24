# Linux Learning Progress Tracker
> Track your Linux learning alongside C learning

---

## Setup Status
- [ ] WSL2 Ubuntu 22.04 installed
- [ ] `build-essential`, `git`, `gdb`, `valgrind` installed
- [ ] Can access C-Learning files from WSL2 (`/mnt/c/Users/...`)
- [ ] First 10 commands working: `ls`, `cd`, `grep`, `find`, `ps`, `dmesg`, `lsmod`, `man`

---

## Phase Progress

### Phase 1: Linux Basics (Week 1)
- [ ] Filesystem hierarchy understood (/proc, /sys, /dev)
- [ ] Navigation commands mastered
- [ ] `grep`, `awk`, `sed` used on real log files
- [ ] `lspci`, `lsmod`, `dmesg` used
- [ ] SSH configured (key-based auth)
- [ ] **Combined exercise:** Compile and run a C program from WSL2

### Phase 2: Shell Scripting (Week 2)
- [ ] Variables, arrays, arithmetic
- [ ] if/else, case, loops
- [ ] Functions
- [ ] Script: Log parser (parse dmesg output)
- [ ] Script: Build automator for C files
- [ ] Script: Monitor network interface

### Phase 3: File System & Permissions (Week 3)
- [ ] Permission bits understood (rwx = 7/6/5/4/3/2/1/0)
- [ ] `/proc` explored and understood
- [ ] `/sys` explored: found network interface attributes
- [ ] `/dev` explored: found device nodes
- [ ] Hard link vs symlink tested
- [ ] **Combined exercise:** C program that reads `/proc/net/dev`

### Phase 4: Processes, Signals, pthreads (Week 4)
- [ ] `fork()` + `wait()` program written
- [ ] `exec()` program written
- [ ] Signal handler (SIGTERM, SIGUSR1) working
- [ ] pthread program with mutex written
- [ ] Pipe IPC between parent and child
- [ ] **Combined exercise:** Multi-threaded C program on Linux (not just Windows)

### Phase 5: Networking (Week 5)
- [ ] Socket TCP client in C
- [ ] Socket TCP server in C
- [ ] UDP socket program
- [ ] `tcpdump` used to capture own socket traffic
- [ ] `netlink` socket simple example
- [ ] **Chip exercise:** `iw dev wlan0 info` and interpret output

### Phase 6: Build Systems (Week 6)
- [ ] Makefile with multiple C files working
- [ ] CMakeLists.txt basic build working
- [ ] ARM cross-compiler installed
- [ ] Cross-compiled a C program, `file` shows ARM ELF
- [ ] `nm`, `objdump`, `readelf` used on own binaries
- [ ] **Combined exercise:** Cross-compile your Pointers C exercise for ARM

### Phase 7: Debugging Tools (Week 7)
- [ ] GDB: breakpoints, watchpoints, backtrace used
- [ ] `strace` used on a simple program
- [ ] `valgrind` run on a C program with intentional memory leak
- [ ] `ftrace` enabled and traced a function
- [ ] **Combined exercise:** Find a memory bug in your own C code using Valgrind

### Phase 8: Kernel Drivers (Week 8)
- [ ] Hello World kernel module compiled and loaded
- [ ] `dmesg` shows module messages
- [ ] Character device driver loaded
- [ ] `/dev/mydevice` created automatically
- [ ] Read/write to device from user space
- [ ] Sysfs attribute created
- [ ] **Read:** ath11k/pci.c first 100 lines
- [ ] **Identify:** probe function in ath11k

### Phase 9: Embedded Linux (Week 9)
- [ ] Device Tree concept understood
- [ ] Read NXP board .dts file
- [ ] Buildroot built for QEMU ARM target
- [ ] U-Boot basic commands practiced
- [ ] Cross-compiled a kernel module for ARM

### Phase 10: Semiconductor Chip Work (Week 10)
- [ ] QCA6490_NXP_GUIDE.md read completely
- [ ] ath11k driver source navigation attempted
- [ ] One debug scenario practiced
- [ ] Connection between your work experience and Linux internals clear

---

## C + Linux Combined Milestones

| Week | Combined Project | Status |
|------|-----------------|--------|
| 4    | C fork/exec + Linux IPC | [ ] |
| 5    | C TCP socket + tcpdump verification | [ ] |
| 6    | Cross-compile C program for ARM | [ ] |
| 7    | Debug own C program with GDB on Linux | [ ] |
| 8    | Write kernel module (C) that exposes sysfs attribute | [ ] |
| 10   | Read 100 lines of real QCA6490 driver (ath11k/pci.c) | [ ] |

---

## Key Insight: C ↔ Linux Synergy

```
C Skill         +  Linux Context  =  Semiconductor Skill
─────────────────────────────────────────────────────────
Pointers        + mmap/device mmap = Register-mapped I/O
Structs         + file_operations  = Driver vtable
Memory Mgmt     + kmalloc/kfree    = Kernel memory
File I/O        + char device      = /dev node driver
Function ptrs   + callbacks/irq    = Interrupt handlers
Macros          + kernel macros    = MODULE_*, DEFINE_*
```

---

*Updated: Start of Linux learning journey*
