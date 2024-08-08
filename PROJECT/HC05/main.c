#include <msp430g2553.h>
#include "UART.h"
#include <stdio.h>


#define Trig    BIT0
#define Echo    BIT1


void Config_Clock(void);
unsigned long millis(void);
void Timer_Init(void);
void Get_HC05(void);

volatile unsigned long millis_count = 0;
char buff[30];

float Distance;
unsigned long start, end ;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    Config_Clock();
    Timer_Init();
    Uart_Init(9600);
    
    P2DIR |= Trig;
    P2DIR &=~ Echo;
    P2OUT &=~ Trig ;
    
    __bis_SR_register(GIE);

    while(1)
    {
        Get_HC05();
        sprintf(buff, "%.2f   \n", Distance);
        Uart_Write_Str(buff);
         __delay_cycles(100000);   
    }
}

void Get_HC05(void){

  P2OUT &=~ Trig;
   __delay_cycles(2);
  P2OUT |= Trig;
  __delay_cycles(20);
  P2OUT &=~ Trig;
  
  P2IE |= Echo; 	// Cho phep ngat tren chân Echo
  P2IES |= Echo; 	// Chon ngat cach xuong
  P2IFG &= ~Echo; 	// Xóa co ngat trên chân Echo
  
  while((P2IN & Echo) == 0);
  start = millis();
}

#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void) {
    if (P2IFG & Echo) { 
        P2IFG &= ~Echo; // Xóa co ngat
        end = millis();
        Distance = ((end - start) * 23.8)/ 29.412 / 2;  // (end - start) = so tich | so tich * nhan 23 us => tg (us)
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_ISR(void){ 
    millis_count++;  // 1 tick = 23 us
}

void Timer_Init(void){
    TACTL = TASSEL_2 + ID_0 + MC_1 + TACLR; // SMCLK, không chia, Mode Up, xóa Timer
    TACCR0 = 20;                // 23us
    TACCTL0 = CCIE; 
}

unsigned long millis(void){
    unsigned long millis_copy;
    __bic_SR_register(GIE);
    millis_copy = millis_count;
    __bis_SR_register(GIE); 
    return millis_copy;
}


void Config_Clock(void)
{
    if (CALBC1_1MHZ == 0xFF) {  
        while(1);               
    }
    DCOCTL = 0;                 
    BCSCTL1 = CALBC1_1MHZ;     
    DCOCTL = CALDCO_1MHZ;       
}
