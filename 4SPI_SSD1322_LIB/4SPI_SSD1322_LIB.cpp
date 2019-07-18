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

  sendCommand(SET_PHASE_LENGTH);
  sendDataByte(0xFF);

  sendCommand(SET_CLK_DIV_OSC_FREQ);
  sendDataByte(0x00);

  sendCommand(SET_SECOND_PRECH_PER);
  sendDataByte(0x00);

  sendCommand(SET_PRECHARGE_VLTG);
  sendDataByte(0x3E);

  sendCommand(SET_VCOMH);
  sendDataByte(0x00);
}

void inverseOLED(void) 
{
  sendCommand(DISPLAY_INVERSE);
}

void normalOLED(void)
{
  sendCommand(DISPLAY_NORMAL);
}

void scrollOLED(const byte value)
{
  sendCommand(SET_OFFSET);
  sendDataByte(value);
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
  sendDataWord(OLED_SEG_NUM);

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
}

void setSegs(const unsigned int x, const unsigned int y, const unsigned int color1,
      const unsigned int color2) {
  unsigned int i = 0;

  sendCommand(SET_COLUMN_ADDRESS);
  sendDataWord(OLED_SEG_NUM | (x << 8));
  //sendDataByte(x);
  //sendDataByte(119);

  sendCommand(SET_ROW_ADDRESS);
  sendDataWord((ROWS - 1) | (y << 8));
  //sendDataByte(y);
  //sendDataByte(127);

  sendCommand(WRITE_RAM);
  sendDataWord(color2 | (color1 << 8));
  //sendDataByte(color1);
  //sendDataByte(color2);
}
