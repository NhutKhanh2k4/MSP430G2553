#include "SPI.h"
#include <msp430g2553.h>

/*--------------------------------------------------------------------------------
Function	: SPI_Init
Purpose		: Init and configure for Modul SPI
Parameters	: Block_SPI (USCIA, USCIB)
Return		: Note
============================== FUNCTION =======================================*/
void SPI_Init(unsigned char Block_SPI)
{
    // Cau hình chân SPI

    if (Block_SPI == SPI_1){
      
      P1SEL  |= BIT1 + BIT2+ BIT4 + BIT5 ;  // Chon chuc nang SPI
      P1SEL2 |= BIT1 + BIT2+ BIT4 + BIT5 ; // Chon chuc nang SPI
    }
    if (Block_SPI == SPI_2){
  
      P1SEL |= BIT4 + BIT5 + BIT6 + BIT7;  // Chon chuc nang SPI
      P1SEL2 |= BIT4 + BIT5 + BIT6 + BIT7; // Chon chuc nang SPI
  
    }


    UCB0CTL1 = UCSWRST;                  // Ðat USCI trong che do reset
    UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC + UCMODE_1; // Cau hình: phase = 1, polarity = 0, MSB first, master mode, dong bo, 4-pin
    UCB0CTL1 = UCSSEL_2 + UCSWRST;       // ChOn nguon xung nhip SMCLK, van giu trong che do reset
    UCB0BR0 = 0x02;                      // Chia xung nhip: BRCLK / 2
    UCB0BR1 = 0;                         // Chia xung nhip: BRCLK / 2
    UCB0CTL1 &= ~UCSWRST;                // Thoát khoi che do reset
    
    IE2 |= UCB0RXIE;                     // Cho phép ngat khi nhan du lieu
}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: SPI_Write
Purpose		: Write 1 byte to SPI
Parameters	: 1 byte data
Return		: Note
============================== FUNCTION =======================================*/
void SPI_Write(unsigned char data)
{
    while (!(IFG2 & UCB0TXIFG));  // Ðoi cho bo dem truyen rong
    UCB0TXBUF = data;             // Gui du lieu
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: SPI_Read
Purpose		: Read 1 byte from SPI
Parameters	: None
Return		: 1 byte data
============================== FUNCTION =======================================*/
unsigned char SPI_Read(void)
{
    
    while (!(IFG2 & UCB0RXIFG));  // Ðoi cho bo dem nhan day
    return UCB0RXBUF;             // Ðoc du lieu tu bo dem
}
/*=========================== END - FUNCTION ====================================*/



/*--------------------------------------------------------------------------------
Function	: Chuong trinh phuc vu ngat RX
NOTR		: Khi su dung can copy de vao main.c
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  receivedData = UCB0RXBUF;     
}

------------------------------------------------------------------------------*/