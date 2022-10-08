#include <Arduino.h>
const int pinTrigger = D2;
const int pinEcho = D3;
const int pinBuzzer = D4;
const int pinLedM = D5;
const int pinLedK = D6;
const int pinLedH = D7;
long durasi, jarak;
unsigned long previousMillis;
unsigned long previousMillisBz;
const long interval = 2000;
const long intervalBz = 2000;
int ledState = LOW;
int bzState = LOW;

void dapatkanDataJarak()
{
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  durasi = pulseIn(pinEcho, HIGH);
  jarak = (durasi / 2) / 29.1;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLedM, OUTPUT);
  pinMode(pinLedK, OUTPUT);
  pinMode(pinLedH, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  dapatkanDataJarak();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(500);
  
  if (jarak >= 4 && jarak <= 5)
  {
    digitalWrite(pinLedH, HIGH);
    tone(pinBuzzer, 700);
    delay(250);
    digitalWrite(pinLedH, LOW);
    noTone(pinBuzzer);
    delay(250);
  } else if (jarak > 5)
  {
    digitalWrite(pinLedH, HIGH);
  }
  else
  {
    digitalWrite(pinLedH, LOW);
  }

  if (jarak >= 9 && jarak <= 10)
  {
    digitalWrite(pinLedK, HIGH);
    tone(pinBuzzer, 800);
    delay(250);
    digitalWrite(pinLedK, LOW);
    noTone(pinBuzzer);
    delay(250);
  }
  else if (jarak > 10)
  {
    digitalWrite(pinLedK, HIGH);
  }
  else
  {
    digitalWrite(pinLedK, LOW);
  }

  if (jarak >= 14 && jarak <= 15)
  {
    digitalWrite(pinLedM, HIGH);
    tone(pinBuzzer, 900);
    delay(250);
    digitalWrite(pinLedM, LOW);
    noTone(pinBuzzer);
    delay(250);
  }
  else if (jarak > 15)
  {
    digitalWrite(pinLedM, HIGH);
    tone(pinBuzzer, 1000);
  }
  else
  {
    digitalWrite(pinLedM, LOW);
    noTone(pinBuzzer);
  }
}