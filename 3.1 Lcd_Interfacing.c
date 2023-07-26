// PIC16F877 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 6000000

void init();
void Lcd_command(unsigned char);
void Lcd_data(unsigned char);
unsigned char name[15]={"Hello World"};
unsigned char x,i;
void main(){
    init();
    Lcd_command(0x80);
    for(x=0;x<=11;x++){
        Lcd_data(name[x]);
    }
    while(1);
}

void init(){
    PORTC=0x00;
    PORTD=0x00;
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x06);
    __delay_ms(100);
    Lcd_command(0x0C);
    __delay_ms(100);
    Lcd_command(0x01);
    __delay_ms(100);
}
void Lcd_data(unsigned char i){
    PORTC|=0x08;
    PORTD=i;
    PORTC|=0x01;
    PORTC&=~0x01;
}
void Lcd_command(unsigned char i){
    PORTC|=~0x08;
    PORTD=i;
    PORTC|=0x01;
    PORTC&=~0x01;
}
