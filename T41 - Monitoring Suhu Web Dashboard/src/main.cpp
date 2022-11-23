
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPLCNbVqEoF"
#define BLYNK_DEVICE_NAME "T42 Monitor Suhu"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define DHTPIN D6
#define RELAYPIN D2

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <DHT.h>
#include <Arduino.h>

DHT dht(DHTPIN, DHT11);
WidgetLED ledRelay(V2);
float suhu, kelembapan;
BlynkTimer timer;

void sendSensorData()
{
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  Serial.print("% Temperature: ");
  Serial.print(suhu);
  Serial.println("C ");
  Serial.print("% Kelembaban: ");
  Serial.print(kelembapan);
  Serial.println("% ");

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);

  if (suhu >= 30 && kelembapan >= 60)
  {
    ledRelay.on();
    digitalWrite(RELAYPIN, LOW);
  }
  else
  {
    ledRelay.off();
    digitalWrite(RELAYPIN, HIGH);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(RELAYPIN, OUTPUT);
  delay(100);
  BlynkEdgent.begin();
  dht.begin();
  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
