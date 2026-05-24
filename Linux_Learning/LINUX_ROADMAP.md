# Linux Learning Roadmap — Semiconductor Industry Track
> Target: Embedded/Driver/Connectivity Engineer at Semiconductor Company
> Chip Experience: Qualcomm QCA6490 (WiFi 6E + BT 5.2) | NXP Patriot Series
> Parallel Track: C Programming (already running)

---

## Why Linux + C Together is the RIGHT Move

```
C Learning  ──────────────────────────────────────────────────────►
    │  Pointers → Memory Management → Structures → File I/O
    │                    ↓ feeds into ↓
Linux Learning ──────────────────────────────────────────────────►
    │  Commands → Shell → System Calls → Drivers → Embedded Linux
    │
    └── OVERLAP ZONE (Week 4 onwards):
        • C system calls (open, read, write, ioctl)
        • Writing kernel modules in C
        • Cross-compiling C code for ARM chips
        • Debugging C programs on Linux (GDB, Valgrind)
```

**Answer: YES — C and Linux together accelerate each other.**
- Linux kernel and drivers are written in C
- System programming (sockets, processes, threads) is pure C
- QCA6490 and NXP drivers run on Linux — reading them requires both

---

## 10-Week Parallel Plan

| Week | C Learning (existing path)       | Linux Learning (new path)              |
|------|----------------------------------|----------------------------------------|
| 1    | Fundamentals (done)              | Linux Basics: navigation, commands     |
| 2    | Functions & Scope                | Shell Scripting basics (bash)          |
| 3    | Arrays & Strings                 | File System & Permissions              |
| 4    | Pointers (started)               | Processes, Signals (fork/exec)         |
| 5    | Dynamic Memory                   | Networking tools + sockets in C        |
| 6    | Structures                       | Build Systems: Make, CMake, GCC flags  |
| 7    | File I/O                         | Debugging: GDB, strace, valgrind       |
| 8    | Preprocessor & Macros            | Kernel Modules: Hello World driver     |
| 9    | Data Structures                  | Embedded Linux: cross-compile for ARM  |
| 10   | Interview Prep                   | QCA6490/NXP: read real driver code     |

---

## Phase 1: Linux Basics (Week 1)
**Folder:** `01_Basics/`

### Topics:
- [ ] Filesystem navigation: `ls`, `cd`, `pwd`, `find`, `locate`
- [ ] File operations: `cp`, `mv`, `rm`, `mkdir`, `touch`, `ln`
- [ ] Viewing files: `cat`, `less`, `more`, `head`, `tail`
- [ ] Searching: `grep`, `awk`, `sed`, `cut`, `sort`, `uniq`
- [ ] System info: `uname`, `lscpu`, `free`, `df`, `lsblk`, `dmesg`
- [ ] Process basics: `ps`, `top`, `htop`, `kill`, `jobs`, `fg`, `bg`
- [ ] Permissions: `chmod`, `chown`, `ls -l` (preview for Phase 3)
- [ ] Package management: `apt` / `dnf` / `pacman`
- [ ] SSH basics (essential for chip bring-up work)
- [ ] `man` pages — your best friend

**Semiconductor Relevance:** Every chip bring-up, board debug session uses these commands.

---

## Phase 2: Shell Scripting (Week 2)
**Folder:** `02_Shell_Scripting/`

### Topics:
- [ ] Variables, arrays, arithmetic
- [ ] if/else, case, loops (for, while, until)
- [ ] Functions in bash
- [ ] Reading files, parsing logs
- [ ] Script arguments (`$1`, `$2`, `$@`, `$#`)
- [ ] Pipe chains and redirections (`>`, `>>`, `|`, `2>&1`)
- [ ] Cron jobs (automated scripts)
- [ ] Practical: auto-build script, log parser script

**Semiconductor Relevance:**
- Automated firmware flash scripts
- Log parsing from chip debug output
- CI/CD build scripts for driver compilation
- Test automation for WiFi/BT chip validation

---

## Phase 3: File System & Permissions (Week 3)
**Folder:** `03_File_System_Permissions/`

### Topics:
- [ ] Linux filesystem hierarchy: `/proc`, `/sys`, `/dev`, `/etc`
- [ ] File permissions: rwx, octal notation, setuid/setgid
- [ ] Hard links vs symbolic links
- [ ] `/proc` filesystem — read kernel/process info (real driver debug tool)
- [ ] `/sys` filesystem — sysfs for hardware/driver interaction
- [ ] `/dev` — device files (char devices, block devices)
- [ ] `inode`, `mount`, `umount`, `df`, `du`
- [ ] `fstab`, swap, tmpfs

**Semiconductor Relevance:**
- QCA6490 driver exposes nodes in `/sys/class/net/` and `/proc`
- Reading chip registers via `/sys` sysfs attributes
- Device nodes in `/dev` for communication chips

---

## Phase 4: Processes, Threads & Signals (Week 4)
**Folder:** `04_Processes_Signals/`

### Topics (all coded in C — direct overlap!):
- [ ] `fork()`, `exec()`, `wait()`, `waitpid()`
- [ ] Process states, zombie processes
- [ ] Signals: `SIGTERM`, `SIGKILL`, `SIGHUP`, `SIGUSR1`, `SIGUSR2`
- [ ] `signal()` and `sigaction()` handlers
- [ ] POSIX Threads (`pthreads`): create, join, mutex, semaphore
- [ ] Inter-Process Communication (IPC): pipes, named pipes (FIFO)
- [ ] Shared memory (`mmap`, `shmget`)
- [ ] Message queues

**C Overlap:** Entire topic is coded in C using system calls.
**Semiconductor Relevance:** Chip daemons (wpa_supplicant, bluetoothd) use IPC heavily.

---

## Phase 5: Networking (Week 5)
**Folder:** `05_Networking/`

### Topics:
- [ ] OSI model review — focus on Layer 2/3 (important for WiFi chip)
- [ ] `ip`, `ifconfig`, `iwconfig`, `iw` commands
- [ ] `ping`, `traceroute`, `netstat`, `ss`, `tcpdump`, `wireshark`
- [ ] Socket programming in C (TCP + UDP)
- [ ] Netlink sockets (how user-space talks to kernel — critical for WiFi drivers)
- [ ] `nl80211` / `cfg80211` — the Linux WiFi driver framework
- [ ] `wpa_supplicant`, `hostapd` basics
- [ ] Bluetooth: `hciconfig`, `hcitool`, `bluetoothctl`

**Semiconductor Relevance:**
- QCA6490 is a WiFi 6E + BT chip — this is its exact stack
- `nl80211`/`cfg80211` is what QCA6490 Linux driver registers with
- Understanding this = reading/debugging actual QCA6490 driver code

---

## Phase 6: Build Systems (Week 6)
**Folder:** `06_Build_Systems/`

### Topics:
- [ ] GCC flags deep dive: `-O2`, `-g`, `-Wall`, `-march=`, `-mcpu=`
- [ ] Makefiles: variables, rules, phony targets, pattern rules
- [ ] CMake basics: `CMakeLists.txt`, `cmake`, `make`
- [ ] Static vs shared libraries: `.a`, `.so`
- [ ] Cross-compilation: target ARM, host x86 (`arm-linux-gnueabihf-gcc`)
- [ ] Kernel build system (Kbuild): `Kconfig`, `Makefile`
- [ ] `objdump`, `nm`, `readelf`, `ldd` — binary analysis tools
- [ ] `pkg-config`

**Semiconductor Relevance:**
- NXP and QCA drivers are compiled via Kbuild against a specific kernel version
- Cross-compiling for ARM Cortex-A (NXP i.MX) is daily work
- Buildroot/Yocto recipes call CMake/Make under the hood

---

## Phase 7: Debugging Tools (Week 7)
**Folder:** `07_Debugging_Tools/`

### Topics:
- [ ] GDB: breakpoints, watchpoints, backtrace, core dumps
- [ ] GDB with kernel modules (KGDB)
- [ ] `strace` — trace system calls of a running process
- [ ] `ltrace` — trace library calls
- [ ] `valgrind` — memory leak detection (for C programs)
- [ ] `AddressSanitizer` (ASAN) — faster memory debugging
- [ ] `perf` — performance profiling
- [ ] `ftrace` — kernel function tracing (critical for driver debug)
- [ ] `kprobes`, `tracepoints`
- [ ] `dmesg` log analysis, `dev_dbg`, `pr_info` in kernel

**C Overlap:** GDB directly debugs your C programs from the C track.

---

## Phase 8: Kernel Modules & Device Drivers (Week 8) ← MOST IMPORTANT
**Folder:** `07_Kernel_Drivers/`

### Topics:
- [ ] Linux kernel architecture overview
- [ ] Writing your first kernel module (Hello World `init`/`exit`)
- [ ] Kernel module Makefile
- [ ] `insmod`, `rmmod`, `lsmod`, `modinfo`, `modprobe`
- [ ] Character device driver: `file_operations` struct, `open`/`read`/`write`/`ioctl`
- [ ] `copy_to_user` / `copy_from_user`
- [ ] Sysfs attribute creation (sysfs_create_file)
- [ ] Platform drivers and Device Tree
- [ ] Interrupt handlers (`request_irq`, `free_irq`)
- [ ] DMA basics
- [ ] Workqueues, tasklets (deferred work in kernel)
- [ ] Spinlocks, mutexes in kernel
- [ ] PCI/PCIe driver model (QCA6490 uses PCIe!)
- [ ] USB driver model (QCA6490 also has USB interface)
- [ ] SDIO driver model (common for WiFi chips)

**C Overlap:** 100% — kernel is C, same pointer/struct/memory skills apply.
**Semiconductor Relevance:** This IS the job at Qualcomm/NXP — writing/maintaining drivers.

---

## Phase 9: Embedded Linux (Week 9)
**Folder:** `09_Embedded_Linux/`

### Topics:
- [ ] Boot process: Bootloader (U-Boot) → Kernel → Rootfs → Init
- [ ] U-Boot basics: environment variables, boot commands
- [ ] Device Tree Source (DTS): what it is, how to read/modify
- [ ] Buildroot: build minimal Linux for ARM board
- [ ] Yocto Project basics: layers, recipes, bitbake
- [ ] Root filesystem types: ext4, UBIFS, SquashFS
- [ ] `busybox` based systems
- [ ] NFS boot (network boot for development)
- [ ] JTAG/OpenOCD debugging
- [ ] Secure Boot, OP-TEE basics (NXP platforms use this)

**Semiconductor Relevance:**
- NXP i.MX platforms use Yocto (NXP's Yocto layer: `meta-imx`)
- QCA6490 driver enabled in Yocto kernel config
- Board bring-up work = U-Boot + DTS + driver integration

---

## Phase 10: Semiconductor-Specific Work (Week 10)
**Folder:** `10_Semiconductor_Chip_Work/`

### Topics:
- [ ] Read QCA6490 Linux driver source (ath11k / ath12k)
- [ ] Understand cfg80211/mac80211 framework
- [ ] NXP Patriot / i.MX SDK structure
- [ ] WLAN regulatory framework in Linux
- [ ] Firmware download mechanism (ath11k firmware loading)
- [ ] Calibration data, board data files
- [ ] WiFi certification testing (FCC/ETSI/MIC)
- [ ] AT commands / QMI protocol (Qualcomm chipsets)
- [ ] Power management: suspend/resume for WiFi/BT chips

---

## Key Resources

### Books (in reading order):
1. **"The Linux Command Line"** — William Shotts (free at linuxcommand.org)
2. **"Linux Kernel Development"** — Robert Love ← most important for semiconductor
3. **"Linux Device Drivers, 3rd Ed"** — Corbet, Rubini (free at lwn.net/Kernel/LDD3)
4. **"Embedded Linux Primer"** — Christopher Hallinan

### Online:
- kernel.org — official kernel source
- elixir.bootlin.com — browse kernel source online (search ath11k/ath12k)
- lwn.net — Linux kernel news & deep-dive articles
- elinux.org — embedded Linux wiki

### Tool Setup (WSL2 on Windows — start here):
```bash
# In PowerShell (as admin):
wsl --install -d Ubuntu-22.04

# After install, inside Ubuntu:
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) git gdb valgrind
```

---

## What Semiconductor Companies Expect

| Skill Level | Expectation |
|-------------|-------------|
| **Basic**   | Navigate Linux, read logs, compile C code, use GDB |
| **Mid**     | Write shell scripts, understand build systems, read driver code |
| **Senior**  | Write/debug kernel modules, cross-compile, Yocto, Device Tree |
| **Expert**  | PCIe/USB/SDIO driver, bring-up from scratch, power management |

**Your current position:** Moving from automotive → semiconductor
**Your advantage:** QCA6490 and NXP experience = you've used these drivers
**Gap to close:** Understand what's happening inside those drivers

---

*Start with Phase 1 this week while continuing C Phase 4 (Pointers)*
*Both reinforce each other starting from Week 4*
