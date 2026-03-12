/******************************************************************************
 * File Name : main.c
 * Description : RFID Attendance System with RTC
 ******************************************************************************/

#include "header.h"                 // Include header file containing declarations

extern int i;                      // UART interrupt counter (counts received RFID bytes)
unsigned char temp[100];           // Buffer storing RFID data received from reader

int main()
{

    unsigned char empl[100];       // Buffer to store attendance data sent to PC
    int flag1 = 0, j;              // flag1 indicates RFID received
    int index;                     // Stores day index from RTC
    int flag, k;                   // flag used for AM/PM detection
    unsigned char h, m, s, t;      // Variables for hour, minute, second and formatted hour
    unsigned char date, month, year; // Variables storing date from RTC

    i2c_init();                    // Initialize I2C communication (for RTC)
    lcd_init();                    // Initialize LCD display
    uart0_init(9600);              // Initialize UART0 with baud rate 9600

    config_vic();                  // Configure interrupt controller
    en_uart0_intr();               // Enable UART0 interrupt for RFID reception

    uart0_tx_string("DS1307 RTC\r\n"); // Send startup message to PC terminal

    lcd_cmd(0x01);                 // Clear LCD
    lcd_string("Scan Your Card");  // Initial LCD message

    // RTC initialization (set time/date)
    i2c_byte_write_frame(0XD0,0X2,0X52); // Hour
    i2c_byte_write_frame(0XD0,0X1,0X40); // Minute
    i2c_byte_write_frame(0XD0,0X0,0X00); // Second
    i2c_byte_write_frame(0XD0,0X4,0X12); // Date
    i2c_byte_write_frame(0XD0,0X5,0X05); // Month
    i2c_byte_write_frame(0XD0,0X6,0X24); // Year
    i2c_byte_write_frame(0XD0,0X3,0X01); // Day index

    while(1)                       // Infinite loop
    {

        lcd_cmd(0x80);             // Move LCD cursor to first row

        // Read time from RTC
        h = i2c_byte_read_frame(0XD0,0X02);
        m = i2c_byte_read_frame(0XD0,0X01);
        s = i2c_byte_read_frame(0XD0,0X00);

        // Read date from RTC
        date  = i2c_byte_read_frame(0XD0,0X04);
        month = i2c_byte_read_frame(0XD0,0X05);
        year  = i2c_byte_read_frame(0XD0,0X06);

        index = i2c_byte_read_frame(0XD0,0X03); // Day index

        t = (h & 0x1f);            // Extract hour value

        // Check AM / PM
        if((h>>5)&1)
            flag = 1;              // PM
        else
            flag = 0;              // AM

        // Display time
        lcd_data(t/16+48);
        lcd_data(t%16+48);
        lcd_data(':');
        lcd_data(m/16+48);
        lcd_data(m%16+48);
        lcd_data(':');
        lcd_data(s/16+48);
        lcd_data(s%16+48);

        if(flag==1)
            lcd_string(" PM");
        else
            lcd_string(" AM");

        lcd_cmd(0xC0);             // Move cursor to second row

        // Display date
        lcd_data(date/16+48);
        lcd_data(date%16+48);
        lcd_data('/');

        lcd_data(month/16+48);
        lcd_data(month%16+48);
        lcd_data('/');

        lcd_data(year/16+48);
        lcd_data(year%16+48);

        lcd_cmd(0xcf-3);           // Cursor position for day

        // Display day
        if(index==1) lcd_string("SUN");
        if(index==2) lcd_string("MON");
        if(index==3) lcd_string("TUE");
        if(index==4) lcd_string("WED");
        if(index==5) lcd_string("THU");
        if(index==6) lcd_string("FRI");
        if(index==7) lcd_string("SAT");

        // Check if RFID data received
        if(i==12)
        {
            flag1 = 1;             // RFID detected
            i = 0;                 // Reset counter
        }

        // When card scanned
        if(flag1==1)
        {

            lcd_cmd(0x01);                 // Clear LCD
            lcd_string("Employee Verified");// Show verification message

            lcd_cmd(0xC0);                 // Move to second row
            lcd_string("Attendance Marked");// Show attendance confirmation

            // Copy RFID data to attendance buffer
            for(j=0,k=0;temp[k];k++)
                empl[j++] = temp[k];

            empl[j++]=' ';

            // Add time
            empl[j++]=t/16+48;
            empl[j++]=t%16+48;
            empl[j++]=':';
            empl[j++]=m/16+48;
            empl[j++]=m%16+48;
            empl[j++]=':';
            empl[j++]=s/16+48;
            empl[j++]=s%16+48;

            empl[j++]=' ';

            // Add date
            empl[j++]=date/16+48;
            empl[j++]=date%16+48;
            empl[j++]='/';
            empl[j++]=month/16+48;
            empl[j++]=month%16+48;
            empl[j++]='/';
            empl[j++]=year/16+48;
            empl[j++]=year%16+48;

            empl[j++]='\r';
            empl[j++]='\n';
            empl[j]='\0';

            uart0_tx_string(empl);   // Send attendance record to PC

            delay_ms(2000);          // Wait so user can read message

            lcd_cmd(0x01);           // Clear LCD
            lcd_string("Scan Your Card"); // Ready for next scan

            flag1=0;                 // Reset flag
        }

        // If external logic reports invalid card
        if(flag1==-1)
        {
            lcd_cmd(0x01);           // Clear LCD
            lcd_string("Invalid Card");

            lcd_cmd(0xC0);           // Second line
            lcd_string("Access Denied");

            delay_ms(2000);

            lcd_cmd(0x01);
            lcd_string("Scan Your Card");

            flag1=0;
        }

    }

}
