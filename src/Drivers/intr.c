/******************************************************************************
 UART0 Interrupt Handler
 Handles incoming RFID characters
******************************************************************************/

#include "header.h"            // Include project header file containing function declarations

int i = 0;                     // Counter variable used to store number of received UART characters

#include <LPC21xx.H>           // Header file for LPC21xx microcontroller register definitions

extern unsigned char temp[100];// Buffer declared in another file to store received RFID data


// UART0 interrupt service routine
void uart0_handler(void) __irq
{

   int t = U0IIR;              // Read UART0 Interrupt Identification Register to know interrupt source

   if(t & 4)                   // Check 4th bit to confirm interrupt occurred due to UART RX (data received)
   {

      temp[i++] = U0RBR;       // Read received byte from UART Receive Buffer Register and store in buffer

   }

   VICVectAddr = 0;            // Mandatory line to signal end of interrupt to VIC (Vector Interrupt Controller)

}


// Function to configure the Vector Interrupt Controller
void config_vic(void)
{

   VICIntSelect = 0;           // Select IRQ type interrupt (not FIQ)

   VICVectCntl0 = 6 | (1<<5);  // Configure slot 0 for UART0 interrupt and enable that slot

   VICVectAddr0 = (int)uart0_handler; // Assign UART0 interrupt handler address to slot 0

   VICIntEnable |= 1<<6;       // Enable UART0 interrupt in VIC

}


// Function to enable UART0 interrupts
void en_uart0_intr(void)
{

   U0IER = 3;                  // Enable UART0 RX interrupt and TX interrupt

}
