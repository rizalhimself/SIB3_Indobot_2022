#include <Arduino.h>
#define ledPin 26

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); //
}
void loop()
{
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');

    if (command == "ON")
    {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED is turned ON");
    }
    else if (command == "OFF")
    {
      digitalWrite(ledPin, LOW);
      Serial.println("LED is turned OFF");
    }
  }
}