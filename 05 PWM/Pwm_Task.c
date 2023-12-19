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

void pwm_set(void);
void pwm_values(void);

unsigned char pwmhigh20,pwmlow20;
unsigned char pwmhigh60,pwmlow60;
unsigned char pwmhigh90,pwmlow90;
/* Declaring necessary function prototypes and variables*/
void main(){
    pwm_set();
    while(1){
        pwm_values();
    }
}

void pwm_set(){
    TRISC=0xFB;// make rc2 as output
    CCP1CON=0x3C; //Enable pwm mode and controller register
    T2CON=0x06; //timer register 
    PR2=0x2F;  // to set period 
    pwmhigh20=0x09; //calculated value of pwm high of 20% duty cycle
    pwmlow20=0x10;  //calculated value of pwm low of 20% duty cycle
    pwmhigh60=0x1C; //calculated value of pwm high of 60% duty cycle
    pwmlow60=0x10;  //calculated value of pwm low of 60% duty cycle
    pwmhigh90=0x2A; //calculated value of pwm high of 90% duty cycle 
    pwmlow90=0x10;  //calculated value of pwm low of 90% duty cycle
}
void pwm_values(){
    CCPR1L=pwmhigh20;//duty cycle
    CCP1CON=(CCP1CON&0xCF)|pwmlow20; //set without effect ccp1con
    __delay_ms(3000);
    CCPR1L=pwmhigh60;
    CCP1CON=(CCP1CON&0xCF)|pwmlow60; //set without effect ccp1con
    __delay_ms(3000);
    CCPR1L=pwmhigh90;
    CCP1CON=(CCP1CON&0xCF)|pwmlow90; //set without effect on ccp1con
    __delay_ms(3000);
    
}
