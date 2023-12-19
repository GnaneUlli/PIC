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

unsigned char *dir_reg1  = (unsigned char *) 0x87;  //Address of TRISC Register to dir reg
unsigned char *data_reg1 = (unsigned char *) 0x07; //Address of PORTC Register to data reg
unsigned char *dir_reg2  = (unsigned char *) 0x86;  //Address of TRISB Register to dir reg
unsigned char *data_reg2 = (unsigned char *) 0x06; //Address of PORTB Register to data reg
unsigned char *option_reg = (unsigned char *) 0x81; //Address of Option Register

void main(){
    *dir_reg1  = 0x00;  //Making RC0 to RC7 as output
    *data_reg1 = 0x00;  //set all port c pins off
    *dir_reg2  = 0xF0;  //set p RB4 to RB7 as input
    *data_reg2 = 0x00;  //set all port b pins off
    *option_reg&=0x7F;  //activating internal pull up.
      while(1){
        switch(*data_reg2){
            case 0xE0:  *data_reg1=0x02; //Make RC1 on  and RC7 off.
            __delay_ms(100);
            break;
            case 0xD0:  *data_reg1=0x82; //Make RC1 on and RC7 on.
            __delay_ms(100);
            break;
            case 0xB0:  *data_reg1=0x80; //Make RC1 off and RC7 on 
            __delay_ms(100);
            break;
            case 0x70:  *data_reg1=0x00; //Make RC1 and RC7 off
            __delay_ms(100);
            break;
        }
    }
}
