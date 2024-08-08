/**********************************************************************************************************************

LIBARRY: I2C.h
FUNCTION: Interfacing I2C
CREATED: 23/5/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/


/*-----------------------------------------------------------------------------*/
/* Header inclusions */
/*-----------------------------------------------------------------------------*/
#include <msp430g2553.h>


/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/*Khoi tao module I2C  */
void I2C_Init(unsigned char slaveAddress);
void I2C_Set_Address(unsigned char slaveAddress);
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/*Function giao tiep i2c ( model 1)
  Note: Moi 1 lan giao tiep 12c thì chi read or wrtie 1 byte*/
void I2C_Write_Byte(unsigned char slaveAddress, unsigned char byte);
unsigned char I2C_Read_Byte(unsigned char slaveAddress);
unsigned char I2C_Read_String(unsigned char slaveAddress, unsigned char *data, unsigned char length);
/*-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------*/
/*Function giao tiep i2c ( model 2)
  Note: Khi bat dau giao tiep i2c, co the doc or ghi nhieu byte trong 1 lan giao tiep*/
void i2c_start(unsigned char slaveAddress, unsigned char mode); //Mode write data (mode = 1),  Mode Read data (mode = 0).
void i2c_write_byte(unsigned char byte);
unsigned char i2c_read_byte(unsigned char ack);  // ack = 1 => tiep tuc doc, ack = 0 => dung doc
void i2c_stop(void);


/*
@  Sample program Write data

    i2c_start(Address, 1);
    i2c_write_byte(data);
    i2c_write_byte(data);
    ......
    i2c_stop();

@ Sample program Read data

    i2c_start(Address, 0);
    data1 = i2c_read_byte(1);
    data2 = i2c_read_byte(1);
    ......
    data1 = i2c_read_byte(0); // stop read
    i2c_stop();

*/


/*-----------------------------------------------------------------------------*/





