# Phase 1: Linux Basics — Theory & Commands
> Time: Week 1 | Daily: 1 hour | Prerequisite: None

---

## 1.1 Linux Filesystem Hierarchy (FHS)

```
/
├── bin/        # Essential user binaries (ls, cp, cat)
├── boot/       # Bootloader files, kernel image (vmlinuz)
├── dev/        # Device files — EVERY hardware is a file here
├── etc/        # System configuration files
├── home/       # User home directories
├── lib/        # Shared libraries (.so files)
├── media/      # Mount points for removable media
├── mnt/        # Temporary mount points
├── opt/        # Optional software packages
├── proc/       # Virtual: kernel & process info (not on disk!)
├── root/       # Root user's home
├── sbin/       # System binaries (ifconfig, mount)
├── sys/        # Virtual: hardware/driver info (sysfs, not on disk!)
├── tmp/        # Temporary files (cleared on reboot)
├── usr/        # User programs, headers, documentation
│   ├── include/    # C header files (use in your C programs!)
│   ├── lib/        # Libraries
│   └── src/        # Source code (kernel source goes in /usr/src/)
└── var/        # Variable data: logs, databases, mail
    └── log/    # System logs ← very important for debugging
```

**Critical for semiconductor work:**
```
/proc/         ← Read kernel internals, process memory maps
/sys/          ← Read/write driver attributes, chip registers
/dev/          ← Device nodes for your chips (ttyUSB0, spidev, i2c)
/var/log/      ← syslog, kern.log — driver crash logs
```

---

## 1.2 Navigation Commands

```bash
pwd                    # Print working directory
ls                     # List files
ls -la                 # Long format + hidden files (permissions shown)
ls -lh                 # Human-readable sizes
ls -lt                 # Sort by modification time
cd /path/to/dir        # Change directory
cd ..                  # Go up one level
cd ~                   # Go to home directory
cd -                   # Go to previous directory

# Find files
find / -name "ath11k.ko" 2>/dev/null    # Find kernel module
find /sys -name "operstate" 2>/dev/null # Find sysfs attribute
locate filename                          # Fast search (uses index)
which gcc                               # Find command location
type ls                                 # Show if alias or binary
```

---

## 1.3 File Operations

```bash
# Create
touch file.txt              # Create empty file
mkdir dir_name              # Create directory
mkdir -p a/b/c              # Create nested directories

# Copy, Move, Delete
cp source dest              # Copy file
cp -r source/ dest/         # Copy directory recursively
mv source dest              # Move OR rename
rm file.txt                 # Delete file
rm -rf directory/           # Delete directory recursively (CAREFUL!)
ln -s /target /link         # Create symbolic link (like shortcut)
ln /target /link            # Create hard link

# View files
cat file.txt                # Print all content
less file.txt               # Scrollable view (q to quit)
head -20 file.txt           # First 20 lines
tail -20 file.txt           # Last 20 lines
tail -f /var/log/syslog     # Follow log in real time ← use for driver logs
file binary_file            # Show file type (ELF, text, etc.)
```

---

## 1.4 Text Processing (Critical for Log Analysis)

```bash
# grep — search text
grep "error" dmesg.log                  # Find lines with "error"
grep -i "error" dmesg.log              # Case-insensitive
grep -r "ath11k" /sys 2>/dev/null      # Recursive search
grep -n "pattern" file.txt             # Show line numbers
grep -v "pattern" file.txt             # Invert: lines NOT matching
grep -E "error|warn|fail" dmesg.log    # OR pattern (extended regex)

# awk — column-based text processing
awk '{print $1}' file.txt            # Print first column
awk -F',' '{print $2}' csv.txt       # Set delimiter to comma
awk '/pattern/ {print $3}' log.txt   # Print column 3 of matching lines
dmesg | awk '{print $3}' | sort | uniq -c | sort -rn  # Count unique events

# sed — stream editor (find & replace)
sed 's/old/new/g' file.txt           # Replace all occurrences
sed -n '5,10p' file.txt              # Print lines 5-10
sed '/pattern/d' file.txt            # Delete lines matching pattern

# cut — extract columns
cut -d':' -f1 /etc/passwd            # Print usernames (field 1, colon delimited)
cut -c1-10 file.txt                  # Characters 1-10 of each line

# sort and count
sort file.txt                        # Sort alphabetically
sort -n file.txt                     # Sort numerically
sort -rn file.txt                    # Reverse numeric sort
uniq file.txt                        # Remove consecutive duplicates
uniq -c file.txt                     # Count occurrences
sort file.txt | uniq -c | sort -rn   # Frequency count ← use on logs!

# wc — count
wc -l file.txt                       # Count lines
wc -w file.txt                       # Count words
```

---

## 1.5 System Information

```bash
uname -a                    # Kernel version, hostname, arch
uname -r                    # Kernel version only (e.g., 5.15.0-56-generic)
cat /proc/version           # Kernel build info
cat /proc/cpuinfo           # CPU details
cat /proc/meminfo           # Memory details
free -h                     # Memory summary (human readable)
df -h                       # Disk usage
df -h /                     # Root partition usage
du -sh /path/               # Directory size
lscpu                       # CPU info (cores, cache, architecture)
lsblk                       # Block devices (disks, partitions)
lspci                       # PCI devices
lspci -v | grep -A5 -i "wireless\|wifi\|qualcomm"  # Find WiFi chip
lsusb                       # USB devices
lsmod                       # Loaded kernel modules (ath11k will appear here)
modinfo ath11k              # Info about QCA6490 driver
```

---

## 1.6 Process Management

```bash
ps aux                      # All processes
ps aux | grep wpa_supplicant  # Find WiFi daemon
top                         # Real-time process viewer
htop                        # Better top (install with apt)
kill PID                    # Send SIGTERM (15) - graceful stop
kill -9 PID                 # Send SIGKILL (9) - force kill
kill -l                     # List all signals
pkill process_name          # Kill by name
jobs                        # Show background jobs
fg %1                       # Bring job 1 to foreground
bg %1                       # Send job 1 to background
command &                   # Run in background
nohup command &             # Run immune to hangup
```

---

## 1.7 I/O Redirection & Pipes

```bash
command > file.txt          # Redirect stdout to file (overwrite)
command >> file.txt         # Redirect stdout to file (append)
command 2> errors.txt       # Redirect stderr to file
command 2>&1                # Redirect stderr to stdout
command > /dev/null 2>&1    # Discard all output
command1 | command2         # Pipe stdout of cmd1 to cmd2

# Real examples from chip debugging:
dmesg > dmesg_boot.log              # Save boot messages
dmesg 2>&1 | grep -i ath11k        # Filter QCA6490 messages
lspci -vv 2>&1 > pci_devices.txt   # Save PCI device info
cat /proc/net/wireless | tee wifi_stats.txt  # Print AND save
```

---

## 1.8 SSH (Essential for Chip Bring-up)

```bash
ssh user@192.168.1.100          # Connect to remote board
ssh -p 2222 user@host           # Non-standard port
ssh user@board "dmesg | tail -50"  # Run remote command
scp file.txt user@board:/tmp/   # Copy file to remote board
scp user@board:/tmp/file.txt .  # Copy from board to local
scp -r dir/ user@board:/tmp/    # Copy directory to board

# SSH key setup (no password login — needed for automation)
ssh-keygen -t ed25519           # Generate key pair
ssh-copy-id user@board          # Install public key on board

# Serial console (more common in embedded work)
# Replace SSH with: minicom, picocom, or screen for UART
picocom -b 115200 /dev/ttyUSB0  # Connect to board UART
```

---

## 1.9 Package Management

```bash
# Ubuntu/Debian (APT):
sudo apt update                         # Update package list
sudo apt upgrade                        # Upgrade installed packages
sudo apt install build-essential gcc gdb  # Install packages
sudo apt search kernel-headers          # Search for package
sudo apt show package-name              # Show package details
sudo apt remove package-name            # Remove package
dpkg -l | grep gcc                      # List installed packages matching "gcc"

# Install kernel headers (needed for kernel module compilation):
sudo apt install linux-headers-$(uname -r)
```

---

## 1.10 man Pages — Your Most Important Tool

```bash
man ls                  # Manual for ls command
man 2 open             # Section 2 = system calls (open, read, write, ioctl)
man 3 printf           # Section 3 = C library functions
man 7 signal           # Section 7 = overview topics

# Sections:
# 1 = User commands
# 2 = System calls (open, read, fork, mmap) — critical for your C+Linux work
# 3 = C library (printf, malloc, pthread_create)
# 7 = Overview pages (netlink, socket, signal)
# 8 = System admin commands
```

---

## Practice Exercises

1. Navigate to `/proc/net`, identify what files are there, read `/proc/net/dev`
2. Use `grep` to find all lines with "error" in `/var/log/syslog`
3. Use `awk` to print only the process name column from `ps aux`
4. Use `find` to locate all `.ko` (kernel module) files on your system
5. Use `lspci` to list all PCI devices and filter for any network devices
6. Check if `ath11k` or `ath12k` module is listed in `lsmod`
7. Create a command pipeline: `dmesg | grep -i "usb\|pci" | sort | uniq -c | sort -rn`
8. Use `tail -f /var/log/syslog` and plug/unplug a USB device — watch the logs

---

*Next: `02_Shell_Scripting/THEORY.md`*
