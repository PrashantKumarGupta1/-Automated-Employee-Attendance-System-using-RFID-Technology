/******************************************************************************
 I2C Driver for DS1307 RTC
******************************************************************************/

#include "header.h"                 // Include project header file containing typedefs, prototypes and macros
#define SI ((I2CONSET>>3)&1)        // Macro to check SI (Serial Interrupt) flag bit from I2C control register

// Function to initialize I2C peripheral
void i2c_init(void)
{
 PINSEL0 |=0x50;                   // Configure P0.2 and P0.3 as SDA and SCL pins for I2C function
 I2SCLH=75;                        // Set I2C clock HIGH time (controls I2C clock frequency)
 I2SCLL=75;                        // Set I2C clock LOW time
 I2CONSET=(1<<6);                  // Enable I2C interface by setting I2EN bit
}

// Function to write a byte to I2C device
void  i2c_byte_write_frame(u8 sa,u8 mr,u8 data)
{
 I2CONSET=(1<<5);                  // Generate START condition
 I2CONCLR=(1<<3);                  // Clear SI flag to start operation
 while(SI==0);                     // Wait until SI flag becomes 1 (operation completed)
 I2CONCLR=(1<<5);                  // Clear START bit
 if(I2STAT !=0X08)                 // Check if START condition transmitted successfully
   {
    uart0_tx_string("err:start condition in write\r\n"); // Send error message if start fails
    goto exit;                     // Jump to exit label
   }
  I2DAT=sa;                        // Load slave address + write bit into I2C data register
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait until transmission completes
   if(I2STAT==0X20)                // Check if slave did not acknowledge address
   {
    uart0_tx_string("err:sa+w in write \r\n"); // Send error message
    goto exit;                     // Jump to exit
   }
    I2DAT=mr;                      // Send memory/register address inside slave device
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait for completion
   if(I2STAT==0X30)                // Check if memory address not acknowledged
   {
    uart0_tx_string("err:memory addr in write\r\n"); // Send error message
    goto exit;                     // Jump to exit
   }
   I2DAT=data;                     // Send actual data byte to slave device
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait for transmission complete
   if(I2STAT==0X30)                // Check if data not acknowledged
   {
    uart0_tx_string("err:data in write\r\n"); // Send error message
    goto exit;                     // Jump to exit
   }   
    exit:                          // Exit label for error handling
     I2CONSET=(1<<4);              // Generate STOP condition
     I2CONCLR=(1<<3);              // Clear SI flag
}

// Function to read a byte from I2C device
unsigned char i2c_byte_read_frame(u8 sa,u8 mr)
{
 unsigned char temp;               // Variable to store received data
   I2CONSET=(1<<5);                // Generate START condition
 I2CONCLR=(1<<3);                  // Clear SI flag
 while(SI==0);                     // Wait until START transmitted
 I2CONCLR=(1<<5);                  // Clear START bit
 if(I2STAT !=0X08)                 // Verify START condition transmitted
   {
    uart0_tx_string("err:start condition in read\r\n"); // Error message
    goto exit;                     // Jump to exit
   }
  I2DAT=sa;                        // Send slave address with write bit
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait for completion
   if(I2STAT==0X20)                // Check if slave did not acknowledge
   {
    uart0_tx_string("err:sa+w in read\r\n"); // Error message
    goto exit;
   }
    I2DAT=mr;                      // Send memory/register address
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait for completion
   if(I2STAT==0X30)                // Check if address not acknowledged
   {
    uart0_tx_string("err:memory addr in  read\r\n"); // Error message
    goto exit;
   }
   I2CONSET=(1<<5);                // Generate RESTART condition
 I2CONCLR=(1<<3);                  // Clear SI flag
 while(SI==0);                     // Wait for restart completion
 I2CONCLR=(1<<5);                  // Clear START bit
 if(I2STAT !=0X10)                 // Verify restart transmitted
   {
    uart0_tx_string("err:restart condition in read\r\n"); // Error message
    goto exit;
   }
     I2DAT=sa | 1;                 // Send slave address with READ bit
  I2CONCLR=(1<<3);                 // Clear SI flag
  while(SI==0);                    // Wait for response
   if(I2STAT==0X48)                // Check if slave not acknowledged
   {
    uart0_tx_string("err:sa+r in read \r\n"); // Error message
    goto exit;
   }
   I2CONCLR=(1<<3);                // Clear SI flag to receive data
   while(SI==0);                   // Wait until data received
   temp=I2DAT;                     // Read received byte from I2C data register
   exit:                           // Exit label
    I2CONSET=(1<<4);               // Generate STOP condition
    I2CONCLR=(1<<3);               // Clear SI flag
    return temp;                   // Return received data
}

// Function to convert decimal number to hexadecimal ASCII representation
char num_to_hex(int num)
{
   int sum=0;                      // Variable to store final converted result
    int i=0,a[10];                 // Temporary array to store hex digits
   while(num!=0)                   // Repeat until number becomes zero
     {
      int rem=num%16;              // Get remainder by dividing with 16
      if(rem>9 && rem<16)          // If remainder corresponds to A–F
        a[i++]=(rem-10)+65;        // Convert to ASCII character A-F
      else
        a[i++]=(rem+48);           // Convert to ASCII character 0-9
    num=num/16;                    // Divide number by 16 for next digit
   }
  for(--i;i>=0;i--)                // Reverse the stored digits
    {
     sum=sum*10+a[i];              // Build final number
     }
   return(sum);                    // Return converted value
}
