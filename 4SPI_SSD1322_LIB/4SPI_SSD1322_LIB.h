#ifndef _4SPI_SSD1322
#define _4SPI_SSD1322

#include <SPI.h>

#define RES       10
#define OLED_CS   11
#define OLED_DC   12

#define OLED_SDIN 51
#define OLED_SCLK 52

#define DEL       500

void initSPIandOLED(void);
void sendCommand(const char value);

#endif
