## 🧪 Example Test: Attendance Logging (`attendance_logging_test`)

### 📌 Purpose

This test demonstrates end-to-end RFID-based attendance logging, where the embedded system sends timestamped data over UART and a Linux application processes it to generate structured CSV logs with IN/OUT tracking.

👉 It represents a **real-world embedded-to-Linux integration pipeline**.

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
Database Match
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

* First 12 characters → RFID ID  
* Remaining string → TIME + DATE  

---

### 🔧 Linux Processing Logic (Implementation Mapping)

#### 1️⃣ Read UART Data

```c
read(serial_port, &read_buf, sizeof(read_buf));
```

#### 2️⃣ Extract RFID ID

```c
for(i = 0; i < 12; i++)
    id[i] = read_buf[i];
id[i] = '\0';
```

#### 3️⃣ Extract Timestamp (TIME + DATE)

```c
for(j = 13; j < 30; j++)
    time[j - 13] = read_buf[j];
time[j - 13] = '\0';
```

#### 4️⃣ Split TIME and DATE

```c
sscanf(time, "%s %s", scan_time, scan_date);
```

---

### 🧠 Core Logic

#### ✅ Employee Verification

* Opens `database` file  
* Matches RFID using `strstr()`  
* Extracts employee name from matched record  

---

#### 🔁 IN / OUT Decision Logic

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
RFID_ID,NAME,TYPE,TIME,DATE
4900C8EC3855,PRASHANT,IN,09:15:22,01/12/2024
4900C8EC3855,PRASHANT,OUT,18:10:33,01/12/2024
```

---

### ⚠️ Special Case Handling

#### 🚫 New Card Registration (Disabled in Code)

```c
/*
if(f==0)
{
    printf("CARD NOT FOUND\n");
    printf("Enter employee name for this RFID\n");

    scanf("%s",name);

    FILE *file=fopen("database","a+");
    fprintf(file,"%s %s\n",id,name);
    fclose(file);

    FILE *log_file=fopen("attendance.csv","a+");
    fprintf(log_file,"%s,%s,IN,%s,%s\n",
            id,name,scan_time,scan_date);
    fclose(log_file);

    printf("New employee added successfully\n");
}
*/
```

👉 This block enables:

* New RFID registration  
* Auto database update  
* First attendance marked as **IN**  

(Currently disabled for controlled testing)

---

### 🖥️ Output Behavior

| Scenario       | Result                    |
| -------------- | ------------------------- |
| First Scan     | IN entry stored           |
| Second Scan    | OUT entry stored          |
| Valid Employee | Logged into CSV file      |
| Unknown Card   | Ignored (feature disabled)|

---

### 🚀 Why This Test is Important

This test validates:

* ✔ Embedded ↔ Linux UART communication  
* ✔ Real-time clock integration  
* ✔ Data parsing and formatting  
* ✔ File-based database handling  
* ✔ CSV-based structured logging  

👉 This is a **complete system-level validation**, not just a unit/module test.
