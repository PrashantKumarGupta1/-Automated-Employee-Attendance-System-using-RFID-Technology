#include"header.h"

extern int i;
unsigned char temp[100];

int main()
{

    unsigned char empl[100];
    int flag1=0,j;
    int index;
    int flag,k;

    unsigned char h,m,s,t;
    unsigned char date,month,year;

    i2c_init();
    lcd_init();
    uart0_init(9600);

    config_vic();
    en_uart0_intr();

    uart0_tx_string("DS1307 RTC\r\n");

    lcd_cmd(0x01);
    lcd_string("Scan Your Card");

    i2c_byte_write_frame(0XD0,0X2,0X52);
    i2c_byte_write_frame(0XD0,0X1,0X40);
    i2c_byte_write_frame(0XD0,0X0,0X00);
    i2c_byte_write_frame(0XD0,0X4,0X12);
    i2c_byte_write_frame(0XD0,0X5,0X05);
    i2c_byte_write_frame(0XD0,0X6,0X24);
    i2c_byte_write_frame(0XD0,0X3,0X01);

    while(1)
    {

        lcd_cmd(0x80);

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

        lcd_cmd(0xC0);

        lcd_data(date/16+48);
        lcd_data(date%16+48);
        lcd_data('/');

        lcd_data(month/16+48);
        lcd_data(month%16+48);
        lcd_data('/');

        lcd_data(year/16+48);
        lcd_data(year%16+48);

        lcd_cmd(0xcf-3);

        if(index==1) lcd_string("SUN");
        if(index==2) lcd_string("MON");
        if(index==3) lcd_string("TUE");
        if(index==4) lcd_string("WED");
        if(index==5) lcd_string("THU");
        if(index==6) lcd_string("FRI");
        if(index==7) lcd_string("SAT");

        if(i==12)
        {
            flag1=1;
            i=0;
        }

        if(flag1==1)
        {

            lcd_cmd(0x01);
            lcd_string("Employee Verified");

            lcd_cmd(0xC0);
            lcd_string("Attendance Marked");

            for(j=0,k=0;temp[k];k++)
                empl[j++]=temp[k];

            empl[j++]=' ';
            empl[j++]=t/16+48;
            empl[j++]=t%16+48;
            empl[j++]=':';
            empl[j++]=m/16+48;
            empl[j++]=m%16+48;
            empl[j++]=':';
            empl[j++]=s/16+48;
            empl[j++]=s%16+48;

            empl[j++]=' ';
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

            uart0_tx_string(empl);

            flag1=0;

            delay_ms(2000);

            lcd_cmd(0x01);
            lcd_string("Scan Your Card");

        }

    }

}
