#include <Arduino.h>
#include <Esp.h>
#define pinLED LED_BUILTIN

unsigned long waktuSebelum = 0;
const long interval = 1000;
int stats = 0;
int ledValue = 255;
float precentage;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  Serial.println("===Program LED Berbasis Serial Monitor WeMos D1===");

  Serial.println("===Pilihan program yang tersedia: ===");
  Serial.println("1. Hidupkan LED");
  Serial.println("2. Matikan LED");
  Serial.println("3. Atur Kecerahan LED");
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
      if (stats == 2)
      {
        analogWrite(pinLED, 0);
      }
      else if (stats == 1)
      {
        analogWrite(pinLED, ledValue);
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
      Serial.println("Atur Kecerahan Lampu");
      Serial.println("Masukkan Prosentase Kecerahan = ");
      while (Serial.available() == 0)
      {
        // dont do anything 
      }
      precentage = Serial.parseInt();
      ledValue = (precentage / 100.0) * 255;
      Serial.print("Kecerahan layar ");
      Serial.print(precentage);
      Serial.print(" %\tdengan value ");
      Serial.println(ledValue);
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