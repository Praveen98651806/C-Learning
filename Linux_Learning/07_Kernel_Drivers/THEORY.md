# Phase 7: Kernel Modules & Device Drivers — Theory & Code
> Time: Week 8 | Prerequisite: C Pointers + Structures + Phase 6 Build Systems
> THIS IS THE CORE TOPIC for semiconductor engineers

---

## Why This is the Most Important Phase

QCA6490 (ath11k) is a kernel driver.
NXP Patriot platform uses kernel drivers.
Understanding this = understanding your daily work tool.

---

## 7.1 Linux Kernel Architecture

```
User Space:
  Applications (wpa_supplicant, bluetoothd, your app)
       │
  System Call Interface (glibc wraps it)
       │
Kernel Space:
  ┌─────────────────────────────────────────────────────┐
  │  Process Management  │  Memory Management           │
  │  VFS (Virtual FS)    │  Network Stack               │
  │  ┌───────────────────────────────────────────────┐  │
  │  │         Device Driver Layer                   │  │
  │  │  WiFi Driver │ UART Driver │ SPI Driver │ ...  │  │
  │  └───────────────────────────────────────────────┘  │
  │                                                     │
  └───────────────────┬─────────────────────────────────┘
                      │ Hardware Abstraction
  ┌───────────────────▼─────────────────────────────────┐
  │  Hardware: QCA6490 (PCIe) │ NXP MCU │ SPI flash     │
  └─────────────────────────────────────────────────────┘
```

---

## 7.2 First Kernel Module — Hello World

```c
// hello_module.c
#include <linux/init.h>       // module_init, module_exit macros
#include <linux/module.h>     // MODULE_LICENSE, printk
#include <linux/kernel.h>     // KERN_INFO

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Hello World Driver");
MODULE_VERSION("1.0");

// Called when module is loaded (insmod)
static int __init hello_init(void)
{
    printk(KERN_INFO "hello_module: Loaded! Hello from kernel space\n");
    return 0;  // 0 = success, negative = error
}

// Called when module is removed (rmmod)
static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello_module: Removed!\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

### Makefile for kernel module:
```makefile
obj-m += hello_module.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
```

### Build and test:
```bash
make                           # Build module
sudo insmod hello_module.ko    # Load module
dmesg | tail -5                # See "Hello from kernel space"
lsmod | grep hello             # Confirm it's loaded
sudo rmmod hello_module        # Remove module
dmesg | tail -3                # See "Removed!"
```

---

## 7.3 printk and Log Levels

```c
// Kernel printk levels (like printf but in kernel)
printk(KERN_EMERG   "System crash\n");        // 0 - Imminent crash
printk(KERN_ALERT   "Action required\n");     // 1
printk(KERN_CRIT    "Critical error\n");      // 2
printk(KERN_ERR     "Error occurred\n");      // 3
printk(KERN_WARNING "Warning: %s\n", msg);   // 4
printk(KERN_NOTICE  "Notice\n");              // 5
printk(KERN_INFO    "Info: chip %s\n", name); // 6
printk(KERN_DEBUG   "Debug: val=%d\n", val);  // 7

// Shorthand macros (in actual drivers):
pr_err("Error: %d\n", ret);
pr_warn("Warning: %s\n", str);
pr_info("Driver loaded\n");
pr_debug("Debug value: %d\n", val);

// Device-specific (preferred in modern drivers):
dev_err(dev, "Failed to init chip\n");
dev_info(dev, "QCA6490 initialized\n");
dev_dbg(dev, "Register value: 0x%08x\n", reg_val);
```

---

## 7.4 Character Device Driver

A character device exposes a file in `/dev`. User applications read/write through it.
This is how many chip interfaces work (UART, SPI, I2C exposed as `/dev/ttyS0`, `/dev/spidev`, etc.)

```c
// char_device.c — Simple character device driver
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>        // file_operations, register_chrdev
#include <linux/uaccess.h>   // copy_to_user, copy_from_user
#include <linux/cdev.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "mydevice"
#define BUFFER_SIZE 1024

static int    major_number;
static char   kernel_buffer[BUFFER_SIZE];
static int    buffer_len = 0;
static struct class  *dev_class;
static struct device *dev_device;

// Called when user opens /dev/mydevice
static int device_open(struct inode *inode, struct file *file)
{
    pr_info("mydevice: opened\n");
    return 0;
}

// Called when user closes /dev/mydevice
static int device_release(struct inode *inode, struct file *file)
{
    pr_info("mydevice: closed\n");
    return 0;
}

// Called when user reads from /dev/mydevice
// IMPORTANT: data is in kernel space, user needs copy_to_user
static ssize_t device_read(struct file *file, char __user *user_buf,
                            size_t count, loff_t *offset)
{
    int bytes_to_copy = min((int)count, buffer_len);
    
    if (copy_to_user(user_buf, kernel_buffer, bytes_to_copy))
        return -EFAULT;    // Memory copy failed
    
    pr_info("mydevice: sent %d bytes to user\n", bytes_to_copy);
    return bytes_to_copy;
}

// Called when user writes to /dev/mydevice
static ssize_t device_write(struct file *file, const char __user *user_buf,
                             size_t count, loff_t *offset)
{
    buffer_len = min((int)count, BUFFER_SIZE - 1);
    
    if (copy_from_user(kernel_buffer, user_buf, buffer_len))
        return -EFAULT;
    
    kernel_buffer[buffer_len] = '\0';
    pr_info("mydevice: received: %s\n", kernel_buffer);
    return buffer_len;
}

// File operations table — this is what makes it a "driver"
// Think of it as a vtable/function pointer table for the device
static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = device_open,
    .release = device_release,
    .read    = device_read,
    .write   = device_write,
};

static int __init chardev_init(void)
{
    // Register character device - kernel assigns major number
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        pr_err("Failed to register: %d\n", major_number);
        return major_number;
    }
    
    // Create /sys/class/mydevice
    dev_class = class_create(THIS_MODULE, DEVICE_NAME);
    
    // Create /dev/mydevice automatically
    dev_device = device_create(dev_class, NULL, MKDEV(major_number, 0),
                               NULL, DEVICE_NAME);
    
    pr_info("mydevice: registered with major=%d\n", major_number);
    return 0;
}

static void __exit chardev_exit(void)
{
    device_destroy(dev_class, MKDEV(major_number, 0));
    class_destroy(dev_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    pr_info("mydevice: unregistered\n");
}

module_init(chardev_init);
module_exit(chardev_exit);
```

### User space test program (C):
```c
// test_device.c - test the char device
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/mydevice", O_RDWR);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }
    
    // Write to device (goes to kernel buffer)
    char *msg = "Hello from user space!";
    write(fd, msg, strlen(msg));
    
    // Read back from device
    char buf[1024];
    int n = read(fd, buf, sizeof(buf));
    buf[n] = '\0';
    printf("Read from device: %s\n", buf);
    
    close(fd);
    return 0;
}
```

---

## 7.5 Sysfs — Expose Driver Data to User Space

Sysfs (`/sys`) is how drivers expose attributes that can be read/written from shell.
This is how you'd tune QCA6490 parameters or read NXP register values.

```c
// Adding sysfs attribute to your driver
#include <linux/sysfs.h>
#include <linux/kobject.h>

static struct kobject *chip_kobj;
static int chip_power_level = 100;

// Sysfs "show" function (user reads /sys/chip_driver/power_level)
static ssize_t power_level_show(struct kobject *kobj,
                                 struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", chip_power_level);
}

// Sysfs "store" function (user writes to /sys/chip_driver/power_level)
static ssize_t power_level_store(struct kobject *kobj,
                                  struct kobj_attribute *attr,
                                  const char *buf, size_t count)
{
    sscanf(buf, "%du", &chip_power_level);
    return count;
}

// Declare the attribute (name, permissions, show function, store function)
static struct kobj_attribute power_attr =
    __ATTR(power_level, 0664, power_level_show, power_level_store);

// In init:
chip_kobj = kobject_create_and_add("chip_driver", kernel_kobj);
sysfs_create_file(chip_kobj, &power_attr.attr);

// User can now:
// cat /sys/chip_driver/power_level        -> reads power_level
// echo 50 > /sys/chip_driver/power_level  -> sets power_level to 50
```

---

## 7.6 Platform Driver and Device Tree

Modern embedded Linux (NXP boards) uses Device Tree instead of hardcoded hardware config.

```c
// platform_driver.c — matches device from Device Tree
#include <linux/platform_device.h>
#include <linux/of.h>           // Device Tree support

// Called when kernel finds matching DT node
static int my_chip_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    
    dev_info(dev, "Chip found! probing...\n");
    
    // Get resources from Device Tree
    struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    void __iomem *base = devm_ioremap_resource(dev, res);  // Map registers
    
    // Read chip ID register
    u32 chip_id = readl(base + 0x0000);
    dev_info(dev, "Chip ID: 0x%08x\n", chip_id);
    
    return 0;
}

// Device Tree compatible string — matches "compatible" in .dts file
static const struct of_device_id my_chip_of_match[] = {
    { .compatible = "mycompany,my-chip" },
    {},
};
MODULE_DEVICE_TABLE(of, my_chip_of_match);

static struct platform_driver my_chip_driver = {
    .probe  = my_chip_probe,
    .driver = {
        .name           = "my-chip",
        .of_match_table = my_chip_of_match,
    },
};

module_platform_driver(my_chip_driver);
```

Device Tree snippet (`.dts` file on NXP board):
```dts
my_chip: chip@40000000 {
    compatible = "mycompany,my-chip";
    reg = <0x40000000 0x1000>;   /* base address, size */
    interrupts = <0 100 4>;
    clocks = <&clks IMX6UL_CLK_AHB>;
};
```

---

## 7.7 Interrupt Handler

```c
#include <linux/interrupt.h>

static irqreturn_t my_chip_irq_handler(int irq, void *dev_id)
{
    struct my_chip_priv *priv = dev_id;
    
    // Read interrupt status register
    u32 status = readl(priv->base + IRQ_STATUS_REG);
    
    // Clear interrupt
    writel(status, priv->base + IRQ_CLEAR_REG);
    
    // Process interrupt (schedule work for heavy processing)
    schedule_work(&priv->irq_work);
    
    return IRQ_HANDLED;  // Tell kernel we handled it
}

// Register interrupt in probe:
ret = devm_request_irq(dev, irq, my_chip_irq_handler,
                        IRQF_SHARED, "my-chip", priv);
```

---

## 7.8 Kernel Synchronization (Critical for Multi-core)

```c
#include <linux/mutex.h>
#include <linux/spinlock.h>

// Mutex (can sleep, for sleepable context)
static DEFINE_MUTEX(chip_mutex);

mutex_lock(&chip_mutex);
// Critical section (can sleep here)
chip_register_write(addr, value);
mutex_unlock(&chip_mutex);

// Spinlock (cannot sleep, for interrupt context)
static DEFINE_SPINLOCK(chip_lock);
unsigned long flags;

spin_lock_irqsave(&chip_lock, flags);    // Disable interrupts + lock
// Critical section (CANNOT sleep here)
chip_register_write(addr, value);
spin_unlock_irqrestore(&chip_lock, flags); // Restore interrupts + unlock
```

---

## 7.9 PCIe Driver (QCA6490 uses PCIe)

```c
// pcie_driver.c — QCA6490 connects via PCIe
#include <linux/pci.h>

static int qca6490_pcie_probe(struct pci_dev *pdev,
                               const struct pci_device_id *id)
{
    // Enable PCI device
    pci_enable_device(pdev);
    pci_set_master(pdev);       // Enable DMA bus mastering
    
    // Map BAR0 (Base Address Register 0 = chip register space)
    void __iomem *base = pci_iomap(pdev, 0, 0);
    
    // Read Chip ID
    u32 chip_id = readl(base + CHIP_ID_REG);
    dev_info(&pdev->dev, "QCA6490 found! ID=0x%08x\n", chip_id);
    
    return 0;
}

static const struct pci_device_id qca6490_pci_id[] = {
    // Qualcomm QCA6490 PCIe Vendor:Device ID
    { PCI_DEVICE(0x17CB, 0x1103) },   // actual QCA6490 ID
    {}
};
MODULE_DEVICE_TABLE(pci, qca6490_pci_id);

static struct pci_driver qca6490_driver = {
    .name     = "qca6490",
    .id_table = qca6490_pci_id,
    .probe    = qca6490_pcie_probe,
};
```

---

## Practice Exercises

1. Build and load the Hello World kernel module
2. Verify with `dmesg` and `lsmod`
3. Build the character device — test with `echo "hello" > /dev/mydevice`
4. Add one more ioctl command to the character device
5. Browse the real ath11k driver source: `elixir.bootlin.com` → search `ath11k_pci_probe`
6. Identify the PCIe Vendor/Device ID in ath11k source code

---

*Next: `09_Embedded_Linux/THEORY.md`*
*Also See: `10_Semiconductor_Chip_Work/QCA6490_GUIDE.md`*
