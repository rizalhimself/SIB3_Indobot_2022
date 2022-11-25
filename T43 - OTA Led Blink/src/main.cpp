
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPL-Yuk1grF"
#define BLYNK_DEVICE_NAME "43 OTA"

#define BLYNK_FIRMWARE_VERSION "0.1.2"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#define pinLed D7

int pinVal;

BLYNK_WRITE(V0){
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

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  delay(100);

  BlynkEdgent.begin();
}

void loop()
{
  BlynkEdgent.run();
}
