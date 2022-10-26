#include <Arduino.h>

String a, b;
void setup()
{
  // put your setup code here, to run once:
  b = "Hello World";
  Serial.begin(115200);
  Serial.println("Silakan Masukkan Nama Anda: ");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    a = Serial.readString();
    delay(1000);
    Serial.println(a);
    Serial.println(b);
  }
}