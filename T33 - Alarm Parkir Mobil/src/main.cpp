#include <Arduino.h>
#include <SPI.h>              // pemanggil library SPI
#include <Wire.h>             // pemanggil library komunikasi serial
#include <Adafruit_GFX.h>     //pemanggilan library GFX
#include <Adafruit_SSD1306.h> //pemanggilan library OLED SSD1306
#include <HCSR04.h>           //Memasukkan library HCSR04
int Buzzer = D3;              // Membuat variabel Buzzer berisi 3
float jarak;                  // Membuat variabel jarak
UltraSonicDistanceSensor hc(D5, D6);            // Mendefinisikan pin D5 sebagai Trig dan D6 sebagai Echo

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); // OLED menggunakan kolom 128 pixel dan baris 64 pixel
#define SCREEN_ADDRESS 0x3C                                  // alamat untuk I2C OLED

void setup()
{
  pinMode(Buzzer, OUTPUT);
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
}

void loop()
{
  jarak = hc.measureDistanceCm();
  if (jarak < 5)
  { // jika jarak < 5 cm maka

    digitalWrite(Buzzer, HIGH); // buzzer menyala selama
    delay(100);                 // 100 ms
    digitalWrite(Buzzer, LOW);  // buzzer mati selama
    delay(100);                 // 100ms
    display.setTextSize(1);     // menentukan ukuran teks
    display.setCursor(0, 35);
    display.print("Hati-Hati!!!");
  }

  else if (jarak < 10)
  {                             // jika jarak < 10 cm maka
    digitalWrite(Buzzer, HIGH); // buzzer menyala selama
    delay(250);                 // 250 ms
    digitalWrite(Buzzer, LOW);  // buzzer mati selama
    delay(250);                 // 250 ms
    display.setTextSize(1);     // menentukan ukuran teks
    display.setCursor(0, 35);
    display.print("Sangat Dekat!!");
  }

  else if (jarak < 15)
  {                             // jika jarak < 15 cm maka
    digitalWrite(Buzzer, HIGH); // buzzer menyala selama
    delay(500);                 // 500 ms
    digitalWrite(Buzzer, LOW);  // buzzer mati selama
    delay(500);                 // 500 ms
    display.setTextSize(1);     // menentukan ukuran teks
    display.setCursor(0, 35);
    display.print("Dekat");
  }
  Serial.print("Jarak(cm) : ");
  Serial.println(jarak);
  display.setTextSize(1);      // menentukan ukuran teks
  display.setCursor(0, 0);     // mengatur posisi teks
  display.print("Jarak(cm) "); // menampilkan teks ke OLED
  display.setTextSize(2);      // menentukan ukuran teks
  display.setCursor(0, 10);    // mengatur posisi teks
  display.print(jarak);        // menampilkan pembacaan kelembaban

  delay(10);              // jeda untuk menyalakan OLED
  display.display();      // menampilkan isi OLED
  display.clearDisplay(); // membersihkan tampilan
}