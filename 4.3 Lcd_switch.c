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
void init(void);
void Lcd_command(unsigned char);
void Lcd_data(unsigned char);
void Lcdoutput(unsigned int);
void keyscane();
unsigned char x,value;
unsigned int  i,j,d4,d3,d2,d1;
unsigned char array[16]={"SET SPD:    rpm"};
/*Declaration of necessary function prototypes and variables*/

void main(){
    init();
    while(1){
        keyscane();
    }
}

void init()
{
    TRISC=0xF6;//set pin RC0 and RC3 as output
    TRISD=0x00;//data flow through all pins in port d
    TRISB=0xF0;//set p RB4 to RB7 as input
    PORTB=0x00;
    OPTION_REG&=0x7F;//For pull up resistor activation 
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
    j=0;
}
void keyscane(){
    value=PORTB;
    switch(value){
        case 0xE0:
            Lcd_command(0x80);
            for(x=0;x<8;x++){
                Lcd_data(array[x]);
            }
            Lcd_command(0x8C);
            for(x=12;x<=15;x++){
                Lcd_data(array[x]);
            }
            Lcd_command(0x88);
            Lcdoutput(j);
            break;
        case 0xD0:
            j++;
            if(j>5000){
                j=5000;
            }
            Lcd_command(0x88);
            Lcdoutput(j);
            break;
        case 0xB0:
            j--;
            if(j<1){
                j=1;
            }
            Lcd_command(0x88);
            Lcdoutput(j);
            break;
        case 0x70:
            j=0;
            Lcd_command(0x88);
            Lcdoutput(j);
            break;
    }

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

void Lcdoutput(unsigned int i){
    d4=(unsigned char)(i/1000);
    d3=(unsigned char)((i-(d4*1000))/1000);
    d2=(unsigned char)((i-(d4*1000)-(d3*100))/10);
    d1=(unsigned char)(i-(d4*1000)-(d3*100)-(d2*10));
    Lcd_command(0x88);
    Lcd_data(0x30+d4);
    Lcd_command(0x89);
    Lcd_data(0x30+d3);
    Lcd_command(0x8A);
    Lcd_data(0x30+d2);
    Lcd_command(0x8B);
    Lcd_data(0x30+d1);
}

