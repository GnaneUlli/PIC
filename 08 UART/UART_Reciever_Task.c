
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
void Lcd_command(unsigned char);
void Lcd_data(unsigned char);
char lcd1[15]={"Received :"};
char lcd2[15]={"Transmitted :"};
unsigned char val,i;
void main(){
    init();
    while(1){
        if(PIR1 & 0x20){
            val = RCREG;
            switch(val){
                case 'A':
                    // Send 'a' back
                    while(!TXIF); // Wait until buffer is empty
                    TXREG = 'a';
                    Lcd_command(0x80);
                    for(i=0;i<10;i++){
                        Lcd_data(lcd1[i]);
                    }
                    Lcd_command(0x8A);
                    Lcd_data('A');
                    Lcd_command(0xC0);
                    for(i=0;i<13;i++){
                        Lcd_data(lcd2[i]);
                    }
                    Lcd_command(0xCD);
                    Lcd_data('a');
                    break;
                case 'B':
                    // Send 'b' back
                    while(!TXIF); // Wait until buffer is empty
                    TXREG = 'b';
                    Lcd_command(0x80);
                    for(i=0;i<10;i++){
                        Lcd_data(lcd1[i]);
                    }
                    Lcd_command(0x8A);
                    Lcd_data('B');
                    Lcd_command(0xC0);
                    for(i=0;i<13;i++){
                        Lcd_data(lcd2[i]);
                    }
                    Lcd_command(0xCD);
                    Lcd_data('b');
                    break;
                case 'C':
                    // Send 'c' back
                    while(!TXIF); // Wait until buffer is empty
                    TXREG = 'c';
                    Lcd_command(0x80);
                    for(i=0;i<10;i++){
                        Lcd_data(lcd1[i]);
                    }
                    Lcd_command(0x8A);
                    Lcd_data('C');
                    Lcd_command(0xC0);
                    for(i=0;i<13;i++){
                        Lcd_data(lcd2[i]);
                    }
                    Lcd_command(0xCD);
                    Lcd_data('c');
                    break;
                case 'D':
                    // Send 'd' back
                    while(!TXIF); // Wait until buffer is empty
                    TXREG = 'd';
                    Lcd_command(0x80);
                    for(i=0;i<10;i++){
                        Lcd_data(lcd1[i]);
                    }
                    Lcd_command(0x8A);
                    Lcd_data('D');
                    Lcd_command(0xC0);
                    for(i=0;i<13;i++){
                        Lcd_data(lcd2[i]);
                    }
                    Lcd_command(0xCD);
                    Lcd_data('d');
                    
                    break;
            }
        }
    }
}

void init(){
    TRISD = 0x00;   // Set TRISD as output
    TRISC = 0xC0;   // Set RC6 and RC7 as per UART flow
    RCSTA = 0x90;  // UART reception
    TXSTA = 0x20;  // UART transmission, enable TXEN bit for full-duplex
    SPBRG = 0x09;  // Baud rate configuration
    Lcd_command(0x38);//as per Lcd flow
    __delay_ms(10);
    Lcd_command(0x38);
    __delay_ms(10);
    Lcd_command(0x38);
    __delay_ms(10);
    Lcd_command(0x38);//To set number of lines and character display
    __delay_ms(10);
    Lcd_command(0x06);//To set starting and moving position
    __delay_ms(10);
    Lcd_command(0x0C);//Cursor or display shift
    __delay_ms(10);
    Lcd_command(0x01);// To clear display
    __delay_ms(10);
}
void Lcd_data(unsigned char i){
    
    PORTC|=0x08;//set to data mode
    PORTD=i;
    PORTC|=0x01;//Enable to on
    PORTC&=~0x01;//Enable to off
    __delay_ms(10);
    
}
void Lcd_command(unsigned char i){
    
    PORTC&=~0x08;//set to command mode
    PORTD=i;
    PORTC|=0x01;//Enable on 
    PORTC&=~0x01;//Enable off
    __delay_ms(10);
    
}
