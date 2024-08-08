/**********************************************************************************************************************

LIBARRY: DS1302.h
FUNCTION: Interfacing modul RTC DS1302  with MSP430G2553
CREATED: 4/6/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/


/*=============================================================================
                          Set up time
-----------------------------------------------------------------------------

DateTime rtc = {second, minute, hour, day, month, weekdays, year };

#vi du:  DateTime rtc = {0,45,19,4,6,2,24};
         DS1302_Set_Time(&rtc);
==============================================================================*/




/*============================================================================*/
/* Defines interface pins with modul DS1302 */
/*-----------------------------------------------------------------------------*/
#define CLK             BIT3                        //1302 clock
#define DATA            BIT4                       //1302 data
#define ENA             BIT5                       //1302 enable bit (RST/CE)
#define PORD_DIR        P1DIR
#define PORD_OUT        P1OUT
#define PORD_IN         P1IN
/*============================================================================*/




/*============================================================================*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_CONTROL		 0x8E
#define DS1302_TRICKLE		 0x90
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF
/*============================================================================*/




/*============================================================================*/
/* Defines to configure pins. */
/*-----------------------------------------------------------------------------*/
#define ENA_DIR_OUTPUT()		{PORD_DIR |= ENA; P1REN &= ~ENA;}
#define ENA_HIGH()     		        PORD_OUT |= ENA
#define ENA_LOW()     		        PORD_OUT &= ~ENA

#define CLK_DIR_OUTPUT()		{PORD_DIR |= CLK; P1REN &= ~CLK;}
#define CLK_HIGH()     		        PORD_OUT |= CLK
#define CLK_LOW()     		        PORD_OUT &= ~CLK

#define DATA_HIGH()      	        PORD_OUT |= DATA
#define DATA_LOW()      	        PORD_OUT &= ~DATA
#define DATA_INPUT()      	        PORD_IN  &  DATA
#define DATA_DIR_OUTPUT()   	        {PORD_DIR |= DATA; P1REN &= ~DATA;}
#define DATA_DIR_INPUT()   	        {PORD_DIR &= ~DATA; P1REN &= ~DATA;}

/*============================================================================*/



typedef struct {
      unsigned char second;
      unsigned char minute;
      unsigned char hour;
      unsigned char day;          
      unsigned char month;          
      unsigned char dow;          
      unsigned char year;   
} DateTime;



/*============================================================================*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
void DS1302_Init(void);

void DS1302_Start(void);

void DS1302_Stop(void);

unsigned char DS1302_Read_Byte(void);

void DS1302_Write_Byte(unsigned char);

void DS1302_Set_Time(DateTime* dt);

void DS1302_Read_Time(DateTime* dt);

void DS1302_Write_RAM(unsigned char *,unsigned char);

void DS1302_Read_RAM(unsigned char *,unsigned char char8_t);

unsigned char DS1302_BCD_to_Bin(unsigned char value);

unsigned char DS1302_BIN_to_BCD(unsigned char value);

/*============================================================================*/


