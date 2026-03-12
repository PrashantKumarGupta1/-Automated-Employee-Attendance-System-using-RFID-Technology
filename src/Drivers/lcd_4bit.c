/******************************************************************************
 LCD 16x2 Driver in 4-bit Mode
******************************************************************************/

#include <lpc21xx.h>          // Header file for LPC21xx microcontroller register definitions
#include "header.h"           // Project header file containing function prototypes and macros

// Function to send data (characters) to LCD
void lcd_data(unsigned char data)
{
    unsigned int temp;        // Temporary variable used to store shifted data bits

    IOCLR1 |= 0XFE<<16;       // Clear LCD data pins connected to Port1 (upper nibble)

    temp = (data & 0xf0) << 16;   // Extract upper 4 bits of data and shift to LCD data pin position
    IOSET1 = temp;                // Send upper nibble to LCD data pins

    IOSET1 = (1<<17);         // Set RS pin HIGH to indicate data register
    IOCLR1 = (1<<18);         // Clear RW pin (write operation)

    IOSET1 = (1<<19);         // Set Enable pin HIGH to latch data
    delay_ms(2);              // Small delay for LCD processing
    IOCLR1 = (1<<19);         // Clear Enable pin (falling edge triggers LCD write)



    IOCLR1 |= 0XFE<<16;       // Clear LCD data pins again before sending lower nibble

    temp = (data & 0x0f) << 20;   // Extract lower 4 bits and shift to correct LCD pin position
    IOSET1 = temp;                // Send lower nibble to LCD

    IOSET1 = (1<<17);         // RS HIGH again (data mode)
    IOCLR1 = (1<<18);         // RW LOW for write operation

    IOSET1 = (1<<19);         // Enable HIGH
    delay_ms(2);              // Delay for LCD execution
    IOCLR1 = (1<<19);         // Enable LOW to complete transfer
}



// Function to send command instructions to LCD
void lcd_cmd(unsigned char cmd)
{
    unsigned int temp;        // Temporary variable for bit manipulation

    IOCLR1 |= 0XFE<<16;       // Clear LCD data pins

    temp = (cmd & 0xf0) << 16;    // Extract upper nibble of command
    IOSET1 = temp;                // Send upper nibble to LCD


    IOCLR1 = (1<<17);         // RS LOW (command register selected)
    IOCLR1 = (1<<18);         // RW LOW (write mode)

    IOSET1 = (1<<19);         // Enable HIGH to latch command
    delay_ms(2);              // Small delay
    IOCLR1 = (1<<19);         // Enable LOW to complete write



    IOCLR1 |= 0XFE<<16;       // Clear data pins again

    temp = (cmd & 0x0f) << 20;    // Extract lower nibble of command
    IOSET1 = temp;                // Send lower nibble

    IOCLR1 = (1<<17);         // RS LOW (still command mode)
    IOCLR1 = (1<<18);         // RW LOW

    IOSET1 = (1<<19);         // Enable HIGH
    delay_ms(2);              // Delay for command processing
    IOCLR1 = (1<<19);         // Enable LOW to finish command
}



// Function to initialize LCD module
void lcd_init(void)
{
    PINSEL2 = 0;              // Configure Port1 pins as GPIO (not alternate function)
    IODIR1 |= 0XFE<<16;       // Set LCD control and data pins as OUTPUT
    lcd_cmd(0x02);            // Initialize LCD in 4-bit mode
    lcd_cmd(0x03);            // Initialization sequence step
    lcd_cmd(0x28);            // Set LCD to 4-bit mode, 2-line display, 5x7 font
    lcd_cmd(0x0E);            // Display ON, cursor ON
    lcd_cmd(0x01);            // Clear LCD display
}

// Function to display a string on LCD
void lcd_string(char *p)
{
    while(*p != 0)            // Loop until null character encountered
    {
        lcd_data(*p);         // Send each character to LCD
        p++;                  // Move pointer to next character
    }
}



/*
void lcd_int(int num)
{
    int arr[10],i=0;
    
    if(num==0)
    {
        lcd_data('0');
        return;
    }

    if(num<0)
    {
        lcd_data('-');
        num=-num;
    }

    i=0;

    while(num>0)
    {
        arr[i]=num%10;
        num=num/10;
        i++;
    }

    for(--i;i>=0;i--)
    {
        lcd_data(arr[i]+48);
    }
}
*/
