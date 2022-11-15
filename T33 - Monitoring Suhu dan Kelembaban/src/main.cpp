#include <Arduino.h>
#include <SPI.h>              // pemanggil library SPI
#include <Wire.h>             // pemanggil library komunikasi serial
#include <Adafruit_GFX.h>     //pemanggilan library GFX
#include <Adafruit_SSD1306.h> //pemanggilan library OLED SSD1306
#include "DHT.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); // OLED menggunakan kolom 128 pixel dan baris 64 pixel
#define SCREEN_ADDRESS 0x3C                                  // alamat untuk I2C OLED

#define DHTPIN 18         // deklarasi DHT11 di pin D4 wemos
#define DHTTYPE DHT11     // menentukan tipe dht
DHT dht(DHTPIN, DHTTYPE); // deklarasi pin DHT dan tipe dht

void setup()
{
  Serial.begin(9600);                      // menentukan baudrate di 9600
  Serial.println("OLED FeatherWing test"); // menampilkan teks ke serial monitor

  // Memastikan OLED dapat berjalan atau tidak
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // ujicoba display teks OLED
  display.setTextSize(2);              // ukuran teks
  display.setTextColor(SSD1306_WHITE); // warna OLED (putih)
  display.clearDisplay();              // membersihkan display oled
  dht.begin();                         // memulai pembacaan sensor DHT11
}

void loop()
{
  float h = dht.readHumidity();    // pengukuran kelembaban
  float t = dht.readTemperature(); // pengukuran tempperature
  display.setTextSize(1);          // menentukan ukuran teks
  display.setCursor(0, 0);         // mengatur posisi teks
  display.print("Kelembaban");     // menampilkan teks ke OLED
  display.setTextSize(2);          // menentukan ukuran teks
  display.setCursor(0, 10);        // mengatur posisi teks
  display.print(h);                // menampilkan pembacaan kelembaban
  display.print(" %");             // menampilkan teks ke OLED
  display.setTextSize(1);          // menentukan ukuran teks
  display.setCursor(0, 35);        // mengatur posisi teks
  display.print("Temperatur");     // menampilkan teks ke OLED
  display.setTextSize(2);          // menampilkan ukuran teks
  display.setCursor(0, 45);        // mengatur posisi teks
  display.print(t);                // menampilkan pembacaan suhu
  display.print(" C");             // menampilkan teks ke OLED

  delay(10);              // jeda untuk menyalakan OLED
  display.display();      // menampilkan isi OLED
  display.clearDisplay(); // membersihkan tampilan
}