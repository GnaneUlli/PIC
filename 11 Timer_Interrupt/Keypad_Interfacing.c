
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

////**** KEYPAD INTERFACING WITH PIC16F877A  ****////

#include <xc.h>
#define _XTAL_FREQ 6000000
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_cmd(unsigned char);
void keypad(void);
#define r1 RB0
#define r2 RB1
#define r3 RB2
#define r4 RB3
#define c1 RB4
#define c2 RB5
#define c3 RB6
#define c4 RB7

void main()
{
    TRISC=0X00;
    TRISD=0X00;
    TRISB=0XF0;
    PORTB=0X00;
    PORTD=0X00;
    PORTC=0X00;
    OPTION_REG&=0X7F;
    lcd_init();
    {
        keypad();
    }
    
}
void lcd_init()
{
    lcd_cmd(0x30);
    __delay_ms(100);
    lcd_cmd(0x30);
    __delay_ms(100);
    lcd_cmd(0x30);
    __delay_ms(100);
    lcd_cmd(0x38);
    __delay_ms(100);
    lcd_cmd(0x06);
    __delay_ms(100);
    lcd_cmd(0x0C);
    __delay_ms(100);
    lcd_cmd(0x01);
    __delay_ms(100);
}
void keypad(void)
{
	while(1)
    {
        r1=0;r2=1;r3=1;r4=1;    
        if (c1==0)
        {
            __delay_ms(100);
            while (c1==0);
            lcd_data('7');
        }
        if (c2==0)
        {
        __delay_ms(100);
        while (c2==0);
        lcd_data('8');
        }
        if (c3==0)
        {
        __delay_ms(100);
        while (c3==0);
        lcd_data('9');
        }
        if (c4==0)
        {
        __delay_ms(100);
        while (c4==0);
        lcd_data('/');
        }
        
        
        r1=1;r2=0;r3=1;r4=1;    
        if (c1==0)
        {
            __delay_ms(100);
            while (c1==0);
            lcd_data('4');
        }
        if (c2==0)
        {
        __delay_ms(100);
        while (c2==0);
        lcd_data('5');
        }
        if (c3==0)
        {
        __delay_ms(100);
        while (c3==0);
        lcd_data('6');
        }
        if (c4==0)
        {
        __delay_ms(100);
        while (c4==0);
        lcd_data('*');
        }
        
        r1=1;r2=1;r3=0;r4=1;    
        if (c1==0)
        {
            __delay_ms(100);
            while (c1==0);
            lcd_data('1');
        }
        if (c2==0)
        {
        __delay_ms(100);
        while (c2==0);
        lcd_data('2');
        }
        if (c3==0)
        {
        __delay_ms(100);
        while (c3==0);
        lcd_data('3');
        }
        if (c4==0)
        {
        __delay_ms(100);
        while (c4==0);
        lcd_data('-');
        }
        
        r1=1;r2=1;r3=1;r4=0;    
        if (c1==0)
        {
            __delay_ms(100);
            while (c1==0);
            lcd_data('_');
        }
        if (c2==0)
        {
        __delay_ms(100);
        while (c2==0);
        lcd_data('0');
        }
        if (c3==0)
        {
        __delay_ms(100);
        while (c3==0);
        lcd_data('=');
        }
        if (c4==0)
        {
        __delay_ms(100);
        while (c4==0);
        lcd_data('+');
        }
    }        

}
void lcd_data(unsigned char i)
{
    PORTC|=0x08; // RS = 1
    PORTD=i;
    PORTC|=0x01; // EN = 1
    __delay_ms(100);
    PORTC&=~0x01; // EN = 0
}

void lcd_cmd(unsigned char i)
{
    PORTC&=~0x08; // RS = 0
    PORTD=i;
    PORTC|=0x01; // EN = 1
    __delay_ms(100);
    PORTC&= ~0x01; // EN = 0
}