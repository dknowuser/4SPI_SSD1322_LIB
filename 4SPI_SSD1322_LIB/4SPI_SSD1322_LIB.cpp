#include "4SPI_SSD1322_LIB.h"

void initSPIandOLED(void)
{
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_SCLK, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);
  pinMode(RES, OUTPUT);
  
  SPI.setClockDivider(1);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  digitalWrite(RES, HIGH);

  sendCommand(SLEEP_MODE_OFF);
  sendCommand(ENABLE_GR_SCL_MODE);
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
