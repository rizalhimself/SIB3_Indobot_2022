// blynk parameter
#define BLYNK_TEMPLATE_ID "TMPLssl0lDbc"
#define BLYNK_DEVICE_NAME "T38 Challenge Kendali dan Monitoring"
#define BLYNK_AUTH_TOKEN "ELHAeXWfFy0h4mPAGfjis97C0mV6oGEr"

// init libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// hw parameter
#define LED D6
#define Buzzer D5
#define Relay D7
#define DHTPin D8
#define DHTType DHT11

// wifi parameer
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo1820";
char pass[] = "sinta123";

// create variable
#define BLYNK_PRINT Serial
BlynkTimer timer;
float suhu, kelembapan;
DHT dht(DHTPin, DHTType);

void sendSensorValue()
{
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  Serial.print("% Temperature: ");
  Serial.print(suhu);
  Serial.println("C ");
  Serial.print("% Kelembaban: ");
  Serial.print(kelembapan);
  Serial.println("% ");

  Blynk.virtualWrite(V3, suhu);
  Blynk.virtualWrite(V4, kelembapan);
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(LED, pinValue);
  if (pinValue == 0)
  {
    Serial.println("LED Off");
  }
  else
  {
    Serial.println("LED On");
  }
}

BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt();
  if (pinValue2 == 1)
  {
    tone(Buzzer, 700);
    Serial.println("Buzzer Berbunyi");
  }
  else
  {
    noTone(Buzzer);
    Serial.println("Buzzer Mati");
  }
}

BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt();
  digitalWrite(Relay, pinValue1);
  if (pinValue1 == 1)
  {
    Serial.println("Relay Off");
  }
  else
  {
    Serial.println("Relay On");
  }
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
  dht.begin();
  timer.setInterval(1000L, sendSensorValue);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}