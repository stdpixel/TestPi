#ifndef MPU6050_H_
#define MPU6050_H_

#define MPU6050_DEFAULT_ADDRESS     0x68
#define MPU6050_DEFAULT_DEVICE_ID   0x34

#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_WHO_AM_I         0x75

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_PWR1_SLEEP_BIT      6

#include <stdint.h>

class MPU6050
{
public:
  MPU6050(uint8_t devAddr);

  uint8_t getDeviceId();
  bool isConnected();

  void setSleepEnabled(bool enabled);
  uint8_t isSleepEnabled();

  void setFullScaleGyroRange(uint8_t range);
  uint8_t getFullScaleGyroRange();

  void setFullScaleAccelRange(uint8_t range);
  uint8_t getFullScaleAccelRange();

private:
  uint8_t _devAddr;
};

#endif /* MPU6050_H_ */
