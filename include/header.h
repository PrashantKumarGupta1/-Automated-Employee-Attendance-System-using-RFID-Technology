#include<lpc21xx.h>
	   	/*typedef*/
 typedef unsigned int u32;
 typedef signed int s32;
 typedef unsigned char u8;
 typedef signed char s8;
			 /*delay*/
extern void delay_ms(unsigned int ms);
			/*uart0*/
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(unsigned char *p);
extern void uart0_tx_integer(int num);
extern void uart0_float(float f);
extern void uart0_rx_string(char *ptr,u8 len);
		/*lcd_*/
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *p);
extern void cgram_init(void);
extern void lcd_int(int num);
			/*i2c*/
 extern  char num_to_hex(int num);
 extern void  i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
 extern unsigned char i2c_byte_read_frame(u8 sa,u8 mr);
 extern void i2c_init (void );
 extern void uart0_handler(void)__irq;
 extern void config_vic(void);
 extern void en_uart0_intr(void);


 


