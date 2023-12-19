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

void main(){
    unsigned char x;
    TRISB=0xF0;  //Making RB4 to RB7 as input Remaining output
    TRISC=0x00;  //Making RC0 to RC7 as output
    PORTB=0x00;  //set all port b pins off
    PORTC=0x00;  //set all port c pins off
    while(1){
        x=PORTB;
        switch(x){
            case 0xE0:  PORTC=0x02; //Make RC1 on  and RC7 off.
            break;
            case 0xD0:  PORTC=0x82; //Make RC1 on and RC7 on.
            break;
            case 0xB0:  PORTC=0x80; //Make RC1 off and RC7 on 
            break;
            case 0x70:  PORTC=0x00; //Make RC1 and RC7 off
            break;
            case 0xF0:  PORTC=0x00; //Set to normal state.
            break;
        }
    }
}
