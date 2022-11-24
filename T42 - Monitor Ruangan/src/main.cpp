
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPL6qyKS5k8"
#define BLYNK_DEVICE_NAME "T42 MR"

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
#include "DHT.h"

#define relayPin D4
#define dhtPin D5
#define ledPin D3
#define ldrPin A0
#define ledMerahPin D6
#define ledHijauPin D7

#define vPinTemp V0
#define vPinKelembapan V1
#define vPinIntenCahaya V2
#define vPinStatRelay V4
#define vPinStatLampu V3
#define vPinStatLampuHijau V5
#define vPinStatLampuMerah V6

DHT dht(dhtPin, DHT11);
BlynkTimer timer;
WidgetLED wLed1(vPinStatLampu);
WidgetLED wLedH(vPinStatLampuHijau);
WidgetLED wLedM(vPinStatLampuMerah);
WidgetLED wLedRelay(vPinStatRelay);

float suhu = 0.0;
float kelembapan = 0.0;
float voltage = 0.0;
int nilaiLDR = 0;

void sendSensorData()
{
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  nilaiLDR = analogRead(ldrPin);
  voltage = nilaiLDR * (5.0 / 1023.0);

  Serial.print("% Temperature: ");
  Serial.print(suhu);
  Serial.println("C ");
  Serial.print("% Kelembaban: ");
  Serial.print(kelembapan);
  Serial.println("% ");
  Serial.print("% Nilai LDR: ");
  Serial.print(nilaiLDR);
  Serial.println("r ");
  Serial.print("% Voltase: ");
  Serial.print(voltage);
  Serial.println("V ");

  Blynk.virtualWrite(vPinTemp, suhu);
  Blynk.virtualWrite(vPinKelembapan, kelembapan);
  Blynk.virtualWrite(vPinIntenCahaya, nilaiLDR);

  if (suhu > 30 && kelembapan > 50)
  {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledMerahPin, HIGH);
    digitalWrite(ledHijauPin, LOW);
    wLedRelay.on();
    wLedM.on();
    wLedH.off();
    Serial.println("+ Relay Hidup");
    Serial.println("+ LED Merah Menyala");
  }
  else
  {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledMerahPin, LOW);
    digitalWrite(ledHijauPin, HIGH);
    wLedRelay.off();
    wLedH.on();
    wLedM.off();
    Serial.println("+ Relay Mati");
    Serial.println("+ LED Hijau Menyala");
  }

  if (nilaiLDR > 500)
  {
    digitalWrite(ledPin, HIGH);
    wLed1.on();
    Serial.println("+ LED LDR Hidup");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    wLed1.off();
    Serial.println("+ LED LDR Mati");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  dht.begin();
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledHijauPin, OUTPUT);
  pinMode(ledMerahPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  BlynkEdgent.begin();
  timer.setInterval(2000L, sendSensorData);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
