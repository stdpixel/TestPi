#ifndef MAINMPU6050_H_
#define MAINMPU6050_H_

#include <stdio.h>
#include <MPU6050/MPU6050.h>
#include <time.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);
float gyro_xout_offset, gyro_yout_offset, gyro_zout_offset;
float tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg, totalx, totaly, totalz;

void handle_interrupt()
{
  printf("BAM INTERRUPT!!!\n");
}

float dist(float a, float b)
{
  return sqrt((a * a) + (b * b));
}

float get_rotation_x(float x, float y, float z)
{
  float radians = atan2(x, dist(y,z));
  return radians * (180.0 / M_PI);
}

void setupMain_MPU6050()
{
  if (wiringPiSetup() == -1)
    printf("ERROR GPIO");

  pinMode(0, INPUT);
  digitalWrite(0, HIGH);

  wiringPiISR(0, INT_EDGE_FALLING, handle_interrupt);
  mpu6050.initialize();

  delay(50);

  // float selfTest[6];
  // mpu6050.getSelfTestFactoryTrim(selfTest);

  // printf("x-axis self test: acceleration trim within: %f of factory value\n", selfTest[0]);
  // printf("y-axis self test: acceleration trim within: %f of factory value\n", selfTest[1]);
  // printf("z-axis self test: acceleration trim within: %f of factory value\n", selfTest[2]);
  // printf("x-axis self test: gyration trim within: %f of factory value\n", selfTest[3]);
  // printf("y-axis self test: gyration trim within: %f of factory value\n", selfTest[4]);
  // printf("z-axis self test: gyration trim within: %f of factory value\n", selfTest[5]);

  // if(selfTest[0] < 1.0f && selfTest[1] < 1.0f && selfTest[2] < 1.0f && selfTest[3] < 1.0f && selfTest[4] < 1.0f && selfTest[5] < 1.0f)
  //   printf("Self test: PASS\n");
  // else
  //   printf("Self test: FAILED\n");

  // TODO: Calibrate here
  // TODO: Initialize here

  // printf("========= CONFIG =========\n");
  // printf("DeviceId: 0x%0x\n", mpu6050.getDeviceId());
  // printf("Sleep enabled: %s\n", mpu6050.isSleepEnabled() ? "YES" : "NO");
  // printf("Gyro range: 0x0%i\n", mpu6050.getFullScaleGyroRange());
  // printf("Accel range: 0x0%i\n", mpu6050.getFullScaleAccelRange());
  // printf("\n");
  // delay(1000);

  printf("Calibrate Gyro\n");

  mpu6050.Calibrate_Gyros(&gyro_xout_offset, &gyro_yout_offset, &gyro_zout_offset);
  printf("Gyro calibrated with offset: x%f y%f z%f \n", gyro_xout_offset, gyro_yout_offset, gyro_zout_offset);
}

float timeing;
struct timeval tval_before, tval_after, tval_result;
int factor = 10;
float xaLast = 0.0, yaLast = 0.0, zaLast = 0.0;
void loopMain_MPU6050()
{
  // for (int i = 0; i < MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT; ++i)
  gettimeofday(&tval_before, NULL);

  for (int i = 0; i < MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT; ++i)
  {
    int16_t xa, ya, za, xg, yg, zg, tg;

    mpu6050.readAccelData(&xa, &ya, &za);
    mpu6050.readGyroData(&xg, &yg, &zg);

    tmp_zg += (float)zg;
    tmp_yg += (float)yg;
    tmp_xg += (float)xg;
    tmp_za += (float)za;
    tmp_ya += (float)ya;
    tmp_xa += (float)xa;
    delay(factor);
  }

  //now we needed something liek 10*30 ms secs = 300 ms
  tmp_xa /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_ya /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_za /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_zg /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_yg /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;
  tmp_xg /= (float)MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT;

  tmp_xa /= 4096.0;
  tmp_ya /= 4096.0;
  tmp_za /= 4096.0;

  tmp_xg -= gyro_xout_offset;
  tmp_yg -= gyro_yout_offset;
  tmp_zg -= gyro_zout_offset;

  tmp_zg /= 131.0;
  tmp_yg /= 131.0;
  tmp_xg /= 131.0;

  //delay(MPU6050_SLEEPTIME);
  printf("XA(%f) YA(%f) ZA(%f) -- XG(%f) YG(%f) ZG(%f)\n", tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg);
  // now multiply the total assumed change of degrees by the time needed per second
  // gettimeofday(&tval_after, NULL);
  // timersub(&tval_after, &tval_before, &tval_result);

  // float diff = MPU6050_FILTER_ARITHMETIC_MIDDLE_COUNT / factor;
  float diff = (float)tval_result.tv_usec / 1000000;
  // float diff = 1.0;
  // printf("Diff: %f\n", diff);
  // tmp_zg *= diff;
  // tmp_yg *= diff;
  // tmp_xg *= diff;

  float accelTol = 0.03;
  float abs_xa = xaLast - tmp_xa;
  // printf("XALAST(%f) YALAST(%f) ZALAST(%f) -- XADIFF(%f) YADIFF(%f) ZADIFF(%f)\n", xaLast, yaLast, zaLast, abs_xa, abs_xa, abs_xa);

  // if (abs_xa > accelTol || abs_xa < -accelTol) {
    totalx = 0.98 * (totalx + tmp_xg * diff) + 0.02 * get_rotation_x(tmp_xa, tmp_ya, tmp_za);
  // }

  if (abs(tmp_ya) > accelTol) {
    totaly = 0.98 * (totaly + tmp_yg * diff) + 0.02 * tmp_ya;
  }

  if (abs(tmp_za) > accelTol) {
    totalz = 0.98 * (totalz + tmp_zg * diff) + 0.02 * tmp_za;
  }

  // if (tmp_xg > 0.1 || tmp_xg < -0.1)
  //   totalx += tmp_xg;

  // if (tmp_yg > 0.1 || tmp_yg < -0.1)
  //   totaly += tmp_yg;

  // if (tmp_zg > 0.1 || tmp_zg < -0.1)
  //   totalz += tmp_zg;

  printf("XA(%f) YA(%f) ZA(%f) -- XGscaled (%f) YG scaled (%f) ZG scaled (%f)\n", tmp_xa, tmp_ya, tmp_za, tmp_xg, tmp_yg, tmp_zg);
  printf("XA(%f) YA(%f) ZA(%f) -- XG total (%f) YG total (%f) ZG total (%f)\n", tmp_xa, tmp_ya, tmp_za, totalx, totaly, totalz);

  // delay(10);

  gettimeofday(&tval_after, NULL);
  timersub(&tval_after, &tval_before, &tval_result);
  printf("Timeing: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
  xaLast = tmp_xa;
  yaLast = tmp_ya;
  zaLast = tmp_za;
}

#endif /* MAINMPU6050_H_ */
