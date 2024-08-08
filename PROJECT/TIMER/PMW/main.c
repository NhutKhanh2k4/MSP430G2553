
#include "msp430g2553.h"

void Config_Clock(void);



void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL  = CALDCO_1MHZ;

  P1DIR |= BIT2 + BIT6;
  P1SEL |= BIT2 + BIT6;  // Cau hinh chan pwm

  
  TA0CCR0 = 999;  // Chu ki
  TA0CCR1 = 300;  // Ton
  //TA1CCR2 = 200;
  
  TA0CCTL1 = OUTMOD_7;  // Mode set/reset
  //TA1CCTL2 = OUTMOD_7;
       
  TA0CTL = TASSEL_2 | ID_3 | MC_1; // Xung clock DCO, Chia 8, Mode up
    
  

  while(1){
     
    
  }
  
  
}

void Config_Clock(void){
    if ( CALBC1_1MHZ == 0xFF) while(1);
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ; 
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 |= SELM_0; 
}