#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCAdrress 0x3c

Adafruit_SSD1306 screen = Adafruit_SSD1306(128, 64, &Wire);
String inputTeks1 = "";
String inputTeks2 = "";
String inputTeks3 = "";

void setup()
{
  // put your setup code here, to run once:
  screen.begin(SSD1306_SWITCHCAPVCC, SCAdrress);
  screen.display();
  delay(1000);
  screen.clearDisplay();
  screen.display();
  Serial.begin(115200);
  Serial.println("===Program OLED Berbasis Serial Monitor===");
  delay(1000);
  Serial.println("===Pilihan program yang tersedia: ===");
  Serial.println("1. Input Teks 1");
  Serial.println("2. Input Teks 2");
  Serial.println("3. Input Teks 3");
  Serial.println("4. Hapus Teks");
  Serial.println("5. Restart Device");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Masukkan pilihan anda = ");

  while (Serial.available() == 0)
  {
    screen.setTextSize(1);
    screen.setTextColor(SSD1306_WHITE);
    screen.setCursor(0, 0);
    screen.print(inputTeks1);
    screen.setCursor(0, 20);
    screen.print(inputTeks2);
    screen.setCursor(0, 40);
    screen.print(inputTeks3);
    delay(10);
    screen.display();
  }

  int pilihanMenu = Serial.parseInt();
  switch (pilihanMenu)
  {
  case 1:
    Serial.println("Input Teks 1");
    Serial.println("Masukkan input teks = ");
    while (Serial.available() == 0)
    {
      // dont do anything
    }
    inputTeks1 = Serial.readString();
    Serial.print("Inputan Teks 1 Adalah: ");
    Serial.println(inputTeks1);
    break;

  case 2:

    Serial.println("Input Teks 2");
    Serial.println("Masukkan input teks = ");
    while (Serial.available() == 0)
    {
      // dont do anything
    }
    inputTeks2 = Serial.readString();
    Serial.print("Inputan Teks 2 Adalah: ");
    Serial.println(inputTeks2);
    break;

  case 3:

    Serial.println("Input Teks 3");
    Serial.println("Masukkan input teks = ");
    while (Serial.available() == 0)
    {
      // dont do anything
    }
    inputTeks3 = Serial.readString();
    Serial.print("Inputan Teks 3 Adalah: ");
    Serial.println(inputTeks3);
    break;

  case 4:

    inputTeks1 = "";
    inputTeks2 = "";
    inputTeks3 = "";
    screen.clearDisplay();
    break;

  case 5:
    ESP.restart();
    break;

  default:
    break;
  }
}