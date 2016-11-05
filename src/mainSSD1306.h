#ifndef MAINSSD1306_H_
#define MAINSSD1306_H_

#include <stdio.h>
#include <SSD1306/SSD1306.h>
#include <wiringPi.h>

SSD1306 ssd1306(0x3C);

class MainSSD1306
{
public:
  void static setup()
  {
  }

  void static loop()
  {
    ssd1306.begin(SSD1306_SWITCHCAPVCC);
    ssd1306.display();
    delay(5000);
    ssd1306.end();
    delay(3000);
  }
};

#endif /* MAINSSD1306_H_ */
