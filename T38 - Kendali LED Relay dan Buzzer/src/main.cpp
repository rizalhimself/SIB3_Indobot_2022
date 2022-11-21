// blynk parameter
#define BLYNK_TEMPLATE_ID "TMPL14751ZPj"
#define BLYNK_DEVICE_NAME "T38 Kendali LED Relay dan Buzzer"
#define BLYNK_AUTH_TOKEN "6mSUUUtoKYSFJ_HTdP2i5k-rmXBqKChC"

// init libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// hw parameter
#define LED D6
#define Buzzer D5
#define Relay D7

// wifi parameer
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo1820";
char pass[] = "sinta123";

// create variable
#define BLYNK_PRINT Serial

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(LED, pinValue);
}

BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt();
  if (pinValue1 == 1)
  {
    tone(Buzzer, 700);
  } else
  {
    noTone(Buzzer);
  }
}

BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt();
  int nR = 1;
  if (pinValue2 == 1)
  {
    nR = 0;
  } else
  {
    nR = 1;
  }
  digitalWrite(Relay, nR);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
}