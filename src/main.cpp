#include <I2Cdev/I2Cdev.h>
#include <MPU6050/MPU6050.h>
// LOAD PROGRAM
#include "mainMPU6050.h"

int main()
{
  I2Cdev::initialize();

  setup();
  float GYRO_XOUT_OFFSET,GYRO_YOUT_OFFSET,GYRO_ZOUT_OFFSET;
  float totalx, totaly, totalz;

  mpu6050.Calibrate_Gyros(&GYRO_XOUT_OFFSET,&GYRO_YOUT_OFFSET,&GYRO_ZOUT_OFFSET);
  printf("Calibrating gyros with offset %f %f %f \n",GYRO_XOUT_OFFSET,GYRO_YOUT_OFFSET,GYRO_ZOUT_OFFSET );
  while (1)
  {
    loop(totalx, totaly, totalz, GYRO_XOUT_OFFSET,GYRO_YOUT_OFFSET,GYRO_ZOUT_OFFSET);
  }

  return 0;
}
