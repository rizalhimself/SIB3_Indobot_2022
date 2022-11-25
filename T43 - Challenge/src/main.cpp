
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

#define pinLed D5
#define pinLDR A0
#define pinDHT D6

#define vPinSwLED V0
#define vPinNLDR V1
#define vPinVl V2
#define vPinSh V3
#define vPinKl V4

DHT dht(pinDHT,DHT11);
BlynkTimer timer;

int pinVal = 0;
int nilaiLDR = 0;
float voltase = 0.0;
float suhu, kelembapan;

BLYNK_WRITE(vPinSwLED)
{
  pinVal = param.asInt();
  if (pinVal == 1)
  {
    digitalWrite(pinLed, HIGH);
  }
  else
  {
    digitalWrite(pinLed, LOW);
  }
}

void sendSensorData()
{
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  nilaiLDR = analogRead(pinLDR);
  voltase = nilaiLDR * (5.0 / 1023.0);

  Serial.print("% Temperature: ");
  Serial.print(suhu);
  Serial.println("C ");
  Serial.print("% Kelembaban: ");
  Serial.print(kelembapan);
  Serial.println("% ");
  Serial.print("% Nilai LDR: ");
  Serial.print(nilaiLDR);
  Serial.println("r ");
  Serial.print("% Voltase: ");
  Serial.print(voltase);
  Serial.println("V ");

  Blynk.virtualWrite(vPinNLDR, nilaiLDR);
  Blynk.virtualWrite(vPinVl, voltase);
  Blynk.virtualWrite(vPinSh, suhu);
  Blynk.virtualWrite(vPinKl, kelembapan);
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  dht.begin();
  pinMode(pinLed, OUTPUT);

  BlynkEdgent.begin();
  timer.setInterval(2000L, sendSensorData);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
