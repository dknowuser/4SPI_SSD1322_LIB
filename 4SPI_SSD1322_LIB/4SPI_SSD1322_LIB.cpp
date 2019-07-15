#include "4SPI_SSD1322_LIB.h"

void initSPIandOLED(void)
{
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_SCLK, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);
  pinMode(RES, OUTPUT);
  
  SPI.setClockDivider(128);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  digitalWrite(RES, HIGH);

  sendCommand(SLEEP_MODE_OFF);
  sendCommand(ENABLE_GR_SCL_MODE);
  
  sendCommand(SET_GR_SCL_TABLE);
  sendData(0x00);
  sendData(0x0C);
  sendData(0x18);
  sendData(0x24);
  sendData(0x30);
  sendData(0x3C);
  sendData(0x48);
  sendData(0x54);
  sendData(0x60);
  sendData(0x6C);
  sendData(0x78);
  sendData(0x84);
  sendData(0x90);
  sendData(0x9C);
  sendData(0xA8);
  sendData(0xB4);
}

void sendCommand(const char value)
{
  digitalWrite(OLED_DC, LOW);
  digitalWrite(OLED_CS, LOW);
  SPI.transfer(value);
  digitalWrite(OLED_CS, HIGH);
}

void sendData(const char value)
{
  digitalWrite(OLED_DC, HIGH);
  digitalWrite(OLED_CS, LOW);
  SPI.transfer(value);
  digitalWrite(OLED_CS, HIGH);
}

void clearScreen(const int backgroundColor) {
  
}

void setPoint(const unsigned int x, const unsigned int y, const unsigned int color) {
  unsigned int i = 0;

  /*sendCommand(SET_COLUMN_ADDRESS);
  sendData(x / 2);
  sendData(119);*/

  sendCommand(SET_ROW_ADDRESS);
  sendData(y);
  sendData(127);

  sendCommand(WRITE_RAM);

  while(i < 512) {
  /*if(x & 2)  
    sendData((color << 4));
  else
    sendData((color));*/
  sendData(color | (color << 4));

    i++;
  };
}
