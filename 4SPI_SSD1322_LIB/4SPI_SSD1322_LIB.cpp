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

  sendCommand(REMAP_DUAL_COM);
  sendDataByte(0x02);
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
  
  sendCommand(SET_COLUMN_ADDRESS);
  sendDataWord(OLED_SEG_NUM);

  sendCommand(SET_ROW_ADDRESS);
  sendDataWord(ROWS - 1);

  sendCommand(WRITE_RAM);
  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR;
  for(i = 0; i < ((COLUMNS / 2) * ROWS) / GLOBAL_BUFFER_SIZE; i++) {
    memset(quarterFrame, (backgroundColor << 4) | backgroundColor, GLOBAL_BUFFER_SIZE);    
    SPI.transfer(quarterFrame, GLOBAL_BUFFER_SIZE);    
  };
  PORTB |= OLED_CS_SET;

  deleteShapeQueue();
}

void setSegs(const unsigned int x, const unsigned int y, const unsigned int color1,
      const unsigned int color2)
{
  unsigned int i = 0;

  sendCommand(SET_COLUMN_ADDRESS);
  sendDataWord(OLED_SEG_NUM | (x << 8));

  sendCommand(SET_ROW_ADDRESS);
  sendDataWord((ROWS - 1) | (y << 8));

  sendCommand(WRITE_RAM);
  sendDataWord(color2 | (color1 << 8));
}

void deleteShapeQueue(void)
{
  if(shapeQueue) {
    lastShape = NULL;
    ShapeElement *temp;

    while(shapeQueue) {
      temp = shapeQueue;
      shapeQueue = shapeQueue->next;
      delete temp;
    }
  };
}

void addShapeQueueElement(const Shape *shape) 
{
  if(shapeQueue) {
    lastShape->next = new ShapeElement;
    if(!lastShape->next)
      return;
  }
  else {
    shapeQueue = new ShapeElement;
    if(!shapeQueue)
      return;
      
    lastShape = shapeQueue;
  };
  lastShape->shape.x1 = shape->x1;
  lastShape->shape.y1 = shape->y1;
  lastShape->shape.color = shape->color;
  lastShape->shape.type = shape->type;
  lastShape->next = NULL;
}

void updateScreen(const int backgroundColor)
{
  updateQuarter(TOP_LEFT, backgroundColor);
  updateQuarter(TOP_RIGHT, backgroundColor);
  updateQuarter(BOTTOM_LEFT, backgroundColor);
  updateQuarter(BOTTOM_RIGHT, backgroundColor);
}

void updateQuarter(const byte quarter, const int backgroundColor)
{
  memset(quarterFrame, backgroundColor | backgroundColor << 4, GLOBAL_BUFFER_SIZE);
  switch(quarter) {
  case TOP_LEFT:
    sendCommand(SET_COLUMN_ADDRESS);
    sendDataWord(OLED_SEG_NUM / 2);
  
    sendCommand(SET_ROW_ADDRESS);
    sendDataWord((ROWS - 1) / 4);    
    break;
    
  case TOP_RIGHT:
    sendCommand(SET_COLUMN_ADDRESS);
    sendDataWord(OLED_SEG_NUM | ((OLED_SEG_NUM / 2) << 8));
  
    sendCommand(SET_ROW_ADDRESS);
    sendDataWord((ROWS - 1) / 4);    
    break;

  case BOTTOM_LEFT:
    sendCommand(SET_COLUMN_ADDRESS);
    sendDataWord(OLED_SEG_NUM / 2);
  
    sendCommand(SET_ROW_ADDRESS);
    sendDataWord(((ROWS - 1) / 2) | (((ROWS - 1) / 4) << 8));    
    break;

  case BOTTOM_RIGHT:
    sendCommand(SET_COLUMN_ADDRESS);
    sendDataWord(OLED_SEG_NUM | ((OLED_SEG_NUM / 2) << 8));
  
    sendCommand(SET_ROW_ADDRESS);
    sendDataWord(((ROWS - 1) / 2) | (((ROWS - 1) / 4) << 8));    
    break;
  }

  drawQueue(quarter);
  sendCommand(WRITE_RAM);
  PORTB |= OLED_DC_SET;
  PORTB &= OLED_CS_CLEAR; 
  SPI.transfer(quarterFrame, GLOBAL_BUFFER_SIZE);    
  PORTB |= OLED_CS_SET;
}

void drawQueue(const byte quarter)
{
  quarterFrame[0] = 0xFFFF;
  /*if(shapeQueue) {
    ShapeElement *temp = shapeQueue;
    while(temp) {
      switch(temp->shape.type) {
      case POINT:
        switch(quarter) {
        case TOP_LEFT:
          quarterFrame[100] = 0xFF;
          /*if((temp->shape.x1 < (OLED_SEG_NUM / 2)) && (temp->shape.y1 < ((ROWS - 1) / 4))) {
              quarterFrame[temp->shape.y1 * (COLUMNS / 2) / 2 + temp->shape.x1] = (temp->shape.color & 0x0F)
                              << (4 * !(temp->shape.x1 % 2));
          }*/
          /*break;
        }
        break;
      default:
        break;
      }
      temp = temp->next;
    }
  }*/
}

void setPoint(const unsigned x, const unsigned y, const unsigned color)
{
  Shape shape;
  shape.x1 = x;
  shape.y1 = y;
  shape.color = color;
  shape.type = POINT;

  addShapeQueueElement(&shape);
}
