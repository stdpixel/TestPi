#include <stdio.h>
#include <MPU6050/MPU6050.h>

MPU6050 mpu6050(MPU6050_DEFAULT_ADDRESS);

int main()
{
  printf("MPU6050 online: %s", mpu6050.isConnected() ? "YES" : "NO");

  return 0;
}
