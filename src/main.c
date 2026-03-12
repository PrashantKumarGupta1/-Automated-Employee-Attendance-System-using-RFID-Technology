/******************************************************************************
 * File Name : main.c
 * Description : RFID Attendance System with RTC
 ******************************************************************************/

#include "header.h"

extern int i;                 // Global interrupt counter
unsigned char temp[100];      // Buffer storing RFID data

int main()
{

	unsigned char empl[100];  // Employee data buffer
	int flag1=0,j;
	int index;
	int flag,k;

	unsigned char h,m,s,t;    // Time variables
	unsigned char date,month,year;

	i2c_init();               // Initialize I2C
	lcd_init();               // Initialize LCD
	uart0_init(9600);         // Initialize UART
	config_vic();             // Configure interrupt controller
	en_uart0_intr();          // Enable UART interrupt

	uart0_tx_string("DS1307 RTC\r\n");

	/* Display welcome message */
	lcd_cmd(0x01);
	lcd_string("Scan Your Card");

	/* RTC initialization */
	i2c_byte_write_frame(0XD0,0X2,0X52);
	i2c_byte_write_frame(0XD0,0X1,0X40);
	i2c_byte_write_frame(0XD0,0X0,0X00);

	while(1)
	{

	/* Read RTC time */
	h=i2c_byte_read_frame(0XD0,0X02);
	m=i2c_byte_read_frame(0XD0,0X01);
	s=i2c_byte_read_frame(0XD0,0X00);

	date=i2c_byte_read_frame(0XD0,0X04);
	month=i2c_byte_read_frame(0XD0,0X05);
	year=i2c_byte_read_frame(0XD0,0X06);

	index=i2c_byte_read_frame(0XD0,0X03);

	t=(h & 0x1f);

	if((h>>5)&1)
	flag=1;
	else
	flag=0;

	/* If RFID card detected */
	if(i==12)
	{
	flag1=1;
	i=0;

	lcd_cmd(0x01);
	lcd_string("Employee Verified");

	lcd_cmd(0xC0);
	lcd_string("Attendance Marked");
	}

	/* Send attendance to PC */
	if(flag1==1)
	{
	for(j=0,k=0;temp[k];k++)
	empl[j++]=temp[k];

	empl[j++]='\r';
	empl[j++]='\n';
	empl[j]='\0';

	uart0_tx_string(empl);

	flag1=0;
	}

	}
}
