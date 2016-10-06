#include "MPU6050.h"

#include <I2Cdev/I2Cdev.h>
#include <stdio.h>
#include <global.h>

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
