/ 'C' source line config statements

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

// Global variable
unsigned char toggleFlag = 0; // Flag to track toggle state


void main(){
    TRISA0 = 0; // Set RA0 (pin 17) as output
    RA0 = 0;    // Initialize the pin low
    
    // Configure Timer0
    OPTION_REG = 0x04; // Prescaler 1:32, internal instruction cycle clock (Fosc/4)
    TMR0 = 100;      // Initialize Timer0 value for a 5ms delay (256 - (5ms / (1 / (4MHz / 4 / 256))))
    TMR0IE = 1;   // Enable Timer0 overflow interrupt
    while (1) {
         if (TMR0IF) {
             TMR0IF = 0; // Clear Timer0 interrupt flag
             
             // Toggle the pin based on the toggleFlag
             if (toggleFlag) {
                 // Turn the pin HIGH for 15ms
                 RA0 = 1;
                 __delay_ms(150);
                 // Turn the pin LOW for 10ms
                 RA0 = 0;
                 __delay_ms(100);
                 toggleFlag = 0; // Set the flag for the next cycle
             } else {
                 toggleFlag = 1; // Set the flag for the next cycle
             }
             // Reload Timer0 for a 5ms delay (assuming 4 MHz clock)
             TMR0 = 100; // 256 - (5ms / (1 / (4MHz / 4 / 256)))
         }
    }
}
