#include "msp430g2553.h"
#include "SEG_7_LED.h"


/*--------------------------------------------------------------------------------
Function	: Init_SEG7_LED
Purpose		: Init 7 segment led 
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
void Init_SEG7_LED(void){
  
  MCU_DIR |= (DATA + LATCH + CLK);
  
}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: OutByte
Purpose		: Send byte out 74HC595 
Parameters	: hex, latch signal
Return		: Note
============================== FUNCTION =======================================*/
void OutByte(unsigned char hex, unsigned char latch) {
  
    for (char i = 0; i < 8; i++) {
        if ((hex << i) & 0x80) {
            MCU_OUT_IC595 |= DATA;
        } else {
            MCU_OUT_IC595 &= ~DATA;
        }
        MCU_OUT_IC595 |= CLK;
        MCU_OUT_IC595 &= ~CLK;
    }
    if (latch) {
        MCU_OUT_IC595 &= ~LATCH;
        MCU_OUT_IC595 |= LATCH;
    }
    
}
/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: DisplayNumber
Purpose		: Display numbers on LED
Parameters	: Number 
Return		: Note
============================== FUNCTION =======================================*/
void DisplayNumber(long num) {
  
    for (int n = 0; n < NumberLED; n++) {
          DATA_LED[n] = num % 10;
          num /= 10;
    }
  
    for (int i = 0; i < NumberLED; i++) {
        OutByte(Hex_Number[DATA_LED[i]], 0);
        OutByte(1 << i, 1);
        OutByte(0xFF, 0);
        OutByte(0xFF, 1);
    }
    
}
/*=========================== END - FUNCTION ====================================*/



