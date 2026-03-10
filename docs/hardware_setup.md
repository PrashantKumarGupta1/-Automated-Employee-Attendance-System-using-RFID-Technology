# 🔧 Hardware Setup

## Overview

The Automated RFID Attendance System consists of several hardware components that work together to detect RFID cards and record attendance automatically.

The system is built using the **8051 microcontroller development board (Redolabz)**.

---

## Hardware Components

| Component | Description |
|----------|-------------|
| 8051 Microcontroller | Main controller of the system |
| RFID Reader Module | Reads RFID card UID |
| RFID Tags | Unique employee identification cards |
| RTC Module | Provides real-time date and time |
| 16x2 LCD Display | Displays attendance messages |
| Buzzer | Provides audio feedback |
| Power Supply | Provides operating voltage |

---

## 1️⃣ Microcontroller Board

The **8051 microcontroller** acts as the central controller.

Functions:

- Reads RFID data
- Processes employee ID
- Controls LCD display
- Records attendance
- Activates buzzer

Development board used:

**Redolabz 8051 Development Board**

---

## 2️⃣ RFID Reader

The RFID reader detects RFID tags and reads their unique identification number.

Features:

- Contactless reading
- Fast scanning
- Unique ID detection

Connection type:

- Serial communication (UART)

---

## 3️⃣ RFID Cards (Employee Tags)

Each employee is assigned a **unique RFID card**.

When the card is scanned:

1. RFID reader detects UID
2. Microcontroller receives UID
3. System verifies the employee

---

## 4️⃣ Real Time Clock (RTC)

The RTC module keeps track of real-time date and time.

Functions:

- Provides timestamp for attendance
- Maintains accurate time even when system restarts

Example:
```
Date: 12/04/2025
Time: 09:02 AM
```

---

## 5️⃣ LCD Display

A **16x2 LCD display** is used to provide user feedback.

Example messages:
```
Scan Your Card

Employee Verified
Attendance Marked

Invalid Card
Access Denied
```

---

## 6️⃣ Buzzer

The buzzer provides audio feedback.

Usage:

| Event | Buzzer Action |
|------|---------------|
| Valid card | Short beep |
| Invalid card | Long beep |

---

## Power Supply

The system requires a **stable regulated power supply**.

Typical configuration:
```
5V regulated supply → Microcontroller
5V → RFID reader
5V → LCD display
```

---

## Hardware Implementation

Below is the real hardware implementation of the project.
<p align="center">
  <img src="../images/project_hardware.jpeg" width="500">
</p>

This image shows the complete hardware setup of the RFID attendance system.
