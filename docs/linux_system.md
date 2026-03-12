# 🐧 Linux System Documentation

### RFID Attendance System

---

## 📌 Overview

The Linux application receives RFID attendance data from the embedded hardware through **UART serial communication**.
It processes the data, verifies employee details from the database, and logs **IN/OUT attendance records**.

The program is written in **C language** and runs on a **Linux operating system**.

---

## 🎯 Objectives

The Linux system performs the following tasks:

*  Receive RFID data from microcontroller
*  Extract RFID ID and timestamp
*  Verify employee in database
*  Record attendance (**IN / OUT**)
*  Store records in log file

---

## 🖥 System Requirements

### 🔧 Hardware

* Linux PC / Laptop
* USB-to-UART Converter
* RFID Embedded System

### 💻 Software

* Linux OS (**Ubuntu / Debian recommended**)
* GCC Compiler

### 📚 Libraries Used

| Library     | Purpose                            |
| ----------- | ---------------------------------- |
| `stdio.h`   | Input / Output operations          |
| `string.h`  | String processing                  |
| `fcntl.h`   | File control                       |
| `errno.h`   | Error handling                     |
| `termios.h` | Serial communication configuration |
| `unistd.h`  | System calls like read/write       |

---

## 🔌 Serial Communication

The embedded system sends attendance data through **UART communication**.

### Serial Device Used

```bash
/dev/ttyUSB0
```

### Serial Configuration

| Parameter    | Value    |
| ------------ | -------- |
| Baud Rate    | 9600     |
| Data Bits    | 8        |
| Stop Bits    | 1        |
| Parity       | None     |
| Flow Control | Disabled |

---

## 📡 Data Format

Data received from the embedded system:

```
RFID_ID TIME DATE
```

### Example

```
123456789111 09:15:22 01/12/2024
```

### Data Fields

| Field   | Description        |
| ------- | ------------------ |
| RFID_ID | Unique card number |
| TIME    | Scan time          |
| DATE    | Scan date          |

---

## ⚙ Program Working

The Linux program follows these steps:

1️. Open serial port `/dev/ttyUSB0`                          
2️. Configure UART settings                              
3️. Read data from embedded system                          
4️. Extract **RFID ID** and **Time/Date**                                  
5️. Search employee in database                       
6️. Log attendance record                  
7️. Repeat continuously                          

---

## 📂 Database File

Employee information is stored in a below file:


[Database](../log_file/database)


### Example Database

```
4900C8EC3855 PRASHANT
4900C86CE30E GANESH
```

The system checks whether the scanned RFID card exists in this database.

---

## 📝 Log File

Attendance records are stored in:

```
attendance.csv
```

### Example Entry

```
RFID_ID,NAME,TYPE,TIME,DATE
123456789111,PRASHANT,IN,09:15:22,01/12/2024
123456789111,PRASHANT,OUT,18:10:33,01/12/2024
```

This file can be opened directly in:

* 📊 Microsoft Excel
* 📊 LibreOffice Calc
* 📊 Google Sheets

---

## ⏱ IN / OUT Logic

The system automatically determines attendance type:

| Condition        | Result   |
| ---------------- | -------- |
| Even occurrences | IN Time  |
| Odd occurrences  | OUT Time |

This helps track employee **entry and exit times**.

---

## 🔄 Continuous Monitoring

The program runs in an infinite loop:

```
while(1)
```

This allows the system to **continuously monitor RFID scans**.

---

## ⚠ Error Handling

The program handles common errors such as:

* ❌ Serial port opening failure
* ❌ Serial data reading errors

Error messages are printed using:

```
printf()
strerror()
```

---

## ▶ Program Execution

### Compile the Program

```
gcc rfid_logger.c -o rfid_logger
```

### Run the Program

```
./rfid_logger
```

---

## ✅ Advantages

* Real-time attendance monitoring
* Low-cost hardware implementation
* Easy Linux integration
* Simple database management
* Exportable attendance records

---

## 📌 Conclusion

The Linux system acts as the **data processing and logging unit** of the RFID Attendance System.

It receives RFID data from the embedded hardware, verifies employee records from the database, and stores **accurate attendance logs automatically**.
