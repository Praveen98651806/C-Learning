# LINUX MEMORY MANAGEMENT
## A Comprehensive Engineering Guide
### Beginner to Kernel Internals

---

> **Audience**: Engineers preparing for kernel-level work, system design, or performance tuning.
> **Platform**: Linux kernel 5.x/6.x on x86-64 (architecture-specific notes included where relevant).

---

## TABLE OF CONTENTS

1. [Introduction](#1-introduction)
2. [Basic Concepts](#2-basic-concepts-beginner-level)
3. [Process Memory Layout](#3-process-memory-layout)
4. [Paging and Virtual Memory](#4-paging-and-virtual-memory-intermediate)
5. [Linux-Specific Memory Management](#5-linux-specific-memory-management)
6. [Kernel Memory Management](#6-kernel-memory-management)
7. [Advanced Concepts](#7-advanced-concepts)
8. [Performance & Tuning](#8-performance--tuning)
9. [Debugging & Observability](#9-debugging--observability)
10. [Expert / Kernel Internals](#10-expert--kernel-internals)
11. [Real-World Scenarios](#11-real-world-scenarios)
12. [Diagrams](#12-diagrams)
13. [Best Practices](#13-best-practices)

---

## 1. INTRODUCTION

### 1.1 What Is Memory Management in an OS?

Memory management is the OS subsystem responsible for allocating, tracking, protecting, and reclaiming physical and virtual memory resources. It acts as the intermediary between hardware (RAM, MMU) and software (processes, kernel subsystems).

**Core responsibilities:**
- Allocating physical memory to processes on demand
- Isolating memory between processes (security and stability)
- Abstracting physical addresses via virtual address spaces
- Reclaiming memory when processes exit or when the system is under pressure
- Managing caches (page cache, slab) to improve I/O and allocation performance

### 1.2 Why It Matters

| Concern       | Impact of Poor Memory Management                                          |
|---------------|---------------------------------------------------------------------------|
| Performance   | Excessive page faults, high swap I/O, TLB thrashing, cache pressure       |
| Isolation     | Bug in process A corrupts process B; security vulnerabilities             |
| Efficiency    | RAM wasted on dead objects; demand paging and COW maximise utilisation    |
| Scalability   | NUMA-unaware allocation causes expensive cross-node memory accesses       |
| Reliability   | OOM kills wrong processes; memory leaks bring down long-running services  |

---

## 2. BASIC CONCEPTS (Beginner Level)

### 2.1 Physical vs Virtual Memory

**Physical memory** is the actual RAM installed in the system (e.g., 16 GB DDR4). Addresses are real hardware addresses (0 to RAM_SIZE-1).

**Virtual memory** is an abstraction. Each process sees its own private address space, independent of physical RAM. The OS maintains a mapping from virtual addresses (VA) to physical addresses (PA).

```
Process A:                          Physical RAM:
  VA 0x1000  ─────────────────►  PA 0x45000
  VA 0x2000  ─────────────────►  PA 0x91000

Process B:
  VA 0x1000  ─────────────────►  PA 0x73000   ← same VA, different PA!
  VA 0x2000  ─────────────────►  PA 0xA4000
```

This decoupling enables:
- More virtual memory than physical RAM (via swap/demand paging)
- Full memory isolation between processes
- Position-independent code and shared libraries

---

### 2.2 Address Space Layout (User vs Kernel Space)

On **x86-64** Linux the 64-bit virtual address space is divided at the canonical hole:

```
0xFFFFFFFFFFFFFFFF ─┐
                    │  Kernel Space  (~128 TB)
0xFFFF800000000000 ─┘  kernel code, data, page tables, kmalloc, vmalloc

        [non-canonical hole  ~16 EB — hardware-invalid addresses]

0x00007FFFFFFFFFFF ─┐
                    │  User Space   (~128 TB)
0x0000000000000000 ─┘  stack, heap, mmap, text, data
```

On **32-bit x86**:
- User space:   `0x00000000 – 0xBFFFFFFF`  (3 GB)
- Kernel space: `0xC0000000 – 0xFFFFFFFF`  (1 GB)

The kernel is mapped into every process's virtual address space, but protected via CPU privilege levels (ring 0 vs ring 3). This enables fast syscall entry without a full address-space switch.

---

### 2.3 Paging Basics

**Paging** divides both physical and virtual memory into fixed-size units:
- **Page**  — unit of virtual memory
- **Frame** — unit of physical memory (same size as a page)

The OS maintains **page tables** mapping pages → frames. When a process accesses a VA, the MMU walks the page table to find the PA. If no mapping exists → **page fault** → kernel handles it.

---

### 2.4 Page Size and Frames

Default page size on Linux x86-64: **4 KB** (4096 bytes).

```
Virtual Address breakdown (4-level paging, x86-64):

  Bits [63:48] — sign extension (unused)
  Bits [47:39] — PGD index  (9 bits → 512 entries)
  Bits [38:30] — PUD index  (9 bits → 512 entries)
  Bits [29:21] — PMD index  (9 bits → 512 entries)
  Bits [20:12] — PTE index  (9 bits → 512 entries)
  Bits [11:0]  — Page offset (12 bits → 4096 bytes)
```

- Total addressable per process: 2^48 = **256 TB**
- Huge pages: **2 MB** (PMD-level) and **1 GB** (PUD-level) are also supported.

---

### 2.5 Role of MMU and TLB

**MMU (Memory Management Unit)**: Hardware unit inside the CPU that translates virtual → physical addresses by walking page tables stored in RAM. Without the MMU there is no virtual memory.

**TLB (Translation Lookaside Buffer)**: A hardware cache inside the CPU that stores recent VA→PA translations, avoiding a full page-table walk on every access.

```
CPU issues VA
     │
     ▼
TLB lookup ──► HIT  ──►  PA returned immediately     (~4 cycles, fast)
     │
     └──► MISS ──►  MMU walks page table  ──►  PA found, TLB updated  (~100 cycles)
                         │
                         └──►  Page not present  ──►  #PF raised, kernel handles
```

**Key TLB facts:**
- TLB is flushed on context switch (except with PCID/ASID hardware support)
- TLB misses cost 50–200 CPU cycles
- Huge pages reduce TLB pressure by covering more memory per TLB entry

---

## 3. PROCESS MEMORY LAYOUT

### 3.1 Segments

A Linux process virtual address space consists of several **regions** (VMAs — Virtual Memory Areas):

```
High Address
┌──────────────────────────────────┐  0x00007FFFFFFFFFFF
│           Stack  (grows ↓)       │  local vars, function frames, return addrs
│               ↓                  │
│      [stack guard page]          │
│                                  │
│      mmap region  (grows ↓)     │  shared libs, file mappings, anon mmap
│      (libc.so, libpthread.so…)  │
│               ↑                  │
│           Heap  (grows ↑)        │  malloc/free, brk()
│                                  │
│     [BSS  segment]               │  uninitialized globals (zero-filled)
│     [Data segment]               │  initialized globals & static vars
│     [Text segment]               │  read-only executable code
└──────────────────────────────────┘  ~0x0000000000400000
```

| Segment | Contents                          | Typical Permissions |
|---------|-----------------------------------|---------------------|
| Text    | Machine code                      | r-x (read, execute) |
| Data    | Initialized global/static vars    | rw-                 |
| BSS     | Uninitialized global/static vars  | rw- (zeroed by OS)  |
| Heap    | Dynamic allocations (malloc)      | rw-                 |
| Stack   | Function frames, local variables  | rw-                 |
| mmap    | Shared libs, file maps, anon maps | varies              |

---

### 3.2 mmap Regions

`mmap()` creates new memory mappings in the VMA list:

```c
// Anonymous mmap — not backed by file (used by malloc for large allocs)
void *p = mmap(NULL, size,
               PROT_READ | PROT_WRITE,
               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

// File-backed mmap — maps file data directly into address space
int fd = open("data.bin", O_RDONLY);
void *p = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

// Shared file mmap — changes visible to all processes mapping same file
void *p = mmap(NULL, size,
               PROT_READ | PROT_WRITE,
               MAP_SHARED, fd, 0);
```

---

### 3.3 Example Memory Map of a Linux Process

```bash
$ cat /proc/self/maps
```

```
55a3c1234000-55a3c1235000  r--p  /bin/bash        ← text (read-only rodata)
55a3c1235000-55a3c1300000  r-xp  /bin/bash        ← text (executable)
55a3c1300000-55a3c1340000  r--p  /bin/bash        ← text (read-only data)
55a3c1341000-55a3c1345000  rw-p  /bin/bash        ← data/bss (writable)
55a3c3b10000-55a3c3c00000  rw-p  [heap]
7f9a10000000-7f9a10200000  rw-p  [anon]           ← thread stack (anon mmap)
7f9a20000000-7f9a21800000  r--p  /lib/x86_64-linux-gnu/libc.so.6
7f9a21800000-7f9a21980000  r-xp  /lib/x86_64-linux-gnu/libc.so.6
7f9a21980000-7f9a219d0000  r--p  /lib/x86_64-linux-gnu/libc.so.6
7f9a219d1000-7f9a219d5000  rw-p  /lib/x86_64-linux-gnu/libc.so.6
7fffd4e00000-7fffd5000000  rw-p  [stack]
7fffd5ffd000-7fffd6000000  r--p  [vvar]           ← kernel-exported data
7fffd6000000-7fffd6001000  r-xp  [vdso]           ← virtual DSO (fast syscalls)
```

---

## 4. PAGING AND VIRTUAL MEMORY (Intermediate)

### 4.1 Page Tables (Multi-Level)

Linux on x86-64 uses a **4-level page table** hierarchy (5-level is optional for >128 TB):

```
CR3 register (holds physical addr of PGD)
     │
     ▼
┌─────────┐     ┌─────────┐     ┌─────────┐     ┌─────────┐
│  PGD    │────►│  PUD    │────►│  PMD    │────►│  PTE    │──► Physical Frame
│ (L4)    │     │  (L3)   │     │  (L2)   │     │  (L1)   │
└─────────┘     └─────────┘     └─────────┘     └─────────┘
 512 entries     512 entries     512 entries     512 entries
   × 8 bytes       × 8 bytes       × 8 bytes       × 8 bytes
 = 4 KB           = 4 KB           = 4 KB           = 4 KB
```

Each **PTE (Page Table Entry)** is 8 bytes and contains:

```
PTE (64-bit x86-64):

  [63]      NX bit (No Execute)
  [62:52]   Available for OS use
  [51:12]   Physical Frame Number (PFN)
  [11:9]    Available for OS use
  [8]       Global  — survives TLB flush on CR3 reload
  [7]       PS      — 1 = large page (2 MB at PMD, 1 GB at PUD)
  [6]       Dirty   — set by CPU on write
  [5]       Accessed — set by CPU on read or write
  [4]       PCD     — Page-level Cache Disable
  [3]       PWT     — Write-Through
  [2]       U/S     — User/Supervisor (0=kernel only)
  [1]       R/W     — Read/Write
  [0]       P       — Present (1=in RAM, 0=not present)
```

---

### 4.2 Page Faults (Minor vs Major)

A **page fault** (#PF) is raised by the CPU when a virtual address has no valid PTE or a permission is violated.

```
CPU accesses VA
     │
     ▼
MMU: PTE absent (P=0) or permission violation
     │
     ▼
CPU raises #PF exception  →  kernel do_page_fault() handler
     │
     ├──► Valid VMA, page IN RAM but PTE missing  →  map it         MINOR FAULT  (~1 µs)
     ├──► Valid VMA, page NOT in RAM              →  fetch from disk MAJOR FAULT  (~5 ms)
     ├──► COW fault (write to shared read-only)   →  copy page       MINOR FAULT
     └──► Invalid (no VMA, wrong perms)           →  SIGSEGV
```

```bash
# Count page faults for a program
$ /usr/bin/time -v ./my_program 2>&1 | grep "page faults"
  Major (I/O) page faults: 12
  Minor (reclaiming a frame) page faults: 3401
```

---

### 4.3 Demand Paging

Linux does **not** allocate physical memory at `malloc()` or `mmap()` time. Physical frames are allocated only when the page is **first accessed**.

```c
char *p = malloc(100 * 1024 * 1024);  // Reserve 100 MB virtual space
// No physical RAM used yet!

p[0]    = 'x';   // page fault → kernel allocates 1 × 4 KB frame
p[4096] = 'y';   // page fault → kernel allocates another 4 KB frame
```

Benefits:
- Fast process creation — `fork()` doesn't copy all memory instantly
- Memory overcommit — commit more VM than physical RAM
- Lazy loading of shared libraries — only touched pages consume RAM

---

### 4.4 Copy-on-Write (COW)

When `fork()` is called, the child **shares** all parent pages (marked read-only). On the first write by either process → page fault → kernel allocates a new frame and copies the page.

```
BEFORE write (parent and child share one frame):

  Parent PTE ─────────┐
                       ▼
  Child PTE  ─────── [Physical Frame]   (read-only, ref_count = 2)


AFTER child writes:

  Parent PTE ─────── [Original Frame]   (ref_count = 1)
  Child PTE  ─────── [New Frame]         (copy of original)
```

COW makes `fork()` + `exec()` very cheap — most pages are never written, so they are never copied.

---

### 4.5 Swapping and Swap Space

When physical RAM is exhausted, the kernel moves **inactive pages** to swap space (disk partition or swap file) to free frames.

```
RAM:   [A][B][C][D][E] ... (all frames full)

Swap out C (least recently used):
RAM:   [A][B][_][D][E]
Swap:  [C]  ← written to /dev/sda2
PTE C: P=0, swap_entry encoded in PTE bits

Later — process accesses C:
  → Major page fault
  → Kernel reads C from swap into free frame
  → PTE updated, process resumes
```

```bash
# Check swap usage
$ free -h
              total   used   free   shared  buff/cache   available
Mem:           15G    8.2G   2.1G    450M        4.7G       6.5G
Swap:           4G    1.1G   2.9G

# View swap file/partition details
$ cat /proc/swaps
Filename        Type        Size      Used    Priority
/dev/sda3       partition   4194300   1120256  -2
```

---

## 5. LINUX-SPECIFIC MEMORY MANAGEMENT

### 5.1 Buddy Allocator

The **buddy allocator** manages physical page frames, grouping free pages by **order** (power-of-2 block sizes).

```
Order 0:  1  page  (  4 KB)
Order 1:  2  pages (  8 KB)
Order 2:  4  pages ( 16 KB)
Order 3:  8  pages ( 32 KB)
…
Order 10: 1024 pages (4 MB)
```

**Allocation**: Find the smallest order satisfying the request. If unavailable, split a larger block.
**Free**: If the freed block's "buddy" (adjacent same-size block) is also free → merge into a larger block (coalescing).

```
Initial free list — one order-2 block (4 pages: [0][1][2][3])

Request: allocate order-0 (1 page)
  Split [0-3] (order-2) → [0-1](order-1) + [2-3](order-1)
  Split [0-1] (order-1) → [0](order-0)   + [1](order-0)
  Allocate [0]

Free list: order-0:[1]   order-1:[2-3]

Free page [0]:
  [0] buddies with [1] → merge → [0-1](order-1)
  [0-1] buddies with [2-3] → merge → [0-3](order-2)  ← back to start
```

```bash
# View current buddy allocator state
$ cat /proc/buddyinfo
Node 0, zone   Normal   1234  678  345  123  56  28  12  5  2  1  0
#                        ^0   ^1   ^2  ... free blocks per order
```

---

### 5.2 Slab / SLUB / SLOB Allocators

The buddy allocator works at page granularity. For small, frequently allocated kernel objects (e.g., `task_struct`, `inode`, `dentry`), a **slab allocator** is used to avoid internal fragmentation and initialisation overhead.

| Allocator | Status          | Description                                                  |
|-----------|-----------------|--------------------------------------------------------------|
| SLAB      | Original        | Per-cache pools of pre-allocated/pre-initialised objects     |
| SLUB      | Current default | Simplified SLAB; better NUMA support, less metadata overhead |
| SLOB      | Legacy          | Tiny allocator for embedded / ultra-low-memory systems       |

```
SLUB cache: "task_struct"
├── cpu_slab  (per-CPU, lock-free fast path)
│     └── [obj][obj][obj][obj]...   ← active slab page
│
├── partial list  (partially filled slabs)
│     └── [obj][obj][---][---]...
│
└── full list
      └── [obj][obj][obj][obj]...
```

```bash
$ sudo slabtop
 Active / Total Objects:  1,234,567 / 1,345,678 (91.8%)
  OBJS  ACTIVE  USE  OBJ SIZE  SLABS  OBJ/SLAB  CACHE SIZE  NAME
 98304   91245  92%     0.10K   2560        38     10240K  ext4_inode_cache
 65536   60123  91%     0.19K   1638        40     13104K  dentry
```

---

### 5.3 kmalloc vs vmalloc

| Feature            | `kmalloc`                          | `vmalloc`                             |
|--------------------|------------------------------------|---------------------------------------|
| Physical layout    | Physically **contiguous**          | Virtually contiguous only             |
| Max size           | ~8 MB (order-limited)              | Limited by vmalloc area (~32 TB)      |
| Speed              | Fast (direct buddy allocation)     | Slower (page table setup required)    |
| Use case           | DMA buffers, hardware I/O          | Large kernel data structures          |
| `virt_to_phys()`   | Works                              | Does **not** work                     |

```c
// kmalloc — physically contiguous, safe for DMA
void *buf = kmalloc(4096, GFP_KERNEL);
kfree(buf);

// vmalloc — virtually contiguous, for large allocations
void *buf = vmalloc(10 * 1024 * 1024);   // 10 MB
vfree(buf);
```

**GFP flags** (Get Free Pages):
| Flag          | Meaning                                      |
|---------------|----------------------------------------------|
| `GFP_KERNEL`  | Normal allocation; may sleep                 |
| `GFP_ATOMIC`  | Interrupt context; cannot sleep              |
| `GFP_DMA`     | Must reside in ZONE_DMA (0–16 MB)            |
| `GFP_NOWAIT`  | Non-blocking; returns NULL on failure        |
| `__GFP_ZERO`  | Zero-fill the allocated memory               |

---

### 5.4 Zone Architecture

Linux divides physical memory into **zones** based on hardware DMA constraints:

```
Physical Memory Layout (32-bit example):
┌──────────────┬─────────────┬──────────────┬──────────────────┐
│  ZONE_DMA    │ ZONE_DMA32  │ ZONE_NORMAL  │  ZONE_HIGHMEM    │
│  (0–16 MB)   │ (0–4 GB)    │ (16M–896M)   │  (>896 MB)       │
│ ISA DMA      │ 32-bit PCI  │ kernel direct│  not permanently │
│ devices      │ devices     │ mapped       │  mapped (32-bit) │
└──────────────┴─────────────┴──────────────┴──────────────────┘
```

- **ZONE_DMA**: Legacy ISA devices that can only DMA to the first 16 MB
- **ZONE_DMA32**: 32-bit PCI devices (0–4 GB); important even on 64-bit systems
- **ZONE_NORMAL**: Directly mapped in kernel address space
- **ZONE_HIGHMEM**: Only on 32-bit kernels; RAM above 896 MB not permanently mapped

> On x86-64, `ZONE_HIGHMEM` does not exist — the kernel can directly address all physical RAM.

```bash
$ cat /proc/zoneinfo | head -50
Node 0, zone      DMA
  pages free     3968
  ...
Node 0, zone   Normal
  pages free     892345
  pages min      4567
  pages low      9134
  pages high     13701
```

---

### 5.5 NUMA Basics

**NUMA (Non-Uniform Memory Access)**: On multi-socket servers, each CPU socket has its own local memory bank. Accessing remote memory (another socket's RAM) is 2–3× slower.

```
Socket 0:                    Socket 1:
┌──────────────────┐         ┌──────────────────┐
│  CPU 0–15        │         │  CPU 16–31        │
│  Local DRAM 0–63G│◄──QPI──►│  Local DRAM 64–127G│
└──────────────────┘         └──────────────────┘
       NUMA Node 0                 NUMA Node 1

Local memory access:   ~70 ns
Remote memory access:  ~140 ns  (2× penalty)
```

```bash
$ numactl --hardware
available: 2 nodes (0-1)
node 0 cpus: 0 1 2 3 4 5 6 7
node 0 size: 64350 MB
node 1 cpus: 8 9 10 11 12 13 14 15
node 1 size: 64350 MB
node distances:
node   0   1
  0:  10  21
  1:  21  10

# Pin process memory and CPUs to node 0
$ numactl --cpubind=0 --membind=0 ./my_server

# Show per-NUMA-node stats
$ numastat
```

The kernel's NUMA-aware allocator (called via `alloc_pages_node()`) allocates from the local node first, falling back to remote nodes if local memory is exhausted.

---

## 6. KERNEL MEMORY MANAGEMENT

### 6.1 Kernel Virtual Address Space (x86-64)

```
Kernel Virtual Address Space Layout (x86-64):

  0xFFFF800000000000  ← start of kernel space
  │
  ├─ 0xFFFF888000000000 – 0xFFFFC87FFFFFFFFF
  │    Direct mapping of ALL physical memory  (64 TB)
  │    Physical address X  →  VA = 0xFFFF888000000000 + X
  │
  ├─ 0xFFFFC90000000000 – 0xFFFFE8FFFFFFFFFF
  │    vmalloc / ioremap space  (32 TB)
  │    vmalloc() allocates here
  │
  ├─ 0xFFFFEA0000000000 – 0xFFFFEAFFFFFFFFFF
  │    Virtual memory map  (struct page array)
  │    page_to_virt / virt_to_page translations
  │
  ├─ 0xFFFFFF0000000000 – 0xFFFFFF7FFFFFFFFF
  │    Kernel text, loaded modules
  │
  └─ 0xFFFFFFFF80000000 – 0xFFFFFFFFFFFFFFFF
       Kernel image, fixmap, vsyscall page
```

---

### 6.2 Direct Mapping

All physical memory is mapped to a fixed virtual address offset:

```
Physical Address X  ──►  Virtual Address:  PAGE_OFFSET + X
```

On x86-64: `PAGE_OFFSET = 0xFFFF888000000000`

This allows the kernel to access any physical page without setting up a temporary mapping. `phys_to_virt()` and `virt_to_phys()` are simple arithmetic:

```c
#define phys_to_virt(x)  ((void *)((unsigned long)(x) + PAGE_OFFSET))
#define virt_to_phys(x)  ((unsigned long)(x) - PAGE_OFFSET)
```

Direct mapping covers all installed RAM and is set up by the boot-time page table initialisation (`init_mem_mapping()`).

---

### 6.3 High Memory Handling (32-bit Only)

On 32-bit kernels, only **896 MB** of RAM can be permanently mapped in the 1 GB kernel address space. RAM above 896 MB is called **high memory** and cannot be permanently mapped.

To temporarily access high memory pages, the kernel uses:

| API              | Sleeps? | Description                               |
|------------------|---------|-------------------------------------------|
| `kmap(page)`     | Yes     | Permanent-ish mapping in kmap area        |
| `kmap_atomic()`  | No      | Temporary per-CPU atomic mapping (fast)   |
| `kunmap()`       | —       | Release a `kmap()` mapping                |

> On **64-bit kernels** this problem is eliminated — all physical RAM is covered by the direct mapping.

---

### 6.4 Per-CPU Memory

For high-frequency per-CPU counters or caches that would otherwise require locks, the kernel uses **per-CPU variables**:

```c
// Declaration
DEFINE_PER_CPU(int, my_counter);

// Access — must be in non-preemptible context
int val = get_cpu_var(my_counter);
val++;
put_cpu_var(my_counter);

// Preemption-safe this_cpu_* macros (preferred)
this_cpu_inc(my_counter);
this_cpu_add(my_counter, 5);
val = this_cpu_read(my_counter);
```

Per-CPU data eliminates false cache-line sharing between CPUs. Used in:
- `vmstat` counters (`vm_stat[]`)
- SLUB allocator cpu_slab caches
- Network subsystem packet counters
- RCU state

---

## 7. ADVANCED CONCEPTS

### 7.1 Page Cache

The **page cache** stores file data in RAM to avoid repeated disk reads. When you `read()` a file, the kernel stores the data in the page cache. Subsequent reads are served directly from RAM.

```
read() syscall:
     │
     ▼
Does page cache have the page?
     ├── YES → copy from page cache to user buffer                 (fast path, µs)
     └── NO  → allocate cache page, read from disk, copy to user  (slow path, ms)

write() syscall:
     │
     ▼
Write to page cache (page becomes "dirty")
     └── background writeback (pdflush/bdi threads) → flush dirty pages to disk
```

```bash
$ free -h
              total   used   free   shared  buff/cache   available
Mem:           15G    4.5G   2.1G    450M        8.4G       10.5G
#                                              ^^^^^^^^ page cache + buffers
```

The page cache is the single biggest consumer of RAM on most systems. `MemAvailable` accounts for this being reclaimable.

---

### 7.2 Buffer Cache vs Page Cache

Historically separate in Linux; now **fully unified** in the page cache:

| Name          | Historical Content                    | Modern Status            |
|---------------|---------------------------------------|--------------------------|
| Buffer cache  | Block device buffers (FS metadata)    | Backed by page cache     |
| Page cache    | File data pages                       | Still exists, unified    |

`struct buffer_head` objects still exist but they are attached to pages in the page cache rather than managed separately.

---

### 7.3 Transparent Huge Pages (THP)

THP automatically promotes 4 KB anonymous pages to 2 MB pages where possible, reducing TLB pressure without any application changes.

```bash
# Check THP status
$ cat /sys/kernel/mm/transparent_hugepage/enabled
[always] madvise never
#  ^ always = auto-promote
#    madvise = only when application hints MADV_HUGEPAGE
#    never = disabled

# THP statistics in /proc/meminfo
$ grep -i huge /proc/meminfo
AnonHugePages:    524288 kB   ← anonymous THP currently in use
ShmemHugePages:        0 kB
HugePages_Total:       0     ← static HugeTLB pages
HugePages_Free:        0
Hugepagesize:       2048 kB
```

**THP trade-offs:**

| Benefit                        | Cost                                          |
|--------------------------------|-----------------------------------------------|
| Fewer TLB entries needed       | `khugepaged` compaction adds latency spikes   |
| Better CPU performance         | 2 MB wasted for sparse/small allocations      |
| No app changes required        | Harder to reclaim under memory pressure       |

For latency-sensitive workloads (Redis, databases), consider `madvise` or `never`.

---

### 7.4 HugeTLB (Static Huge Pages)

Unlike THP, HugeTLB pages are **pre-allocated at boot** and reserved permanently. Applications must explicitly opt in via `mmap(MAP_HUGETLB)` or SysV shared memory.

```bash
# Reserve 512 × 2MB huge pages = 1 GB total
$ echo 512 > /proc/sys/vm/nr_hugepages

# Or with sysctl
$ sysctl -w vm.nr_hugepages=512

$ grep HugePages /proc/meminfo
HugePages_Total:     512
HugePages_Free:      512
HugePages_Rsvd:        0
Hugepagesize:       2048 kB
```

Used by: Oracle Database, DPDK (networking), KVM guest memory for predictable latency.

---

### 7.5 Memory Overcommit

Linux **overcommits** virtual memory by default — processes may allocate more VM than physical RAM + swap.

```bash
$ cat /proc/sys/vm/overcommit_memory
0
# 0 = heuristic overcommit (allow up to ~50% over total physical)
# 1 = always overcommit (dangerous; used in HPC/batch jobs)
# 2 = strict (RSS ≤ swap + overcommit_ratio% of RAM)
```

**Why overcommit?** Many allocations are never fully touched:
```c
// This succeeds even with only 16 GB RAM + 4 GB swap:
char *p = malloc(100ULL * 1024 * 1024 * 1024);  // "allocate" 100 GB
// Physical frames only allocated on access, demand-paging style
```

---

### 7.6 OOM Killer

When the system truly exhausts all RAM and swap, the **OOM (Out-Of-Memory) killer** is invoked by the kernel to free memory by terminating a process.

**Scoring algorithm** (`oom_score`, 0–1000):
- Higher RSS → higher score (more memory freed by killing)
- Long-running processes → slightly lower score
- Root processes → slight penalty reduction
- `oom_score_adj` (−1000 to +1000): manual override

```bash
# View OOM score of a running process
$ cat /proc/$(pgrep firefox)/oom_score
350

# Protect a critical process from OOM kill
$ echo -1000 > /proc/$$/oom_score_adj        # current shell

# Make a process more likely to be sacrificed first
$ echo 500 > /proc/$(pgrep chrome)/oom_score_adj
```

**OOM event in kernel log:**
```
kernel: Out of memory: Kill process 12345 (chrome) score 650 or sacrifice child.
kernel: Killed process 12345 (chrome) total-vm:2048MB, anon-rss:1024MB, file-rss:64MB
```

**Cgroup-level OOM control:**
```bash
# Limit a cgroup to 2 GB RAM; OOM kills within cgroup only
$ echo $((2 * 1024 * 1024 * 1024)) \
    > /sys/fs/cgroup/memory/mygroup/memory.limit_in_bytes
$ cgexec -g memory:mygroup ./my_service
```

---

## 8. PERFORMANCE & TUNING

### 8.1 vm.swappiness

Controls the kernel's tendency to swap anonymous pages vs. reclaim clean page cache pages.

```bash
$ cat /proc/sys/vm/swappiness
60     ← default

# Range: 0–200 (kernel 5.8+)  /  0–100 (older kernels)
# 0   = avoid swapping, prefer dropping page cache
# 60  = balanced (default)
# 200 = aggressively swap anonymous pages

# Recommended for database servers:
$ sysctl -w vm.swappiness=10

# Persist:
$ echo "vm.swappiness=10" >> /etc/sysctl.d/99-memory.conf
```

---

### 8.2 vm.overcommit_memory

```bash
$ sysctl vm.overcommit_memory
vm.overcommit_memory = 0

# Strict mode: total committed ≤ swap + (RAM × overcommit_ratio / 100)
$ sysctl -w vm.overcommit_memory=2
$ sysctl -w vm.overcommit_ratio=80    # default 50

# Check current commitment
$ grep -E "CommitLimit|Committed_AS" /proc/meminfo
CommitLimit:    12345678 kB
Committed_AS:    8901234 kB
```

Use `overcommit_memory=2` on production systems where OOM kills are unacceptable.

---

### 8.3 Page Reclaim (LRU Lists)

When memory is low the kernel reclaims pages by scanning **LRU (Least Recently Used) lists**:

```
LRU Lists (per NUMA node, per zone):
┌──────────────────┬───────────────────┐
│   Active Anon    │  Inactive Anon    │  ← heap/stack (can be swapped)
├──────────────────┼───────────────────┤
│   Active File    │  Inactive File    │  ← page cache (can be dropped)
└──────────────────┴───────────────────┘

Flow:
  New page  ──►  Active list
                     │
              (not accessed / aged out)
                     ▼
               Inactive list
                     │
              (still not accessed)
                     ▼
             Reclaim:
               File page  ──►  writeback if dirty, then drop
               Anon page  ──►  write to swap, then free frame
```

```bash
$ grep -E "Active|Inactive" /proc/meminfo
Active(anon):   2456320 kB
Inactive(anon):  345678 kB
Active(file):   3456789 kB
Inactive(file):  789012 kB
```

---

### 8.4 Dirty Pages and Writeback

When processes write to page cache, pages become **dirty** and must eventually be flushed to disk by the writeback subsystem.

```bash
# Background writeback starts when dirty pages exceed this % of RAM
$ sysctl vm.dirty_background_ratio   # default: 10%

# Synchronous writeback (process blocks) when this % of RAM is dirty
$ sysctl vm.dirty_ratio              # default: 20%

# How often writeback threads wake up (in centiseconds)
$ sysctl vm.dirty_writeback_centisecs   # default: 500 = 5 seconds

# Max age of dirty data before forced flush
$ sysctl vm.dirty_expire_centisecs     # default: 3000 = 30 seconds
```

**For write-heavy workloads (logs, databases):**
```bash
$ sysctl -w vm.dirty_ratio=5
$ sysctl -w vm.dirty_background_ratio=2
```

---

### 8.5 Essential Tools

```bash
# Overall memory summary (most-used first tool)
$ free -h

# Detailed per-second statistics
$ vmstat 2
procs ---memory---- --swap-- ---io---- --cpu--
 r  b  swpd   free    buff  cache  si  so  bi  bo  us  sy  id  wa
 1  0  1234  234567  12345  456789   0   0   1   5  12   3  84   1
#                                    ^si ^so  ← swap-in/out pages/s (>0 = swapping)

# Per-process memory details
$ cat /proc/$(pgrep nginx)/status | grep -E "VmRSS|VmSize|VmSwap"
VmSize:   512345 kB    ← total virtual memory
VmRSS:    102400 kB    ← resident set size (physical RAM in use)
VmSwap:     4096 kB    ← currently swapped out

# Detailed per-VMA mapping
$ pmap -x $(pgrep nginx)

# Per-VMA stats including PSS, swap
$ cat /proc/$(pgrep nginx)/smaps | head -80

# Real-time slab cache usage
$ sudo slabtop

# System-wide memory events (page faults, OOM, swapping)
$ cat /proc/vmstat | grep -E "pgfault|pgmajfault|oom|swap"
```

---

## 9. DEBUGGING & OBSERVABILITY

### 9.1 /proc/meminfo Analysis

```bash
$ cat /proc/meminfo
MemTotal:       16384000 kB   ← total physical RAM
MemFree:         1234567 kB   ← completely unused (not useful alone)
MemAvailable:    6789012 kB   ← available without swapping  *** USE THIS ***
Buffers:          345678 kB   ← block device read buffers
Cached:          4567890 kB   ← page cache (file data)
SwapCached:        12345 kB   ← pages in swap that are also back in RAM
Active:          5678901 kB   ← recently used, not reclaimed
Inactive:        3456789 kB   ← candidate for reclaim
SwapTotal:       4194304 kB
SwapFree:        3456789 kB
Dirty:             23456 kB   ← pages awaiting disk write
Writeback:           123 kB   ← pages currently being written to disk
AnonPages:       2345678 kB   ← anonymous (heap/stack) pages
Mapped:           456789 kB   ← mmap'd file pages
Shmem:             78901 kB   ← shared memory (tmpfs, shm_open)
KReclaimable:     234567 kB   ← kernel reclaimable (slab caches)
Slab:             345678 kB   ← total slab
SReclaimable:     234567 kB   ← reclaimable slab (dentry, inode caches)
SUnreclaim:       111111 kB   ← non-reclaimable slab (in-use kernel objects)
PageTables:        23456 kB   ← memory used by page table structures
CommitLimit:    12345678 kB   ← max committable memory (overcommit=2)
Committed_AS:    8901234 kB   ← total committed virtual memory
VmallocTotal:  34359738367 kB
VmallocUsed:      123456 kB
```

**Key relationships:**
- `MemAvailable` ≠ `MemFree`; it includes reclaimable page cache + slab
- High `Dirty` + low `MemFree` → I/O bottleneck, writeback lagging
- `Committed_AS > CommitLimit` → under `overcommit_memory=2`, allocations fail
- High `SUnreclaim` → possible kernel memory leak

---

### 9.2 strace and Page Faults

```bash
# Count all syscalls and timing
$ strace -c ./my_program

# Watch only memory-related syscalls
$ strace -e trace=mmap,mmap2,munmap,brk,mprotect,madvise ./my_program

# Example output:
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f1234000000
brk(NULL)                               = 0x55a3c3b10000
brk(0x55a3c3b31000)                     = 0x55a3c3b31000  ← heap grew by 132 KB
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f1234001000
```

---

### 9.3 perf Memory Analysis

```bash
# Record memory access events (requires kernel perf support)
$ perf mem record ./my_program
$ perf mem report

# Hardware performance counters for memory behaviour
$ perf stat -e cache-misses,cache-references,dTLB-misses,LLC-misses ./my_program
     1,234,567      cache-misses          #  15.23% of all cache refs
     8,112,345      cache-references
        45,678      dTLB-misses           #   0.56% of all TLB refs
       123,456      LLC-misses            ← LLC = Last Level Cache

# Flame graph for memory-related functions
$ perf record -e page-faults -g ./my_program
$ perf report --stdio

# NUMA memory profiling
$ perf stat -e numa-hit,numa-miss ./my_program
```

---

### 9.4 slabtop and pmap

```bash
# Real-time slab cache monitoring
$ sudo slabtop
# Sort by size:   press 'l'
# Sort by count:  press 'o'
# Sort by slabs:  press 's'

# Detailed process memory map with RSS and dirty
$ pmap -x 1234
Address           Kbytes     RSS   Dirty  Mode   Mapping
0000000000400000       4       4       0  r-x--  bash
00007f1234000000    4096    3456       0  r--s-  libc.so
00007fff12345000     132      60      60  rw---  [stack]
----------------  ------  ------  ------
total kB           45678   12345    4567

# Smaps rollup (summary per process, accurate)
$ cat /proc/1234/smaps_rollup
Rss:               12345 kB
Pss:                8901 kB    ← proportional share of shared pages
Shared_Clean:       3456 kB
Shared_Dirty:          0 kB
Private_Clean:      1234 kB
Private_Dirty:      7654 kB
Anonymous:          7654 kB
```

**PSS (Proportional Set Size)**: If a 1 MB shared library is used by 4 processes, each process is attributed 256 KB of PSS. PSS is more accurate than RSS for memory accounting.

---

## 10. EXPERT / KERNEL INTERNALS

### 10.1 struct page

Every **physical page frame** is represented by `struct page` in the kernel (defined in `<linux/mm_types.h>`). The entire array of `struct page` objects lives in the direct mapping area.

```c
struct page {
    unsigned long flags;           /* PG_dirty, PG_locked, PG_uptodate, PG_lru … */

    union {
        struct {
            struct list_head lru;        /* LRU list linkage (active/inactive) */
            struct address_space *mapping; /* Page cache mapping (file or anon) */
            pgoff_t index;               /* Offset within mapping */
        };
        struct {                         /* Slab pages */
            struct kmem_cache *slab_cache;
            void *freelist;              /* Next free object */
        };
        /* compound_head for THP/HugeTLB; page_pool for networking; … */
    };

    atomic_t _refcount;            /* Number of references (get_page/put_page) */
    atomic_t _mapcount;            /* Number of PTEs mapping this page (-1=unmapped) */
};
```

**Important page flags:**
```c
PG_locked      /* I/O in progress on this page — wait_on_page_locked() */
PG_dirty       /* Page has been written since last sync to disk */
PG_uptodate    /* Page data is valid (read from disk or just written) */
PG_referenced  /* Page was recently accessed (used by LRU aging) */
PG_active      /* Page is on the active LRU list */
PG_slab        /* Page is owned by the slab allocator */
PG_reserved    /* Do not free (e.g., kernel image, BIOS reserved) */
PG_compound    /* This is a compound (huge) page */
PG_writeback   /* Page is being written to disk by writeback */
```

**Conversions:**
```c
struct page *page = pfn_to_page(pfn);   /* PFN → struct page */
unsigned long pfn = page_to_pfn(page);  /* struct page → PFN */
void *virt  = page_address(page);       /* struct page → virtual address */
phys_addr_t pa = page_to_phys(page);    /* struct page → physical address */
```

---

### 10.2 mm_struct and vm_area_struct (VMA)

Each process has one `mm_struct` (memory descriptor), accessible via `task->mm`:

```c
struct mm_struct {
    struct vm_area_struct *mmap;     /* Linked list of all VMAs */
    struct rb_root         mm_rb;   /* Red-black tree for fast VMA lookup by address */

    unsigned long start_code, end_code;   /* .text boundaries */
    unsigned long start_data, end_data;   /* .data boundaries */
    unsigned long start_brk, brk;         /* Heap: start and current end */
    unsigned long start_stack;             /* Stack start (top of stack) */
    unsigned long mmap_base;               /* Base of mmap area */

    pgd_t        *pgd;               /* Top-level page table (physical addr) */

    atomic_t mm_users;               /* # threads sharing this mm (fork increments) */
    atomic_t mm_count;               /* Structural reference count */

    unsigned long total_vm;          /* Total pages mapped */
    unsigned long locked_vm;         /* Pages locked via mlock() */
    unsigned long pinned_vm;         /* Pages pinned (cannot be reclaimed) */

    struct rss_stat rss_stat;        /* RSS counters (anon, file, shmem, swap) */
};
```

Each mapped region is a `vm_area_struct` (VMA):
```c
struct vm_area_struct {
    unsigned long vm_start;          /* VMA start address (inclusive) */
    unsigned long vm_end;            /* VMA end address (exclusive) */

    struct vm_area_struct *vm_next;  /* Next VMA in address-ordered linked list */
    struct rb_node vm_rb;            /* Node in mm->mm_rb red-black tree */

    pgprot_t vm_page_prot;           /* Hardware page protection flags */
    unsigned long vm_flags;          /* VM_READ, VM_WRITE, VM_EXEC, VM_SHARED, VM_LOCKED … */

    struct file *vm_file;            /* Backing file (NULL for anonymous) */
    unsigned long vm_pgoff;          /* File offset in PAGE_SIZE units */

    const struct vm_operations_struct *vm_ops;  /* fault(), open(), close() */
    void *vm_private_data;           /* Private data for vm_ops */
};
```

---

### 10.3 Page Reclaim Internals

Implemented in `mm/vmscan.c`. Two reclaim paths exist:

**kswapd (background, proactive):**
- Woken when free pages drop below `pages_low` watermark
- Target: restore free pages to `pages_high`

**Direct reclaim (synchronous, on-demand):**
- Called by the allocating process itself when kswapd hasn't freed enough
- `try_to_free_pages()` → `shrink_zones()` → `shrink_node()`

```
shrink_node()
     │
     ├── shrink_lruvec()
     │       ├── shrink_active_list()   → demote active→inactive pages
     │       └── shrink_inactive_list()
     │               ├── File pages (clean) → drop immediately
     │               ├── File pages (dirty) → queue for writeback, keep
     │               └── Anon pages         → swap out
     │
     └── shrink_slab()
             ├── dentry_cache shrinker   → drop unused dentry objects
             └── inode_cache shrinker    → drop clean inode objects
```

**Watermark levels** (per zone):
```
  ┌──────────────┐
  │              │ ← pages_high:   kswapd stops reclaiming
  │              │
  │              │ ← pages_low:    kswapd starts reclaiming
  │              │
  │              │ ← pages_min:    direct reclaim; below this, kswapd works harder
  └──────────────┘ ← 0
```

---

### 10.4 Reverse Mapping (rmap)

**Problem**: During page reclaim the kernel must find and unmap *all* PTEs pointing to a page before it can be reclaimed. This is **reverse mapping** (physical page → all PTEs).

**Anonymous rmap** — via `anon_vma` chains:
- Each page's `mapping` field points to an `anon_vma`
- `fork()` creates a tree of `anon_vma` objects linking parent and child VMAs
- Walking the tree finds all PTEs that reference the page

**File rmap** — via `address_space.i_mmap` interval tree:
- Each `struct address_space` (one per file) has an interval tree of all VMAs mapping it
- Walking the interval tree finds all VMAs (and their PTEs) mapping a given file page

```c
/* Kernel reverse map entry point (simplified from mm/rmap.c) */
void try_to_unmap(struct folio *folio, enum ttu_flags flags) {
    if (folio_test_anon(folio))
        rmap_walk_anon(folio, &rwc, false);  /* walk anon_vma tree */
    else
        rmap_walk_file(folio, &rwc, false);  /* walk i_mmap interval tree */
}
```

---

### 10.5 Memory Compaction

Over time, physical memory becomes **fragmented** — many small free regions scattered throughout, making it impossible to allocate high-order (large contiguous) pages needed for huge pages or DMA.

**Compaction** migrates movable pages to create large contiguous free regions:

```
Before compaction:
[USED][FREE][USED][FREE][USED][FREE][USED][FREE]
  Pages scattered — no contiguous 2-page block available!

After compaction (migration):
[USED][USED][USED][USED][FREE][FREE][FREE][FREE]
  Four contiguous free pages — order-2 allocation now possible!
```

```bash
# Trigger manual compaction (for all zones)
$ echo 1 > /proc/sys/vm/compact_memory

# Check compaction statistics
$ grep compact /proc/vmstat
compact_migrate_scanned  12345
compact_free_scanned     67890
compact_isolated         2345
compact_stall            12     ← processes stalled waiting for compaction
compact_success          890
compact_fail             23
compact_daemon_wake      45
```

---

### 10.6 Kswapd and Direct Reclaim

**kswapd** is a per-NUMA-node kernel thread:

```bash
$ ps aux | grep kswapd
root    19  0.0  0.0  0  0  ?  S  Jun26  0:01  [kswapd0]
root    20  0.0  0.0  0  0  ?  S  Jun26  0:00  [kswapd1]

# Watch kswapd activity in vmstat (si/so columns):
$ vmstat 1
b  swpd    free    buff  cache   si   so
0  45678  123456  12345 456789    0    0   ← no swapping
0  45678   23456  12345 456789   12   34   ← kswapd swapping!
```

**`alloc_stall`** in `/proc/vmstat` counts direct-reclaim stalls — high values mean the system is memory-pressured and allocating processes are stalling waiting for reclaim to complete.

---

### 10.7 Fault Handling Flow in Kernel

```
User process accesses VA (read/write)
     │
     ▼
CPU: PTE not present (P=0) or permission mismatch
     │
     ▼
#PF exception raised  →  do_page_fault()  [arch/x86/mm/fault.c]
     │
     ▼
__do_page_fault()
     │
     ├──► Kernel address space fault
     │       ├── Expected (e.g., vmalloc area, fixmap): handle silently
     │       └── Unexpected: kernel OOPS / BUG
     │
     └──► User address space fault  →  handle_user_fault()
               │
               ▼
          find_vma(mm, faulting_address)
               │
               ├──► No VMA found  →  SIGSEGV (null deref, stack overflow)
               │
               └──► VMA found  →  handle_mm_fault()
                         │
                         ▼
                    __handle_mm_fault()
                         │
                         ├──► PMD-level huge page  →  create_huge_pmd()
                         │
                         └──► PTE-level page  →  handle_pte_fault()
                                   │
                                   ├──► PTE absent, anonymous  →  do_anonymous_page()
                                   │      alloc_zeroed_user_highpage_movable()
                                   │      mk_pte()  →  set_pte_at()
                                   │
                                   ├──► PTE absent, file-backed  →  do_fault()
                                   │      vm_ops->fault()  (reads page from disk/cache)
                                   │
                                   ├──► PTE absent, swap entry  →  do_swap_page()
                                   │      read_swap_cache_async() → swapin_readahead()
                                   │
                                   └──► Write to read-only (COW)  →  do_wp_page()
                                          alloc new page, copy data, remap PTE
```

---

## 11. REAL-WORLD SCENARIOS

### 11.1 Memory Leak Detection

**Symptoms**: RSS grows continuously, application eventually OOM-killed or crashes.

**Step 1 — Confirm the leak**
```bash
# Watch RSS growth over time
$ while true; do
    ps -o pid,rss,vsz,comm -p $(pgrep myapp)
    sleep 5
  done

# Use smem for PSS tracking (more accurate)
$ smem -P myapp -c "pid pss rss vss name"
```

**Step 2 — Valgrind (development / staging)**
```bash
$ valgrind --leak-check=full \
           --show-leak-kinds=all \
           --track-origins=yes \
           ./myapp

==12345== LEAK SUMMARY:
==12345==    definitely lost: 4,096 bytes in 1 blocks
==12345==    indirectly lost:     0 bytes in 0 blocks
==12345==      possibly lost: 2,048 bytes in 3 blocks
==12345==    still reachable: 1,024 bytes in 2 blocks
```

**Step 3 — AddressSanitizer (production-grade, ~2× slower)**
```bash
$ gcc -fsanitize=address,leak -g -o myapp myapp.c
$ ./myapp

==12345==ERROR: LeakSanitizer: detected memory leaks
Direct leak of 4096 byte(s) in 1 object(s) allocated from:
    #0 malloc (.../myapp.c:45)
    #1 init_buffer (.../myapp.c:123)
    #2 main (.../myapp.c:200)
```

**Step 4 — Kernel object leaks**
```bash
$ echo scan > /sys/kernel/debug/kmemleak
$ cat /sys/kernel/debug/kmemleak    # shows unreferenced kernel allocations
```

---

### 11.2 High Swap Usage Diagnosis

**Symptoms**: System sluggish, `vmstat` shows `si/so > 0`, `free` shows swap used.

```bash
# Step 1: Identify which processes are swapped out most
$ for pid in /proc/[0-9]*; do
    swap=$(grep VmSwap $pid/status 2>/dev/null | awk '{print $2}')
    comm=$(cat $pid/comm 2>/dev/null)
    [ -n "$swap" ] && echo "$swap kB  $comm  ($pid)"
  done | sort -rn | head -20

# Step 2: Confirm with smem
$ smem --sort=swap | head -20

# Step 3: Understand why — is swappiness too high?
$ sysctl vm.swappiness
$ grep -E "SwapCached|Active.anon|Inactive.anon" /proc/meminfo

# Step 4: Tune
$ sysctl -w vm.swappiness=10
$ sysctl -w vm.vfs_cache_pressure=50   # retain dentry/inode cache longer

# Step 5: Force swap-in (WARNING: needs available free RAM)
$ swapoff -a && swapon -a
```

---

### 11.3 OOM Debugging Case Study

**Scenario**: Production database server OOM-killed during peak load.

```bash
# Step 1: Find OOM event in kernel logs
$ dmesg | grep -B2 -A30 "Out of memory"
[123456.789] kswapd: page allocation failure: order:0, mode:0x20
[123456.790] Out of memory: Kill process 12345 (postgres) score 650 or sacrifice child.
[123456.791] Killed process 12345 (postgres) total-vm:8192MB, anon-rss:7168MB

# Step 2: Examine memory state at time of OOM
$ dmesg | grep -A 60 "Mem-Info:"
# Reveals: per-zone free pages, active/inactive counts, slab usage

# Step 3: Current meminfo — was there reclaimable memory?
$ grep -E "MemFree|MemAvailable|Cached|SReclaimable|SwapFree" /proc/meminfo
# If Cached is large + swappiness is high → vm.swappiness too aggressive
# If SUnreclaim is large → possible kernel memory leak

# Step 4: Preventive measures

## Option A: Increase swap space
$ fallocate -l 8G /swapfile
$ chmod 600 /swapfile ; mkswap /swapfile ; swapon /swapfile

## Option B: Limit other processes with cgroups
$ cgcreate -g memory:web-tier
$ echo $((2 * 1024 * 1024 * 1024)) \
    > /sys/fs/cgroup/memory/web-tier/memory.limit_in_bytes
$ cgexec -g memory:web-tier nginx

## Option C: Protect the database process
$ echo -1000 > /proc/$(pgrep postgres)/oom_score_adj

## Option D: Enable earlyoom (userspace OOM daemon, faster response)
$ systemctl enable --now earlyoom
```

---

## 12. DIAGRAMS

### 12.1 Virtual Memory Layout (x86-64 Linux Process)

```
Virtual Address Space  (x86-64, not to scale)

┌──────────────────────────────────────────────────┐ 0xFFFFFFFFFFFFFFFF
│                  Kernel Space                    │
│  (kernel code, vmalloc, direct map of all RAM)   │
│             [protected — ring 0 only]            │
├──────────────────────────────────────────────────┤ 0xFFFF800000000000
│                                                  │
│            [non-canonical hole ~16 EB]           │
│            (hardware-invalid addresses)          │
│                                                  │
├──────────────────────────────────────────────────┤ 0x00007FFFFFFFFFFF
│          Stack (grows downward ↓)                │
│  ┌────────────────────────────────────────────┐  │
│  │ frame N:   local vars, saved regs, ret addr│  │
│  │ frame N-1: ...                             │  │
│  │            ...                             │  │
│  └────────────────────────────────────────────┘  │
│                                                  │
│          [ASLR randomised gap]                   │
│                                                  │
│          mmap region (grows downward ↓)         │
│  ┌────────────────────────────────────────────┐  │
│  │ /lib/x86_64-linux-gnu/libpthread.so  r-xp  │  │
│  │ /lib/x86_64-linux-gnu/libc.so        r-xp  │  │
│  │ anonymous mmaps (thread stacks, large alloc│  │
│  └────────────────────────────────────────────┘  │
│                                                  │
│          [heap–mmap gap / guard]                 │
│                                                  │
│          Heap (grows upward ↑)                   │
│  ┌────────────────────────────────────────────┐  │
│  │  malloc'd objects                          │  │
│  │  brk pointer ─────────────────────────── ↑│  │
│  └────────────────────────────────────────────┘  │
│                                                  │
│  ┌────────────────────────────────────────────┐  │
│  │ BSS   (uninitialized globals — zeroed)     │  │
│  │ Data  (initialized globals & statics)      │  │
│  │ Text  (r-x, read-only executable code)     │  │
│  └────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────┘ 0x0000000000400000
```

---

### 12.2 Page Table Hierarchy (x86-64, 4-level paging)

```
VA [47:39]    VA [38:30]    VA [29:21]    VA [20:12]    VA [11:0]
    │              │              │              │            │
    ▼              ▼              ▼              ▼            │
 PGD[idx]  →   PUD[idx]  →   PMD[idx]  →   PTE[idx]         │
  (Level 4)     (Level 3)     (Level 2)     (Level 1)        │
CR3 ──► ┌───┐  ┌───┐         ┌───┐         ┌───┐            │
        │   │─►│   │─►       │   │─►       │   │            │
        │   │  │   │         │   │         │PFN│──► Frame ──+──► PA
        │   │  │   │         │   │         │   │
        └───┘  └───┘         └───┘         └───┘
       512×8B  512×8B  PS=1→2MB page here  512×8B
               (skips PMD+PTE levels for 2MB huge pages)

Memory overhead: 4 × 4 KB = 16 KB per fully-populated path
TLB caches recent translations to avoid full walks.

5-Level paging (kernel 4.14+, >128 TB address space):
  CR3 → P4D(L5) → PGD(L4) → PUD(L3) → PMD(L2) → PTE(L1) → Physical
  Extends VA from 48 bits (256 TB) to 57 bits (128 PB)
```

---

### 12.3 Buddy Allocator Visualization

```
System: 16 pages total (order-4 free block at start)

Initial state:
Free lists:   order-4: [0─────────────────15]

━━━━━━━━━━━ Request: allocate 3 pages (next power-of-2 = order-2) ━━━━━━━━━━

Split order-4 → two order-3 blocks:
  order-4: (empty)
  order-3: [0──────7]  [8─────15]

Split [0─7] (order-3) → two order-2 blocks:
  order-3: [8─────15]
  order-2: [0───3]  [4───7]

Allocate [0─3] (order-2, 4 pages):
  order-3: [8─────15]
  order-2: [4───7]
  ALLOCATED: [0─3]  ← returned to caller

━━━━━━━━━━━ Request: allocate 1 page (order-0) ━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Split [4─7] (order-2) → two order-1 blocks:
  order-1: [4─5]  [6─7]

Split [4─5] (order-1) → two order-0 blocks:
  order-0: [4]  [5]

Allocate [4] (order-0):
  order-3: [8─────15]
  order-1: [6─7]
  order-0: [5]
  ALLOCATED: [0─3] and [4]

━━━━━━━━━━━ Free [4] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[4] and buddy [5] are both free → merge → [4─5] (order-1)
[4─5] and buddy [6─7] both free → merge → [4─7] (order-2)

  order-3: [8─────15]
  order-2: [4───7]
  ALLOCATED: [0─3]

━━━━━━━━━━━ Free [0─3] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[0─3] and buddy [4─7] both free → merge → [0─7] (order-3)
[0─7] and buddy [8─15] both free → merge → [0─15] (order-4) ← full coalesce!

  order-4: [0─────────────────15]   ← back to initial state, no fragmentation
```

---

## 13. BEST PRACTICES

### 13.1 Writing Memory-Efficient Applications

**1. Allocate late, free early**
```c
// BAD: hold 100 MB allocation while doing unrelated work
char *buf = malloc(100 * 1024 * 1024);
do_30_seconds_of_unrelated_work();
process(buf);
free(buf);

// GOOD: allocate just before use
do_30_seconds_of_unrelated_work();
char *buf = malloc(100 * 1024 * 1024);
process(buf);
free(buf);
```

**2. Use memory pools for frequent small allocations**
```c
// BAD: many malloc/free cycles cause fragmentation
for (int i = 0; i < 100000; i++) {
    Node *n = malloc(sizeof(Node));
    use(n);
    free(n);
}

// GOOD: pool allocator
NodePool *pool = pool_create(sizeof(Node), 1024);
for (int i = 0; i < 100000; i++) {
    Node *n = pool_alloc(pool);
    use(n);
    pool_free(pool, n);
}
pool_destroy(pool);
```

**3. Access memory sequentially (cache-friendly)**
```c
// BAD: random access — poor cache and TLB utilisation
for (int i = 0; i < N; i++)
    sum += matrix[rand() % ROWS][rand() % COLS];

// GOOD: row-major sequential access
for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
        sum += matrix[r][c];
```

**4. Use `madvise()` to inform the kernel**
```c
// Sequential I/O pattern — kernel prefetches ahead
madvise(buf, size, MADV_SEQUENTIAL);

// Random access — disable prefetch, don't cache
madvise(buf, size, MADV_RANDOM);

// Done with this data — release physical pages now
madvise(buf, size, MADV_DONTNEED);

// Hint for transparent huge page promotion
madvise(buf, size, MADV_HUGEPAGE);

// Exclude from core dumps
madvise(buf, size, MADV_DONTDUMP);
```

---

### 13.2 Choosing malloc vs mmap

| Scenario                                  | Use                          | Reason                                   |
|-------------------------------------------|------------------------------|------------------------------------------|
| Objects < 128 KB                          | `malloc()`                   | Managed heap, low overhead               |
| Objects > 128 KB                          | `mmap()` (glibc auto-uses)   | Direct kernel mapping; no heap growth    |
| Shared memory between processes           | `mmap(MAP_SHARED)`           | Single physical copy; no IPC copy needed |
| Memory-mapped file I/O                    | `mmap()` on file descriptor  | Zero-copy; kernel handles paging         |
| Large temporary buffer                    | `mmap(MAP_ANONYMOUS)`        | `munmap()` returns pages to OS instantly |
| SIMD / DMA aligned memory                 | `posix_memalign()` or `mmap` | Guaranteed power-of-2 alignment          |
| Short-lived small object                  | Stack (`alloca()`)           | Fastest path; zero overhead              |

```c
// Large temp buffer: mmap returns pages to OS immediately on munmap
void *buf = mmap(NULL, 100 * 1024 * 1024,
                 PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
use(buf);
munmap(buf, 100 * 1024 * 1024);     // pages freed immediately

// vs malloc: glibc heap may not release to OS after free
void *buf = malloc(100 * 1024 * 1024);
use(buf);
free(buf);
malloc_trim(0);                     // explicitly ask glibc to release to OS
```

---

### 13.3 Avoiding Fragmentation

**1. Allocate and free in LIFO order where possible**
```c
// LIFO minimises heap fragmentation
void *a = malloc(100);
void *b = malloc(200);
void *c = malloc(100);
free(c);   // LIFO — buddy of b, coalescing possible
free(b);
free(a);
```

**2. Use size-class pools for objects of known sizes**
```c
// Pre-allocate fixed-size pools matching common object sizes
Pool *pool_small  = pool_create(16,  10000);
Pool *pool_medium = pool_create(64,   5000);
Pool *pool_large  = pool_create(256,  1000);
```

**3. Use a better allocator for multi-threaded applications**
```bash
# jemalloc: better per-thread arenas, lower fragmentation
$ gcc -o myapp myapp.c -ljemalloc

# Or use LD_PRELOAD without recompiling
$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.2 ./myapp

# tcmalloc (Google): similar goals, often lower latency
$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libtcmalloc.so.4 ./myapp
```

**4. Detect and monitor fragmentation**
```c
#include <malloc.h>

struct mallinfo2 mi = mallinfo2();
printf("arena:     %zu bytes (total heap)\n", mi.arena);
printf("uordblks:  %zu bytes (in-use)\n",     mi.uordblks);
printf("fordblks:  %zu bytes (free in heap)\n", mi.fordblks);
// Large fordblks relative to arena = high internal fragmentation
```

```bash
# Kernel physical memory fragmentation
$ cat /proc/pagetypeinfo
# Shows distribution of free pages by type (Movable, Reclaimable, Unmovable)
# Sparse high orders in Unmovable = external fragmentation concern
```

---

## REFERENCE SUMMARY

### Quick Diagnostic Checklist

| Symptom                        | First Command to Run                          | Likely Cause                          |
|--------------------------------|-----------------------------------------------|---------------------------------------|
| System is slow, swap used      | `vmstat 1` (check si/so)                      | Insufficient RAM, high swappiness     |
| Process OOM-killed             | `dmesg \| grep "Out of memory"`               | Process RSS too large, no swap        |
| Memory leak suspected          | `watch -n5 'ps -o pid,rss,comm -p PID'`       | Missing `free()` or reference cycles  |
| High kernel memory usage       | `sudo slabtop`                                | Kernel cache not reclaiming           |
| Allocation latency spikes      | `grep alloc_stall /proc/vmstat`               | Direct reclaim pressure               |
| TLB pressure / CPU cache misses| `perf stat -e dTLB-misses ./app`              | Random access pattern, 4K pages only |
| High `Dirty` in meminfo        | `sysctl vm.dirty_ratio`                       | Write burst, writeback too slow       |

### Essential /proc Files

| File                    | Content                                          |
|-------------------------|--------------------------------------------------|
| `/proc/meminfo`         | System-wide memory statistics                    |
| `/proc/PID/maps`        | VMA layout for process                           |
| `/proc/PID/smaps`       | Per-VMA detailed stats (RSS, PSS, dirty, swap)   |
| `/proc/PID/smaps_rollup`| Aggregated smaps for whole process               |
| `/proc/PID/status`      | VmRSS, VmSize, VmSwap, etc.                      |
| `/proc/vmstat`          | Kernel VM event counters                         |
| `/proc/buddyinfo`       | Buddy allocator free page counts per order       |
| `/proc/zoneinfo`        | Per-zone detailed stats and watermarks           |
| `/proc/pagetypeinfo`    | Page type distribution (fragmentation insight)   |
| `/proc/swaps`           | Active swap devices                              |

---

*Document covers Linux kernel 5.x / 6.x on x86-64.*
*Prepared for kernel engineers, system performance analysts, and engineers preparing for deep Linux system work.*
