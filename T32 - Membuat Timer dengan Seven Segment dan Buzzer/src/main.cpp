#include <Arduino.h>
#include <TM1637Display.h>
#define CLK D4
#define DIO D3
TM1637Display display(CLK, DIO);

int timer_menit = 1; // Setting waktu untuk Menit
int timer_detik = 0; // Setting waktu untuk Detik

int firstnum = 0;
int secondnum = 0;
int thirdnum = 0;
int fournum = 0;

int buzzer = D6;

void setup()
{
  pinMode(buzzer, OUTPUT);
  display.setBrightness(7);
  delay(1500);
  digitalWrite(buzzer, LOW);
}

void loop()
{
  uint8_t titikdua;
  titikdua = 0x80;
  display.setSegments(&titikdua, true, 1);

  while (timer_menit == 0 && timer_detik == 0)
  {
    digitalWrite(buzzer, HIGH);
    uint8_t data[] = {0b00111111, 0b00111111, 0b00111111, 0b00111111};
    display.setSegments(data);
    titikdua = 0x80;
    display.setSegments(&titikdua, true, 1);
  }

  if (timer_menit > 9)
  {
    firstnum = timer_menit / 10 % 10;
    secondnum = timer_menit % 10;
  }

  else
  {
    secondnum = timer_menit;
  }

  if (timer_detik > 9)
  {
    thirdnum = timer_detik / 10 % 10;
    fournum = timer_detik % 10;
  }

  else
  {
    thirdnum = 0;
    fournum = timer_detik;
  }

  uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
  display.setSegments(data);
  titikdua = 0x80;
  display.setSegments(&titikdua, true, 1);

  if (timer_menit > 9)
  {
    display.showNumberDec(firstnum, false, 1, 0);
  }

  if (timer_menit > 0)
  {
    display.showNumberDec(secondnum, false, 1, 1);
  }

  if (timer_detik > 9 || timer_menit > 0)
  {
    display.showNumberDec(thirdnum, false, 1, 2);
  }

  display.showNumberDec(fournum, false, 1, 3);
  timer_detik = timer_detik - 1;
  delay(1000); // Delay of 1 second

  if (timer_detik == -1)
  {
    timer_menit = timer_menit - 1;
    timer_detik = 59;
  }
}