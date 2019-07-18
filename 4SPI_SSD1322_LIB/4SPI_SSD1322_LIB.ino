#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0x0;
  
  initSPIandOLED();

  clearScreen(0x00);

  for(i = 0; i < 100; i++)
    setSegs(i, 50, 0xF0, 0xF0);

  while(1) {
    i = i % 128;
    scrollOLED(i);
    i += 4;
    delay(20);
  };
}

void loop() {
  // put your main code here, to run repeatedly:

}
