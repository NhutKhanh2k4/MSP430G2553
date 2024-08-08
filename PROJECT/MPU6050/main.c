#include <msp430g2553.h>
#include "mpu6050_NK.h"
#include "main.h"
#include "I2C_NK.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "UART.h"

int rawAccX, rawAccY, rawAccZ, rawTemp, rawGyroX, rawGyroY, rawGyroZ;
float gyroXoffset, gyroYoffset, gyroZoffset;
float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
float angleGyroX, angleGyroY, angleGyroZ,angleAccX, angleAccY, angleAccZ;
float angleX, angleY, angleZ;
float interval;
long preInterval;
float accCoef , gyroCoef ;

unsigned long millis_count = 0;

char buff[100];

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;			// Stop Watchdog
        Config_Clock();
	Uart_Init(9600);
        Timer_Init();
        __bis_SR_register(GIE);
        
        I2C_Init(MPU6050_ADDR);
        
        mpu6050_begin();
        //calcGyroOffsets(0);
        
        
        while(1){
            mpu6050_update();
            sprintf(buff, "%.2f  |  %.2f  |  %.2f  |  %.2f   \n", temp, angleX, angleY, angleZ);
            Uart_Write_Str(buff);
        }
        
}


void Timer_Init(void){
    TACTL = TASSEL_2 + ID_0 + MC_1 + TACLR; // SMCLK, không chia, Mode Up, xóa Timer
    TACCR0 = 1000 - 1; 
    TACCTL0 = CCIE; 
}


unsigned long millis(void){
    unsigned long millis_copy;
    __bic_SR_register(GIE);
    millis_copy = millis_count;
    __bis_SR_register(GIE); 
    return millis_copy;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_ISR(void){
    millis_count++;
}
 



void Config_Clock(void){
  if (CALBC1_1MHZ==0xFF) while(1);						
  DCOCTL = 0;							
  BCSCTL1 = CALBC1_1MHZ;				
  DCOCTL = CALDCO_1MHZ;
}


