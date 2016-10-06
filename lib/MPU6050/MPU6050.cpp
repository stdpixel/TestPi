#include "MPU6050.h"

#include <I2Cdev/I2Cdev.h>
#include <stdio.h>

MPU6050::MPU6050(uint8_t devAddr) : _devAddr(devAddr)
{}

uint8_t MPU6050::getDeviceId()
{
  uint8_t buffer, deviceId;

  if (I2Cdev::readByte(_devAddr, MPU6050_RA_WHO_AM_I, &buffer) != 0)
  {
    deviceId = (buffer & 0x7E) >> 1; // mask 0111 1110
  }

  return deviceId;
}

bool MPU6050::isConnected()
{
  return getDeviceId() == MPU6050_DEFAULT_DEVICE_ID;
}

void MPU6050::setSleepEnabled(bool enabled)
{
  I2Cdev::writeBit(_devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

uint8_t MPU6050::isSleepEnabled()
{
  uint8_t buffer;
  I2Cdev::readBit(_devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, &buffer);

  return buffer;
}

void MPU6050::setFullScaleGyroRange(uint8_t range)
{
  I2Cdev::writeBits(_devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

uint8_t MPU6050::getFullScaleGyroRange()
{
  uint8_t buffer;
  I2Cdev::readBits(_devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, &buffer);
  return buffer;
}

void MPU6050::setGyroSelfTestEnabled()
{
  I2Cdev::writeByte(_devAddr, MPU6050_RA_GYRO_CONFIG, 0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
}

uint8_t MPU6050::getGyroSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r)
{
  uint8_t buffer[1], count;

  if ((count = I2Cdev::readByte(_devAddr, MPU6050_RA_GYRO_CONFIG, buffer)) != 0)
  {
    *x = (buffer[0] & 0x80) >> 7; // mask 1000 0000
    *y = (buffer[0] & 0x40) >> 6; // mask 0100 0000
    *z = (buffer[0] & 0x20) >> 5; // mask 0010 0000
    *r = (buffer[0] & 0x18) >> 3; // mask 0001 1000
  }

  return count;
}

void MPU6050::setFullScaleAccelRange(uint8_t range)
{
  I2Cdev::writeBits(_devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

uint8_t MPU6050::getFullScaleAccelRange()
{
  uint8_t buffer;
  I2Cdev::readBits(_devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, &buffer);
  return buffer;
}

void MPU6050::setAccelSelfTestEnabled()
{
  I2Cdev::writeByte(_devAddr, MPU6050_RA_ACCEL_CONFIG, 0xF0); // Enable self test on all three axes and set accelerometer range to +/- 8 g
}

uint8_t MPU6050::getAccelSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r)
{
  uint8_t buffer[1], count;

  if ((count = I2Cdev::readByte(_devAddr, MPU6050_RA_ACCEL_CONFIG, buffer)) != 0)
  {
    *x = (buffer[0] & 0x80) >> 7; // mask 1000 0000
    *y = (buffer[0] & 0x40) >> 6; // mask 0100 0000
    *z = (buffer[0] & 0x20) >> 5; // mask 0010 0000
    *r = (buffer[0] & 0x18) >> 3; // mask 0001 1000
  }

  return count;
}
