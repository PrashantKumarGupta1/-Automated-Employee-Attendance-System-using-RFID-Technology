# 🐧 Linux System Documentation
**RFID Attendance System**

## 📌 Overview
The Linux application receives RFID attendance data from the embedded hardware through **UART serial communication**.  
It processes the data, verifies employee details from the database, and logs **IN/OUT attendance records**.

The program is written in **C language** and runs on a **Linux operating system**.

---

## 🎯 Objectives
The Linux system performs the following tasks:

✔ Receive RFID data from microcontroller  
✔ Extract RFID ID and timestamp  
✔ Verify employee in database  
✔ Record attendance (IN / OUT)  
✔ Store records in log file  

---

## 🖥 System Requirements

### Hardware
🔹 Linux PC / Laptop  
🔹 USB-to-UART converter  
🔹 RFID embedded system  

### Software
🔹 Linux OS (Ubuntu / Debian recommended)  
🔹 GCC Compiler  

### Libraries Used
- stdio.h
- string.h
- fcntl.h
- errno.h
- termios.h
- unistd.h

---

## 🔌 Serial Communication

The embedded system sends attendance data through **UART**.

Device used in Linux:
```
/dev/ttyUSB0
```

### Serial Configuration

| Parameter | Value |
|-----------|-------|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | Disabled |

---

## 📡 Data Format

Data received from the embedded system:
```
RFID_ID TIME DATE
```

Example:
```
123456789111 09:15:22 01/12/2024
```

### Data Fields

| Field | Description |
|------|-------------|
| RFID_ID | Unique card number |
| TIME | Scan time |
| DATE | Scan date |

---

# ⚙ Program Working

The Linux program follows these steps:

1️⃣ Open serial port `/dev/ttyUSB0`  
2️⃣ Configure UART settings  
3️⃣ Read data from embedded system  
4️⃣ Extract **RFID ID** and **time/date**  
5️⃣ Search employee in database  
6️⃣ Log attendance record  
7️⃣ Repeat continuously  

---

# 📂 Database File

Employee information is stored in:
```
database
```

Example:
```
123456789111 PRASHANT
987654321234 RAHUL
```

The program checks whether the scanned RFID ID exists in this file.

---

# 📝 Log File

Attendance records are stored in:
```
log_file
```

Example entry:
```
ID=123456789111 NAME=PRASHANT IN-TIME 09:15:22 01/12/2024
```

---

# ⏱ IN / OUT Logic

The system automatically determines attendance type.

✔ Even occurrences → **IN Time**  
✔ Odd occurrences → **OUT Time**

This helps track employee entry and exit.

---

# 🔄 Continuous Monitoring

The program runs in an infinite loop:
```
while(1)
```

This allows the system to **continuously monitor RFID scans**.

---

# ⚠ Error Handling

The program checks for:

❌ Serial port opening errors  
❌ Data read errors  

Error messages are printed using `printf()` and `strerror()`.

---

# ▶ Program Execution

Compile program:
```
gcc rfid_logger.c -o rfid_logger
```

Run program:
```
./rfid_logger
```

---

# ✅ Advantages

✔ Real-time attendance monitoring  
✔ Simple database system  
✔ Low hardware cost  
✔ Easy integration with embedded systems  

---

# 📌 Conclusion

The Linux system acts as the **data processing and logging unit** of the RFID Attendance System.

It receives RFID data from the embedded hardware, verifies employees, and stores accurate attendance records automatically.
