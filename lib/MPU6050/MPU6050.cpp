#include "MPU6050.h"

#include <I2Cdev/I2Cdev.h>

MPU6050::MPU6050(uint8_t devAddr) : _devAddr(devAddr)
{}

uint8_t MPU6050::getDeviceId()
{
  uint8_t buffer[1], deviceId;

  if (I2Cdev::readByte(_devAddr, MPU6050_RA_WHO_AM_I, buffer) != 0)
  {
    deviceId = (buffer[0] & 0x7E) >> 2; // mask 0111 1110
  }

  return deviceId;
}

bool MPU6050::isConnected()
{
  return getDeviceId() == MPU6050_DEFAULT_DEVICE_ID;
}
