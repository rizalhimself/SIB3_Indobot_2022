#include <Arduino.h>
#include <TM1637Display.h>
#include <Esp.h>
#define CLK 19
#define DIO 18

TM1637Display display(CLK, DIO);
int angka = 0;

const uint8_t allOn[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t allOff[] = {0x00, 0x00, 0x00, 0x00};

void setup()
{
  // put your setup code here, to run once:
  display.setBrightness(7);
  display.setSegments(allOn);
  delay(1000);
  display.setSegments(allOff);
  delay(1000);
  Serial.begin(115200);
  Serial.println("===Program Seven Segement Berbasis Serial Monitor===");
  delay(1000);
  Serial.println("===Pilihan program yang tersedia: ===");
  Serial.println("1. Input Angka Display");
  Serial.println("2. Hapus Angka Display");
  Serial.println("3. Restart Device");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Masukkan pilihan anda = ");

  while (Serial.available() == 0)
  {
    display.showNumberDec(angka);
  }

  int pilihanMenu = Serial.parseInt();
  switch (pilihanMenu)
  {
  case 1:
    Serial.println("Input Angka Display");
    Serial.println("Masukkan input angka (4) karakter = ");
    while (Serial.available() == 0)
    {
      // dont do anything
    }
    angka = Serial.parseInt();
    Serial.print("Inputan Angka Adalah: ");
    Serial.println(angka);
    break;

  case 2:

    angka = 0;
    break;

  case 3:
    ESP.restart();
    break;

  default:
    break;
  }
}