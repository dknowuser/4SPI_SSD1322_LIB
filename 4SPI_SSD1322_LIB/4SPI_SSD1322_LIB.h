#ifndef _4SPI_SSD1322
#define _4SPI_SSD1322

#include <SPI.h>

// Arduino Mega 2560 pin defines
#define RES       10
#define OLED_CS   11
#define OLED_DC   12
#define OLED_SDIN 51
#define OLED_SCLK 52

//OLED commands
#define ENABLE_GR_SCL_MODE  0x00
#define SET_COLUMN_ADDRESS  0x15
#define WRITE_RAM           0x5C
#define READ_RAM            0x5D
#define SET_ROW_ADDRESS     0x75
#define REMAP_DUAL_COM      0xA0
#define SET_START_LINE      0xA1 // May be used for vertical scrolling
#define SET_OFFSET          0xA2 // May be used for vertical scrolling


#define SLEEP_MODE_ON 0xAE
#define SLEEP_MODE_OFF 0xAF

// Delay
#define DEL       500

// Function for SPI and OLED initialization
void initSPIandOLED(void);

// Function for sending command to SSD1322
void sendCommand(const char value);

// Function for sending data to SSD1322
void sendData(const char value);

#endif
