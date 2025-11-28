# ESP32-S3 RC522 RFID LED Control

## Overview

This project demonstrates a simple **RFID-based LED control system** using the **ESP32-S3 N16R8** development board and an **RC522 RFID module**. The ESP32-S3 reads RFID cards and controls an LED based on the scanned card:

* **First card (UID: B3 0A F9 05)** → turns **LED ON**
* **Second card (UID: BD 25 73 06)** → turns **LED OFF**

All card detections and actions are displayed on the **Serial Monitor**, making it easy to monitor in real-time.

This project is ideal for **educational purposes**, learning **RFID systems**, **SPI communication**, and **ESP32 GPIO control**.

---

## Features

* Scans multiple RFID cards and detects their UID.
* Controls an LED based on specific card UIDs.
* Prints card UID and type to Serial Monitor.
* Works with **ESP32-S3 N16R8** using custom SPI pin mapping.

---

## Hardware Requirements

| Component                  | Model / Notes                       |
| -------------------------- | ----------------------------------- |
| ESP32-S3 Development Board | N16R8 variant, 16MB Flash           |
| RC522 RFID Module          | MFRC522                             |
| LED                        | Any 3.3V or 5V compatible LED       |
| Resistor                   | 220–330Ω for LED (current limiting) |
| Jumper Wires               | For SPI and GPIO connections        |
| Breadboard                 | Optional                            |

---

## Software Requirements

* **Arduino IDE** (or PlatformIO in VS Code)
* **MFRC522 Library** by GithubCommunity / Miguel Balboa
* ESP32 Board Support Package (latest via Arduino Board Manager)

---

## Connections

| RC522 Pin | ESP32-S3 Pin      | Notes                     |
| --------- | ----------------- | ------------------------- |
| 3.3V      | 3.3V              | Power supply              |
| GND       | GND               | Ground                    |
| SDA (SS)  | GPIO 10           | SPI Slave Select          |
| SCK       | GPIO 12           | SPI Clock                 |
| MOSI      | GPIO 11           | SPI Data Out              |
| MISO      | GPIO 13           | SPI Data In               |
| RST       | GPIO 9            | Reset pin                 |
| IRQ       | Leave unconnected | Optional for interrupts   |
| LED       | GPIO 15           | Output controlled by card |

> ⚠️ Ensure RC522 is powered with 3.3V — connecting to 5V may damage the module.

---

## How It Works

1. The ESP32-S3 initializes SPI and the RC522 module.
2. Continuously scans for new RFID cards.
3. When a card is detected, its **UID is read and printed** to Serial Monitor.
4. Compares the UID to predefined card arrays:

   * If **Card 1**, LED turns **ON**.
   * If **Card 2**, LED turns **OFF**.
5. Unknown cards are ignored but printed in Serial Monitor.
6. The module halts the card and waits for the next scan.

---

## Usage

1. **Connect the hardware** according to the table above.
2. **Install the MFRC522 library** in Arduino IDE.
3. **Flash the code** to your ESP32-S3 N16R8.
4. **Open Serial Monitor** at 115200 baud.
5. Place the RFID card near the RC522 antenna and observe:

   * LED state changes.
   * Card UID and type printed on Serial Monitor.

---

## Example Serial Output

```
RC522 RFID LED Control Starting...
RC522 initialized. Scan your card...

Card detected!
UID: B3 0A F9 05
Card 1 detected: LED ON
----------------------------
Card detected!
UID: BD 25 73 06
Card 2 detected: LED OFF
----------------------------
```

---

## Notes / Tips

* **Capacitor (10–100µF)** across VCC and GND of RC522 module can stabilize readings.
* **Keep cards close to antenna** for reliable detection.
* Use **pin mapping compatible with your ESP32-S3**.
* Modify `card1UID` and `card2UID` in code to add more cards or change behavior.

---

## License

This project is released under the **MIT License** — free to use, modify, and share for educational purposes.

Do you want me to do that?
