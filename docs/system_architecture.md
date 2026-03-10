# 🏗 System Architecture

## Overview

The **Automated Employee Attendance System using RFID Technology** is an embedded system designed to automatically record employee attendance using RFID identification.

The system uses **two microcontrollers**:

- **8051 Microcontroller** – dedicated for RFID card reading
- **LPC2129 Microcontroller** – main controller responsible for processing, time logging, display control, and communication with the PC.

This modular architecture improves reliability and distributes tasks efficiently across the system.

---

## System Architecture Layers

The system is organized into multiple functional layers.

---

### 1️⃣ Identification Layer

This layer is responsible for detecting employee RFID cards.

Components:

- RFID Tags (Employee Cards)
- EM-18 RFID Reader

When a card is placed near the reader, the EM-18 extracts the **unique 12-digit identification number** stored in the RFID tag.

---

### 2️⃣ Card Reading Controller (8051 Microcontroller)

The **8051 microcontroller is dedicated only for RFID card reading**.

Responsibilities:

- Receive RFID ID from EM-18 reader
- Validate received data format
- Forward RFID ID to LPC2129 via UART communication

Using a separate controller for RFID reading simplifies system design and improves modularity.

---

### 3️⃣ Main Processing Controller (LPC2129)

The **LPC2129 microcontroller acts as the main processing unit** of the system.

Its responsibilities include:

- Receiving RFID ID from the 8051
- Communicating with RTC module
- Controlling LCD display
- Processing attendance records
- Sending attendance data to a PC

---

### 4️⃣ Time Management Layer

A **Real-Time Clock (RTC) module** is connected to the LPC2129 via **I²C communication**.

The RTC provides:

- Current date
- Current time

This ensures accurate **timestamp logging** for every attendance record.

---

### 5️⃣ User Interface Layer

The system provides user feedback using a **16×2 LCD display**.

The LCD shows messages such as:
```
SCAN YOUR ID
Attendance Recorded
Invalid Card
```

The LCD is controlled through **GPIO pins of LPC2129** using 4-bit communication mode.

---

### 6️⃣ Data Communication Layer

Attendance data is transmitted to a **Linux PC terminal** via UART communication.

The PC receives attendance records and stores them in a **database or text file** for report generation and analysis.

---

## Architecture Flow

**RFID Card → EM-18 RFID Reader → 8052 Microcontroller (UID Capture & Verification) → LPC2129 Microcontroller → RTC Timestamp → LCD Display & Buzzer → Data Sent to PC → Linux Attendance Logging**

---

## Key Features

- Contactless attendance recording
- Automatic timestamp generation
- Real-time user feedback
- Reliable data logging

---

## Advantages of the Architecture

- Modular embedded system design
- Dedicated RFID card reading controller
- Accurate time logging using RTC
- Real-time attendance transmission
- Scalable system for organizational use
