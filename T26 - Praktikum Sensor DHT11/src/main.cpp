#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define dhtPin D8
#define DHTTYPE DHT11
DHT dht(dhtPin,DHTTYPE);
float kelembapan, suhu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  Serial.println("Room Monitor");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  Serial.print("Suhu saat ini = ");
  Serial.print(suhu);
  Serial.println(" *C");
  delay(1000);
  Serial.print("Kelembapan saat ini = ");
  Serial.print(kelembapan);
  Serial.println(" %");
  delay(1000);
}