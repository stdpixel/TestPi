#include <stdio.h>
#include <MPU6050/MPU6050.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

void setup()
{
  printf("MPU6050 online: %s\n", mpu6050.isConnected() ? "YES" : "NO");

  mpu6050.setSleepEnabled(false);
  mpu6050.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu6050.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

  delay(250);
}

void loop()
{
  printf("========= CONFIG =========\n");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());
  printf("Sleep enabled: %s\n", mpu6050.isSleepEnabled() ? "YES" : "NO");
  printf("Gyro range: 0x0%i\n", mpu6050.getFullScaleGyroRange());
  printf("Accel range: 0x0%i\n", mpu6050.getFullScaleAccelRange());
  printf("\n");

  delay(3000);
}
