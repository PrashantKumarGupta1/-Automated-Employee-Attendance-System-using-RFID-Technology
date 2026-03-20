## 🧪 Example Test: RFID Authentication (`rfid_authentication_test`)

---

### 📌 Purpose

This test demonstrates how the system validates an RFID card using **UART interrupt-driven data reception** before triggering attendance marking.

👉 It represents the **real-time authentication layer** of the system.

---

### ⚙️ What It Covers

* UART interrupt-based RFID data reception  
* Buffer-based data storage (`temp[]`)  
* Byte-count based **data validation (12-byte RFID)**  
* **Real-time authentication decision**  
* LCD feedback for user interaction  

---

### 🔄 System Flow

```text
RFID Card Scan
      ↓
UART RX Interrupt Triggered
      ↓
Data Stored in Buffer (temp[])
      ↓
Byte Count Reaches 12
      ↓
Authentication Decision
      ↓
Valid → Attendance Process
Invalid → Access Denied
```

---

### 📡 RFID Data Format

```text
123456789111
```

* Fixed length → 12 characters  
* Stored in buffer via interrupt  

---

### 🔧 Authentication Logic (Main Loop)

#### 1️⃣ Check Data Reception

```c
if(i == 12)
{
    flag1 = 1;   // RFID received
    i = 0;       // Reset counter
}
```

---

#### 2️⃣ Valid Card Handling

```c
if(flag1 == 1)
{
    lcd_cmd(0x01);
    lcd_string("Employee Verified");

    lcd_cmd(0xC0);
    lcd_string("Attendance Marked");
}
```

---

#### 3️⃣ Invalid Card Handling

```c
if(flag1 == -1)
{
    lcd_cmd(0x01);
    lcd_string("Invalid Card");

    lcd_cmd(0xC0);
    lcd_string("Access Denied");
}
```

---

### 🔌 Interrupt-Based Data Capture

```c
void uart0_handler(void) __irq
{
   int t = U0IIR;

   if(t & 4)                 // RX interrupt
   {
      temp[i++] = U0RBR;     // Store incoming RFID byte
   }

   VICVectAddr = 0;          // End of interrupt
}
```

---

### 🧠 Core Logic

#### ✅ Data Reception

* UART interrupt triggers on incoming data  
* Each byte stored in `temp[]`  
* Counter `i` tracks received bytes  

---

#### 🔁 Authentication Decision

```c
if(i == 12)
    → Process RFID
```

✔ Ensures **complete RFID data received**  
✔ Prevents partial/invalid reads  

---

### 🖥️ Output Behavior

| Scenario     | LCD Output         | System Action      |
| ------------ | ----------------- | ------------------ |
| Valid Card   | Employee Verified | Attendance Trigger |
|              | Attendance Marked | Data sent to Linux |
| Invalid Card | Invalid Card      | Access Denied      |
| Idle State   | Scan Your Card    | Waiting for input  |

---

### 🚀 Why This Test is Important

This test validates:

* ✔ Interrupt-driven UART communication  
* ✔ Real-time RFID data capture  
* ✔ Reliable authentication mechanism  
* ✔ User feedback via LCD display  

👉 This is the **foundation layer** of the attendance system — ensuring only valid RFID data is processed further.
