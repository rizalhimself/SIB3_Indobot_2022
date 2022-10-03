#include <Arduino.h>

const int pinPB1 = D4;
const int pinPB2 = D5;
const int pinLED1 = D2;
const int pinLED2 = D3;

long waktuSebelum = 0;
long interval = 50;

int statsBT1, statsBT2;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinPB1, INPUT_PULLUP);
  pinMode(pinPB2, INPUT_PULLUP);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long waktuSekarang  = millis();

  if (waktuSekarang - waktuSebelum > interval)
  {
    statsBT1 = digitalRead(pinPB1);
    statsBT2 = digitalRead(pinPB2);
    
    waktuSebelum = waktuSekarang;
  }

  if (statsBT1 == LOW)
  {
    digitalWrite(pinLED1, HIGH);
  } else
  {
    digitalWrite(pinLED1, LOW);
  }

  if (statsBT2 == LOW)
  {
    digitalWrite(pinLED2, HIGH);
  } else
  {
    digitalWrite(pinLED2, LOW);
  }
}