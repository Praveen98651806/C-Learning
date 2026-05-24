# Bitwise & Logical Operators in WiFi Driver Code

> In embedded/driver code, bitwise operators are used **everywhere** —
> register configuration, flag checks, packet parsing, hardware control.

---

## Why Bitwise Matters in Drivers

| Use Case | Operator | Example |
|---|---|---|
| Set a hardware register bit | `\|=` | Enable TX interrupt |
| Clear a register bit | `&= ~` | Disable RX interrupt |
| Toggle a bit | `^=` | Flip antenna state |
| Check if a bit is set | `&` | Is DMA ready? |
| Pack/unpack fields | `<<` `>>` | Build WiFi frame header |
| Mask a value | `&` | Extract channel number |

---

## 1. Register Bit Set / Clear / Check

```c
/* ----- WiFi Interrupt Enable Register (32-bit) -----
   Bit 0 : TX complete
   Bit 1 : RX ready
   Bit 2 : DMA error
   Bit 4 : Beacon received
*/
#define WIFI_INT_TX_DONE     (1 << 0)   /* 0x01 */
#define WIFI_INT_RX_READY    (1 << 1)   /* 0x02 */
#define WIFI_INT_DMA_ERROR   (1 << 2)   /* 0x04 */
#define WIFI_INT_BEACON      (1 << 4)   /* 0x10 */

uint32_t reg = 0;

/* SET: enable TX and RX interrupts */
reg |= (WIFI_INT_TX_DONE | WIFI_INT_RX_READY);

/* CLEAR: disable DMA error interrupt */
reg &= ~WIFI_INT_DMA_ERROR;

/* CHECK: is RX ready? */
if (reg & WIFI_INT_RX_READY) {
    handle_rx();
}

/* TOGGLE: flip beacon interrupt */
reg ^= WIFI_INT_BEACON;
```

---

## 2. Bit Masking — Extract Fields from a Register

```c
/* WiFi Channel Register layout (32-bit):
   Bits [7:0]   = channel number
   Bits [11:8]  = bandwidth (0=20MHz, 1=40MHz, 2=80MHz)
   Bits [15:12] = band (0=2.4GHz, 1=5GHz)
*/
#define CHANNEL_MASK    0x000000FF
#define BW_MASK         0x00000F00
#define BW_SHIFT        8
#define BAND_MASK       0x0000F000
#define BAND_SHIFT      12

uint32_t reg = 0x00001136;  /* example register value */

uint8_t  channel   = (reg & CHANNEL_MASK);            /* = 0x36 = 54 */
uint8_t  bandwidth = (reg & BW_MASK)   >> BW_SHIFT;   /* = 1 = 40MHz */
uint8_t  band      = (reg & BAND_MASK) >> BAND_SHIFT;  /* = 0 = 2.4GHz */
```

---

## 3. Build a Value — Pack Fields Into a Register

```c
/* Set channel=6, bandwidth=1(40MHz), band=0(2.4GHz) */
uint32_t channel_reg = 0;
channel_reg |= (6  & 0xFF);          /* bits [7:0]   */
channel_reg |= (1  & 0xF) << 8;      /* bits [11:8]  */
channel_reg |= (0  & 0xF) << 12;     /* bits [15:12] */

/* Result: 0x00000106 */
write_register(WIFI_CHANNEL_REG, channel_reg);
```

---

## 4. Qualcomm-Style Flag Handling (ATH/QCA Pattern)

```c
/* From ath10k / QCA WLAN driver style */

/* capability flags */
#define ATH10K_FW_FEATURE_WMI_10X       BIT(0)
#define ATH10K_FW_FEATURE_RAW_MODE      BIT(1)
#define ATH10K_FW_FEATURE_HAS_WMI_MGMT  BIT(2)

/* BIT(n) expands to (1UL << n) */

struct ath10k {
    unsigned long fw_features;   /* bitmask of enabled features */
};

/* Check if feature is supported */
static inline bool ath10k_has_feature(struct ath10k *ar, int feature)
{
    return ar->fw_features & BIT(feature);
}

/* Enable a feature */
static void enable_wmi(struct ath10k *ar)
{
    ar->fw_features |= ATH10K_FW_FEATURE_HAS_WMI_MGMT;
}

/* Disable a feature */
static void disable_raw_mode(struct ath10k *ar)
{
    ar->fw_features &= ~ATH10K_FW_FEATURE_RAW_MODE;
}
```

---

## 5. Logical vs Bitwise — Don't Confuse Them

```c
uint32_t status = 0x02;   /* RX_READY bit set */

/* WRONG — logical AND, checks non-zero, not the bit */
if (status && WIFI_INT_RX_READY) { }   // always true if status != 0

/* CORRECT — bitwise AND, checks the specific bit */
if (status & WIFI_INT_RX_READY) { }    // true only if bit 1 is set

/* WRONG — logical OR for combining flags */
reg = WIFI_INT_TX_DONE || WIFI_INT_RX_READY;   // = 1 (boolean!)

/* CORRECT — bitwise OR for combining flags */
reg = WIFI_INT_TX_DONE | WIFI_INT_RX_READY;    // = 0x03
```

---

## 6. Packet Header Parsing (802.11 Frame)

```c
/* 802.11 Frame Control field (16-bit):
   Bits [1:0]  = protocol version
   Bits [3:2]  = type (management=0, control=1, data=2)
   Bits [7:4]  = subtype
*/
uint16_t frame_ctrl = 0x0008;   /* data frame */

uint8_t version = (frame_ctrl >> 0) & 0x3;
uint8_t type    = (frame_ctrl >> 2) & 0x3;   /* = 2 = data */
uint8_t subtype = (frame_ctrl >> 4) & 0xF;

if (type == 0x2) {
    process_data_frame();
}
```

---

## Key Takeaways

1. **`|=`** to set bits, **`&= ~`** to clear bits, **`&`** to test bits
2. **`<<` / `>>`** to pack/unpack fields within a register
3. **Always use bitwise (`&`, `|`)** for flags — never logical (`&&`, `||`)
4. **`#define BIT(n) (1UL << n)`** is the standard driver pattern
5. Use **masks + shifts** to extract fields: `(reg & MASK) >> SHIFT`

---

*Patterns used in: Linux kernel ath10k, ath11k, QCA drivers, Qualcomm WLAN HAL*
