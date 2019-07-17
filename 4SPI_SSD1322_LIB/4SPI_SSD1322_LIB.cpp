#include "4SPI_SSD1322_LIB.h"

void initSPIandOLED(void)
{
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_SCLK, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);
  pinMode(RES, OUTPUT);
  
  //SPI.setClockDivider(1);
  //SPI.setBitOrder(MSBFIRST);
  SPI.beginTransaction(SPISettings(MAX_SPI_SPEED, MSBFIRST, SPI_MODE0));
  SPI.begin();  

  PORTB |= RES_PIN_SET; // RES = 1

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

  sendCommand(SET_PHASE_LENGTH);
  sendData(0x32);

  //sendCommand(SET_VCOMH);
  //sendData(0x07);
}

void sendCommand(const char value)
{
  PORTB &= OLED_DC_CLEAR;
  PORTB &= OLED_CS_CLEAR;
  SPI.transfer(value);
  PORTB |= OLED_CS_SET;
}

void sendData(const char value)
{
  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR;
  SPI.transfer(value);
  PORTB |= OLED_CS_SET;
}

void clearScreen(const int backgroundColor) {
  unsigned int i = 0;
  
  sendCommand(SET_COLUMN_ADDRESS);
  sendData(0);
  sendData(119);

  sendCommand(SET_ROW_ADDRESS);
  sendData(0);
  sendData(ROWS - 1);

  sendCommand(WRITE_RAM);
  for(i = 0; i < (COLUMNS / 2) * ROWS; i++)
    sendData(backgroundColor | (backgroundColor << 4));
}

void setSegs(const unsigned int x, const unsigned int y, const unsigned int color1,
      const unsigned int color2) {
  unsigned int i = 0;

  sendCommand(SET_COLUMN_ADDRESS);
  sendData(x);
  sendData(119);

  sendCommand(SET_ROW_ADDRESS);
  sendData(y);
  sendData(127);

  sendCommand(WRITE_RAM);
  sendData(color1);
  sendData(color2);
}
