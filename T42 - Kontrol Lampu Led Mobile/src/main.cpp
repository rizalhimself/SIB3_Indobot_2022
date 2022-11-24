
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPLz2AkoHPB"
#define BLYNK_DEVICE_NAME "T42 Kontrol LED"

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

#define pinLED1 D6
#define pinLED2 D7
#define vpLED1 V0
#define vpLED2 V1
#define vpWg1 V2
#define vpWg2 V3

WidgetLED wgLed1(vpWg1);
WidgetLED wgLed2(vpWg2);

BLYNK_WRITE(vpLED1)
{
  int pinVal1 = param.asInt();
  digitalWrite(pinLED1, pinVal1);
  if (pinVal1 == 1)
  {
    wgLed1.on();
  }
  else
  {
    wgLed1.off();
  }
}

BLYNK_WRITE(vpLED2)
{
  int pinVal2 = param.asInt();
  digitalWrite(pinLED2, pinVal2);
  if (pinVal2 == 1)
  {
    wgLed2.on();
  }
  else
  {
    wgLed2.off();
  }
}
void setup()
{
  Serial.begin(115200);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  delay(100);

  BlynkEdgent.begin();
}

void loop()
{
  BlynkEdgent.run();
}
