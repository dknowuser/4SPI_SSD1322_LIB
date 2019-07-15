#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0x50;
  
  initSPIandOLED();
  //sendCommand(WRITE_RAM);

  while(1) {
    if(i == 127) i = 0x50;
    setPoint(0, i++, 0x0);
    //delay(100);
  };

}

void loop() {
  // put your main code here, to run repeatedly:

}
