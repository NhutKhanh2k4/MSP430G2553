#include <msp430g2553.h>

#define BUTTON_PIN BIT3
#define LED_PIN BIT0

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; 

    P1DIR |= LED_PIN; 
    P1OUT &= ~LED_PIN; 
    P1DIR &= ~BUTTON_PIN; 
    
    P1REN |= BUTTON_PIN; // Bat dien tro treo l�n
    P1OUT |= BUTTON_PIN; // �at dien tro keo len

    
    P1IE |= BUTTON_PIN; // Cho phep ngat tren ch�n BUTTON
    P1IES |= BUTTON_PIN; // Chon ngat cach xuong
    P1IFG &= ~BUTTON_PIN; // X�a co ngat tr�n ch�n BUTTON

    _BIS_SR(GIE); // Cho phep ngat toan cuc
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    if (P1IFG & BUTTON_PIN) { // kiem tra co phai ngat tren ch�n BUTTON
        P1OUT ^= LED_PIN; // �ao trang thai LED
        P1IFG &= ~BUTTON_PIN; // X�a co ngat
    }
}
