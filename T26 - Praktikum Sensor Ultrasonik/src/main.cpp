#include <Arduino.h>
const int pinTrigger = D2;
const int pinEcho = D3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long durasi, jarak;
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  durasi = pulseIn(pinEcho, HIGH);
  jarak = (durasi/2) / 29.1;
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(500);
}