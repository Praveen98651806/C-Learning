# Semiconductor Chip Work — QCA6490 & NXP Guide
> This is where your existing experience connects to Linux knowledge

---

## Your Advantages Coming In

You've used these chips. You know:
- What the chip does (WiFi 6E + BT 5.2 for QCA6490)
- How it's connected to a host (PCIe, USB, SDIO)
- What failure modes look like (firmware crash, init fail, performance drop)

What this guide fills in:
- What's happening in the Linux kernel when you see those behaviors
- How to read/debug the actual driver source
- How to modify/maintain drivers at a new job

---

## QCA6490 Linux Stack

```
User Space:
  wpa_supplicant          bluetoothd
       │                       │
  nl80211 (netlink)       HCI socket
       │                       │
Kernel Space:
  ┌─── cfg80211 ──────── mac80211 ───┐      ┌── Bluetooth Core ──┐
  │    (WiFi cfg API)  (WiFi MAC layer)│      │  (HCI layer)        │
  └────────────┬─────────────────────┘      └────────┬────────────┘
               │                                     │
          ath11k / ath12k driver                 btusb / ath driver
               │                                     │
  ┌────────────▼─────────────────────────────────────▼────────────┐
  │                    PCIe / USB / SDIO bus driver               │
  └────────────────────────────────┬──────────────────────────────┘
                                   │
                              QCA6490 Hardware
                        (WiFi 6E Radio + BT 5.2 Radio)
```

---

## Key Linux Commands for QCA6490 Debug

```bash
# 1. Verify chip is detected
lspci | grep -i qualcomm
# Expected: 17:00.0 Network controller: Qualcomm Device 1103 (or similar)

# 2. Check driver loaded
lsmod | grep ath
# Expected: ath11k_pci  or  ath12k

# 3. Driver initialization messages
dmesg | grep -i "ath11k\|ath12k\|qca6490"
dmesg | grep -i "firmware\|fw\|cal\|calib"   # Firmware load messages

# 4. WiFi interface  
ip link show wlan0
iw dev wlan0 info
iw phy phy0 info                     # Shows supported bands, rates, capabilities

# 5. Read sysfs attributes
cat /sys/class/net/wlan0/operstate   # up/down/unknown
cat /sys/class/net/wlan0/statistics/rx_bytes
cat /sys/class/net/wlan0/statistics/tx_bytes

# 6. WiFi scan
iw dev wlan0 scan | grep -E "SSID|signal|freq"

# 7. Connection info
iw dev wlan0 link
iw dev wlan0 station dump

# 8. Firmware path (ath11k firmware files)
ls /lib/firmware/ath11k/
ls /lib/firmware/ath11k/QCA6490/
# These .bin files are loaded by driver at init time

# 9. Debug level (increase driver verbosity)
echo "module ath11k +p" | sudo tee /sys/kernel/debug/dynamic_debug/control
# or
echo 0xffffffff | sudo tee /sys/kernel/debug/ath11k/*/debug_mask

# 10. Interface statistics
cat /proc/net/dev | grep wlan
ethtool -S wlan0          # Extended stats (if supported)
```

---

## QCA6490 Driver Source Navigation

Driver location in kernel tree: `drivers/net/wireless/ath/ath11k/`

Key source files to read (in order):
```
ath11k/
├── core.h          ← Main data structures (ath11k_hw, ath11k_vif, etc.)
├── core.c          ← Core initialization
├── pci.c           ← PCIe bus probe/remove ← START HERE
├── ahb.c           ← AHB bus (for integrated chips)
├── mac.c           ← MAC layer (connect to mac80211)
├── wmi.c           ← WMI commands to firmware (WiFi Management Interface)
├── htc.c           ← HTC protocol (Host-Target Communication)
├── hif.h           ← Hardware Interface abstraction
├── ce.c            ← Copy Engine (DMA engine for PCIe transfers)
├── dp.c            ← Data path (RX/TX data packets)
├── reg.c           ← Regulatory domain handling
├── thermal.c       ← Thermal management
├── debugfs.c       ← /sys/kernel/debug/ath11k/ entries
└── fw.c            ← Firmware download
```

### How to browse online:
- Go to: https://elixir.bootlin.com/linux/latest/source/drivers/net/wireless/ath/ath11k
- Search for `ath11k_pci_probe` — this is the entry point when QCA6490 is detected
- Follow the call chain: `probe` → `ath11k_core_create` → `ath11k_core_init`

---

## NXP Patriot / i.MX Linux Stack

```
NXP i.MX Application Processor (Cortex-A)
  │
  ├── Runs Linux (NXP's Yocto-based BSP)
  ├── U-Boot bootloader
  ├── Device Tree defines all peripherals
  └── NXP SDK / meta-imx Yocto layer

Peripherals driven by kernel drivers:
  - UART:   imx-uart driver
  - SPI:    imx-spi / spi-imx driver
  - I2C:    i2c-imx driver
  - GPIO:   gpio-mxc driver
  - Ethernet: fec driver (Fast Ethernet Controller)
  - USB:    ci_hdrc_imx driver
  - PCIe:   imx6-pcie driver
  - SDIO:   sdhci-esdhc-imx driver ← WiFi modules often connect here
```

---

## Key Commands for NXP Board Bring-up

```bash
# Check U-Boot version (from serial console on boot)
# => version

# In Linux on the NXP board:
cat /proc/device-tree/compatible   # What board/SoC we're running
ls /proc/device-tree/              # Full DT contents as filesystem
dtc -I fs /proc/device-tree > board.dts  # Dump full compiled DT to text

# Find which driver owns a device
cat /sys/bus/platform/devices/30be0000.ethernet/driver  # FEC ethernet
ls /sys/bus/platform/devices/ | head -30                # All platform devices

# Load/unload NXP WiFi driver (if using WiFi module on SDIO)
modprobe ath11k_sdio          # Load
rmmod ath11k_sdio              # Remove
dmesg | grep ath11k            # Check init messages

# Cross-compile kernel module for NXP ARM64 target
export ARCH=arm64
export CROSS_COMPILE=aarch64-poky-linux-
make -C /path/to/nxp/kernel M=$PWD modules
# Copy .ko to board via SCP
scp my_driver.ko root@board_ip:/tmp/
# On board:
insmod /tmp/my_driver.ko
```

---

## Device Tree for QCA6490 on PCIe (Example)

```dts
/* In board .dts file */
&pcie0 {
    status = "okay";
    
    wifi: wifi@0,0 {
        reg = <0x00000000 0 0 0 0>;
        compatible = "pci17cb,1103";   /* Qualcomm QCA6490 */
        
        /* Firmware path override */
        qcom,ath11k-fw-memory-mode = <1>;
    };
};
```

---

## Firmware Management (QCA6490)

```bash
# QCA6490 requires firmware files at boot:
ls /lib/firmware/ath11k/QCA6490/hw2.0/
# Should contain:
#   amss.bin        - Main firmware
#   m3.bin          - WiFi co-processor firmware
#   board-2.bin     - Board calibration data
#   regdb.bin       - Regulatory database

# If firmware missing, dmesg shows:
# ath11k_pci: firmware file /lib/firmware/ath11k/QCA6490/hw2.0/amss.bin not found

# Update firmware:
cp new_firmware/*.bin /lib/firmware/ath11k/QCA6490/hw2.0/
# Reload driver:
sudo modprobe -r ath11k_pci && sudo modprobe ath11k_pci
dmesg | tail -20   # Check if it loaded correctly
```

---

## Common Debug Scenarios

### Scenario 1: WiFi chip not detected
```bash
lspci | grep -i qualcomm   # Check if PCIe sees the chip
# If not found:
# - Check PCIe cable/connector
# - Check power supply to chip
# - Check U-Boot PCIe initialization
lspci -vv | grep -A30 "Network controller"  # Detailed PCI info
```

### Scenario 2: Firmware load failure
```bash
dmesg | grep -i "ath11k\|firmware\|fw"
# Look for: "Direct firmware load for ... failed"
# Fix: check /lib/firmware/ath11k/ path
ls -la /lib/firmware/ath11k/QCA6490/hw2.0/
```

### Scenario 3: WiFi connected but slow
```bash
iw dev wlan0 station dump    # Check signal, bitrate, retries
iw dev wlan0 info            # Check channel, power
cat /sys/kernel/debug/ath11k/wifi0/stats  # Driver stats
# Look for: high retry count, low RSSI, incorrect channel width
```

### Scenario 4: Kernel crash (BUG/OOPS) in driver
```bash
dmesg | grep -A30 "BUG:\ Unable\|kernel BUG\|Oops"
# Oops message contains:
# - Call trace (function that crashed)
# - Register values
# - Instruction pointer (where crash happened)
# Use addr2line to decode addresses to source lines:
addr2line -e vmlinux -a 0xffffffffc0deadbeef
```

---

## Recommended Learning Path Using Your Experience

1. **Week 8 (Kernel Drivers phase):**
   - Write hello world module
   - Read `ath11k/pci.c` first 100 lines — identify `probe` function

2. **Week 9 (Embedded Linux phase):**
   - Set up Buildroot for ARM (QEMU ARM target first)
   - Enable ath11k in kernel config (`make menuconfig`)

3. **Week 10:**
   - Compile ath11k as out-of-tree module
   - Read ath11k WMI commands — understand firmware communication
   - Compare with your QCA6490 experience (the WMI commands ARE what you've been triggering)

---

## Tools Specific to Wireless/BT Development

```bash
# WiFi
iw                   # Modern wireless tool (replaces iwconfig)
hostapd              # Access Point daemon
wpa_supplicant       # Station mode daemon
iw dev wlan0 scan    # Scan for networks
iw dev wlan0 connect "SSID"   # Connect to open network

# Bluetooth
bluetoothctl         # Interactive BT management
hciconfig hci0 up    # Bring up BT interface
hcitool scan         # Scan for BT devices
btmon                # Monitor BT HCI traffic (like Wireshark for BT)

# Network analysis
tcpdump -i wlan0 -w capture.pcap   # Capture WiFi packets
wireshark capture.pcap              # Analyze in Wireshark
iw dev wlan0 set monitor none       # Set monitor mode (packet capture)

# Qualcomm debugging tools (from QCA SDK)
# These are vendor tools, not upstream:
# qca-wifi-tool, athstats, ath11k-fwlog-parser
```

---

*You now have a complete map from your chip experience to the Linux internals.*
*Each phase in LINUX_ROADMAP.md builds towards reading and modifying this code.*
