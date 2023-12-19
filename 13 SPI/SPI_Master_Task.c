#include <xc.h>
#define _XTAL_FREQ 6000000
#define UP RD3
#define Down RD4
#define Send RD5
void SPI_Master_Init( void);
void SPI_Write(uint8_t);
void main(void)
{
  SPI_Master_Init();
  uint8_t data=0;
  TRISB=0x00;
  TRISD=0x38;
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
    PORTB = data;
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





