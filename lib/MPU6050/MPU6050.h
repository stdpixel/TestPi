#ifndef MPU6050_H_
#define MPU6050_H_

#define MPU6050_DEFAULT_ADDRESS     0x68
#define MPU6050_DEFAULT_DEVICE_ID   0x34

#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_WHO_AM_I         0x75

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

private:
  uint8_t _devAddr;
};

#endif /* MPU6050_H_ */
