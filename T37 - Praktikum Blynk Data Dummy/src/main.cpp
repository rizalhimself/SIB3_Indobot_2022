// blynk parameter
#define BLYNK_TEMPLATE_ID "TMPLCHOpu0yo"
#define BLYNK_DEVICE_NAME "Task 37 Praktikum Data Dummy"
#define BLYNK_AUTH_TOKEN "qCQqg3DObyAvqzMQmo8Xm83xHNjda8WD"

// init libraries
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// wifi parameer
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo1820";
char pass[] = "sinta123";

// create variable
#define BLYNK_PRINT Serial
BlynkTimer timer;

// create function
void myTimerEvent()
{
  Blynk.virtualWrite(V0, millis() / 1000);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}