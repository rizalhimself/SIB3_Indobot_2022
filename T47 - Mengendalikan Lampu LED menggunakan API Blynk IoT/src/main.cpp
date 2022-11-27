#define BLYNK_TEMPLATE_ID "TMPLIwod7PUR"
#define BLYNK_DEVICE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "6YE0Yj6e_Bfig7epSLIfbYKvNoGhORmy"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo1820";
char password[] = "sinta123";

#define led1 D5
#define led2 D6
#define vPinLedKuning V1
#define vPinLedHijau V0
#define vPinDataTimer V2

BlynkTimer timer;

BLYNK_WRITE(vPinLedHijau)
{
  int pinValue = param.asInt();
  digitalWrite(led1, pinValue);
}

BLYNK_WRITE(vPinLedKuning)
{
  int pinValue1 = param.asInt();
  digitalWrite(led2, pinValue1);
}

void myTimerEvent(){
  Blynk.virtualWrite(vPinDataTimer, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Blynk.begin(auth, ssid, password);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}