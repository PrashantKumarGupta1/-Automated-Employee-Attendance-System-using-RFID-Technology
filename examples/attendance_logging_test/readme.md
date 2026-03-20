## 🧪 Example Test: Attendance Logging (`attendance_logging_test`)

### 📌 Purpose

This test demonstrates end-to-end RFID-based attendance logging, where the embedded system sends timestamped data over UART and a Linux application processes it to generate structured CSV logs with IN/OUT tracking.

👉 It demonstrates a **real-world embedded-to-Linux integration pipeline**.

---

### ⚙️ What It Covers

* UART communication between microcontroller and Linux  
* RTC-based **timestamp generation (time + date)**  
* RFID-based **employee identification**  
* File-based **database lookup**  
* **IN / OUT decision logic (even/odd entry count)**  
* CSV file generation (`attendance.csv`)  

---

### 🔄 System Flow

```text
RFID Card Scan
      ↓
UART Interrupt (Microcontroller)
      ↓
RTC Timestamp Attached
      ↓
UART Data Sent to Linux
      ↓
Linux Serial Read
      ↓
ID Extraction + Time Parsing
      ↓
Database Match (Employee पहचान)
      ↓
IN / OUT Decision Logic
      ↓
CSV Log Entry (attendance.csv)
```

---

### 📡 Data Format (From Embedded System)

```text
123456789111 01:01:12 01/12/2024
```

* First 12 chars → RFID ID  
* Next → TIME + DATE (combined string)  

---

### 🔧 Linux Processing Logic (Your Code Behavior)

#### 1️⃣ Read UART Data

```c
read(serial_port, &read_buf, sizeof(read_buf));
```

#### 2️⃣ Extract RFID ID

```c
for(i = 0; i < 12; i++)
    id[i] = read_buf[i];
```

#### 3️⃣ Extract Timestamp

```c
for(j = 13; j < 30; j++)
    time[j - 13] = read_buf[j];
```

#### 4️⃣ Split TIME & DATE

```c
sscanf(time, "%s %s", only_time, only_date);
```

---

### 🧠 Core Logic

#### ✅ Employee Verification

* Reads from `database`  
* Matches RFID ID using `strstr()`  

#### 🔁 IN / OUT Decision

```c
if(c % 2 == 0)
    → IN
else
    → OUT
```

✔ Even count → IN  
✔ Odd count → OUT  

---

### 📁 CSV Output Format

File: `attendance.csv`

```csv
ID,NAME,STATUS,TIME,DATE
123456789111,PRASHANT,IN,10:30:15,12/05/24
123456789111,PRASHANT,OUT,06:15:42,12/05/24
```

---

### ⚠️ Special Case Handling

#### 🚫 New Card (Currently Disabled in Code)

```c
/*
if(f == 0)
{
    // Add new employee to database
    // Mark first entry as IN
}
*/
```

👉 This block allows:

* Adding new RFID users  
* Auto-registering them into database  
* Logging first attendance  

(Currently commented for controlled testing)

---

### 🖥️ Output Behavior

| Scenario       | Result                    |
| -------------- | ------------------------- |
| First Scan     | IN marked                 |
| Second Scan    | OUT marked                |
| Valid Employee | Logged in CSV             |
| Unknown Card   | Ignored (or optional add) |

---

### 🚀 Why This Test is Important

This example proves:

* ✔ Embedded ↔ Linux communication  
* ✔ Real-time clock integration  
* ✔ File-based database handling  
* ✔ Practical attendance logic  
* ✔ Industry-style logging (CSV format)  

👉 This is a **complete system-level validation**, not just a module test.
