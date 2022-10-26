#include <Arduino.h>

#define PinLED 18
void setup() {
  // put your setup code here, to run once:
  pinMode(PinLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PinLED, ! digitalRead(PinLED));
  delay(1000);
}