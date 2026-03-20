# 📡 Automated Employee Attendance System using RFID

An embedded system project that automates employee attendance recording using RFID technology.

---

## 🚀 Overview

Traditional attendance systems are manual, time-consuming, and prone to errors such as proxy attendance.

This project implements an **RFID-based automated attendance system** that records employee attendance quickly, securely, and efficiently.

The system uses **RFID cards 🪪, dual microcontrollers, and real-time clock integration** to record employee attendance accurately and transmit data to a computer system.

Each employee is assigned a unique RFID card. When the card is scanned, the system records the employee ID along with the current date and time.

---

## 🔧 Features

- RFID Card based authentication
- Real-time clock integration using DS1307
- UART communication with Linux PC
- LCD display for real-time feedback
- Automatic attendance logging
- Interrupt-based RFID reception
- I2C communication with RTC module

---

## 🧠 System Architecture

The system uses **two microcontrollers**:

| Microcontroller | Role |
|----------------|------|
| **[8051](https://en.wikipedia.org/wiki/8051)** | RFID card reading |
| **[LPC2129 ARM7](https://www.nxp.com/products/LPC2129)** | Main system controller |

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

- **[8051 Microcontroller](https://en.wikipedia.org/wiki/8051)**  
- **[LPC2129 ARM7 Microcontroller](https://www.nxp.com/products/LPC2129)**  
- **[EM-18 RFID Reader](https://components101.com/modules/em18-rfid-reader-module)**  
- **[RFID Tags / Cards](https://www.rfidjournal.com/what-is-rfid)**  
- **[RTC Module (DS1307)](https://www.analog.com/en/products/ds1307.html)**  
- **[16×2 LCD Display](https://components101.com/displays/16x2-lcd-pinout-datasheet)**  
- **[Power Supply Circuit](https://en.wikipedia.org/wiki/Power_supply)**  

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
│ ├── linux_system.md
│ └── communication_protocols.md
│
├── images/
│ ├── block_diagram.png
│ ├── flowchart.png
│ ├── project_hardware.png
│ ├── project_output.png
│ ├── proteus_simulation.jpg
│ └── system_flow.png
│
├── src/
│ ├── Drivers/
│ │         ├── delay.c
│ │         ├── i2c_driver.c
│ │         ├── intr.c
│ │         ├── lcd_4bit.c
│ │         └── uart0.c
│ │
│ ├── linux.c
│ └── main.c
│
├── linux_code/
│ └── rfid_logger.c
│
├── log_file/
│ ├── database
│ └── attendance.csv
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

- Serial communication
- LCD interface
- Microcontroller logic

Simulation are included in the repository.
[View Simulation Diagram](images/proteus_simulation.jpg)

## 🎯 Key Features

- Contactless RFID attendance
- Real-time timestamp logging
- Dual microcontroller architecture
- LCD user interface
- UART-based PC logging
- Scalable for organizational use

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
