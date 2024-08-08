#include "msp430g2553.h"
#include "UART.h"
#include <stdio.h>
#include "ADC.h"

void Config_Clock(void);


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // D?ng Watchdog Timer

    Config_Clock();
    Uart_Init(9600);
    ADC_Init(CHANNEL_A3);

    unsigned int adc;
    char buff[20];

    while(1)
    {
        adc = ADC_Get_Value();          // Ð?c giá tr? ADC t? chân A5
        sprintf(buff, "%d   \n", adc);  // Chuy?n d?i giá tr? ADC thành chu?i
        Uart_Write_Str(buff);           // G?i chu?i qua UART
        __delay_cycles(500000);         // Ð?i m?t kho?ng th?i gian
    }
}



void Config_Clock(void)
{
    if (CALBC1_1MHZ == 0xFF) while(1); // N?u không có giá tr? hi?u chu?n, d?ng l?i
    DCOCTL = 0;                        // Xóa các bit DCO
    BCSCTL1 = CALBC1_1MHZ;             // Thi?t l?p giá tr? hi?u chu?n cho xung nh?p 1MHz
    DCOCTL = CALDCO_1MHZ;              // Thi?t l?p giá tr? DCO tuong ?ng
}
