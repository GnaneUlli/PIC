
#include <xc.h>
#include "config.h"
#include "I2C_EEPROM.h"
#define _XTAL_FREQ 16000000
void main(void) {
    
    
    I2C_Master_Init(100000);
    unsigned int Address = 0x0023; 
    unsigned char Data = 'A';     
    
    EEPROM_Write(Address, Data++); 
     __delay_ms(100); 
    Address = 0x0036;
    EEPROM_Write(Address, Data++); 
    __delay_ms(100);
    
    Address = 0x0042;
    EEPROM_Write(Address, Data);     
    __delay_ms(100);                  
    
    Address = 0x0023;               
    TRISD = 0x00;   
    PORTD = EEPROM_Read(Address);  
    __delay_ms(100);
    
    Address = 0x0036;
    PORTD = EEPROM_Read(Address);  
    __delay_ms(100);
    
    Address = 0x0042;
    PORTD = EEPROM_Read(Address);    

    while(1)
    {
        
    }
    return;
}
