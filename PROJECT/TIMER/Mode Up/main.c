
#include "msp430g2553.h"

void Config_Clock(void);
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  P1DIR |= BIT0 + BIT6;
  P1OUT &= ~BIT0;
  P1OUT |= BIT6;
  
  Config_Clock(); // 1Mhz
  __bis_SR_register(GIE);
  
  //TIMER0_A0_VECTOR
  TA0CTL |= TASSEL_2 + MC_1 + ID_0 + TAIE;
  TA0CCR0 = 10000 ;
  TA0CCTL0 = CCIE; 
  
  /*TIMER0_A1_VECTOR*/
  /*TA0CTL |= TASSEL_2 + MC_1 + ID_0 + TAIE;
  TA0CCR0 = 6000 ;*/

  /*TIMER1_A0_VECTOR*/
    /*TA1CCTL0 = CCIE;                
    TA1CCR0 = 62500 - 1;            
    TA1CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;
  
  /*TIMER1_A1_VECTOR*/          
    /*TA1CCR0 = 62500 - 1;            
    TA1CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;*/
  
  
  while(1){
 
    
  }
  
  
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_ISR(void) {  	
    if( TA0IV ==  10){          // Timer A0
      
      P1OUT ^= BIT0;
      P1OUT ^= BIT6;        
    
    }
    /*if( TA1IV ==  10){        // Timer A1
      
      P1OUT ^= BIT0;
      P1OUT ^= BIT6;        
    
    }*/
}


void Config_Clock(void){
    if ( CALBC1_1MHZ == 0xFF) while(1);
    DCOCTL = 0;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 |= SELM_0; 
}