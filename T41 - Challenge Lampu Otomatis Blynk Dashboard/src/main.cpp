
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPLfqOobXmZ"
#define BLYNK_DEVICE_NAME "T41 CH1"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define LED D7

#define vPinMode V0
#define vPinSwOnOff V1
#define vPinVoltase V2
#define vPinLDR V3
#define vPinLedStats V4

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include <Arduino.h>
#include "BlynkEdgent.h"
BlynkTimer timer;
int ldrValue;
int ledstats = 0;
int ledSwitch = 0;
int pinModeVal = 0;
float voltage;

void lampuOtomatis()
{
  if (ldrValue <= 700)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}

void lampuManual()
{
  if (ledSwitch == 1)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}

BLYNK_WRITE(vPinMode)
{
  pinModeVal = param.asInt();
}

BLYNK_WRITE(vPinSwOnOff)
{
  ledSwitch = param.asInt();
}

void sendSensorValue()
{
  ldrValue = analogRead(A0);
  ledstats = digitalRead(LED);
  voltage = ldrValue * (5.0 / 1023.0);

  Serial.print("Analog = ");
  Serial.println(ldrValue);
  Serial.print("Voltage = ");
  Serial.println(voltage);
  if (ledstats == 1)
  {
    Serial.println("Led Menyala!");
  }
  else
  {
    Serial.println("Led Mati!");
  }
  Blynk.virtualWrite(vPinLDR, ldrValue);
  delay(500);
  Blynk.virtualWrite(vPinVoltase, voltage);
  delay(500);
  Blynk.virtualWrite(vPinLedStats, ledstats);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(1000L, sendSensorValue);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();

  if (pinModeVal == 1)
  {
    lampuOtomatis();
  }
  else
  {
    lampuManual();
  }
}
