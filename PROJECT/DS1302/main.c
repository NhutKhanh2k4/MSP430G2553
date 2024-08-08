#include <msp430g2553.h>
#include "UART.h"
#include <stdio.h>
#include "DS1302.h"


void Config_Clock(void);
unsigned char weekday[7][10] = {"Mo","Tu","We","Th","Fr","Sa","Su"};
char time[30];
char day[30];

 void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    Config_Clock();
    Uart_Init(9600);
    __bis_SR_register(GIE);

    DS1302_Init();
    DateTime rtc = {0,45,19,4,6,2,24};
    
    DS1302_Set_Time(&rtc);
    while(1){
         
        DS1302_Read_Time(&rtc);
        sprintf(time,"TIME: %02d:%02d:%02d  \n", rtc.hour, rtc.minute, rtc.second);
        sprintf(day,"DAY: %s %02d/%02d/%02d \n\n",weekday[(rtc.dow) - 1], rtc.day, rtc.month, rtc.year); 
        Uart_Write_Str(time);
        Uart_Write_Str(day);
        __delay_cycles(1000000);
    }
}



void Config_Clock(void)
{
    if (CALBC1_1MHZ == 0xFF) {  // N?u không có giá tr? hi?u ch?nh
        while(1);               // D?ng chuong trình
    }
    DCOCTL = 0;                 // Ch?n t?n s? th?p nh?t
    BCSCTL1 = CALBC1_1MHZ;      // Cài d?t DCO cho 1MHz
    DCOCTL = CALDCO_1MHZ;       // Cài d?t DCO cho 1MHz
}
