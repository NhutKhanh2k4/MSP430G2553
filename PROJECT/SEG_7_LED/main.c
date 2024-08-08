#include "msp430g2553.h"
#include "SEG_7_LED.h"

long a = 1234;

char DATA_LED[NumberLED] ;
 char Hex_Number[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;

    //P2DIR |= (DATA + LATCH + CLK);
    Init_SEG7_LED();
    
    while (1) {
        
        DisplayNumber(a);
        
    }
}

