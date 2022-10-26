#include <Arduino.h>
#define ldrPin 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrValue = analogRead(ldrPin);

  float voltage = ldrValue * (5.0 / 1023.0);
  Serial.print("Nilai LDR = ");
  Serial.println(ldrValue);
  Serial.print("Nilai Voltase = ");
  Serial.print(voltage);
  Serial.println(" Volt");
  delay(1000);
}