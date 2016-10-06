#include <I2Cdev/I2Cdev.h>

// LOAD PROGRAM
#include "mainMPU6050.h"

int main()
{
  I2Cdev::initialize();

  setup();

  while (1)
  {
    loop();
  }

  return 0;
}
