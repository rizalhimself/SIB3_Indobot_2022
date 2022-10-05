#include <Arduino.h>
const int pinLDR = A2;
int valSensor;
float voltageSensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valSensor = analogRead(pinLDR);
  voltageSensor = valSensor * (5.0 / 1023.0);
  Serial.print("Pembacaan Analog: ");
  Serial.println(valSensor);
  Serial.print("Pembacaan Voltase: ");
  Serial.print(voltageSensor);
  Serial.println(" volt");

  delay(1000);
}