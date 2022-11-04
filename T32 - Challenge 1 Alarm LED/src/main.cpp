#include <SPI.h>              // pemanggil library SPI
#include <Wire.h>             // pemanggil library Wire.h
#include <Adafruit_GFX.h>     //pemanggilan library GFX
#include <Adafruit_SSD1306.h> //pemanggilan library OLED
#include <TimeLib.h>          //Pemanggilan library time

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); // OLED menggunakan kolom 128 pixel dan baris 64 pixel
#define SCREEN_ADDRESS 0x3C                                  // alamat untuk I2C OLED
#define pinLED 18                                            // alamat untuk pin LED

// ini adalah function untuk nilai 0 hingga 9 agar diberikan angka nol di depannya
void printkurangdarinol(int data)
{
  if (data >= 0 && data < 10)
  {                     // 0 - 9
    display.write('0'); //
  }
  display.print(data);
}

void hidupkanLED()
{
  digitalWrite(pinLED, HIGH);
  Serial.println("Alarm Aktif");
}

void matikanLED()
{
  digitalWrite(pinLED, LOW);
  Serial.println("Alarm Nonaktif");
}

void setup()
{
  Serial.begin(115200);                    // menentukan baudrate di 115200
  Serial.println("Challenge OLED LED Alarm"); // menampilkan teks ke serial monitor
  pinMode(pinLED, OUTPUT);

  // Memastikan OLED dapat berjalan atau tidak
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // text display tests
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  setTime(17, 59, 55, 03, 11, 22); // jam,menit,detik,tanggal,bulan,tahun
}
void loop()
{ 
  // menampilkan tanggal pada OLED
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Tanggal: ");
  Serial.print("Tanggal: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  printkurangdarinol(day());
  Serial.print(day());
  display.print(":");
  Serial.print(":");
  printkurangdarinol(month());
  Serial.print(month());
  display.print(":");
  Serial.print(":");
  printkurangdarinol(year());
  Serial.println(year());

  // menampilkan waktu pada OLED
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Waktu: ");
  Serial.print("Waktu: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  printkurangdarinol(hour());
  Serial.print(hour());
  display.print(":");
  Serial.print(":");
  printkurangdarinol(minute());
  Serial.print(minute());
  display.print(":");
  Serial.print(":");
  printkurangdarinol(second());
  Serial.println(second());
  delay(1000);
  display.display();
  display.clearDisplay();
  if (hour() == 18 && minute() == 00 && second() > 00)
  {
    hidupkanLED();
  }
  else
  {
    matikanLED();
  }
}
