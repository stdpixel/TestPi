#include <stdio.h>
#include <MPU6050/MPU6050.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

void setup()
{
  printf("MPU6050 online: %s\n", mpu6050.isConnected() ? "YES" : "NO");
  if (!mpu6050.isConnected())
  {
    while (1)
    {
      delay(1000);
    }
  }
  mpu6050.setSleepEnabled(false);
  mpu6050.setGyroSelfTestEnabled();
  mpu6050.setAccelSelfTestEnabled();

  // mpu6050.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  // mpu6050.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

  delay(250);
}

void loop()
{
  printf("========= CONFIG =========\n");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());
  printf("Sleep enabled: %s\n", mpu6050.isSleepEnabled() ? "YES" : "NO");
  printf("Gyro range: 0x0%i\n", mpu6050.getFullScaleGyroRange());
  printf("Accel range: 0x0%i\n", mpu6050.getFullScaleAccelRange());

  uint8_t x, y, z, r;

  mpu6050.getGyroSelfTestEnabled(&x, &y, &z, &r);
  printf("Gyro SelfTest Enabled: x(%i) y(%i) z(%i) r(0x0%i)\n", x, y, z, r);

  mpu6050.getAccelSelfTestEnabled(&x, &y, &z, &r);
  printf("Accel SelfTest Enabled: x(%i) y(%i) z(%i) r(0x0%i)\n", x, y, z, r);
  printf("\n");

  float selfTest[6];

  mpu6050.getSelfTestFactoryTrim(selfTest);
  printf("x-axis self test: acceleration trim within: %f of factory value\n", selfTest[0]);
  printf("y-axis self test: acceleration trim within: %f of factory value\n", selfTest[1]);
  printf("z-axis self test: acceleration trim within: %f of factory value\n", selfTest[2]);
  printf("x-axis self test: gyration trim within: %f of factory value\n", selfTest[3]);
  printf("y-axis self test: gyration trim within: %f of factory value\n", selfTest[4]);
  printf("z-axis self test: gyration trim within: %f of factory value\n", selfTest[5]);

  if(selfTest[0] < 1.0f && selfTest[1] < 1.0f && selfTest[2] < 1.0f && selfTest[3] < 1.0f && selfTest[4] < 1.0f && selfTest[5] < 1.0f)
    printf("Self test: PASS");
  else
    printf("Self test: FAILED");

  printf("\n");
  delay(3000);
}
