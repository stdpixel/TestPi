#include <stdio.h>
#include <MPU6050/MPU6050.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

void setup()
{
  printf("MPU6050 online: %s\n", mpu6050.isConnected() ? "YES" : "NO");
  mpu6050.setSleepEnabled(false);
}

void loop()
{
  printf("========= CONFIG =========\n");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());
  printf("Sleep enabled: %s\n", mpu6050.isSleepEnabled() ? "YES" : "NO");
  printf("\n");

  delay(3000);
}
