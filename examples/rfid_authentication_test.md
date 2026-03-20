## 🧪 Example Test: RFID Authentication (`rfid_authentication_test`)

---

### 📌 Purpose

This test demonstrates how the system validates an RFID card using **UART interrupt-driven data reception** and basic verification logic before marking attendance.

---

### ⚙️ How It Works

- RFID reader sends **12-byte card ID** via UART  
- `uart0_handler()` interrupt stores data into `temp[]` buffer  
- Counter `i` tracks received bytes  
- Once 12 bytes are received → authentication is triggered  
- System decides:
  - ✅ Valid Card → Attendance marked  
  - ❌ Invalid Card → Access denied  

---

### 🔧 Core Flow (Integrated with Main System)

```c
// Check if RFID data received
if(i == 12)
{
    flag1 = 1;
    i = 0;
}

// Valid card
if(flag1 == 1)
{
    lcd_cmd(0x01);
    lcd_string("Employee Verified");

    lcd_cmd(0xC0);
    lcd_string("Attendance Marked");
}

// Invalid card
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
      temp[i++] = U0RBR;     // Store RFID data
   }

   VICVectAddr = 0;          // End of interrupt
}
```

---

### 🖥️ Output Behavior

| Scenario     | LCD Output        | System Action      |
| ------------ | ----------------- | ------------------ |
| Valid Card   | Employee Verified | Attendance Marked  |
|              | Attendance Marked | Data sent to Linux |
| Invalid Card | Invalid Card      | Access Denied      |
| Idle State   | Scan Your Card    | Waiting for input  |

---

### 🚀 Why This Example Matters

👉 This test represents the core logic of the entire system:

- Interrupt-driven RFID data handling
- Real-time authentication decision
- Seamless integration with LCD + UART logging
- Foundation for secure attendance systems
