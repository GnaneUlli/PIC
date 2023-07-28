//PIC16F877A Configuration Bit Settings
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

#define _XTAL_FREQ 600000

void init();
void Lcd_data(unsigned char);
void Lcd_command(unsigned char);
unsigned char My_name[12]={"GNANESWARAO"};
unsigned char x,i,n;
void main(){
    init();
    Lcd_command(0x06);
    Lcd_command(0x83);
    for(x=0;x<=10;x++){
        Lcd_data(My_name[x]);
    }
    Lcd_command(0x04);
    Lcd_command(0xCD);
    for (n = 0; n < 11; n++) {
        Lcd_data(My_name[n]); // Print characters in reverse order
    }
    while (1);
}
void init()
{
    TRISC=0xF6;//set pin RC0 and RC3 as output
    TRISD=0x00;//To flow data through all pins in port d
    Lcd_command(0x38);//as per Lcd flow
    __delay_ms(100);
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x38);
    __delay_ms(100);
    Lcd_command(0x38);//To set number of lines and character display
    __delay_ms(100);
    //Lcd_command(0x04);//To set starting and moving position
    //__delay_ms(100);
    Lcd_command(0x0C);//display on off control
    __delay_ms(100);
    Lcd_command(0x01);// To clear display
    __delay_ms(100);
}
void Lcd_data(unsigned char i) {
    PORTC |= 0x08; // Set RS (Register Select) to 1 for data mode
    PORTD = i;
    PORTC |= 0x01; // Enable (E) on
    __delay_ms(1); // Short delay to ensure the E pulse is recognized
    PORTC &= ~0x01; // Enable (E) off
    __delay_ms(100);
}
void Lcd_command(unsigned char i) {
    PORTC &= ~0x08; // Set RS (Register Select) to 0 for command mode
    PORTD = i;
    PORTC |= 0x01; // Enable (E) on
    __delay_ms(1); // Short delay to ensure the E pulse is recognized
    PORTC &= ~0x01; // Enable (E) off
    __delay_ms(100);
}
