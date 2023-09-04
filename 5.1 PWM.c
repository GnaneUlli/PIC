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
void pwm_change(void);

unsigned char pwmhigh10,pwmlow10;
unsigned char pwmhigh50,pwmlow50;
unsigned char pwmhigh80,pwmlow80;
/* Declaring necessary function prototypes and variables*/
void main(){
    init();
    while(1){
        pwm_change();
    }
}

void init(){
    TRISC=0xFB;// make rc2 as output
    CCP1CON=0x3C; //Enable pwm mode and controller register
    T2CON=0x06; //timer register 
    PR2=0x5E;  // to set period 
    pwmhigh10=0x09; //calculated value of pwm high of 10% duty cycle
    pwmlow10=0x20;  //calculated value of pwm low of 10% duty cycle
    pwmhigh50=0x2F; //calculated value of pwm high of 50% duty cycle
    pwmlow50=0x00;  //calculated value of pwm low of 50% duty cycle
    pwmhigh80=0x4B; //calculated value of pwm high of 80% duty cycle 
    pwmlow80=0x00; 
}//calculated value of pwm low of 80% duty cycle
void pwm_change(){
    CCPR1L=pwmhigh10;
    CCP1CON=(CCP1CON&0xCF)|pwmlow10; //set without effect ccp1con
    __delay_ms(3000);
    CCPR1L=pwmhigh50;
    CCP1CON=(CCP1CON&0xCF)|pwmlow50; //set without effect ccp1con
    __delay_ms(3000);
    CCPR1L=pwmhigh80;
    CCP1CON=(CCP1CON&0xCF)|pwmlow80; //set without effect on ccp1con
    __delay_ms(3000);
    
}
