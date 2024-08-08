#include <msp430g2553.h>

void I2C_USCI_Init(unsigned char slaveAddress);
void I2C_USCI_Set_Address(unsigned char slaveAddress);
unsigned char I2C_USCI_Write_Byte(unsigned char slaveAddress, unsigned char value);
unsigned char I2C_USCI_Read_Byte(unsigned char slaveAddress);
unsigned char I2C_USCI_Read_Word(unsigned char slaveAddress, unsigned char *data, unsigned char length);