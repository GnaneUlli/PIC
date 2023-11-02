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

void set_flow(void);
void command_mode(unsigned char);
void data_mode(unsigned char);
void Lcdoutput(unsigned int);
unsigned char j,k[10],n;
unsigned int  lovalue,hivalue,m;
unsigned long value,voltage;
unsigned char adcChannel;  // New variable for ADC channel selection
unsigned int i;
unsigned char ch1[5]={"CH1 :"};
unsigned char ch2[5]={"CH2 :"};
/*Declaration of necessary function prototypes and variables*/

void main(){
    set_flow();
    while (1) {
        ADCON0 = 0x89;
        ADCON0 |= 0x04;
        while (ADCON0 & 0x04);
        lovalue = ADRESL;
        hivalue = ADRESH;
        value = ((unsigned int) hivalue << 8) + (unsigned int) lovalue;
        command_mode(0x80);
        for(i=0;i<=4;i++){
            data_mode(ch1[i]);
        }
        command_mode(0x86);
        Lcdoutput(value);
        
        ADCON0=0xB1;
        ADCON0|=0x04;   //Set to start the adc flow and off when conversion is over
        while(ADCON0 & 0x04);
        lovalue=ADRESL;
        hivalue=ADRESH;
        value=((unsigned int )hivalue<<8) + (unsigned int)lovalue;  //Adding 16 bits of lovalue and hivalue
        voltage=(value*338)/1023;
        command_mode(0xC0);
        for(i=0;i<=4;i++){
            data_mode(ch2[i]);
        }
        command_mode(0xC6);
        Lcdoutput(voltage);
        CCPR1L=(voltage)>>2;
        CCP1CON=(CCP1CON&0x0C)+((voltage&0x03)<<4);
        __delay_ms(100);
    }
}

void set_flow()
{
    TRISA=0x02;         //Set A2 as input remaining as output
    TRISC=0x00;         //Set pin RC0 to RC7  as output
    TRISD=0x00;         //data flow through all pins in port d
    TRISE=0x02;          //Set A6 as input in Port E.
    ADCON0=0x89;        //set the adc flow
    ADCON1=0x80;        //set to Right justified 
    CCP1CON=0x3C;       //To set pwm flow
    CCPR1L=0x2E;  
    T2CON=0x06;          //Timer register
    PR2=0x5E;           //to set period
    command_mode(0x38);  //as per Lcd flow
    __delay_ms(10);
    command_mode(0x38);
    __delay_ms(10);
    command_mode(0x38);
    __delay_ms(10);
    command_mode(0x38);  //To set number of lines and character display
    __delay_ms(10);
    command_mode(0x06);  //To set starting and moving position
    __delay_ms(10);
    command_mode(0x0C);  //Cursor or display shift
    __delay_ms(10);
    command_mode(0x01);  // To clear display
    __delay_ms(10);
}
void Lcdoutput(unsigned int i){
    unsigned char s;
    j=1;
    m=i;
    while(m!=0){
    s=m-((m/10)*10);
    k[j]=s;
    j++;
    m=m/10;
    }
    k[j]='\0';
    j=j-1;
    if(k[4]>0){
        n=0x30+k[4];
        data_mode(n);
    }
    else{
        data_mode(0x20);
    }
    if(k[3]>=0){
        n=0x30+k[3];
        data_mode(n);
    }
    else{
        data_mode(0x20);
    }
    if(k[2]>=0){
        n=0x30+k[2];
        data_mode(n);
    }
    else{
        data_mode(0x20);
    }
    n=0x30+k[1];
    data_mode(n);
    data_mode(0x56);

}
void data_mode(unsigned char i){
    
    PORTC|=0x08;//set to data mode
    PORTD=i;
    PORTC|=0x01;//Enable to on
    PORTC&=~0x01;//Enable to off
    __delay_ms(10);
    
}
void command_mode(unsigned char i){
    
    PORTC&=~0x08;//set to command mode
    PORTD=i;
    PORTC|=0x01;//Enable on 
    PORTC&=~0x01;//Enable off
    __delay_ms(10);
    
}
