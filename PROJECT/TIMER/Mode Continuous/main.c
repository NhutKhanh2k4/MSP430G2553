
#include "msp430g2553.h"

void Config_Clock(void);

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  P1DIR |= BIT0 + BIT6;
  P1OUT &= ~BIT0;
  P1OUT |= BIT6;
  
  Config_Clock();   // Config xung clock MCU 1MHz
  
  _BIS_SR(GIE);    // Cho phet ngat toan cuc
  
  TACTL |= TASSEL_2 + MC_2 + ID_3 + TAIE; // Chon nguon xung clock tu CDO, Continous Mode, chia 8, bat ngat timer

  while(1){
 
    
  }
}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_ISR(void) {  	
    if( TA0IV ==  10 && TAIFG == 1){
      
      P1OUT ^= BIT0; 
      P1OUT ^= BIT6;        
      
    }
}

void Config_Clock(void){
  
    if ( CALBC1_1MHZ == 0xFF) while(1);
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ; 
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 |= SELM_0; 
}