/*******************************************************************************

LIBARRY: SEG_7_LED.h
FUNCTION: Interfacing 7 Segment led  with MSP430G2553
CREATED: 1/6/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

*******************************************************************************/




/*============================================================================*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define SEG_1   0x01            // 1 LED
#define SEG_2   0x02            // 2 LED
#define SEG_4   0x04            // 4 LED
#define SEG_6   0x06            // 6 LED
#define SEG_8   0x08            // 8 LED
#define PORD_1  0xA1            // PORD CONTROL
#define PORD_2  0xA2            // PORD CONTROL
/*============================================================================*/





/*============================================================================*/
/* Defines interface pins with 7 Segment LED*/
/*-----------------------------------------------------------------------------*/
#define SEG7_LED_PORD   PORD_2
#define DATA            BIT0
#define LATCH           BIT1
#define CLK             BIT2
#define NumberLED       SEG_4          
/*============================================================================*/



/*============================================================================*/
/* Defines the PORD function of the MCU */
/*-----------------------------------------------------------------------------*/
#if SEG7_LED_PORD == PORD_1

  #define MCU_DIR               P1DIR
  #define MCU_OUT_IC595         P1OUT

#elif SEG7_LED_PORD == PORD_2

  #define MCU_DIR               P2DIR
  #define MCU_OUT_IC595         P2OUT

#endif
/*============================================================================*/




extern  char DATA_LED[NumberLED];
extern  char Hex_Number[10];

/******************************************************************************
              COPY AND PASTE INTO MAIN.C TO AVOID ERRORS
                    
-------------------------------------------------------------------------------
                      ( 7 SEGMENT LED ANODE )
char DATA_LED[NumberLED];
char Hex_Number[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
-------------------------------------------------------------------------------
                      ( 7 SEGMENT LED CATHODE )

unsigned char DATA_LED[NumberLED];
unsigned char Hex_Number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
-------------------------------------------------------------------------------
NOTE: Neu muon hien dau cham (dp) => Hex_Number[i] |= 0x80;

*******************************************************************************/




/*============================================================================*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
void Init_SEG7_LED(void);
void OutByte(unsigned char hex, unsigned char latch);
void DisplayNumber(long num);
/*============================================================================*/
