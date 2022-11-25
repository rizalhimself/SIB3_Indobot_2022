
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPL-Yuk1grF"
#define BLYNK_DEVICE_NAME "43 OTA BLINK"

#define BLYNK_FIRMWARE_VERSION "0.1.1"

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

BlynkTimer timer;
int st;

void ledBlink()
{
  if (st == 0)
  {
    digitalWrite(pinLed, HIGH);
    st = 1;
    Serial.println(st);
  }
  else
  {
    digitalWrite(pinLed, LOW);
    st = 0;
    Serial.println(st);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(500L, ledBlink);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
