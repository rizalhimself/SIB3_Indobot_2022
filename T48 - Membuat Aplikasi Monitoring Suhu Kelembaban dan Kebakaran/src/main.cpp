#define BLYNK_TEMPLATE_ID "TMPLIwod7PUR"
#define BLYNK_DEVICE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "6YE0Yj6e_Bfig7epSLIfbYKvNoGhORmy"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo1820";
char password[] = "sinta123";

#define pinDHT D5
#define pinFS A0
#define vPinKelembapan V1
#define vPinSuhu V0
#define vPinDataIRSensor V2

BlynkTimer timer;
DHT dht(pinDHT, DHT11);

// lowest and highest sensor readings:
const int sensorMin = 0;    // sensor minimum
const int sensorMax = 1024; // sensor maximum
int sensorReading, range;
float suhu, kelembapan;

void sendSensorData()
{
  suhu = dht.readTemperature();
  Blynk.virtualWrite(vPinSuhu, suhu);
  Serial.print("% Temperature: ");
  Serial.print(suhu);
  Serial.println("C ");
  delay(250);

  kelembapan = dht.readHumidity();
  Blynk.virtualWrite(vPinKelembapan, kelembapan);
  Serial.print("% Kelembaban: ");
  Serial.print(kelembapan);
  Serial.println("% ");
  delay(250);

  sensorReading = analogRead(pinFS);
  range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  Serial.print("% Nilai Baca Sensor: ");
  Serial.println(sensorReading);
  Serial.print("% Nilai Range: ");
  Serial.println(range);
  switch (range)
  {
  case 0: // A fire closer than 1.5 feet away.
    Blynk.virtualWrite(vPinDataIRSensor, "3");
    Serial.print("% Nilai: ");
    Serial.print(3);
    Serial.println(" | Api Kurang Dari 1 Meter");
    break;
  case 1: // A fire between 1-3 feet away.
    Blynk.virtualWrite(vPinDataIRSensor, "2");
    Serial.print("% Nilai: ");
    Serial.print(2);
    Serial.println(" | Api Kurang Dari 3 Meter");
    break;
  case 2: // No fire detected.
    Blynk.virtualWrite(vPinDataIRSensor, "1");
    Serial.print("% Nilai: ");
    Serial.print(1);
    Serial.println(" | Tidak Ada Api Terdeteksi");
    break;
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, password);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}