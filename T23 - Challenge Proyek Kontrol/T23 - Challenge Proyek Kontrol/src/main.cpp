#include <Arduino.h>
//konfigurasi PIN
const int pinLED1 = D2;
const int pinLED2 = D3;
const int pinLED3 = D10;
const int pinLED4 = D11;
const int pinPB1 = D4;
const int pinPB2 = D5;
const int pinBZ = D8;
const int pinRLY = D9;
//buat array pin
int pinLED[] = {pinLED1,pinLED2, pinLED3, pinLED4};
//buat variabel milis 
unsigned long waktuSebelum = 0;
unsigned long interval = 50;
//buat variabel status pb
int statsBT1, statsBT2;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinLED[i], OUTPUT);
  }
  pinMode(pinPB1, INPUT_PULLUP);
  pinMode(pinPB2, INPUT_PULLUP);
  pinMode(pinBZ, OUTPUT);
  pinMode(pinRLY, OUTPUT);
  digitalWrite(pinRLY, LOW);
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
    digitalWrite(pinLED3, HIGH);
  } else
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pinLED[i], LOW);
    }
  }

  if (statsBT2 == LOW)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pinLED[i], HIGH);
      tone(pinBZ, 1000);
      noTone(pinBZ);
      tone(pinBZ, 1000);
      noTone(pinBZ);
    }
  } else
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(pinLED[j], LOW);
    }
  }

  if (statsBT1 == LOW && statsBT2 == LOW)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pinLED[i], HIGH);
      tone(pinBZ, 1000);
      digitalWrite(pinRLY, HIGH);
      delay(1000);
      digitalWrite(pinLED[i], LOW);
      noTone(pinBZ);
      digitalWrite(pinRLY, LOW);
      delay(1000);
    }
  } else
  {
    digitalWrite(pinRLY, LOW);
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pinLED[i], LOW);
    }
    noTone(pinBZ);
  }
  
}
