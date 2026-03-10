# 💻 Software Design

## Overview

The software for the RFID attendance system is developed using **Embedded C** and compiled using **Keil µVision IDE**.

The project uses **two separate firmware programs**:

- 8051 firmware for RFID card reading
- LPC2129 firmware for attendance processing

---

# Development Tools

| Tool | Purpose |
|-----|--------|
| Keil µVision | Embedded code compilation |
| Embedded C | Programming language |
| Proteus | Hardware simulation |
| Linux Terminal | Attendance data storage |

---

# Software Modules

---

# 1️⃣ RFID Reader Module (8051)

The 8051 program handles RFID card detection.

Functions:

- Receive serial data from EM-18
- Extract RFID tag ID
- Forward tag ID to LPC2129 via UART

Pseudo logic:
```
Wait for RFID card
Read tag ID
Send tag ID to LPC2129
```

---

# 3️⃣ RTC Communication Module

The LPC2129 communicates with the RTC module using the **I²C protocol**.

The RTC provides:

- Date
- Time

Used to create timestamped attendance records.

---

# 4️⃣ LCD Display Module

The LCD display shows system status messages.

Typical messages include:
```
SCAN YOUR ID
Attendance Recorded
Invalid Card
```

The LCD operates in **4-bit GPIO mode**.

---

# 5️⃣ Attendance Logging Module

Once a card is verified:

1. LPC2129 retrieves date and time
2. Attendance record is created
3. Data is sent to Linux terminal

Example output:
```
Employee ID : 105
Date : 12/04/2025
Time : 09:02 AM
```

---

# Software Flowchart

<p align="center">
  <img src="../images/system_flow.png" width="500">
</p>

> *Actual flow of the Automated Employee Attendance System using RFID Technology.*
---

# Simulation

Before hardware implementation, the system was tested using **Proteus simulation**.

Simulation verifies:

- Serial communication
- LCD display output
- Microcontroller logic

Simulation files are included in the repository.
