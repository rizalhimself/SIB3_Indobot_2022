#include <Arduino.h>
#include <SPI.h>                  // pemanggil library SPI
#include <Wire.h>                 // pemanggil library komunikasi I2C
#include <Adafruit_GFX.h>         // pemanggil library GFX
#include <Adafruit_SSD1306.h>     // pemanggil library SSD
#include <Fonts/FreeSans9pt7b.h>  // menentukan font yang digunakan
#include <Fonts/FreeSans12pt7b.h> // menentukan font yang digunakan

#define SCREEN_WIDTH 128 // lebar OLED dalam pixel
#define SCREEN_HEIGHT 64 // tinggi OLED dalam pixel

// reset OLED
#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  pinMode(18, INPUT_PULLUP);                 // deklarasi pin button di D6 wemos
  pinMode(19, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // menginisialisasi alamat OLED di 0x3C (untuk OLED 128x64)
  display.display();                         // digunakan untuk menampilkan isi OLED
  display.clearDisplay();                    // membersihkan OLED
  display.setFont(&FreeSans9pt7b);           // mengatur font yang digunakan
  display.setTextColor(WHITE);               // mengatur warna
  display.setCursor(0, 25);                  // mengatur posisi
  display.println("TASK 32");                // menampilkan teks ke OLED
  display.setCursor(0, 40);                  // mengatur posisi teks
  display.println("STOPWATCH");                // mengampilkan teks ke OLED
  display.display();                         // menampilkan isi darti OLED
  delay(2000);
}

int sec1 = 0;           // mengatur detik awal
int min1 = 0;           // mengatur menit awal
unsigned long msec = 0; // mengatur mili detik awal
unsigned long mili = 0; // mengatur mili detik awal
int pres = 0;           // tekan tombol
int fase = 0;           // perpindahan dari mulai, berhenti, dan reset
int start = 0;          // memulai perhitungan
unsigned long tim = 0;  // untuk timer

void loop()
{
  display.clearDisplay();   // membersihkan tampilan OLED
  if (digitalRead(19) == 0)
  {
    sec1 = 0;
    min1 = 0;
    tim = 0;
    mili = 0;
    msec = 0;
    fase = 1;
    start = 0;
  }
  
  if (digitalRead(18) == 0) // jika tombol tidak ditekan berarti masuk ke tampilan awal
  {

    // untuk menentukan fase stopwatch
    if (pres == 0)
    {
      fase = fase + 1;
      pres = 1;
      if (fase > 2)
        fase = 0;
    }
  }
  else
  {
    pres = 0;
  }

  if (fase == 0) // masuk ke tampilan awal
  {
    display.setFont(&FreeSans9pt7b);
    display.setFont();
    display.setCursor(33, 15);
    display.println("STOPWATCH");
    display.setFont(&FreeSans12pt7b);
    display.setFont();
    display.setCursor(30, 35);
    display.print("Press Start");

    sec1 = 0;
    min1 = 0;
    tim = 0;
    mili = 0;
    msec = 0;
    start = 0;
  }

  if (fase == 1) // stopwatch mulai berjalan
  {
    display.clearDisplay();
    display.setFont(&FreeSans12pt7b);
    display.setFont();
    display.setCursor(37, 0);
    display.print("Stopwatch");
    display.setFont(&FreeSans9pt7b);

    if (start == 0) // perhitungan waktu
    {
      start = 1;
      tim = millis();
    }
    msec = (millis() - tim);

    min1 = msec / 60000;

    if ((msec / 1000) > 59)
    {
      sec1 = (msec / 1000) - (min1 * 60);
    }
    else
    {
      sec1 = msec / 1000;
    }

    mili = (msec % 1000) / 10;

    display.setCursor(42, 30);
    if (min1 <= 9)
    {
      display.print("0");
      display.print(min1);
    }
    else
    {
      display.print(min1);
    }

    display.print(":");

    if (sec1 <= 9)
    {
      display.print("0");
      display.print(sec1);
    }
    else
    {
      display.print(sec1);
    }
    display.setFont(&FreeSans12pt7b);
    display.setCursor(50, 57);

    if (mili <= 9)
    {
      display.print("0");
      display.print(mili);
    }
    else
    {
      display.print(mili);
    }
  }

  if (fase == 2) // perhitungan stopwatch berhenti
  {
    display.clearDisplay();
    display.setFont(&FreeSans12pt7b);
    display.setFont();
    display.setCursor(52, 0);
    display.print("Time:");
    display.setFont(&FreeSans9pt7b);
    display.setCursor(42, 30);
    if (min1 <= 9)
    {
      display.print("0");
      display.print(min1);
    }
    else
    {
      display.print(min1);
    }

    display.print(":");

    if (sec1 <= 9) // untuk menambahkan angka 0 di depan sebelum angka 9
    {
      display.print("0");
      display.print(sec1);
    }
    else
    {
      display.print(sec1);
    }
    display.setFont(&FreeSans12pt7b);
    display.setCursor(50, 57);

    if (mili <= 9) // untuk menambahkan angka 0 di depan sebelum angka 9
    {
      display.print("0");
      display.print(mili);
    }
    else
    {
      display.print(mili);
    }
  }
  display.display();
}