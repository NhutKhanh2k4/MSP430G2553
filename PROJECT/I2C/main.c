#include <msp430g2553.h>
#include "I2C_NK.h"
void Config_Clock(void);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;       // Stop Watchdog Timer
    Config_Clock();
    I2C_USCI_Init(0x07);
    
    P1DIR |= BIT0;
    P1OUT &=~ BIT0;
    
    while(1)
    {
      if (I2C_USCI_Read_Byte(0x07) == 0x55) {
        P1OUT |= BIT0;
        __delay_cycles(10000);
        P1OUT &=~ BIT0;
      }
      __delay_cycles(1000000);
    }
}

void Config_Clock(void)
{
    if (CALBC1_1MHZ == 0xFF) while(1); // If no calibration constant, trap CPU
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;            
    DCOCTL = CALDCO_1MHZ;
}


