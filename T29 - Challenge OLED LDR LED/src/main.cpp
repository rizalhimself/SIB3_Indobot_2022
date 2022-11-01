#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCAdrress 0x3c
#define pinLDR 39
#define pinLED 18

int nilaiLDR = 0;
String kondisi = "";

Adafruit_SSD1306 screen = Adafruit_SSD1306(128,64,&Wire);

void setup() {
  // put your setup code here, to run once:
  screen.begin(SSD1306_SWITCHCAPVCC, SCAdrress);
  screen.display();
  delay(1000);
  screen.clearDisplay();
  screen.display();
  pinMode(pinLDR, INPUT);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilaiLDR = analogRead(pinLDR);

  if (nilaiLDR >= 1500)
  {
    kondisi = "Gelap";
    digitalWrite(pinLED, HIGH);
  } else
  {
    kondisi = "Terang";
    digitalWrite(pinLED, LOW);
  }
  
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);
  screen.setCursor(0,10);
  screen.print("Intensitas Cahaya");
  screen.setCursor(0,30);
  screen.print("Nilai LDR = ");
  screen.setCursor(75,30);
  screen.print(nilaiLDR);
  screen.setCursor(0,40);
  screen.print("Kondisi = ");
  screen.setCursor(63,40);
  screen.print(kondisi);
  screen.display();
  delay(1000);
  screen.clearDisplay();
}