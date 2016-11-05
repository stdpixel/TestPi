#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

class I2C
{
public:
  I2C(uint8_t devAddr);

  void writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
  void writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
  int writeByte(uint8_t regAddr, uint8_t data);
  void readBit(uint8_t regAddr, uint8_t bitNum, uint8_t* buffer);
  void readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t* buffer);
  void readByte(uint8_t regAddr, uint8_t* buffer);
  void readBytes(uint8_t regAddr, uint8_t length, uint8_t* buffer);

private:
  uint8_t _devAddr;
  int _device;
};

#endif /* I2C_H_ */
