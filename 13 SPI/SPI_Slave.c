
#include <xc.h>
#define _XTAL_FREQ 6000000
void SPI_Slave_Init();
uint8_t SPI_Read();
uint8_t data;

void main(void)
{
  SPI_Slave_Init();
  TRISB = 0x00;
  while(1)
  {
    PORTB=data;
  }
  return;
}

void SPI_Slave_Init()
{
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 1;
  SSPM3 = 0;
  SSPEN = 1;
  CKP = 0;
  CKE = 0;
  SMP = 0;
  TRISC5 = 0;
  TRISC4 = 1;
  TRISC3 = 1;
  PCFG3 = 0;
  PCFG2 = 1;
  PCFG1 = 0;
  PCFG0 = 0;
  TRISA5 = 1;
  SSPIE = 1;
  PEIE = 1;
  GIE = 1;
}

uint8_t SPI_Read()
{
  uint8_t data;
  if (BF)
  {
    data = SSPBUF;
    BF = 0;
    SSPIF = 0;
    SSPOV = 0;
    return data;
  }
  return 0;
}

int __interrupt()ISR(void)
{
  if (SSPIF)
  {
    data = SSPBUF;
    SSPIF = 0;
  }
}