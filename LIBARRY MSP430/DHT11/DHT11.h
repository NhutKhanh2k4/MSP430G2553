/**********************************************************************************************************************

LIBARRY: DHT11.h
FUNCTION: Interfacing DHT11  with MSP430G2553
CREATED: 1/6/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/



/*--------------------------------------------------------------------------------------------
 
                                      Data frame
______________________________________________________________________________________________
Start Sigal |  response signal | integer RH | decimal RH | integer T | decimal T | checkSum |
_____MCU____________DHT11___________DHT11_______DHT11________DHT11______DHT11_______DHT11______


RH: temperature
T: humidity
----------------------------------------------------------------------------------------------- */








/*-----------------------------------------------------------------------------*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define PORD_1  0xF1
#define PORD_2  0xF2
/*-----------------------------------------------------------------------------*/




/*-----------------------------------------------------------------------------*/
/* Defines interface pins with DHT11*/
/*-----------------------------------------------------------------------------*/
#define DHT11_PORT		PORD_2
#define DHT11_PIN 		BIT0
/*-----------------------------------------------------------------------------*/





/*-----------------------------------------------------------------------------*/
/* Defines the GPIO function of the MCU */
/*-----------------------------------------------------------------------------*/

#if DHT11_PORT == PORD_1

  #define MCU_DIR_OUTPUT()	        P1DIR |= DHT11_PIN
  #define MCU_DIR_INPUT()		P1DIR &= ~DHT11_PIN
  #define MCU_INPUT()		       (P1IN & DHT11_PIN)
  #define MCU_OUT_LOW()		        P1OUT &= ~DHT11_PIN
  #define MCU_OUT_HIGH()	        P1OUT |= DHT11_PIN

#elif DHT11_PORT == PORD_2

  #define MCU_DIR_OUTPUT()	        P2DIR |= DHT11_PIN
  #define MCU_DIR_INPUT()		P2DIR &= ~DHT11_PIN
  #define MCU_INPUT()		       (P2IN & DHT11_PIN)
  #define MCU_OUT_LOW()		        P2OUT &= ~DHT11_PIN
  #define MCU_OUT_HIGH()	        P2OUT |= DHT11_PIN

#endif
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
void DHT11_Start();

unsigned char waiting_for_response();

unsigned char DHT11_Read(unsigned char *temperature, unsigned char *humidity); // Chi can goi ham nay trong main.c de doc data tu DHT11
/*-----------------------------------------------------------------------------*/