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

unsigned char *dir_reg  = (unsigned char *) 0x87; //Address of TRISC Register to dir reg
unsigned char *data_reg = (unsigned char *) 0x07; //Address of PORTC Register to data reg

void main(){
    *dir_reg  = 0xFD; //Set RC1 as output remaining as input
    *data_reg = 0x00; //Set RC1 to RC7 as off
    
    while(1){
        *data_reg = 0x00; //Making all pins as off
        __delay_ms(100);
        *data_reg = 0xFF;
        __delay_ms(100); //Making all pins as on.
    }
}



