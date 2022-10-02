#include <Arduino.h>

const int pinPB = D3;
const int pinLEDB = D2;
const int pinLEDM = D4;
const int pinBZ = D5;

void setup() {
  // put your setup code here, to run once
  pinMode(pinPB, INPUT_PULLUP);
  pinMode(pinLEDB, OUTPUT);
  pinMode(pinLEDM, OUTPUT);
  pinMode(pinBZ, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int statusTombol = digitalRead(pinPB);
  if (statusTombol == LOW)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pinLEDB, HIGH);
      digitalWrite(pinLEDM, LOW);
      tone(pinBZ, 500);
      delay(500);
      for (int y = 0; y < 4; y++)
      {
        digitalWrite(pinLEDM, HIGH);
        digitalWrite(pinLEDB, LOW);
        tone(pinBZ, 1000);
      }
      delay(500);
    }
  } 
  else
  {

    digitalWrite(pinLEDB, HIGH);
    digitalWrite(pinLEDM, LOW);
    tone(pinBZ, 400);
    delay(500);
    digitalWrite(pinLEDB, LOW);
    noTone(pinBZ);
    delay(500);
  }
}