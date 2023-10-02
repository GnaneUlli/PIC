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
    TRISB=0xFF;  //Making RB0 to RB3 as output remaining as input
    TRISC=0x00;  //Making all C port pins as output
    TRISD=0x00;  //Making all d port pins as output
    PORTC=0x00;  //Making all C port pins off
    PORTD=0x00;  //Making all d port pins off
    OPTION_REG=0x00; // For internal pull up
    INTCON|=0x90; //For Enabling Interrupts
    while(1)
    {
        PORTC=0XFF;
        __delay_ms(500);
        PORTC=0X00;
        __delay_ms(500);
    }
}
void __interrupt() _ISR()
{
    if(INTCON&0X02)// check for INTF
    {
        val=PORTB;
        if(val==0XFE)
        {
            PORTD=0XFF;
            __delay_ms(1000);
            PORTD=0X00;
            __delay_ms(1000);
        }
        INTCON&=0XFD;
    }
}
