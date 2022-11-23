
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPLvprjTkTT"
#define BLYNK_DEVICE_NAME "T41 Kontrol Cahaya"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  analogWrite(D3, pinValue);
  Blynk.virtualWrite(V0, pinValue);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop()
{
  BlynkEdgent.run();
}