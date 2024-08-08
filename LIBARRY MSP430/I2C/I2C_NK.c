#include "I2C_NK.h"


/*-----------------------------------------------------------------------------*/
/* Function implementations 												   */
/*-----------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------
Function	: I2C_Init
Purpose		: Init and configure for Modul I2C
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void I2C_Init(unsigned char slaveAddress)
{
    P1SEL |= BIT6 + BIT7;     // Assign I2C pins to USCI_B0
    P1SEL2|= BIT6 + BIT7;
    
    UCB0CTL1 |= UCSWRST;      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST; // Use SMCLK, keep SW reset
    UCB0BR0 = 10;             // Set the baud rate
    UCB0BR1 = 0;
    UCB0I2CSA = slaveAddress; // Set slave address
    UCB0CTL1 &= ~UCSWRST;     // Clear SW reset, resume operation
}
/*=========================== END - FUNCTION ====================================*/



/*--------------------------------------------------------------------------------
Function	: I2C_Set_Address
Purpose		: Set address slave 
Parameters	: address slave 
Return		: Note
============================== FUNCTION =======================================*/
void I2C_Set_Address(unsigned char slaveAddress)
{
    UCB0CTL1 |= UCSWRST;      // Enable SW reset
    UCB0I2CSA = slaveAddress; // Set slave address
    UCB0CTL1 &= ~UCSWRST;     // Clear SW reset, resume operation
}
/*=========================== END - FUNCTION ===================================*/


/*--------------------------------------------------------------------------------
Function	: I2C_Write_Byte
Purpose		: Send 1 byte data to slave 
Parameters	: address slave , byte data
Return		: None
============================== FUNCTION =======================================*/
void I2C_Write_Byte(unsigned char slaveAddress, unsigned char byte)
{
    I2C_Set_Address(slaveAddress);

    while (UCB0CTL1 & UCTXSTP);   // Ensure stop condition got sent
    UCB0CTL1 |= UCTR + UCTXSTT;   // I2C TX, start condition

    while (!(IFG2 & UCB0TXIFG));  // Wait for TX buffer to be ready
    UCB0TXBUF = byte;            // Send data

    while (!(IFG2 & UCB0TXIFG));  // Wait for TX buffer to be ready

    UCB0CTL1 |= UCTXSTP;          // Send stop condition
    while (UCB0CTL1 & UCTXSTP);   // Wait for stop condition to be sent

}
/*=========================== END - FUNCTION ===================================*/


/*--------------------------------------------------------------------------------
Function	: I2C_Read_Byte
Purpose		: Read 1 byte data to slave 
Parameters	: address slave
Return		: 1 byte data
============================== FUNCTION =======================================*/
unsigned char I2C_Read_Byte(unsigned char slaveAddress)
{
    unsigned char data = 0;
    I2C_Set_Address(slaveAddress);

    while (UCB0CTL1 & UCTXSTP);    // Ensure stop condition got sent
    UCB0CTL1 &= ~UCTR;             // Clear I2C TX bit for RX mode
    UCB0CTL1 |= UCTXSTT;           // I2C start condition

    while (UCB0CTL1 & UCTXSTT);    // Start condition sent?
    UCB0CTL1 |= UCTXSTP;           // Send stop condition

    while (!(IFG2 & UCB0RXIFG));   // Wait for RX buffer (full)
    data = UCB0RXBUF;              // Read data

    return data;
}
/*=========================== END - FUNCTION ===================================*/





/*------------------------------------------------------------------------------
Function	: I2C_Read_String
Purpose		: Read String data to slave 
Parameters	: Address slave, string name, length string
Return		: 1 string data
============================== FUNCTION =======================================*/
unsigned char I2C_Read_String(unsigned char slaveAddress, unsigned char *data, unsigned char length)
{
    unsigned char i;
    I2C_Set_Address(slaveAddress);

    while (UCB0CTL1 & UCTXSTP);    // Ensure stop condition got sent
    UCB0CTL1 &= ~UCTR;             // Clear I2C TX bit for RX mode
    UCB0CTL1 |= UCTXSTT;           // I2C start condition

    while (UCB0CTL1 & UCTXSTT);    // Wait for start condition to be sent

    for (i = 0; i < length - 1; i++)
    {
        while (!(IFG2 & UCB0RXIFG)); // Wait for RX buffer (full)
        data[i] = UCB0RXBUF;         // Read data
    }
    
    UCB0CTL1 |= UCTXSTP;             // Send stop condition
    while (!(IFG2 & UCB0RXIFG));     // Wait for RX buffer (full)
    data[length - 1] = UCB0RXBUF;    // Read data

    return 0;
}
/*=========================== END - FUNCTION ===================================*/





/*------------------------------------------------------------------------------
Function	: i2c_start
Purpose		: start interfacing I2C 
Parameters	: address slave, operating mode 
Return		: none
============================== FUNCTION =======================================*/
void i2c_start(unsigned char slaveAddress, unsigned char mode){
    I2C_Set_Address(slaveAddress);
    while (UCB0CTL1 & UCTXSTP);         // Wait for the current communication to complete
    if ( mode == 1){                    // mode == 1 => Write data
      UCB0CTL1 |= UCTR + UCTXSTT;  
      while (!(IFG2 & UCB0TXIFG));      // Wait for the transmit buffer to be ready
    }
    else {                              // mode == 0 ==> Read data   
      UCB0CTL1 &= ~UCTR;                // Set to receive mode
      UCB0CTL1 |= UCTXSTT;              // Send start condition
      while (UCB0CTL1 & UCTXSTT);       // Wait for the start condition to be sent
      
      
    }
}
/*=========================== END - FUNCTION ===================================*/





/*------------------------------------------------------------------------------
Function	: i2c_write_byte
Purpose		: send 1 byte data to Slave
Parameters	: 1 byte data
Return		: none
============================== FUNCTION =======================================*/
void i2c_write_byte(unsigned char byte)
{
    UCB0TXBUF = byte;                   // put bytes into transmission buffer
    while (!(IFG2 & UCB0TXIFG));        // Wait for TX buffer to be ready
}
/*=========================== END - FUNCTION ===================================*/



/*------------------------------------------------------------------------------
Function	: i2c_read_byte
Purpose		: Read 1 byte to slave
Parameters	: bit ack ( dung de xac dinh co muon read data nua khong )
Return		: 1 byte data
============================== FUNCTION =======================================*/
unsigned char i2c_read_byte(unsigned char ack)
{
    
    while (!(IFG2 & UCB0RXIFG));     // Wait for the receive buffer to be ready
    unsigned char byte = UCB0RXBUF;  // Read byte from receive buffer

    if (ack)
    {
        UCB0CTL1 &= ~UCTXNACK;       // Prepare to send ACK
    }
    else
    {
        UCB0CTL1 |= UCTXNACK;        // Prepare to send NACK
        UCB0CTL1 |= UCTXSTP; 
    }
    return byte;
}
/*=========================== END - FUNCTION ===================================*/


/*------------------------------------------------------------------------------
Function	: i2c_stop
Purpose		: Stop interfacing I2C
Parameters	: none
Return		: none
============================== FUNCTION =======================================*/
void i2c_stop(void)
{
    UCB0CTL1 |= UCTXSTP;        // Send stop condition
    while (UCB0CTL1 & UCTXSTP); // Wait for stop condition to be sent
}
/*=========================== END - FUNCTION ===================================*/


