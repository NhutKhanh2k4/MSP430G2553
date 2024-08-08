/**********************************************************************************************************************

LIBARRY: ADC.h
FUNCTION: Read ADC with MSP430G2553
CREATED: 26/5/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/




/*-----------------------------------------------------------------------------*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define CHANNEL_A0      0
#define CHANNEL_A1      1
#define CHANNEL_A2      2
#define CHANNEL_A3      3
#define CHANNEL_A4      4
#define CHANNEL_A5      5
#define CHANNEL_A6      6
#define CHANNEL_A7      7
/*-----------------------------------------------------------------------------*/




/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
void ADC_Init(unsigned char channel);           // Single-Channel Mode
unsigned int ADC_Get_Value(void);

/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/* Function prototypes Other Mode  */
/*-----------------------------------------------------------------------------*/
void ADC_Init_Mode2(unsigned char end_channel);         // Sequence-of-Channels Mode
void Start_ADC_Mode2(void);                             // Bat dau quá trình chuyen doi
unsigned int ADC_Get_Value_Mode2(void);


void ADC_Init_Mode3(unsigned char channel);             // Repeat-Single-Channel Mode
void Start_ADC_Mode3(void);                             // Bat dau quá trình chuyen doi
unsigned int ADC_Get_Value_Mode3(void);


void ADC_Init_Mode4(unsigned char end_channel);         // Repeat-Sequence-of-Channels Mode      
void Start_ADC_Mode4(void);                             // Bat dau quá trình chuyen doi
unsigned int ADC_Get_Value_Mode4(void);
/*-----------------------------------------------------------------------------*/









