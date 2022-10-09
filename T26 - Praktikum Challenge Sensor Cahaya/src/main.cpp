#include <Arduino.h>

#define pinLDR A0
#define pinLED D8

int valSensor;
float voltageSensor;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  valSensor = analogRead(pinLDR);
  voltageSensor = valSensor * (5.0 / 1023.0);
  Serial.print("Pembacaan Analog: ");
  Serial.println(valSensor);
  Serial.print("Pembacaan Voltase: ");
  Serial.print(voltageSensor);
  Serial.println(" volt");
  delay(1000);

  if (valSensor >= 1000)
  {
    digitalWrite(pinLED, HIGH);
    Serial.println("+++ Lampu Menyala! +++");
  }
  else
  {
    digitalWrite(pinLED, LOW);
    Serial.println("+++ Lampu Mati! +++");
  }
}