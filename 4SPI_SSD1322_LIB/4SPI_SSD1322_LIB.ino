#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0;
  
  initSPIandOLED();

  while(1) {
    if(i == 256) i = 0;
    sendCommand(i++);
  };
}

void loop() {
  // put your main code here, to run repeatedly:

}
