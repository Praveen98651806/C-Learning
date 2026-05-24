# Linux Quick Start — Day 1 Guide
> You have QCA6490 + NXP experience. You're not starting from zero.
> You've used these chips on Linux. Now learn what was happening under the hood.

---

## Step 1: Setup (Do This First — 30 min)

### Option A: WSL2 (Recommended for Windows)
```powershell
# Run in PowerShell as Administrator:
wsl --install -d Ubuntu-22.04
# Restart PC when prompted
# Then open "Ubuntu" from Start Menu
```

### Option B: VirtualBox VM
- Download Ubuntu 22.04 LTS ISO from ubuntu.com
- Create VM: 4GB RAM, 40GB disk, bridged network

### First commands after install:
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install -y build-essential git gdb valgrind strace tree net-tools curl wget
```

---

## Step 2: WSL2 Daily Workflow

```bash
# Access your C-Learning files from WSL2:
cd /mnt/c/Users/9fu97v/Documents/Study/C-Learning

# Compile your C programs in WSL2 (better than MinGW for Linux system calls):
gcc -Wall -g 01_Fundamentals/01_calculator.c -o calc
./calc

# This means you can practice C AND Linux at the same time
```

---

## Step 3: First 5 Commands to Learn NOW

```bash
# 1. Where am I?
pwd

# 2. What's here?
ls -la

# 3. Navigate
cd /proc          # See running kernel info
ls                # See process IDs and kernel info
cat /proc/version # Linux kernel version
cat /proc/cpuinfo # CPU info (like your QCA6490's host CPU)

# 4. Search for something
grep -r "keyword" /path/to/search

# 5. Read system messages (like chip initialization logs)
dmesg | tail -50                    # Last 50 kernel messages
dmesg | grep -i "wifi\|wlan\|bt"   # Filter for WiFi/BT messages
```

---

## Step 4: The /proc and /sys Tour (Do This Day 1)

These are not regular files — they are **windows into the running kernel**.
This is exactly where driver debugging happens with real chips.

```bash
# /proc — process and kernel info
ls /proc
cat /proc/meminfo          # Memory stats
cat /proc/net/dev          # Network interfaces
cat /proc/interrupts       # Hardware IRQ assignments

# /sys — hardware/driver info exposed by kernel
ls /sys/class/net/         # All network interfaces
ls /sys/bus/pci/devices/   # All PCI devices (QCA6490 on PCIe appears here)
ls /sys/bus/usb/devices/   # USB devices

# /dev — device files
ls /dev                    # All device nodes
ls -la /dev/tty*           # Serial terminals (used for UART on boards)
```

---

## Step 5: Compile & Run Your C Programs on Linux

Your existing C programs will now run on a real Linux system:

```bash
cd /mnt/c/Users/9fu97v/Documents/Study/C-Learning/01_Fundamentals/

# Compile
gcc -Wall -g 01_calculator.c -o calculator

# Run
./calculator

# Debug with GDB (practice this early!)
gdb ./calculator
(gdb) break main       # Set breakpoint at main
(gdb) run             # Start program
(gdb) next            # Step line by line
(gdb) print variable  # Print variable value
(gdb) quit
```

---

## Week 1 Practice Checklist

### Day 1-2: Navigation & Files
- [ ] Navigate to `/proc`, `/sys`, `/dev` — understand what's there
- [ ] Use `find / -name "*.c" 2>/dev/null | head -20` 
- [ ] Use `grep -r "QCA\|ath11k" /sys 2>/dev/null` (if WiFi chip is present)
- [ ] Practice: `ls`, `cd`, `pwd`, `mkdir`, `touch`, `cp`, `mv`, `rm`

### Day 3-4: Text Processing (Critical for log analysis)
- [ ] `cat dmesg_log.txt | grep "error"` 
- [ ] `awk '{print $1, $3}' file.txt`
- [ ] `sed 's/old/new/g' file.txt`
- [ ] `cut -d',' -f2 csv_file.txt`
- [ ] `sort`, `uniq -c` (count duplicates — used in log analysis)
- [ ] Practice: parse a dmesg output file

### Day 5-7: Processes & System Info
- [ ] `ps aux | grep wpa_supplicant` (find WiFi daemon)
- [ ] `top` — watch CPU/memory in real time
- [ ] `kill -9 PID` vs `kill -15 PID` — understand the difference
- [ ] `lsmod` — list loaded kernel modules (will show ath11k if QCA6490 present)
- [ ] `modinfo ath11k` — info about QCA6490 driver module
- [ ] `lspci -v` — list PCI devices with details

---

## The QCA6490 Connection (Why This Matters to You)

```bash
# When QCA6490 is connected to a Linux host, you can see:
lspci | grep -i qualcomm       # QCA6490 on PCIe bus
lsmod | grep ath               # ath11k or ath12k driver loaded
ls /sys/class/net/wlan0/       # WiFi interface sysfs attributes
cat /sys/class/net/wlan0/operstate  # Interface state
dmesg | grep ath11k            # Driver initialization messages
iw dev wlan0 info              # WiFi interface details
iw phy phy0 info               # PHY capabilities (WiFi bands, rates)
```

The driver for QCA6490 in upstream Linux is:
- **ath11k** (kernel 5.6+) or **ath12k** (newer variant)
- Located in kernel source: `drivers/net/wireless/ath/ath11k/`
- Read this source once you finish Phase 8 (Kernel Drivers)

---

## Parallel Study Schedule (Suggested Daily)

```
Morning (1 hr):   C Learning — current phase exercises
Evening (1 hr):   Linux Learning — current phase + practice commands
Weekend (2 hrs):  Combined project (e.g., C program that uses Linux system calls)
```

**Combined projects to try:**
- Week 4: Write a C program using `fork()` + `exec()` (C + Linux process knowledge)
- Week 5: Write a C TCP socket program (C + Linux networking knowledge)
- Week 7: Debug your own C program with GDB on Linux
- Week 8: Write a simple kernel module (CHARACTER DEVICE) in C

---

## Start Right Now

```bash
# 1. Open WSL2 Ubuntu terminal
# 2. Run these commands and understand each output:

uname -a                    # Kernel version
cat /etc/os-release         # OS info  
lscpu | grep -E "Model|CPU" # CPU info
free -h                     # Memory
df -h                       # Disk usage
ip addr show                # Network interfaces
cat /proc/net/dev            # Network stats
ls /sys/class/               # All device classes exposed by kernel
```

---

*Next file to read: `01_Basics/THEORY.md`*
