/**********************************************************************************************************************

LIBARRY: MPU6050.h
FUNCTION: Interfacing MPU6050
CREATED: 18/5/2024 to 25/5/2024 by Nguyen Nhut Khanh - Co Dien Tu CTU (^_^)

**********************************************************************************************************************/




/*-----------------------------------------------------------------------------*/
/* Local Constant definitions */
/*-----------------------------------------------------------------------------*/
#define MPU6050_ADDR         0x68
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1A
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6B

#define ACCEL_XOUT_H       0x3B
#define ACCEL_XOUT_L       0x3C
#define ACCEL_YOUT_H       0x3D
#define ACCEL_YOUT_L       0x3E
#define ACCEL_ZOUT_H       0x3F
#define ACCEL_ZOUT_L       0x40

#define MPU6050_TEMP_H     0x41
#define MPU6050_TEMP_L     0x42

#define GYRO_XOUT_H        0x43
#define GYRO_XOUT_L        0x44
#define GYRO_YOUT_H        0x45
#define GYRO_YOUT_L        0x46
#define GYRO_ZOUT_H        0x47
#define GYRO_ZOUT_L        0x48

 
#define pi 3.14
/*-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------*/
/* Global variables */
/*-----------------------------------------------------------------------------*/

extern int rawAccX, rawAccY, rawAccZ, rawTemp, rawGyroX, rawGyroY, rawGyroZ;    // Bien ghi nhan gia tri tho

extern float gyroXoffset, gyroYoffset, gyroZoffset;                             // Bien ghi nhan goc can bu        

extern float  accX, accY, accZ, gyroX, gyroY, gyroZ;                                   

extern float angleGyroX, angleGyroY, angleGyroZ,angleAccX, angleAccY, angleAccZ;// Bien trung gian de tinh toan

extern float temp, angleX, angleY, angleZ;                                            // Gia tri can su dung

extern float interval;

extern long preInterval;

extern float accCoef, gyroCoef;
/*-----------------------------------------------------------------------------*/  




/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/
unsigned char readMPU6050(unsigned char reg);

void writeMPU6050(unsigned char reg, unsigned char data);

void mpu6050_begin(void);

void mpu6050_update(void);

void calcGyroOffsets(char console);

float getAngleX();       // Get the Angle X value

float getAngleY();      // Get the Angle Y value

float getAngleZ();      // Get the Angle Z value

float getTemp();        // Get the temperature value
/*-----------------------------------------------------------------------------*/