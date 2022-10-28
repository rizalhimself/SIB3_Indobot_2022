#include <Arduino.h>
#include <Esp.h>
#define pinLED 26

unsigned long waktuSebelum = 0;
const long interval = 1000;
int stats = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  Serial.println("===Program LED Berbasis Serial Monitor WeMos D1===");

  Serial.println("===Pilihan program yang tersedia: ===");
  Serial.println("1. Hidupkan LED");
  Serial.println("2. Matikan LED");
  Serial.println("3. Kedipkan LED");
  Serial.println("4. Restart Device");
}

void loop()
{
  // put your main code here, to run repeatedly:
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - waktuSebelum >= interval)
  {
    Serial.println("Masukkan pilihan anda = ");

    while (Serial.available() == 0)
    {
      // dont do anything but run switch function
      if (stats == 3)
      {
        for (int i = 0; i < 255; i += 5)
        {
          analogWrite(pinLED, i);
          delay(20);
        }

        for (int i = 255; i > 0; i -= 5)
        {

          analogWrite(pinLED, i);
          delay(20);
        }
      }
      else if (stats == 2)
      {
        analogWrite(pinLED, 0);
      }
      else if (stats == 1)
      {
        analogWrite(pinLED, 255);
      }
    }

    int pilihanMenu = Serial.parseInt();
    switch (pilihanMenu)
    {
    case 1:
      Serial.println("Lampu LED Menyala");
      stats = 1;
      break;

    case 2:

      Serial.println("Lampu LED Mati");
      stats = 2;
      break;

    case 3:
      stats = 3;
      Serial.println("Lampu LED Berkedip");
      break;

    case 4:
      ESP.restart();
      break;

    default:
      break;
    }
    waktuSebelum = waktuSekarang;
  }
}