// Step 1: RFID reader sends 12-byte data via UART
// Example: "123456789111"


// Step 2: UART interrupt triggers on receiving data
void uart0_handler(void) __irq
{
   int t = U0IIR;

   if(t & 4)                     // RX interrupt (data received)
   {
      temp[i++] = U0RBR;         // Store each byte into buffer
   }

   VICVectAddr = 0;              // End of interrupt
}


// Step 3: Check if complete RFID data received (12 bytes)
if(i == 12)
{
    flag1 = 1;                   // Mark RFID received successfully
    i = 0;                       // Reset counter for next scan
}


// Step 4: Process VALID RFID card
if(flag1 == 1)
{
    lcd_cmd(0x01);               // Clear LCD

    lcd_string("Employee Verified");   // Show verification message

    lcd_cmd(0xC0);               // Move to second line

    lcd_string("Attendance Marked");   // Confirm attendance trigger
}


// Step 5: Process INVALID RFID card
if(flag1 == -1)
{
    lcd_cmd(0x01);               // Clear LCD

    lcd_string("Invalid Card");  // Show error

    lcd_cmd(0xC0);               // Second line

    lcd_string("Access Denied"); // Deny access
   
// Step 6: (System Idle State)
    delay_ms(2000);             // Waiting for next RFID scan
   
    lcd_cmd(0x01);
   
    lcd_string("Scan Your Card");

   flag1=0;
}
