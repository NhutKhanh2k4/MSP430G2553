#include "msp430g2553.h"
#include "DHT11.h"
#include "UART.h"
#include <stdio.h>

void main( void )
{
  
    WDTCTL = WDTPW + WDTHOLD;
    Uart_Init(9600);                      
    unsigned char temperature = 0;                     
    unsigned char humidity = 0;
    char buff[50];
  
  while(1){

      DHT11_Read(&temperature, &humidity);    
      
      sprintf(buff, "TEM: %d  |  HUM: %d     \n", temperature,  humidity);
      Uart_Write_Str(buff);
 
      __delay_cycles(1000000);
    
  }
  
}
