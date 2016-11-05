#include "MPU6050.h"

#include <I2C/I2C.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>

MPU6050::MPU6050(uint8_t devAddr) : _devAddr(devAddr), _i2c(devAddr)
{}

void MPU6050::initialize()
{
  _i2c.writeByte(MPU6050_RA_FIFO_EN, 0x70); // Enable FIFO for xg, xy, xz 01110000
  // _i2c.writeByte(MPU6050_RA_INT_ENABLE, 0x11); // Enable interrupt for FIFO and DATA_READY 00010001
  _i2c.writeByte(MPU6050_RA_INT_ENABLE, 0x00); // Disable interrupt
  _i2c.writeByte(MPU6050_RA_INT_PIN_CFG, 0x02); // Enable Hardware Interrupt

  setGyroSelfTestEnabled(false);
  setAccelSelfTestEnabled(false);
  setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
  setSleepEnabled(false);
}

uint8_t MPU6050::getDeviceId()
{
  uint8_t buffer, deviceId;

  _i2c.readByte(MPU6050_RA_WHO_AM_I, &buffer);
  deviceId = (buffer & 0x7E) >> 1;

  return deviceId;
}

bool MPU6050::isConnected()
{
  return getDeviceId() == MPU6050_DEFAULT_DEVICE_ID;
}

void MPU6050::setSleepEnabled(bool enabled)
{
  _i2c.writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

uint8_t MPU6050::isSleepEnabled()
{
  uint8_t buffer;
  _i2c.readBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, &buffer);
  return buffer;
}

void MPU6050::setFullScaleGyroRange(uint8_t range)
{
  _i2c.writeBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

uint8_t MPU6050::getFullScaleGyroRange()
{
  uint8_t buffer;
  _i2c.readBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, &buffer);
  return buffer;
}

void MPU6050::setGyroSelfTestEnabled(bool enabled)
{
  uint8_t data = enabled ? 0x0E : 0x00;
  _i2c.writeByte(MPU6050_RA_GYRO_CONFIG, data); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
}

uint8_t MPU6050::getGyroSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r)
{
  uint8_t buffer[1], count;
  _i2c.readByte(MPU6050_RA_GYRO_CONFIG, buffer);

  *x = (buffer[0] & 0x80) >> 7; // mask 1000 0000
  *y = (buffer[0] & 0x40) >> 6; // mask 0100 0000
  *z = (buffer[0] & 0x20) >> 5; // mask 0010 0000
  *r = (buffer[0] & 0x18) >> 3; // mask 0001 1000

  return count;
}

uint8_t MPU6050::readGyroData(int16_t *x, int16_t *y, int16_t *z)
{
  uint8_t buffer[6], count;
  _i2c.readBytes(MPU6050_RA_GYRO_XOUT_H, 6, buffer);

  *x = (int16_t)((buffer[0] << 8) | buffer[1]); // Combine MSB and LSB into signed 16-bit value
  *y = (int16_t)((buffer[2] << 8) | buffer[3]);
  *z = (int16_t)((buffer[4] << 8) | buffer[5]);

  return count;
}

void MPU6050::setFullScaleAccelRange(uint8_t range)
{
  _i2c.writeBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

uint8_t MPU6050::getFullScaleAccelRange()
{
  uint8_t buffer;
  _i2c.readBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, &buffer);
  return buffer;
}

void MPU6050::setAccelSelfTestEnabled(bool enabled)
{
  uint8_t data = enabled ? 0xF0 : 0x00;

  _i2c.writeByte(MPU6050_RA_ACCEL_CONFIG, data); // Enable self test on all three axes and set accelerometer range to +/- 8 g
}

void MPU6050::LDByteWriteI2C(int16_t adress, int16_t config, int16_t data)
{
  _i2c.writeByte(config, data); // Enable self test on all three axes and set accelerometer range to +/- 8 g
}

uint8_t MPU6050::getAccelSelfTestEnabled(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *r)
{
  uint8_t buffer[1], count;
  _i2c.readByte(MPU6050_RA_ACCEL_CONFIG, buffer);

  *x = (buffer[0] & 0x80) >> 7; // mask 1000 0000
  *y = (buffer[0] & 0x40) >> 6; // mask 0100 0000
  *z = (buffer[0] & 0x20) >> 5; // mask 0010 0000
  *r = (buffer[0] & 0x18) >> 3; // mask 0001 1000

  return count;
}

uint8_t MPU6050::readAccelData(int16_t *x, int16_t *y, int16_t *z)
{
  uint8_t buffer[6], count;
  _i2c.readBytes(MPU6050_RA_ACCEL_XOUT_H, 6, buffer); // Read 6 raw registers as fast as possible

  *x = (int16_t)((buffer[0] << 8) | buffer[1]); // Combine MSB and LSB into signed 16-bit value
  *y = (int16_t)((buffer[2] << 8) | buffer[3]);
  *z = (int16_t)((buffer[4] << 8) | buffer[5]);

  return count;
}

void MPU6050::Calibrate_Gyros( float *GYRO_XOUT_OFFSET,float *GYRO_YOUT_OFFSET,float *GYRO_ZOUT_OFFSET)
{
  int i =0;
  int16_t x,y,z;
  float GYRO_XOUT_OFFSET_1000SUM;
  float GYRO_YOUT_OFFSET_1000SUM;
  float GYRO_ZOUT_OFFSET_1000SUM;
  for(i = 0; i<1000; i++)
  {
    MPU6050::readGyroData(&x,  &y, &z);

    GYRO_XOUT_OFFSET_1000SUM += (float)x;
    GYRO_YOUT_OFFSET_1000SUM += (float)y;
    GYRO_ZOUT_OFFSET_1000SUM += (float)z;

    delay(1);
  }
   *GYRO_XOUT_OFFSET = GYRO_XOUT_OFFSET_1000SUM/1000.0;
   *GYRO_YOUT_OFFSET = GYRO_YOUT_OFFSET_1000SUM/1000.0;
   *GYRO_ZOUT_OFFSET = GYRO_ZOUT_OFFSET_1000SUM/1000.0;

  //printf("\nGyro X offset sum: %ld Gyro X offset: %d", GYRO_XOUT_OFFSET_1000SUM, GYRO_XOUT_OFFSET);
  //printf("\nGyro Y offset sum: %ld Gyro Y offset: %d", GYRO_YOUT_OFFSET_1000SUM, GYRO_YOUT_OFFSET);
  //printf("\nGyro Z offset sum: %ld Gyro Z offset: %d", GYRO_ZOUT_OFFSET_1000SUM, GYRO_ZOUT_OFFSET);
}

void MPU6050::getSelfTestFactoryTrim(float *data)
{
  uint8_t buffer[1];
  uint8_t rawData[4];
  uint8_t selfTest[6];
  float factoryTrim[6];

  _i2c.readByte(MPU6050_RA_SELF_TEST_X, buffer);
  rawData[0] = buffer[0];

  _i2c.readByte(MPU6050_RA_SELF_TEST_Y, buffer);
  rawData[1] = buffer[0];

  _i2c.readByte(MPU6050_RA_SELF_TEST_Z, buffer);
  rawData[2] = buffer[0];

  _i2c.readByte(MPU6050_RA_SELF_TEST_A, buffer);
  rawData[3] = buffer[0];

  // Extract the acceleration test results first
  selfTest[0] = (rawData[0] >> 3) | (rawData[3] & 0x30) >> 4; // XA_TEST(5bit) Combine MSB SELF_TEST_X with LSB SELF_TEST_A (mask 0011 0000)
  selfTest[1] = (rawData[1] >> 3) | (rawData[3] & 0x0C) >> 4; // YA_TEST(5bit) Combine MSB SELF_TEST_Y with LSB SELF_TEST_A (mask 0000 1100)
  selfTest[2] = (rawData[2] >> 3) | (rawData[3] & 0x03) >> 4; // ZA_TEST(5bit) Combine MSB SELF_TEST_Z with LSB SELF_TEST_A (mask 0000 0011)

  // Extract the gyration test results first
  selfTest[3] = rawData[0] & 0x1F; // XG_TEST(5bit) mask 0001 1111
  selfTest[4] = rawData[1] & 0x1F; // YG_TEST(5bit) mask 0001 1111
  selfTest[5] = rawData[2] & 0x1F; // ZG_TEST(5bit) mask 0001 1111

  // Process results to allow final comparison with factory set values
  factoryTrim[0] = (4096.0 * 0.34) * (pow((0.92 / 0.34), (((float)selfTest[0] - 1.0) / 30.0))); // FT[Xa] factory trim calculation
  factoryTrim[1] = (4096.0 * 0.34) * (pow((0.92 / 0.34), (((float)selfTest[1] - 1.0) / 30.0))); // FT[Ya] factory trim calculation
  factoryTrim[2] = (4096.0 * 0.34) * (pow((0.92 / 0.34), (((float)selfTest[2] - 1.0) / 30.0))); // FT[Za] factory trim calculation
  factoryTrim[3] = (25.0 * 131.0) * (pow(1.046, ((float)selfTest[3] - 1.0))); // FT[Xg] factory trim calculation
  factoryTrim[4] = (-25.0 * 131.0) * (pow(1.046, ((float)selfTest[4] - 1.0))); // FT[Yg] factory trim calculation
  factoryTrim[5] = (25.0 * 131.0) * (pow(1.046, ((float)selfTest[5] - 1.0))); // FT[Zg] factory trim calculation

  for (int i = 0; i < 6; i++)
  {
    data[i] = 100.0 + 100.0*((float)selfTest[i] - factoryTrim[i])/factoryTrim[i]; // Report percent differences
  }
}

uint8_t MPU6050::isInterruptTriggered()
{
  uint8_t buffer;
  _i2c.readBit(MPU6050_RA_INT_STATUS, 4, &buffer);

  return buffer;
}
