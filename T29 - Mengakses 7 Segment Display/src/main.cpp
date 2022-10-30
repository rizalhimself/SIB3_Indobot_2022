#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 19
#define DIO 18

TM1637Display display (CLK, DIO);
int angka;

const uint8_t allOn[] = {0xff,0xff,0xff,0xff};
const uint8_t allOff[] = {0x00,0x00,0x00,0x00};

const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

void setup() {
  // put your setup code here, to run once:
  display.setBrightness(7);
  display.setSegments(allOn);
  delay(1000);
  display.setSegments(allOff);
  delay(1000);
  display.setSegments(done);
  delay(1000);
  angka = 1234;
}

void loop() {
  // put your main code here, to run repeatedly:
  display.showNumberDec(angka);
  angka--;
  delay(1000);
}