
/*-----------------------------------------------------------------------------*/
/* Header inclusions */
/*-----------------------------------------------------------------------------*/
#include <msp430g2553.h>
#include "main.h"
#include "mpu6050_NK.h"
#include "I2C_NK.h"
#include "UART.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
/*********************************************************************************/



/*-----------------------------------------------------------------------------*/
/* Function implementations 						       */
/*-----------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------
Function	: writeMPU6050
Purpose		: Write data to the desired register address
Parameters	: register address, 1 byte data
Return		: Note
============================== FUNCTION =======================================*/
void writeMPU6050(unsigned char reg, unsigned char data){
    i2c_start(MPU6050_ADDR, 1);           // Khoi tao giao tiep i2c voi slave de ghi
    i2c_write_byte(reg);                  // Gui dia chi thanh ghi can ghi data vao
    i2c_write_byte(data);                 // Gui data va thanh ghi reg
    i2c_stop();                           // dung giao tiep
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: readMPU6050
Purpose		: Reads data from the desired register address
Parameters	: register address
Return		: 1 byte data
============================== FUNCTION =======================================*/
unsigned char readMPU6050(unsigned char reg) {

    i2c_start(MPU6050_ADDR,1);                    // Khoi tao giao tiep i2c voi slave de ghi
    i2c_write_byte(reg);                          // Gui dia chi thanh ghi can read data
    i2c_stop();                                   // dung giao tiep
    
    i2c_start(MPU6050_ADDR,0);                    // Khoi tao giao tiep i2c voi slave de doc
    unsigned char data = i2c_read_byte(0);         // doc data tu thanh ghi reg
    i2c_stop();                                   // dung giao tiep
    return data;
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: mpu6050_begin
Purpose		: initialization module mpu6050
Parameters	: None
Return		: None
============================== FUNCTION =======================================*/
void mpu6050_begin(void){
  
    accCoef = 0.02f;
    gyroCoef = 0.98f;
    
    writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
    writeMPU6050(MPU6050_CONFIG, 0x00);
    writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
    writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
    writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
    
    preInterval = millis();
  
}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: mpu6050_update
Purpose		: Update the value from mpu6050
Parameters	: None
Return		: None
============================== FUNCTION =======================================*/
void mpu6050_update(void){
  
    /* CACH 1: Read data mpu6050 voi ham readMPU6050() 
    -----------------------------------------------------------*/
    
     /*rawAccX  = (readMPU6050(0x3B) << 8) | readMPU6050(0x3C);
    rawAccY  = (readMPU6050(0x3D) << 8) | readMPU6050(0x3E);
    rawAccZ  = (readMPU6050(0x3F) << 8) | readMPU6050(0x40);
    temp      = (readMPU6050(0x41) << 8) | readMPU6050(0x42);
    rawGyroX = (readMPU6050(0x43) << 8) | readMPU6050(0x44);
    rawGyroY = (readMPU6050(0x45) << 8) | readMPU6050(0x46);
    rawGyroZ = (readMPU6050(0x47) << 8) | readMPU6050(0x48);*/
    /*-----------------------------------------------------------*/
    
    
    /* CACH 2: Read data mpu6050 su dung thu vien I2C
    -----------------------------------------------------------*/
    i2c_start(MPU6050_ADDR,1);                                  // Khoi tao giao tiep i2c voi slave de ghi
    i2c_write_byte(0x3B);                                       // Gui data, dia chi thanh ghi dau tien can read data       
    i2c_stop();                                                 // dung giao tiep
    
    i2c_start(MPU6050_ADDR,0);                                  // Khoi tao giao tiep i2c voi slave de doc
    rawAccX =  i2c_read_byte(1) << 8 | i2c_read_byte(1);        // read 14 byte data
    rawAccY =  i2c_read_byte(1) << 8 | i2c_read_byte(1);
    rawAccZ =  i2c_read_byte(1) << 8 | i2c_read_byte(1);
    rawTemp =  i2c_read_byte(1) << 8 | i2c_read_byte(1);
    rawGyroX = i2c_read_byte(1) << 8 | i2c_read_byte(1);
    rawGyroY = i2c_read_byte(1) << 8 | i2c_read_byte(1);
    rawGyroZ = i2c_read_byte(1) << 8 | i2c_read_byte(0);
    i2c_stop();                        
    /*-----------------------------------------------------------*/
    
    
    accX = ((float)rawAccX) / 16384.0;
    accY = ((float)rawAccY) / 16384.0;
    accZ = ((float)rawAccZ) / 16384.0;

    angleAccX = atan2(accY, accZ + abs(accX)) * 360 / 2.0 / pi;
    angleAccY = atan2(accX, accZ + abs(accY)) * 360 / -2.0 / pi;
    
    temp = (temp / 340) + 36.53 ;
    
    gyroX = ((float)rawGyroX) / 65.5;
    gyroY = ((float)rawGyroY) / 65.5;
    gyroZ = ((float)rawGyroZ) / 65.5; 
    
    gyroX -= gyroXoffset;
    gyroY -= gyroYoffset;
    gyroZ -= gyroZoffset;
    
    interval = (millis() - preInterval) * 0.001;
    
    angleGyroX += gyroX * interval;
    angleGyroY += gyroY * interval;
    angleGyroZ += gyroZ * interval;

    angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
    angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
    angleZ = angleGyroZ; 

    preInterval = millis();
}
/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: calcGyroOffsets
Purpose		: Initialize offset value 
Parameters	: console = 1: Initialize offset value + print uart  ; console = 0: No Initialize
Return		: None
============================== FUNCTION =======================================*/
void calcGyroOffsets(char console){
    float x = 0, y = 0, z = 0;
    int rx, ry, rz;

    __delay_cycles(10000);
    
    if(console){
      Uart_Write_Str("========================================\n");
      Uart_Write_Str("Calculating gyro offsets\n");
      Uart_Write_Str("DO NOT MOVE MPU6050\n");
    }
    
    for(int i = 0; i < 3000; i++){              // Bo loc de tim gia tri bu        
      if(console && i % 1000 == 0){
        Uart_Write('.');
      }
      
      /* CACH 1: Read data mpu6050 voi ham readMPU6050() 
    -----------------------------------------------------------*/
      rx = (readMPU6050(0x43) << 8) | readMPU6050(0x44);
      ry = (readMPU6050(0x45) << 8) | readMPU6050(0x46);
      rz = (readMPU6050(0x47) << 8) | readMPU6050(0x48);
    /*-----------------------------------------------------------*/
      
      
      /* CACH 2: Read data mpu6050 su dung thu vien I2C
    -----------------------------------------------------------*/
      /*i2c_start(MPU6050_ADDR, 1);
      i2c_write_byte(0x43);
      i2c_stop();
      
      i2c_start(MPU6050_ADDR, 0); 
      rx = i2c_read_byte(1) << 8 | i2c_read_byte(1);
      ry = i2c_read_byte(1) << 8 | i2c_read_byte(1);
      rz = i2c_read_byte(1) << 8 | i2c_read_byte(0);*/
    /*-----------------------------------------------------------*/
      
      x += ((float)rx) / 65.5;
      y += ((float)ry) / 65.5;
      z += ((float)rz) / 65.5;
    }
    
    /* Gia tri can bu */
    gyroXoffset = x / 3000;
    gyroYoffset = y / 3000;
    gyroZoffset = z / 3000;

    
    if(console){
      char tmp[50];
      Uart_Write_Str("Done!\n");
      sprintf(tmp, "X: %.2f\nY: %.2f\nZ: %.2f\n\n", gyroXoffset, gyroYoffset, gyroZoffset );
      Uart_Write_Str(tmp);
      Uart_Write_Str("Program will start after 3 seconds\n");
      Uart_Write_Str("========================================\n");
      __delay_cycles(1000000);
    }
}
 /*=========================== END - FUNCTION ====================================*/



float getAngleX(){
  return angleX;
}
float getAngleY(){
  return angleY;
}
float getAngleZ() {
  return angleZ;
}
float getTemp(){ 
   return temp;
}

