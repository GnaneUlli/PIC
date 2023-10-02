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
#define _XTAL_FREQ 6000000
unsigned char val;
void main()
{
    TRISB=0xF0;  //Making RB0 to RB3 as output remaining as input
    TRISC=0x00;  //Making all C port pins as output
    TRISD=0x00;  //Making all d port pins as output
    PORTB=0x00;  //Making all b port pins off
    PORTC=0x00;  //Making all C port pins off
    PORTD=0x00;  //Making all d port pins off
    OPTION_REG&=0x7F; // For internal pull up
    INTCON|=0x88; //For Enabling Interrupts
    while(1)
    {
        PORTC=0xFF;
        __delay_ms(1000);
        PORTC=0x00;
        __delay_ms(500);
    }
}
void __interrupt() _ISR()
{
    if(INTCON&0x01)
    {
        val=PORTB;
        if(val==0xE0)
        {
            PORTD=0x01;
        }
        else if(val==0xD0)
        {
            PORTD=0X02;
        }
        INTCON&=0XFE;
    }
}
