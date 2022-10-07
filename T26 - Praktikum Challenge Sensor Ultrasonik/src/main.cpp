#include <Arduino.h>
const int pinTrigger = D2;
const int pinEcho = D3;
const int pinBuzzer = D4;
const int pinLedM = D5;
const int pinLedK = D6;
const int pinLedH = D7;
long durasi, jarak;


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
  
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(500);
}

void dapatkanDataJarak(){
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  durasi = pulseIn(pinEcho, HIGH);
  jarak = (durasi / 2) / 29.1;
}