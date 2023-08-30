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
unsigned char j,k[10],n;
unsigned int  lovalue,hivalue,m;
unsigned long value,voltage;

/*Declaration of necessary function prototypes and variables*/

void main(){
    init();
    while(1){
        //ADCON0=0x81; 
        ADCON0|=0x04;   //Set to start the adc flow and off when conversion is over
        while(ADCON0 & 0x04);
        lovalue=ADRESL;
        hivalue=ADRESH;
        value=((unsigned int )hivalue<<8) + (unsigned int)lovalue;  //Adding 16 bits of lovalue and hivalue
        voltage=(value*338)/1023;
        Lcd_command(0x80);
        Lcdoutput(voltage);
        CCPR1L=(voltage)>>2;
        CCP1CON=(CCP1CON&0x0C)+((voltage&0x03)<<4);
        __delay_ms(100);
        
    }
}

void init()
{
    TRISA=0x01;         //Set A0 as input remaining as output
    TRISC=0x00;         //Set pin RC0 to RC7  as output
    TRISD=0x00;         //data flow through all pins in port d
    ADCON0=0x81;        //set the adc flow
    ADCON1=0x8E;        //set to right justified 
    CCP1CON=0x3C;       //To set pwm flow
    CCPR1L=0x2E;  
    T2CON=0x06;          //Timer register
    PR2=0x5E;           //to set period
    Lcd_command(0x38);  //as per Lcd flow
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


