// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000
#define RS RC2
#define EN RC1
void init(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void init_i2c(const unsigned long);
void settime(void);
void i2c_start(void);
void i2c_wait(void);
void i2c_stop(void);
void i2c_repeatedstart(void);
void i2c_write(unsigned char);
int bcd2dec(int);
int dec2bcd(int);
void update(void);
char msg1[5]={"TIME:"};
char msg2[5]={"DATE:"};
char msg3[2]={"PM"};
char msg4[2]={"AM"};
int i,j,k,l;
int sec=45;
int min=59;
int hour=11;
int date=28;
int month=12;
int year =23;
int i2c_read(int);
char sec1,sec2,min1,min2,hour1,hour2,date1,date2,month1,month2,year1,year2,hr;
void main()
{
 init();
 init_i2c(100);
 settime();
while(1)
 {
 update();
 sec1=sec/10;//tens position
 sec2=sec%10;//unit position
 min1=min/10;//tens position
 min2=min%10;//unit position
 hour=(hr & 0x1F);//we are taking 0 to 4 bit
 hour=bcd2dec(hour);//dec
 hour1=hour/10;//tens position
 hour2=hour%10;//unit position
 date1=date/10;//tens position
 date2=date%10;//unit position
 month1=month/10;//tens position
 month2=month%10;//unit position
 year1=year/10;//tens position
 year2=year%10;//unit position
 lcdcmd(0x80);//cursor to 1st position
 for(i=0;i<5;i++)
 {
 lcddata(msg1[i]);//TIME will be printed
 }
 lcddata(hour1+'0');//hour printed
 lcddata(hour2+'0');//hour printed
 lcddata(0x2D);//-
 lcddata(min1+'0');//min 
 lcddata(min2+'0');//min
 lcddata(0x2D);//-
 lcddata(sec1+'0');//sec
 lcddata(sec2+'0');//sec
 lcddata(0x20);//space
 if(hr & 0x20)
 {
 for(i=0;i<2;i++)
 {
 lcddata(msg3[i]);
 }
 }
 else
 {
 for(i=0;i<2;i++)
 {
 lcddata(msg4[i]);
 }
 }
 lcdcmd(0xC0);//2nd line 1st position
 for(i=0;i<5;i++) 
 {
 lcddata(msg2[i]);//DATE printed
 }
 lcddata(date1+'0');//date
 lcddata(date2+'0');//date
 lcddata(0x2D);//-
 lcddata(month1+'0');//month
 lcddata(month2+'0');//month
 lcddata(0x2D);//-
 lcddata(year1+'0');//year
 lcddata(year2+'0');//year
 __delay_ms(500);//delay
 }
}
void init(void)
{
 TRISC=0x18;//RC3=1 and RC4=1
 TRISD=0x00;//output pins
 PORTD=0x00;//initiate from zero
 lcdcmd(0x38);
 __delay_ms(5);
 lcdcmd(0x38);
 __delay_ms(5);
 lcdcmd(0x38);
 __delay_ms(5);
 lcdcmd(0x38);
 __delay_ms(5);
 lcdcmd(0x0C);
 __delay_ms(5);
 lcdcmd(0x06);
 __delay_ms(5);
 lcdcmd(0x01);
 __delay_ms(5);
 
}
void lcdcmd(unsigned char mycmd)
{
 RS=0;//we are giving command
 PORTD=mycmd;//command
 EN=1;//Enable=1
 __delay_ms(5);//delay
 EN=0;//Enable=0
}
void lcddata(unsigned char mydata)
{
 RS=1;//we are giving data
 PORTD=mydata;//data
 EN=1;//Enable=1
 __delay_ms(5);
 EN=0;//Enable=0
}
void init_i2c(const unsigned long baud)
{
 SSPCON=0x28;//SSPEN=1 & I2C Master mode
 SSPCON2=0x00;//initiate from zero
 SSPSTAT=0x00;//initiate from zero
 SSPADD=(_XTAL_FREQ/(4*baud*100))-1;//formula
}
void i2c_wait(void)
{
 while( SSPSTAT & 0x04 || SSPCON2 & 0x1F );
}
void i2c_start(void)
{
 i2c_wait();
 SEN=1;
}
void i2c_stop()
{
 i2c_wait();
 PEN=1;
}
void i2c_repeatedstart()
{
 i2c_wait();
 RSEN = 1;
}
void i2c_write(unsigned char data)
{
 i2c_wait();
 SSPBUF=data;
}
int bcd2dec(int data)
{
 return ((data>>4)*10)+(data&0x0F);
}
int dec2bcd(int data)
{ 
return ((data/10)<<4)+(data%10);
}
void settime(void)
{
 i2c_start();//start bit
 i2c_write(0xD0);//slave address
 i2c_write(0x00);//register address
 i2c_write(dec2bcd(sec));//sec
 i2c_write(dec2bcd(min));//min
 i2c_write(0x60 | (dec2bcd(hour)));//hr
 i2c_write(1);//day
 i2c_write(dec2bcd(date));//data
 i2c_write(dec2bcd(month));//month
 i2c_write(dec2bcd(year));//year
 i2c_stop();//stop bit
}
int i2c_read(int ack)
{
 int value;//value
 i2c_wait();//wait
 RCEN=1;//enable receive mode from i2c
 i2c_wait();//wait
 value=SSPBUF;//buffer
 i2c_wait();//wait
 ACKDT=(ack)?0:1;//conditional operator
 ACKEN=1;//transmit ACKDT data bit
 return value;//return value
}
void update(void)
{
 i2c_start();//start bit
 i2c_write(0xD0);//write to slave address
 i2c_write(0x00);//register address
 i2c_repeatedstart();//repeated start
 i2c_write(0xD1);//slave address with read
 sec=(bcd2dec(i2c_read(1)));//sec with ACK
 min=(bcd2dec(i2c_read(1)));//min with ACK
 hr=(i2c_read(1));//bcd value of hour with ACK
 (i2c_read(1));//day with ACK
 date=(bcd2dec(i2c_read(1)));//date with ACK
 month=(bcd2dec(i2c_read(1)));//month with ACk
 year=(bcd2dec(i2c_read(0)));//year with NACK
 i2c_stop();//stop bit
}
