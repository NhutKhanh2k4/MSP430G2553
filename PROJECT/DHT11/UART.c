#include <msp430g2553.h>
#include "UART.h"

/*--------------------------------------------------------------------------------
Function	: Uart_Init
Purpose		: Init and configure for Modul UART
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void Uart_Init(unsigned int Baud_rate){
  
      P1SEL = BIT1 + BIT2 ;		// Select UART RX/TX function on P1.1,P1.2
      P1SEL2 = BIT1 + BIT2;

      UCA0CTL1 |= UCSSEL_2;		// UART Clock -> SMCLK
      
      UCA0BR0 = 104;			// Baud Rate Setting for 1MHz 9600
      UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 9600
      UCA0MCTL = UCBRS_1;		// Modulation Setting for 1MHz 9600
      
      switch(Baud_rate){
        
        case BAUD_RATE_9600:{
          
            UCA0BR0 = 104;			// Baud Rate Setting for 1MHz 9600
            UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 9600
            UCA0MCTL = UCBRS_1;		        // Modulation Setting for 1MHz 9600
          
        }break;
        
        case BAUD_RATE_19200:{
          
            UCA0BR0 = 52;			// Baud Rate Setting for 1MHz 19200
            UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 19200
            UCA0MCTL = UCBRS_0;		        // Modulation Setting for 1MHz 19200
          
        }break;
        
        case BAUD_RATE_38400:{
          
            UCA0BR0 = 26;			// Baud Rate Setting for 1MHz 38400
            UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 38400
            UCA0MCTL = UCBRS_0;		        // Modulation Setting for 1MHz 38400
          
        }break;
        
        case BAUD_RATE_56000:{
          
            UCA0BR0 = 17;			// Baud Rate Setting for 1MHz 56000
            UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 56000
            UCA0MCTL = UCBRS_7;		        // Modulation Setting for 1MHz 56000
          
        }break;
        
        case BAUD_RATE_115200:{
          
            UCA0BR0 = 8;			// Baud Rate Setting for 1MHz 115200
            UCA0BR1 = 0;			// Baud Rate Setting for 1MHz 115200
            UCA0MCTL = UCBRS_6;		        // Modulation Setting for 1MHz 115200
          
        }break;
      
      }
      
      
      UCA0CTL1 &= ~UCSWRST;		// Initialize UART Module
      IE2 |= UCA0RXIE;                  // Enable RX interrupt
      //IE2 |= UCA0TXIE;                // Enable TX interrupt
      __bis_SR_register(GIE);	        // Enter LPM0, Enable Interrupt
  
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: Uart_Write
Purpose		: Send 1 byte data to UART
Parameters	: 1 byte data
Return		: Note
============================== FUNCTION =======================================*/
void Uart_Write(unsigned char data){
    while (!(IFG2 & UCA0TXIFG));   // Ðoi TX buffer trong
    UCA0TXBUF = data;              // Gui du lieu
}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: Uart_Write_Str
Purpose		: Send 1 string data to UART
Parameters	: 1 string 
Return		: Note
============================== FUNCTION =======================================*/
void Uart_Write_Str(char *str){
  while(*str != '\0'){
    Uart_Write(*str);
    str++;
  }
}
/*=========================== END - FUNCTION ====================================*/



/*--------------------------------------------------------------------------------
Function	: Uart_Read
Purpose		: Read 1 byte data from UART
Parameters	: None
Return		: 1 byte data
============================== FUNCTION =======================================*/
unsigned char Uart_Read(void){
    while (!(IFG2 & UCA0RXIFG));   // Ðoi RX buffer có du lieu
    return UCA0RXBUF;              // Tra ve du lieu dã nhan
}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: UART_ISR
Purpose		: Vector ngat RX, xu ly ngat khi nhan lieu
Parameters	: None
Return		: 1 byte data

NOTE            : Khuyen cao nen dung vector ngat de nhan du lieu
                  Chu khi su dung thi dem vao file main
============================== FUNCTION =======================================*/
/*
#pragma vector = USCIAB0RX_VECTOR			// UART RX Interrupt Vector
__interrupt void UART_ISR(void)
{
    
    //data = UCA0RXBUF; 
    
}
*/
/*=========================== END - FUNCTION ====================================*/





// Neu muon su dung ngat TX thi Enable trong ham Init
/*
#pragma vector = USCIAB0TX_VECTOR			// UART RX Interrupt Vector
__interrupt void USCI0TX_ISR(void)
{
	    
}
*/
