# 🔌 Communication Protocols

## Overview

The Automated Employee Attendance System uses multiple communication protocols to enable reliable data exchange between different hardware components.

The primary protocols used in the system are:

- UART (Universal Asynchronous Receiver Transmitter)
- I²C (Inter-Integrated Circuit)
- GPIO (General Purpose Input Output)

Each protocol is selected based on the specific requirements of the connected devices.

---

# 1️⃣ UART Communication

UART is used for **serial communication between microcontrollers and external devices**.

In this project, UART is used in two places.

## 1. 8051 → LPC2129 Communication

The **8051 microcontroller reads RFID card IDs** from the EM-18 reader and sends them to the LPC2129 via UART.

### Data Flow
```
EM-18 RFID Reader
↓
8051 MCU
↓ (UART)
LPC2129 MCU
```

### Configuration

| Parameter | Value |
|----------|------|
| Baud Rate | 9600 bps |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |

---

## 2. LPC2129 → PC Communication

A second UART channel is used to send attendance data to a **Linux terminal on a connected PC**.

### Data Format Example
```
Employee ID : 1032
Date : 12/04/2025
Time : 09:05 AM
```

The Linux program receives this serial data and stores it in a **database or text file** for attendance reporting.

---

# 2️⃣ I²C Communication

I²C (Inter-Integrated Circuit) is a **two-wire communication protocol** used for communication between the LPC2129 microcontroller and the RTC module.

### I²C Lines

| Signal | Function |
|------|---------|
| SDA | Serial Data Line |
| SCL | Serial Clock Line |

### Device Roles

| Device | Role |
|------|------|
| LPC2129 | Master |
| RTC Module | Slave |

### Purpose

The RTC provides:

- Current Date
- Current Time

This ensures accurate **timestamp recording for each attendance entry**.

---

## 3️⃣ GPIO Interface

GPIO pins of the LPC2129 are used to control peripheral devices such as the LCD display, buzzer, and LED indicators.

### 📟 LCD Interface

The **16×2 LCD** operates in **4-bit mode** to reduce the number of required pins.

| LCD Pin | Function |
|-------|--------|
| RS | Register Select |
| EN | Enable |
| D4–D7 | Data Pins |

---

### 📺 LCD Messages

Example messages displayed:
```
SCAN YOUR ID
Attendance Recorded
Invalid Card
```

---

# 🔌Summary of Communication Interfaces


| Interface | Devices Connected | Purpose |
|-----------|------------|---------|
| **[UART](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)** | 8051 ↔ LPC2129 | RFID data transfer |
| UART | LPC2129 ↔ PC | Attendance data logging |
| **[I²C](https://en.wikipedia.org/wiki/I%C2%B2C)** | LPC2129 ↔ RTC | Time and date retrieval |
| **[GPIO](https://en.wikipedia.org/wiki/General-purpose_input/output)** | LPC2129 ↔ LCD | User display interface |

---

# Advantages of the Communication Design

- Reliable serial communication
- Minimal wiring using I²C
- Efficient display control using GPIO
- Real-time data transfer to PC
