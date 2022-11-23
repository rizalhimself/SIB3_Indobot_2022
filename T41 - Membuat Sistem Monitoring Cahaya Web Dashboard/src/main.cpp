
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"

#define BLYNK_TEMPLATE_ID "TMPLYcMX5hxS"
#define BLYNK_DEVICE_NAME "T42 Web Dashboard"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include <Arduino.h>
#include "BlynkEdgent.h"
BlynkTimer timer;
int ldrValue;
float voltage;

void sendSensorValue()
{
  ldrValue = analogRead(A0);
  voltage = ldrValue * (5.0 / 1023.0);

  Serial.print("Analog = ");
  Serial.println(ldrValue);
  Blynk.virtualWrite(V0, ldrValue);
  delay(1000);
  Serial.print("Voltage = ");
  Serial.println(voltage);
  Blynk.virtualWrite(V1, voltage);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(1000L, sendSensorValue);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
