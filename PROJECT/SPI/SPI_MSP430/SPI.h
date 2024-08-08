/**********************************************************************************************************************

LIBARRY: UART.h
FUNCTION: Interfacing UART  with MSP430G2553
CREATED: 12/5/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/


/*-----------------------------------------------------------------------------*/
/*

MSP430G2553 has 2 SPI 


NOTE: This library configures the MSP430g2553 in Master mode 

FIRST: USCIA control (SPI_1)

- Pin CS:       P1.5
- Pin SCK:      P1.4
- Pin MOSI      P1.2
- Pin MISO      P1.1

SECOND: USCIB control (SPI_2)
- Pin CS:       P1.4
- Pin SCK:      P1.5
- Pin MOSI      P1.7
- Pin MISO      P1.6

--------------------------------------------------------------------------------

UCMODEx : select Mode
- 00: 3 pin SPI    --> La che do khong can dung chan CS cua module SPI, dung GPIO lam CS
- 01: 4 pin SPI    --> La che do phai dung chan CS cua module SPI
....


 */
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define SPI_1    0x11
#define SPI_2    0x22
/*-----------------------------------------------------------------------------*/








/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
void SPI_Init(unsigned char Block_SPI);
void SPI_Write(unsigned char data);
unsigned char SPI_Read(void);


/* NOTE: Nen dung ngat de nhan du lieu */

/*-----------------------------------------------------------------------------*/
