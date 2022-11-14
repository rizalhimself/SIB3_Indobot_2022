#include <Arduino.h>
#include <SPI.h>                     // pemanggil library SPI
#include <Wire.h>                    // pemanggil library komunikasi serial
#include <Adafruit_GFX.h>            //pemanggilan library GFX
#include <Adafruit_SSD1306.h>        //pemanggilan library OLED SSD1306
#include <HCSR04.h>                  //Memasukkan library HCSR04
int Buzzer = D2;                     // Membuat variabel Buzzer
int LEDMerah = D10;                  // Membuat Variabel LED Merah
int LEDKuning = D9;                  // Membuat Variabel LED Kuning
int LEDHijau = D8;                   // Membuat Variabel LED Hijau
float jarak;                         // Membuat variabel jarak
UltraSonicDistanceSensor hc(D5, D6); // Mendefinisikan pin D5 sebagai Trig dan D6 sebagai Echo

#define SCREEN_WIDTH 128    // lebar OLED dalam pixel
#define SCREEN_HEIGHT 64    // tinggi OLED dalam pixel
#define SCREEN_ADDRESS 0x3C // alamat untuk I2C OLED
#define OLED_RESET 0        // GPIO0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED menggunakan kolom 128 pixel dan baris 64 pixel

void setup()
{
  pinMode(Buzzer, OUTPUT);
  pinMode(LEDMerah, OUTPUT);
  pinMode(LEDKuning, OUTPUT);
  pinMode(LEDHijau, OUTPUT);
  Serial.begin(9600);                      // menentukan baudrate di 9600
  Serial.println("OLED FeatherWing test"); // menampilkan teks ke serial monitor
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
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
    digitalWrite(LEDMerah, HIGH);
    digitalWrite(LEDKuning, LOW);
    digitalWrite(LEDHijau, LOW);
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
    digitalWrite(LEDMerah, HIGH);
    digitalWrite(LEDKuning, HIGH);
    digitalWrite(LEDHijau, LOW);
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
    digitalWrite(LEDMerah, HIGH);
    digitalWrite(LEDKuning, HIGH);
    digitalWrite(LEDHijau, HIGH);
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