#include "4SPI_SSD1322_LIB.h"

void initSPIandOLED(void)
{
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_SCLK, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);
  pinMode(RES, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(MAX_SPI_SPEED, MSBFIRST, SPI_MODE0));

  PORTB |= RES_PIN_SET; // RES = 1

  sendCommand(SLEEP_MODE_OFF);
  sendCommand(ENABLE_GR_SCL_MODE);
  
  sendCommand(SET_GR_SCL_TABLE);

  sendDataWord(0x000C);
  sendDataWord(0x1824);
  sendDataWord(0x303C);
  sendDataWord(0x4854);
  sendDataWord(0x606C);
  sendDataWord(0x7884);
  sendDataWord(0x909C);
  sendDataWord(0xA8B4);
}

void sendCommand(const byte value)
{
  PORTB &= OLED_DC_CLEAR;
  PORTB &= OLED_CS_CLEAR;
  SPI.transfer(value);
  PORTB |= OLED_CS_SET;
}

void sendDataByte(const byte value)
{
  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR;
  SPI.transfer(value);
  PORTB |= OLED_CS_SET;
}

void sendDataWord(const word value)
{
  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR;
  SPI.transfer16(value);
  PORTB |= OLED_CS_SET;
}

void clearScreen(const int backgroundColor) {
  unsigned int i = 0;  
  unsigned char buffer[GLOBAL_BUFFER_SIZE];
  
  sendCommand(SET_COLUMN_ADDRESS);
  sendDataWord(0x77);

  sendCommand(SET_ROW_ADDRESS);
  sendDataWord(ROWS - 1);

  sendCommand(WRITE_RAM);

  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR;
  for(i = 0; i < ((COLUMNS / 2) * ROWS) / GLOBAL_BUFFER_SIZE; i++) {
    memset(buffer, (backgroundColor << 4) | backgroundColor, GLOBAL_BUFFER_SIZE);    
    SPI.transfer(buffer, GLOBAL_BUFFER_SIZE);    
  };
  PORTB |= OLED_CS_SET;

  //delay(500);
  
  /*for(i = 0; i < (COLUMNS / 2) * ROWS / 2; i++) {
    //sendDataByte(backgroundColor | (backgroundColor << 4));
    sendDataWord(backgroundColor | (backgroundColor << 4) 
      | (backgroundColor << 8) | (backgroundColor << 12));
  };*/
  //delay(500);
  //delete[] buffer;
}

void setSegs(const unsigned int x, const unsigned int y, const unsigned int color1,
      const unsigned int color2) {
  unsigned int i = 0;

  sendCommand(SET_COLUMN_ADDRESS);
  sendDataByte(x);
  sendDataByte(119);

  sendCommand(SET_ROW_ADDRESS);
  sendDataByte(y);
  sendDataByte(127);

  sendCommand(WRITE_RAM);
  sendDataByte(color1);
  sendDataByte(color2);
}
