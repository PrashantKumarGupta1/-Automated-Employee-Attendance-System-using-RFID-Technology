/******************************************************************************
 Timer based delay function
******************************************************************************/

#include "header.h"

void delay_ms(unsigned int ms)
{

int a[]={15,60,30,0,15};     // VPBDIV clock values

int PCLK=0;

PCLK=a[VPBDIV]*1000;         // Calculate clock

T0PC=0;                      // Reset prescaler

T0PR=PCLK-1;                 // Set prescaler

T0TC=0;                      // Reset timer counter

T0TCR=1;                     // Enable timer

while(T0TC<ms);              // Wait for delay

T0TCR=0;                     // Stop timer

}
