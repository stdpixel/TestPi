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


  //Sets sample rate to 8000/1+7 = 1000Hz
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, 0x07);
  //Disable FSync, 256Hz DLPF
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x00);
  //Disable gyro self tests, scale of 500 degrees/s
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0b00001000);
  //Disable accel self tests, scale of +-2g, no DHPF
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 0x00);
  //Freefall threshold of |0mg|
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FF_THR, 0x00);
  //Freefall duration limit of 0
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, 0x00);
  //Motion threshold of 0mg
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, 0x00);
  //Motion duration of 0s
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, 0x00);
  //Zero motion threshold
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, 0x00);
  //Zero motion duration threshold
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, 0x00);
  //Disable sensor output to FIFO buffer
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, 0x00);

  //AUX I2C setup
  //Sets AUX I2C to single master control, plus other config
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
  //Setup AUX I2C slaves
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_REG, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_REG, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_REG, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, 0x00);

  //MPU6050_RA_I2C_MST_STATUS //Read-only
  //Setup INT pin and AUX I2C pass through
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x00);
  //Enable data ready interrupt
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00);

  //Slave out, dont care
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_DO, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_DO, 0x00);
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_DO, 0x00);
  //More slave config
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
  //Reset sensor signal paths
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
  //Motion detection control
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
  //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, 0x00);
  //Sets clock source to gyro reference w/ PLL
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0b00000010);
  //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, 0x00);
  //MPU6050_RA_BANK_SEL            //Not in datasheet
  //MPU6050_RA_MEM_START_ADDR        //Not in datasheet
  //MPU6050_RA_MEM_R_W            //Not in datasheet
  //MPU6050_RA_DMP_CFG_1            //Not in datasheet
  //MPU6050_RA_DMP_CFG_2            //Not in datasheet
  //MPU6050_RA_FIFO_COUNTH        //Read-only
  //MPU6050_RA_FIFO_COUNTL        //Read-only
  //Data transfer to and from the FIFO buffer
  mpu6050.LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, 0x00);
  //MPU6050_RA_WHO_AM_I             //Read-only, I2C address


  mpu6050.setSleepEnabled(false);
  mpu6050.setGyroSelfTestEnabled();
  mpu6050.setAccelSelfTestEnabled();

  delay(250);

  mpu6050.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu6050.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

  float selfTest[6];
  mpu6050.getSelfTestFactoryTrim(selfTest);
  // printf("x-axis self test: acceleration trim within: %f of factory value\n", selfTest[0]);
  // printf("y-axis self test: acceleration trim within: %f of factory value\n", selfTest[1]);
  // printf("z-axis self test: acceleration trim within: %f of factory value\n", selfTest[2]);
  // printf("x-axis self test: gyration trim within: %f of factory value\n", selfTest[3]);
  // printf("y-axis self test: gyration trim within: %f of factory value\n", selfTest[4]);
  // printf("z-axis self test: gyration trim within: %f of factory value\n", selfTest[5]);

  if(selfTest[0] < 1.0f && selfTest[1] < 1.0f && selfTest[2] < 1.0f && selfTest[3] < 1.0f && selfTest[4] < 1.0f && selfTest[5] < 1.0f)
    printf("Self test: PASS\n");
  else
    printf("Self test: FAILED\n");

  // TODO: Calibrate here
  // TODO: Initialize here

  printf("========= CONFIG =========\n");
  printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());
  printf("Sleep enabled: %s\n", mpu6050.isSleepEnabled() ? "YES" : "NO");
  printf("Gyro range: 0x0%i\n", mpu6050.getFullScaleGyroRange());
  printf("Accel range: 0x0%i\n", mpu6050.getFullScaleAccelRange());
  printf("\n");
  delay(3000);
}

void loop(float &totalx, float &totaly, float &totalz, float GYRO_XOUT_OFFSET,float GYRO_YOUT_OFFSET,float GYRO_ZOUT_OFFSET)
{
  float tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg;

  for (int i = 0; i < MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT; ++i)
  //for (int i = 0; i < 1; ++i)
  {
    int16_t xa, ya, za, xg, yg, zg;
    mpu6050.readAccelData(&xa, &ya, &za);
    mpu6050.readGyroData(&xg, &yg, &zg);
    tmp_zg+=(float)zg;
    tmp_yg+=(float)yg;
    tmp_xg+=(float)xg;
    tmp_za+=(float)za;
    tmp_ya+=(float)ya;
    tmp_xa+=(float)xa;
    delay(10);
  }
  //now we needed something liek 10*30 ms secs = 300 ms
  tmp_xa/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_ya/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_za/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_zg/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_yg/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_xg/=(float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;

  tmp_xg -=GYRO_XOUT_OFFSET;
  tmp_yg -=GYRO_YOUT_OFFSET;
  tmp_zg -=GYRO_ZOUT_OFFSET;

  tmp_zg /= 131.0;
  tmp_yg /= 131.0;
  tmp_xg /= 131.0;

  //delay(MPU6050_SLEEPTIME);

  
  printf("XA(%f) YA(%f) ZA(%f) -- XG(%f) YG(%f) ZG(%f)\n", tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg);
  //now multiply the total assumed change of degrees by the time needed per second
  tmp_zg *= 0.1;
  tmp_yg *= 0.1;
  tmp_xg *= 0.1;

  totalx+=tmp_xg;
  totaly+=tmp_yg;
  totalz+=tmp_zg;

  printf("XA(%f) YA(%f) ZA(%f) -- XGscaled (%f) YG scaled (%f) ZG scaled (%f)\n", tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg);

  printf("XA(%f) YA(%f) ZA(%f) -- XG total (%f) YG total (%f) ZG total (%f)\n", tmp_xa, tmp_ya, tmp_za, totalx, totaly, totalz);

  fflush(stdout);
}
