#ifndef MPU6050_H_
#define MPU6050_H_

#define MPU6050_DEFAULT_ADDRESS     0x68
#define MPU6050_DEFAULT_DEVICE_ID   0x34

#define MPU6050_RA_SELF_TEST_X      0x0D  //[7:5] XA_TEST[4-2], [4:0] XG_TEST[4-0]
#define MPU6050_RA_SELF_TEST_Y      0x0E  //[7:5] YA_TEST[4-2], [4:0] YG_TEST[4-0]
#define MPU6050_RA_SELF_TEST_Z      0x0F  //[7:5] ZA_TEST[4-2], [4:0] ZG_TEST[4-0]
#define MPU6050_RA_SELF_TEST_A      0x10  //[5:4] XA_TEST[1-0], [3:2] YA_TEST[1-0], [1:0] ZA_TEST[1-0]
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
  void setGyroSelfTestEnabled();
  uint8_t getGyroSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r);

  void setFullScaleAccelRange(uint8_t range);
  uint8_t getFullScaleAccelRange();
  void setAccelSelfTestEnabled();
  uint8_t getAccelSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r);

  void getSelfTestFactoryTrim(float *data);

private:
  uint8_t _devAddr;
};

#endif /* MPU6050_H_ */
