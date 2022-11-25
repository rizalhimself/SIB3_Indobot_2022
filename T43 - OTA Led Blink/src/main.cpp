
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPL-Yuk1grF"
#define BLYNK_DEVICE_NAME "43 OTA"

#define BLYNK_FIRMWARE_VERSION "0.1.4"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include "DHT.h"

#define pinLed D7
#define pinLDR A0
#define pinDHT D6

#define vPinSwLED V0
#define vPinNLDR V1
#define vPinNvoltase V2
#define vPinNsuhu V3
#define vPinNkelembapan V4

int pinVal, nilaiLDR;
float voltase, suhu, kelembapan;
BlynkTimer timer;
DHT dht(DHT11, pinDHT);

BLYNK_WRITE(vPinSwLED)
{
  pinVal = param.asInt();
  if (pinVal == 1)
  {
    digitalWrite(pinLed, pinVal);
  }
  else
  {
    digitalWrite(pinLed, pinVal);
  }
}

void sendSensorData()
{
  nilaiLDR = analogRead(pinLDR);
  voltase = nilaiLDR * (5.0 / 1023.0);
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  Blynk.virtualWrite(vPinNLDR, nilaiLDR);
  Serial.println("Nilai LDR = ");
  Serial.print(nilaiLDR);
  Serial.print(" K");
  delay(250);
  Blynk.virtualWrite(vPinNvoltase, voltase);
  Serial.println("Voltase = ");
  Serial.print(voltase);
  Serial.print(" Volt");
  delay(250);
  Blynk.virtualWrite(vPinNsuhu, suhu);
  Serial.println("Suhu = ");
  Serial.print(suhu);
  Serial.print(" C");
  delay(250);
  Blynk.virtualWrite(vPinNkelembapan, kelembapan);
  Serial.println("Kelembapan = ");
  Serial.print(kelembapan);
  Serial.print(" %");
  delay(250);
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(pinLed, OUTPUT);
  delay(100);
  timer.setInterval(1000L, sendSensorData);
  BlynkEdgent.begin();
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
