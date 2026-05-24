# Phase 2: Shell Scripting — Theory & Practice
> Time: Week 2 | Daily: 1 hour | Prerequisite: Phase 1

---

## 2.1 Why Shell Scripting for Semiconductor Engineers

Real use cases in your chip work:
- Automate firmware flashing to test boards
- Parse megabytes of dmesg/syslog for specific error patterns
- Auto-run test suites and collect WiFi/BT performance metrics
- Write build scripts for cross-compiling driver modules
- Schedule automated regression tests via cron

---

## 2.2 Bash Script Structure

```bash
#!/bin/bash
# This is called a "shebang" line — specifies the interpreter
# All scripts start with this line

# Make script executable:
# chmod +x my_script.sh
# Run: ./my_script.sh
```

---

## 2.3 Variables

```bash
#!/bin/bash

# Variable assignment (NO spaces around =)
name="QCA6490"
version=1
pi=3.14

# Using variables
echo "Chip: $name"
echo "Chip: ${name}_driver"    # Use {} when adjacent to other text

# Command substitution
kernel_ver=$(uname -r)
date_now=$(date +%Y%m%d)
echo "Building driver for kernel: $kernel_ver"

# Read-only variable
readonly MAX_RETRIES=3

# Environment variables
export MY_SDK_PATH="/opt/qca_sdk"   # Available to child processes
echo $PATH                           # Built-in env var
echo $HOME
echo $USER

# Array variables
chips=("QCA6490" "QCA6391" "QCA6174")
echo "${chips[0]}"          # First element
echo "${chips[@]}"          # All elements
echo "${#chips[@]}"         # Array length
```

---

## 2.4 User Input & Arguments

```bash
#!/bin/bash

# Script arguments:
# ./script.sh arg1 arg2 arg3
echo "Script name: $0"
echo "First arg: $1"
echo "Second arg: $2"
echo "All args: $@"
echo "Arg count: $#"

# Read user input
read -p "Enter chip name: " chip_name
echo "You entered: $chip_name"

# Read with timeout
read -t 5 -p "Enter (5 second timeout): " input
```

---

## 2.5 Conditionals

```bash
#!/bin/bash

# if-else
if [ "$1" == "QCA6490" ]; then
    echo "WiFi 6E chip"
elif [ "$1" == "QCA6174" ]; then
    echo "WiFi 5 chip"
else
    echo "Unknown chip: $1"
fi

# File tests:
if [ -f "/sys/class/net/wlan0/operstate" ]; then
    echo "WiFi interface exists"
fi
if [ -d "/proc/net" ]; then
    echo "Network proc exists"
fi
if [ -r "/dev/spidev0.0" ]; then
    echo "SPI device readable"
fi

# Test operators:
# -f  file exists and is regular file
# -d  directory exists
# -e  file/dir exists
# -r  readable
# -w  writable
# -x  executable
# -z  string is empty
# -n  string is not empty

# Numeric comparisons:
count=5
if [ $count -gt 3 ]; then echo "Greater than 3"; fi
# -eq  equal
# -ne  not equal
# -gt  greater than
# -lt  less than
# -ge  greater than or equal
# -le  less than or equal

# case statement
case "$chip" in
    ath11k|ath12k)
        echo "Qualcomm Atheros driver"
        ;;
    iwlwifi)
        echo "Intel WiFi driver"
        ;;
    *)
        echo "Unknown driver"
        ;;
esac
```

---

## 2.6 Loops

```bash
#!/bin/bash

# for loop
for i in 1 2 3 4 5; do
    echo "Test run: $i"
done

# for loop with range
for i in $(seq 1 10); do
    echo "Iteration: $i"
done

# C-style for loop
for ((i=0; i<10; i++)); do
    echo "i = $i"
done

# Loop over array
chips=("ath11k" "ath12k" "iwlwifi")
for chip in "${chips[@]}"; do
    echo "Checking module: $chip"
    if lsmod | grep -q "$chip"; then
        echo "  $chip is LOADED"
    else
        echo "  $chip is NOT loaded"
    fi
done

# while loop
count=0
while [ $count -lt 5 ]; do
    echo "Count: $count"
    ((count++))
done

# Loop reading file line by line (e.g., parse log file)
while IFS= read -r line; do
    if echo "$line" | grep -q "ERROR"; then
        echo "Found error: $line"
    fi
done < /var/log/syslog
```

---

## 2.7 Functions

```bash
#!/bin/bash

# Define function
build_module() {
    local module_name=$1        # local = scoped to function
    local kernel_ver=$(uname -r)
    
    echo "Building $module_name for kernel $kernel_ver"
    make -C /lib/modules/$kernel_ver/build M=$PWD modules
    
    if [ $? -eq 0 ]; then      # $? = exit code of last command
        echo "Build SUCCESS"
        return 0
    else
        echo "Build FAILED"
        return 1
    fi
}

# Call function
build_module "my_chip_driver"

# Function return value (use $?)
check_interface() {
    if ip link show "$1" > /dev/null 2>&1; then
        return 0    # Success
    else
        return 1    # Failure
    fi
}

if check_interface "wlan0"; then
    echo "wlan0 found"
fi
```

---

## 2.8 Practical Scripts

### Script 1: Chip Driver Log Parser

```bash
#!/bin/bash
# parse_chip_logs.sh — parse dmesg for chip-related messages

CHIP=${1:-"ath11k"}      # Default to ath11k if no arg
LOG_FILE="chip_debug_$(date +%Y%m%d_%H%M%S).log"

echo "=== Parsing dmesg for: $CHIP ===" | tee $LOG_FILE
echo "Timestamp: $(date)" | tee -a $LOG_FILE
echo "" | tee -a $LOG_FILE

# Save filtered logs
dmesg | grep -i "$CHIP" | tee -a $LOG_FILE

# Summary
total=$(dmesg | grep -ic "$CHIP")
errors=$(dmesg | grep -i "$CHIP" | grep -ic "error\|fail\|warn")
echo "" | tee -a $LOG_FILE
echo "Total messages: $total" | tee -a $LOG_FILE
echo "Errors/Warnings: $errors" | tee -a $LOG_FILE
echo "Log saved to: $LOG_FILE"
```

### Script 2: WiFi Interface Monitor

```bash
#!/bin/bash
# monitor_wifi.sh — monitor WiFi interface stats

IFACE=${1:-"wlan0"}
INTERVAL=${2:-2}

if ! ip link show $IFACE > /dev/null 2>&1; then
    echo "Interface $IFACE not found"
    exit 1
fi

echo "Monitoring $IFACE every ${INTERVAL}s (Ctrl+C to stop)"
while true; do
    echo "--- $(date +%T) ---"
    cat /sys/class/net/$IFACE/operstate 2>/dev/null || echo "N/A"
    cat /proc/net/dev | grep $IFACE
    sleep $INTERVAL
done
```

### Script 3: Cross-Compile Driver Build Script

```bash
#!/bin/bash
# cross_build_driver.sh

ARCH="arm64"
CROSS_COMPILE="aarch64-linux-gnu-"
KERNEL_DIR="/path/to/nxp/kernel"
MODULE_DIR="$PWD"

echo "Cross-compiling for $ARCH"
echo "Kernel: $KERNEL_DIR"

make -C $KERNEL_DIR \
     M=$MODULE_DIR \
     ARCH=$ARCH \
     CROSS_COMPILE=$CROSS_COMPILE \
     modules

if [ $? -eq 0 ]; then
    echo "SUCCESS: $(ls *.ko)"
else
    echo "FAILED"
    exit 1
fi
```

---

## 2.9 Pipes, Redirection, and Process Substitution

```bash
# Pipe output to multiple commands simultaneously
command | tee output.txt | grep "pattern"

# Process substitution (compare two command outputs)
diff <(ls dir1/) <(ls dir2/)

# Here document (multi-line string)
cat << EOF > config.txt
CHIP=QCA6490
DRIVER=ath11k
MODE=station
EOF

# Redirect both stdout and stderr
make 2>&1 | tee build.log

# Discard output
command > /dev/null 2>&1
```

---

## 2.10 Error Handling in Scripts

```bash
#!/bin/bash

set -e          # Exit script on any error
set -u          # Error on undefined variable
set -o pipefail  # Catch pipe errors

# Trap to clean up on exit or error
cleanup() {
    echo "Cleaning up..."
    rm -f /tmp/temp_files_*
}
trap cleanup EXIT      # Run on any exit
trap cleanup ERR       # Run on error

# Check command success
if ! gcc -o program program.c; then
    echo "Compilation failed!" >&2
    exit 1
fi

echo "Compilation succeeded"
```

---

## Practice Exercises

1. **Log Parser:** Write a script that takes a log file as argument and counts lines with ERROR, WARN, INFO separately
2. **Module Checker:** Write a script that checks if a list of kernel modules are loaded (use array)
3. **Build Automator:** Write a script that compiles all `.c` files in a directory and reports pass/fail
4. **Interface Monitor:** Write a script that monitors a network interface and alerts when it goes down
5. **File Organizer:** Write a script that moves `.c` files to `src/`, `.h` to `include/`, `.log` to `logs/`

---

*Next: `03_File_System_Permissions/THEORY.md`*
