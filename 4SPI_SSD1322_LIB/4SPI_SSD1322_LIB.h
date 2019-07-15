#ifndef _4SPI_SSD1322
#define _4SPI_SSD1322

#include <SPI.h>

// (0; 0) is at upper right corner

// Arduino Mega 2560 pin defines
#define RES       10
#define OLED_CS   11
#define OLED_DC   12
#define OLED_SDIN 51
#define OLED_SCLK 52

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
#define SET_PRECHARGE_VLTG      0xBB
#define SET_VCOMH                  0xBE
#define SET_CONTRAST_CURRENT       0xC1
#define MASTER_CONTRAST_CURR_CTRL  0xC7
#define SET_MUX_RATIO              0xCA
#define SET_COMMAND_LOCK           0xFD


// Delay
#define DEL       500

// Function for SPI and OLED initialization
void initSPIandOLED(void);

// Function for sending command to SSD1322
void sendCommand(const char value);

// Function for sending data to SSD1322
void sendData(const char value);

// Function for clearing screen
void clearScreen(const bool whiteBackground);

// Function for setting point at (x; y) with desired color
void setPoint(const unsigned int x, const unsigned int y, const unsigned int color);

#endif
