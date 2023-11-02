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

void init();
unsigned char val;
void main(){
    init();
    while(1){
        if(PIR1 & 0X20){
            val=RCREG;
            switch(val){
            case 'A':  PORTD=0X02;//MAKING RD6=0,RD1=1
            break;
            case 'B':  PORTD=0X40;//MAKING RD6=1,RD1=0
            break;
            case 'C':  PORTD=0X42;//MAKING RD6=1,RD1=1
            break;
            case 'D':  PORTD=0X00;//MAKING RD6=0,RD1=0
            break;
            }
        }
    }
}

void init(){
    TRISD=0x00; //Set RB4 to RB7 as input remaining as output
    TRISC=0xC0; //Set RC6 and RC7 as per Uart flow
    PORTD=0x00; //set all as off for port d
    RCSTA=0x90;  //For transmission
    TXSTA=0x20;  //For Receiving
    SPBRG=0x09;  // Baud rate configuration
}

