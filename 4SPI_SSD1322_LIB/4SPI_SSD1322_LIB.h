#ifndef _4SPI_SSD1322
#define _4SPI_SSD1322

#include <SPI.h>

// (0; 0) is at upper left corner

// Arduino Mega 2560 pin defines
#define RES       10
#define OLED_CS   11
#define OLED_DC   12
#define OLED_SDIN 51
#define OLED_SCLK 52

#define RES_PIN_SET   B00010000
#define OLED_CS_SET   B00100000
#define OLED_CS_CLEAR B11011111
#define OLED_DC_SET   B01000000
#define OLED_DC_CLEAR B10111111

//OLED commands
#define ENABLE_GR_SCL_MODE      0x00
#define SET_COLUMN_ADDRESS      0x15
#define WRITE_RAM               0x5C
#define READ_RAM                0x5D
#define SET_ROW_ADDRESS         0x75
#define REMAP_DUAL_COM          0xA0
#define SET_START_LINE          0xA1 // May be used for vertical scrolling
#define SET_OFFSET              0xA2 // May be used for vertical scrolling
#define DISPLAY_OFF             0xA4
#define DISPLAY_ON              0xA5
#define DISPLAY_NORMAL          0xA6
#define DISPLAY_INVERSE         0xA7
#define ENABLE_PARTIAL          0xA8
#define EXIT_PARTIAL            0xA9
#define FUNC_SELECTION          0xAB
#define SLEEP_MODE_ON           0xAE
#define SLEEP_MODE_OFF          0xAF
#define SET_PHASE_LENGTH        0xB1
#define SET_CLK_DIV_OSC_FREQ    0xB3
#define SET_GPIO                0xB5
#define SET_SECOND_PRECH_PER    0xB6
#define SET_GR_SCL_TABLE        0xB8
#define SELECT_GR_SCL_TABLE     0xB9
#define SET_PRECHARGE_VLTG         0xBB
#define SET_VCOMH                  0xBE
#define SET_CONTRAST_CURRENT       0xC1
#define MASTER_CONTRAST_CURR_CTRL  0xC7
#define SET_MUX_RATIO              0xCA
#define SET_COMMAND_LOCK           0xFD

#define DEL                 500 // Delay
#define COLUMNS             480
#define ROWS                128
#define MAX_SPI_SPEED       16000000
#define GLOBAL_BUFFER_SIZE  7680 // Correct this value to free memory 
                                 // for global variables or to speed up OLED update (30720 pixel pairs)
#define OLED_SEG_NUM        0x77
#define OLED_SEG_NUM_REAL   0x5C // Use this value for drawing

// Enumeration for frame quarters
enum {
  TOP_LEFT, TOP_RIGHT, 
  BOTTOM_LEFT, BOTTOM_RIGHT
};

// Structure for storing shape parameters
struct Shape {
  byte x1;
  byte y1;
  byte color;
};

// Structure for shape queue element
struct ShapeElement {
  Shape shape;
  ShapeElement *next;
};

// Function for SPI and OLED initialization
void initSPIandOLED(void);

// Function for OLED contents inversion and normal mode
void inverseOLED(void);
void normalOLED(void);

// Function for scrolling OLED contents
// value should be in range 0-127
void scrollOLED(const byte value);

// Function for sending command to SSD1322
void sendCommand(const byte value);

// Functions for sending data to SSD1322
void sendDataByte(const byte value);
void sendDataWord(const word value);

// Function for clearing screen
void clearScreen(const int backgroundColor);

// Function for updating screen
void updateScreen(void);

// Function for updating desired frame quarter
void updateQuarter(const byte quarter);

// Function for setting segment pair at (x; y) with desired color
// x is offset of 1st segment pair
// Lower half of color parameter is color of 1st pixel
// Higher half of color parameter is color of 2nd pixel
// color1 is color for 1st segment pair
// color2 is color for 2nd segment pair
void setSegs(const unsigned int x, const unsigned int y, const unsigned int color1,
        const unsigned int color2);

// Function for deleting shape queue
void deleteShapeQueue(void);

// Buffer for drawing
const static unsigned char quarterFrame[GLOBAL_BUFFER_SIZE];

// Shape queue for drawing and update
static ShapeElement *shapeQueue = NULL;

// Pointer to last shape queue element for fast insertion
static ShapeElement *lastShape = NULL;
        
#endif
