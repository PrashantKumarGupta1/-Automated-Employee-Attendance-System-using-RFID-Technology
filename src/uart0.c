/******************************************************************************
 * File Name   : uart0.c
 * Description : UART0 Driver for LPC2129
 * Purpose     : Handles serial communication with RFID reader and Linux PC
 ******************************************************************************/

#include "header.h"     // Include project header file

// Macro to check Transmit Holding Register Empty
#define THRE ((U0LSR>>5)&1)

// Macro to check Receive Data Ready
#define RDR (U0LSR&1)


/*------------------------------------------------
 UART0 Initialization
 Configures baud rate and UART settings
------------------------------------------------*/
void uart0_init(unsigned int baud)
{
 int result;                         // Variable to hold divisor value

 int a[]={15,60,30,0,15};            // VPBDIV clock mapping table

 int PCLK=0;                         // Peripheral clock variable

 PCLK=a[VPBDIV]*1000000;             // Calculate PCLK based on VPBDIV

 result=PCLK/(16*baud);              // Baud rate divisor formula

 PINSEL0 |=0X05;                     // Select UART0 TXD0 and RXD0 pins

 U0LCR=0X83;                         // Enable divisor latch access

 U0DLL=(result)&0xff;                // Set lower byte of divisor

 U0DLM=(result>>8)&0xff;             // Set higher byte of divisor

 U0LCR=0X03;                         // Disable divisor latch access
}


/*-----------------------------------------------
 UART transmit single character
-----------------------------------------------*/
void uart0_tx(unsigned char data)
{
U0THR=data;              // Load data into transmit register
while(THRE==0);          // Wait until transmission completes
}


/*-----------------------------------------------
 UART receive single character
-----------------------------------------------*/
unsigned char uart0_rx(void)
{
 while(RDR==0);          // Wait until data is received
 return(U0RBR);          // Return received byte
}


/*-----------------------------------------------
 UART transmit string
-----------------------------------------------*/
void uart0_tx_string(unsigned char *p)
{
while(*p != 0)           // Loop until NULL character
  {
   uart0_tx(*p);         // Send character
    p++;                 // Move pointer forward
  }
}


/*-----------------------------------------------
 UART transmit integer
-----------------------------------------------*/
void uart0_tx_integer(int num)
{
 int a[20],i=0;          // Array to store digits

 if(num==0)
    {
	 uart0_tx('0');      // Send zero
	 return;
	}

  if(num<0)
    {
	 uart0_tx('-');      // Send negative sign
	 num=-(num);
	}

   while(num!=0)
    {
	 a[i]=num%10;       // Extract digit
	 i++;
	 num=num/10;
	}

	for(--i;i>=0;i--)
	  {
	   uart0_tx(a[i]+48);   // Convert digit to ASCII
	  }
}


/*-----------------------------------------------
 UART transmit float
-----------------------------------------------*/
void uart0_float(float f) 
{
 int i;

 i=f;                      // Integer part

 uart0_tx_integer(i);

 uart0_tx('.');            // Decimal point

 i=(f-i)*100;              // Fraction part

 uart0_tx_integer(i);
}


/*-----------------------------------------------
 UART receive string
-----------------------------------------------*/
void uart0_rx_string(char *ptr,u8 len)
{
s32 i;

for(i=0;i<len;i++)
{
while(RDR==0);             // Wait for character

ptr[i]=U0RBR;              // Store character

if(ptr[i]=='\r')           // Stop if ENTER key pressed
break;
}

ptr[i]='\0';               // End string
}
