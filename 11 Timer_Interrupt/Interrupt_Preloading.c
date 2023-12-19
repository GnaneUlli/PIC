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

unsigned char C = 0; // Global Counter Variable

void main()
{
    TRISB = 0x00;
    PORTB = 0x00;

    // Configure Timer1
    TMR1 = 65535 - 50000;  // Preload Timer1 with a value for a 50ms delay
    T1CON = 0x01;         // Timer1 enabled with 1:1 prescaler

    // Enable Timer1 overflow interrupt
    PIE1 = 0x01;

    // Enable global and peripheral interrupts
    INTCON = 0xC0;

    while (1)
    {
        // Your main loop code here
    }
}

// Interrupt Service Routine - ISR
void __interrupt () _ISR()
{
    // Check The Timer1 Overflow Flag Bit
    if (PIR1 & 0x01)
    {
        C++;
        if (C == 15)
        {
            // Event2 = Toggle LED
            PORTB = ~PORTB;
            // Clear The Global Counter
            C = 0;
        }

        // Preload Timer1 for the next delay
        TMR1 = 65535 - 50000;  // Preload Timer1 with a value for a 50ms delay

        // Clear The Timer1 Overflow Flag Bit
        PIR1 &= 0x00;
    }
}
