#include <msp430g2553.h>

void Config_Clock(void);
void Uart_init(void);
void Uart_SendByte(unsigned char c);
void Uart_SendString(char *str);
unsigned char Uart_Receive(void);
void LED(void);
unsigned char text ;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;			// Stop Watchdog
	
        Config_Clock();
	Uart_init();
        
        P1DIR |= BIT6 + BIT0;
        P1OUT &= ~(BIT6 + BIT0);
        
        while(1){
          
        }
        
}

#pragma vector = USCIAB0RX_VECTOR			// UART RX Interrupt Vector
__interrupt void USCI0RX_ISR(void)
{
	text = UCA0RXBUF;                       
        if( text == 'a'){
            P1OUT |= BIT6;
        }
        else if( text == 'b'){
            P1OUT &= ~BIT6;
        }
        else if ( text == 's'){
          Uart_SendString(" NHUT KHANH ");
        }
        else{  
          Uart_SendByte('x');
          LED();
        }
        //LED();
        
}


void LED(void){
        P1OUT |= BIT0;
        __delay_cycles(100000);
        P1OUT &= ~ BIT0;
        __delay_cycles(100000);
        P1OUT |= BIT0;
        __delay_cycles(100000);
        P1OUT &= ~ BIT0;
}

void Uart_SendString(char *str){
  while(*str != '\0'){
    Uart_SendByte(*str);
    str++;
  }
  
}


void Uart_SendByte(unsigned char data){
    while (!(IFG2 & UCA0TXIFG));   // Ðoi TX buffer trong
    UCA0TXBUF = data;              // Gui du lieu
}


unsigned char Uart_Receive(void){
    while (!(IFG2 & UCA0RXIFG));   // Ðoi RX buffer có du lieu
    return UCA0RXBUF;              // Tra ve du lieu dã nhan
}



void Uart_init(void){
  
      P1SEL = BIT1 + BIT2 ;				// Select UART RX/TX function on P1.1,P1.2
      P1SEL2 = BIT1 + BIT2;
  
      UCA0CTL1 |= UCSSEL_2;				// UART Clock -> SMCLK
      UCA0BR0 = 104;					// Baud Rate Setting for 1MHz 9600
      UCA0BR1 = 0;						// Baud Rate Setting for 1MHz 9600
      UCA0MCTL = UCBRS_1;				// Modulation Setting for 1MHz 9600
      UCA0CTL1 &= ~UCSWRST;				// Initialize UART Module
      IE2 |= UCA0RXIE;                                  // Enable RX interrupt
      //IE2 |= UCA0TXIE;                                  // Enable TX interrupt
      __bis_SR_register(GIE);	                        // Enter LPM0, Enable Interrupt
  
}

void Config_Clock(void){
  if (CALBC1_1MHZ==0xFF)while(1);						
  DCOCTL = 0;							
  BCSCTL1 = CALBC1_1MHZ;				
  DCOCTL = CALDCO_1MHZ;
}
