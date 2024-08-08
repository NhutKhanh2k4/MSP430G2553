#include "I2C_NK.h"


void I2C_USCI_Init(unsigned char slaveAddress)
{
    P1SEL |= BIT6 + BIT7;     // Assign I2C pins to USCI_B0
    P1SEL2|= BIT6 + BIT7;
    
    UCB0CTL1 |= UCSWRST;      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST; // Use SMCLK, keep SW reset
    UCB0BR0 = 12;             // Set the baud rate
    UCB0BR1 = 0;
    UCB0I2CSA = slaveAddress; // Set slave address
    UCB0CTL1 &= ~UCSWRST;     // Clear SW reset, resume operation
}

void I2C_USCI_Set_Address(unsigned char slaveAddress)
{
    UCB0CTL1 |= UCSWRST;      // Enable SW reset
    UCB0I2CSA = slaveAddress; // Set slave address
    UCB0CTL1 &= ~UCSWRST;     // Clear SW reset, resume operation
}

unsigned char I2C_USCI_Write_Byte(unsigned char slaveAddress, unsigned char value)
{
    I2C_USCI_Set_Address(slaveAddress);

    while (UCB0CTL1 & UCTXSTP);   // Ensure stop condition got sent
    UCB0CTL1 |= UCTR + UCTXSTT;   // I2C TX, start condition

    while (!(IFG2 & UCB0TXIFG));  // Wait for TX buffer to be ready
    UCB0TXBUF = value;            // Send data

    while (!(IFG2 & UCB0TXIFG));  // Wait for TX buffer to be ready

    UCB0CTL1 |= UCTXSTP;          // Send stop condition
    while (UCB0CTL1 & UCTXSTP);   // Wait for stop condition to be sent

    return 0;
}

unsigned char I2C_USCI_Read_Byte(unsigned char slaveAddress)
{
    unsigned char data = 0;
    I2C_USCI_Set_Address(slaveAddress);

    while (UCB0CTL1 & UCTXSTP);    // Ensure stop condition got sent
    UCB0CTL1 &= ~UCTR;             // Clear I2C TX bit for RX mode
    UCB0CTL1 |= UCTXSTT;           // I2C start condition

    while (UCB0CTL1 & UCTXSTT);    // Start condition sent?
    UCB0CTL1 |= UCTXSTP;           // Send stop condition

    while (!(IFG2 & UCB0RXIFG));   // Wait for RX buffer (full)
    data = UCB0RXBUF;              // Read data

    return data;
}

unsigned char I2C_USCI_Read_Word(unsigned char slaveAddress, unsigned char *data, unsigned char length)
{
    unsigned char i;
    I2C_USCI_Set_Address(slaveAddress);

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