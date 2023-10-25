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

void set(void);
void command_function (unsigned char);
void data_function(unsigned char);
void ascii(unsigned int);
void sub(unsigned int ,unsigned int);
unsigned char v,str[5],plus,equal,minus;
unsigned int  num1,num2,diff,m,n;

/*Declaration of necessary function prototypes and variables*/

void main(){
    set();
    num1=238;
    num2=523;
    command_function(0x80);
    sub(num1,num2);
}

void set()

{
    TRISC=0xF6;//set pin RC0 and RC3 as output
    TRISD=0x00;//data flow through all pins in port d
    command_function(0x38);//as per Lcd flow
    __delay_ms(100);
    command_function(0x38);
    __delay_ms(100);
    command_function(0x38);
    __delay_ms(100);
    command_function(0x38);//To set number of lines and character display
    __delay_ms(100);
    command_function(0x06);//To set starting and moving position
    __delay_ms(100);
    command_function(0x0C);//Cursor or display shift
    __delay_ms(100);
    command_function(0x01);// To clear display
    __delay_ms(100);
}
void ascii(unsigned int i){
    unsigned char s,v=1;
    m=i;
    while(m!=0){
    s=m-((m/10)*10);
    str[v]=s;
    v++;
    m=m/10;
    }                 //Converts decimal to ascii
    str[v]='\0';
    v=v-1;
    while(v!=0){
        n=0x30+str[v];
        data_function(n);
        v--;
}

}
void data_function(unsigned char i){
    
    PORTC|=0x08;//set to data mode
    PORTD=i;
    PORTC|=0x01;//Enable to on
    PORTC&=~0x01;//Enable to off
    __delay_ms(100);
    
}
void command_function(unsigned char i){
    
    PORTC&=~0x08;//set to command mode
    PORTD=i;
    PORTC|=0x01;//Enable on 
    PORTC&=~0x01;//Enable off
    __delay_ms(100);
    
}

void sub(unsigned int a, unsigned int b){
    plus='+';
    minus='-';
    equal='=';
    if(a>b && a-b>=0){
        int diff=a-b;
        ascii(a);
        data_function(minus);
        ascii(b);
        data_function(equal);
        data_function(plus);
        ascii(diff);
    }
    else{
        int diff=b-a;
        ascii(a);
        data_function(minus);
        ascii(b);
        data_function(equal);
        data_function(minus);
        ascii(diff);
    }
}
