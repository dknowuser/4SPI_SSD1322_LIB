#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0;
  
  initSPIandOLED();

  while(1) {
    if(i == 16) i = 0;
    sendCommand(MASTER_CONTRAST_CURR_CTRL);
    sendData(i++);
    delay(500);
  };

  
  //sendData(0xC0);
  ///sendData(1);
  //sendCommand(EXIT_PARTIAL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
