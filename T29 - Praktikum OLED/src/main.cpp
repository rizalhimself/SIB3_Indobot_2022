#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCAdrress 0x3c

Adafruit_SSD1306 screen = Adafruit_SSD1306(128,64,&Wire);

void setup() {
  // put your setup code here, to run once:
  screen.begin(SSD1306_SWITCHCAPVCC, SCAdrress);
  screen.display();
  delay(1000);
  screen.clearDisplay();
  screen.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);
  screen.setCursor(40,10);
  screen.print("INDOBOT");
  screen.setCursor(39,30);
  screen.print("ACADEMY");
  screen.setCursor(48,50);
  screen.print("2022");
  delay(10);
  screen.display();
}