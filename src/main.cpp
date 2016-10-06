#include <stdio.h>
#include <MPU6050/MPU6050.h>
#include <I2Cdev/I2Cdev.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

int main()
{
  I2Cdev::initialize();

  printf("MPU6050 online: %s\n", mpu6050.isConnected() ? "YES" : "NO");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());

  return 0;
}
