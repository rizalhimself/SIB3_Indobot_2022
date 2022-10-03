#include <Arduino.h>

const int pinRL = 26;
void setup()
{
  pinMode(pinRL, OUTPUT);
}

void loop()
{
  digitalWrite(pinRL, LOW);
  delay(1000);
  digitalWrite(pinRL, HIGH);
  delay(1000);
}