# 📡 Automated Employee Attendance System using RFID

An embedded system project that automates employee attendance recording using RFID technology.

The system uses **RFID cards, dual microcontrollers, and real-time clock integration** to record employee attendance accurately and transmit data to a computer system.

---

## 🚀 Overview

Traditional attendance systems are manual, time-consuming, and prone to errors such as proxy attendance.

This project implements an **RFID-based automated attendance system** that records employee attendance quickly, securely, and efficiently.

Each employee is assigned a unique RFID card. When the card is scanned, the system records the employee ID along with the current date and time.

---

## 🧠 System Architecture

The system uses **two microcontrollers**:

| Microcontroller | Role |
|----------------|------|
| 8051 | RFID card reading |
| LPC2129 | Main system controller |

### Data Flow
```
RFID Card
↓
EM-18 RFID Reader
↓
8051 Microcontroller
↓ (UART)
LPC2129 Microcontroller
↓
RTC (I²C)
LCD (GPIO)
PC Linux Terminal (UART)
```

---

## ⚙ Hardware Components

- 8051 Microcontroller
- LPC2129 ARM7 Microcontroller
- EM-18 RFID Reader
- RFID Tags / Cards
- RTC Module
- 16×2 LCD Display
- Power Supply Circuit

---

## 💻 Software Tools

| Tool | Purpose |
|----|----|
| Keil µVision | Embedded C programming |
| Proteus | Circuit simulation |
| Embedded C | Firmware development |
| Linux Terminal | Attendance logging |

---

## 📁 Repository Structure
```
Automated Employee Attendance System using RFID Technology
│
├── docs/
│ ├── system_architecture.md
│ ├── hardware_setup.md
│ ├── working_principle.md
│ ├── software_design.md
│ └── communication_protocols.md
│
├── images/
│ ├── block_diagram.png
│ ├── flowchart.png
│ ├── project_hardware.png
│ ├── project_output.png
│ ├── proteus_simulation.jpg
│ └──system_flow.png
│
├── src/
│ ├── 
│ └── 
│
│
├── text_files/
│ ├── database
│ └── log_file
│
├── include/
│ └── header.h
│
│
│
├── simulation
│ └── proteus_design.pdsprj
│
│
│
│
└── README.md
```

---

## 🖥 System Workflow

1. System initializes all modules.
2. LCD prompts user to **scan RFID card**.
3. RFID reader detects employee card.
4. 8051 reads RFID ID.
5. ID is sent to LPC2129.
6. LPC2129 retrieves **current date and time from RTC**.
7. Attendance record is created.
8. LCD confirms attendance.
9. Data is sent to PC terminal and stored.

---

## 📷 Hardware Implementation


<p align="center">
  <img src="images/project_hardware.png" width="500">
</p>

> *Actual Automated Employee Attendance System using RFID.*

## 🔬 Simulation

The system was simulated using Proteus Design Suite to verify:

Serial communication

LCD interface

Microcontroller logic

Simulation files are included in the repository.

## 🎯 Key Features

✔ Contactless RFID attendance
✔ Real-time timestamp logging
✔ Dual microcontroller architecture
✔ LCD user interface
✔ UART-based PC logging
✔ Scalable for organizational use

## 📈 Future Enhancement

- Cloud-based attendance database
- WiFi or IoT integration
- Web dashboard for attendance monitoring
- Mobile app integration

## 👨‍💻 About Author

**Prashant kumar Gupta**                                                      
*Embedded Systems Learner | C/C++ Programmer | ARM & Linux Enthusiast*                                      
📧 Email: guptaprashant1012@gmail.com                                 
[LinkedIn](https://www.linkedin.com/in/prashant-embedded)                        
[GitHub](https://github.com/PrashantKumarGupta1)  

## 📝 License

This project is open-source and free to use for educational and learning purposes.
