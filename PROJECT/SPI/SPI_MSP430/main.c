#include <msp430g2553.h>
#include "UART.h"
#include "SPI.h"
#include <stdio.h>

void Config_Clock(void);


unsigned char str;
char buff[50];
volatile unsigned char receivedData = 0;
unsigned char data_to_send = 0x01; 
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // D?ng Watchdog Timer

    Config_Clock();
    Uart_Init(9600);
    SPI_Init(SPI_2);
    
    
    P1DIR &= ~BIT3;             
    P1REN |= BIT3;              
    P1OUT |= BIT3;             


    
    __enable_interrupt(); 
    
    while(1)
    {
      
      if (!(P1IN & BIT3)) 
        {
          P1OUT &= ~BIT4;               
          SPI_Write(data_to_send);      
          receivedData = UCB0RXBUF; 
          P1OUT |= BIT4;               
          
          sprintf(buff, "TX %02x  |  RX: %02x \n",data_to_send, receivedData); 
          Uart_Write_Str(buff);         /
          data_to_send++;
          __delay_cycles(500000);       
        }
    }
}


#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  receivedData = UCB0RXBUF;     
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
