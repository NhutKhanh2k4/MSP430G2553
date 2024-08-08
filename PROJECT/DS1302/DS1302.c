/*============================================================================*/
/* ----------------------INCLUDE LIBRARY  -----------------------------------*/
  #include "DS1302.h"
  #include <msp430g2553.h>
/*============================================================================*/



// Structure that simplifies the conversion from BCD to binary.
struct {
	unsigned char BIT4_L:4;
	unsigned char BIT4_H:4;
}BYTE;



/*--------------------------------------------------------------------------------
Function	: DS1302_Init
Purpose		: nitializes the RST and SCLK pins in OUT mode.
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Init(void)
{
	ENA_DIR_OUTPUT();
	CLK_DIR_OUTPUT();
}
/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: DS1302_Start
Purpose		: Starts the communication with the DS1302
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Start(void)
{
	ENA_LOW();
	CLK_LOW();
	ENA_HIGH();
}
/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: DS1302_Stop
Purpose		: Ends communication with the RTC.
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Stop(void)
{
	ENA_LOW();
}
/*=========================== END - FUNCTION ====================================*/







/*--------------------------------------------------------------------------------
Function	: DS1302_Read_Byte
Purpose		: nRead a byte. The bytes should be read on the falling edge
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
unsigned char DS1302_Read_Byte(void)
{
    unsigned char i,byte_data = 0;
    DATA_DIR_INPUT();

    for(i = 8; i > 0; i--)
    {
        CLK_HIGH();
        CLK_LOW();
        byte_data>>=1;

        if(DATA_INPUT())
        {
            byte_data|=0x80;
        }
    }
    return(byte_data);
}
/*=========================== END - FUNCTION ====================================*/







/*--------------------------------------------------------------------------------
Function	: DS1302_Write_Byte
Purpose		: Writes a byte. The bytes should be written on the rising edge.
Parameters	: 1 byte data
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Write_Byte(unsigned char byte_data)
{
    unsigned char i;
    DATA_DIR_OUTPUT();

    for(i = 8; i > 0; i--)
    {
        if(byte_data&0x01)
        {
            DATA_HIGH();
        }
        else
        {
            DATA_LOW();
        }
        CLK_LOW();
        CLK_HIGH();
        byte_data>>=1;
    }
}
/*=========================== END - FUNCTION ====================================*/







/*--------------------------------------------------------------------------------
Function	: DS1302_Set_Time
Purpose		: Set the date and time individually.
Parameters	: Cau truc du lieu DateTime
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Set_Time(DateTime* dt)
{

    dt->second  =  DS1302_BIN_to_BCD(dt->second) & 0x7f;
    dt->minute  =  DS1302_BIN_to_BCD(dt->minute) & 0x7f;
    dt->hour    =  DS1302_BIN_to_BCD(dt->hour  ) & 0x7f;
    dt->day     =  DS1302_BIN_to_BCD(dt->day   ) & 0x3f;
    dt->month   =  DS1302_BIN_to_BCD(dt->month ) & 0x1f;
    dt->dow     =  DS1302_BIN_to_BCD(dt->dow   ) & 0x07;
    dt->year    =  DS1302_BIN_to_BCD(dt->year  ) & 0xff;

    DS1302_Start();
    DS1302_Write_Byte(DS1302_CONTROL);
    DS1302_Write_Byte(0x00);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_SECONDS);
    DS1302_Write_Byte(dt->second);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_MINUTES);
    DS1302_Write_Byte(dt->minute);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_HOURS);
    DS1302_Write_Byte(dt->hour);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_DATE);
    DS1302_Write_Byte(dt->day);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_MONTH);
    DS1302_Write_Byte(dt->month);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_DAY);
    DS1302_Write_Byte(dt->dow);
    DS1302_Stop();
    
    DS1302_Start();
    DS1302_Write_Byte(DS1302_YEAR);
    DS1302_Write_Byte(dt->year);
    DS1302_Stop();
}
/*=========================== END - FUNCTION ====================================*/






// Read the time from the RTC registers in burst mode.
/*--------------------------------------------------------------------------------
Function	: DS1302_Read_Time
Purpose		: Read the time from the RTC registers in burst mode.
Parameters	: Cau truc du lieu DateTime
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Read_Time(DateTime* dt)
{
    DS1302_Start();
    DS1302_Write_Byte(DS1302_CLOCK_BURST_READ);
    
    dt->second = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->minute = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->hour   = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->day    = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->month  = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->dow    = DS1302_BCD_to_Bin(DS1302_Read_Byte());
    dt->year   = DS1302_BCD_to_Bin(DS1302_Read_Byte());

    DS1302_Stop();
}
/*=========================== END - FUNCTION ====================================*/






//**********************************************************************************************************************************************************
// Writes the RAM in burst mode.
/*--------------------------------------------------------------------------------
Function	: DS1302_Write_RAM
Purpose		: Writes the RAM in burst mode.
Parameters	: point array, lenght array
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Write_RAM(unsigned char *buf,unsigned char len)
{
    unsigned int i;

    DS1302_Start();
    DS1302_Write_Byte(DS1302_CONTROL);
    DS1302_Write_Byte(0x00);
    DS1302_Stop();

	DS1302_Start();
    DS1302_Write_Byte(DS1302_RAM_BURST_WRITE);

    for(i = len; i > 0 ; i--)
    {
       DS1302_Write_Byte(buf[len - i]);
    }

    DS1302_Start();
    DS1302_Write_Byte(DS1302_CONTROL);
    DS1302_Write_Byte(0x80);
    DS1302_Stop();
}
/*=========================== END - FUNCTION ====================================*/






//**********************************************************************************************************************************************************
// Read the RAM in burst mode.
/*--------------------------------------------------------------------------------
Function	: DS1302_Read_RAM
Purpose		: Read the RAM in burst mode.
Parameters	: point array, lenght array
Return		: Note
============================== FUNCTION =======================================*/
void DS1302_Read_RAM(unsigned char *buf,unsigned char len)
{
    unsigned int i;
    DS1302_Start();
    DS1302_Write_Byte(DS1302_RAM_BURST_READ);

    for(i = len; i > 0 ; i--)
    {
        buf[len - i]=DS1302_Read_Byte();
    }

    DS1302_Stop();
}
/*=========================== END - FUNCTION ====================================*/






//**********************************************************************************************************************************************************
// Converts from BCD to binary
/*--------------------------------------------------------------------------------
Function	: DS1302_BCD_to_Bin
Purpose		: Converts from BCD to binary
Parameters	: value to be converted
Return		: Note
============================== FUNCTION =======================================*/
unsigned char DS1302_BCD_to_Bin(unsigned char value)
{
   BYTE.BIT4_H = value / 16;
   BYTE.BIT4_L = value % 16;
   return(BYTE.BIT4_H * 10 + BYTE.BIT4_L);
}
/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: DS1302_BIN_to_BCD
Purpose		: Converts from binary to BCD
Parameters	: value to be converted
Return		: Note
============================== FUNCTION =======================================*/
unsigned char DS1302_BIN_to_BCD(unsigned char value)
{
    BYTE.BIT4_H = value / 10; 
    BYTE.BIT4_L = value % 10;  
    return (BYTE.BIT4_H << 4) | BYTE.BIT4_L; 
}
/*=========================== END - FUNCTION ====================================*/
