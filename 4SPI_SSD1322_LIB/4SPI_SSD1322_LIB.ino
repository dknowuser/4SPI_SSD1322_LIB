#include "4SPI_SSD1322_LIB.h"

void setup() {
  // put your setup code here, to run once:
  unsigned int i = 0x0;
  
  initSPIandOLED();

  clearScreen(0x00);

  for(i = 0; i < ROWS; i++)
    setSegs(50, i, 0xFF, 0xFF);

  delay(500);
  updateQuarter(TOP_LEFT);
  updateQuarter(TOP_LEFT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
