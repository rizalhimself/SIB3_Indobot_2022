#include <SPI.h>                                             // pemanggil library SPI
#include <Wire.h>                                            // pemanggil library Wire.h
#include <Adafruit_GFX.h>                                    //pemanggilan library GFX
#include <Adafruit_SSD1306.h>                                //pemanggilan library OLED
#include <TimeLib.h>                                         //Pemanggilan library time
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); // OLED menggunakan kolom 128 pixel dan baris 64 pixel
#define SCREEN_ADDRESS 0x3C                                  // alamat untuk I2C OLED

// ini adalah function untuk nilai 0 hingga 9 agar diberikan angka nol di depannya
void printkurangdarinol(int data)
{
  if (data >= 0 && data < 10)
  {                     // 0 - 9
    display.write('0'); //
  }
  display.print(data);
}

void setup()
{
  // text display tests
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  setTime(12, 35, 50, 03, 11, 22); // jam,menit,detik,tanggal,bulan,tahun
  delay(1000);
}
void loop()
{
  // menampilkan tanggal pada OLED
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Tanggal: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  printkurangdarinol(day());
  display.print(":");
  printkurangdarinol(month());
  display.print(":");
  printkurangdarinol(year());

  // menampilkan waktu pada OLED
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Waktu: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  printkurangdarinol(hour());
  display.print(":");
  printkurangdarinol(minute());
  display.print(":");
  printkurangdarinol(second());
  delay(1000);
  yield();
  display.display();
  display.clearDisplay();
}
