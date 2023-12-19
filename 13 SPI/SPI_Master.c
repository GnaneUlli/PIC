
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
#define UP RB0
#define Down RB1
#define Send RB2
void SPI_Master_Init( void);
void SPI_Write(uint8_t);
void main(void)
{
  SPI_Master_Init();
  uint8_t data=0;
  TRISB=0x07;
  TRISD=0x00;
  PORTD=0x00;
  while(1)
  {
    if (UP)
    {
      data++;
      __delay_ms(100);
      while(UP==1);
    }
    if (Down)
    {
      data--;
      __delay_ms(100);
      while(Down==1);
    }
    if (Send)
    {
      SPI_Write(data);
      __delay_ms(100);
      while(Send==1);
    }
    PORTD = data;
  }
  return;
}
 
void SPI_Master_Init(void)
{
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 0;
  SSPM3 = 0;
  SSPEN = 1;
  CKP = 0;
  CKE = 0;
  SMP = 0;
  TRISC5 = 0;
  TRISC4 = 1;
  TRISC3 = 0;
}
 
void SPI_Write(uint8_t data)
{
  SSPBUF=data;
}


------------------------------------------------------------------------------------------------

