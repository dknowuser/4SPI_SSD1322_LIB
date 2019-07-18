#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0x0;
  
  initSPIandOLED();

  while(1) {
    i = i & 0x0F;
    clearScreen(i++);
    delay(500);
  };

  //setSegs(90, 50, 0xF0, 0x00);
}

void loop() {
  // put your main code here, to run repeatedly:

}
