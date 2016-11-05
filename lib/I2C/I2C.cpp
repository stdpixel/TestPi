#include "I2C.h"
#include <wiringPiI2C.h>
#include <stdio.h>

I2C::I2C(uint8_t devAddr) : _devAddr(devAddr)
{
  _device = wiringPiI2CSetup(devAddr);
  if (_device == -1) {
    printf("Cannot connect to i2c device: 0x%x", devAddr);
  }
}

void I2C::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
{
  writeBits(regAddr, bitNum, 1, data);
}

void I2C::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
  uint8_t buffer;
  readByte(regAddr, &buffer);

  uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
  data <<= (bitStart - length + 1); // shift data into correct position
  data &= mask; // zero all non-important bits in data
  buffer &= ~(mask); // zero all important bits in existing byte
  buffer |= data; // combine data with existing byte

  wiringPiI2CWriteReg8(_device, regAddr, buffer);
}

/**
 * Write single byte to an 8-bit device register.
 *
 * @param regAddr Register address to write to
 * @param data New byte value to write
 *
 * @return -1 for error
 */
int I2C::writeByte(uint8_t regAddr, uint8_t data)
{
  return wiringPiI2CWriteReg8(_device, regAddr, data);
}

void I2C::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* buffer)
{
  readBits(regAddr, bitNum, 1, buffer);
}

void I2C::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* buffer)
{
  readByte(regAddr, buffer);
  uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
  buffer[0] &= mask;
  buffer[0] >>= (bitStart - length + 1);
}

void I2C::readByte(uint8_t regAddr, uint8_t* buffer)
{
  buffer[0] = (uint8_t)wiringPiI2CReadReg8(_device, regAddr);
}

void I2C::readBytes(uint8_t regAddr, uint8_t length, uint8_t* buffer)
{
  for (int i = 0; i < length; i++) {
    uint8_t reg = regAddr + i;
    uint8_t tBuf;
    readByte(reg, &tBuf);
    buffer[i] = tBuf;
  }
}
