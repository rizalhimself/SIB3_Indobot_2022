#include <Arduino.h>
#define led_pin LED_BUILTIN

void setup()
{
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 255; i += 5)
  {
    analogWrite(led_pin, i);
    delay(30);
  }

  for (int i = 255; i > 0; i -= 5)
  {

    analogWrite(led_pin, i);
    delay(30);
  }
}