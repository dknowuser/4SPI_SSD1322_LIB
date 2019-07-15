#include <SPI.h>

#define OLED_DC 12
#define OLED_CS 11
#define RES 10
#define OLED_SCLK 52
#define OLED_SDIN 51

void setup() {
  unsigned int i = 0;
  unsigned int del = 1000;
  
  // put your setup code here, to run once:
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_SCLK, OUTPUT);
  pinMode(OLED_SDIN, OUTPUT);
  pinMode(RES, OUTPUT);

  //digitalWrite(RES, LOW);
  //delay(del);
  
  SPI.setClockDivider(1);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  digitalWrite(RES, HIGH);
  digitalWrite(OLED_DC, LOW);
  digitalWrite(OLED_CS, LOW);
  SPI.transfer(0x0A7);
  digitalWrite(OLED_CS, HIGH);

  while(1) {
    if(i == 256) i = 0;    
    digitalWrite(OLED_DC, LOW);
    digitalWrite(OLED_CS, LOW);
    SPI.transfer(i++);
    digitalWrite(OLED_CS, HIGH);
  };  
}

void loop() {
  // put your main code here, to run repeatedly:

}
