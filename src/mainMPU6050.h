#include <stdio.h>
#include <MPU6050/MPU6050.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

void setup()
{}

void loop()
{
  printf("MPU6050 online: %s\n", mpu6050.isConnected() ? "YES" : "NO");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());

  delay(3000);
}
