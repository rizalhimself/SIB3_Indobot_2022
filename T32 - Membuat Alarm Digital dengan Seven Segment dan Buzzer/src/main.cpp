#include <Arduino.h>
#include <NTPClient.h> //Memanggil Library NTPClient.h
#include <ESP8266WiFi.h> //Memanggil library ESP8266 WiFi
#include <WiFiUdp.h> //Memanggil Library WiFiUdp
#include <TM1637.h> //Library TM1637
#define CLK D4 //Deklarasi Pin Clock pada Pin D4 Wemos
#define DIO D3 //Deklarasi Pin DIO pada pin D3 Wemos
TM1637 tm1637(CLK, DIO); //Deklarasi pin TM1637

int buzzer = D6; //deklarasi pin buzzer pada D6
const char *ssid = "vivo1820";
const char *password = "sinta123";

const long utcOffsetInSeconds = 25200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; //Variabel dengan data hari

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

int hh, mm, ss; //deklarasi variabel jam, menit dan detik.

void setup() {
Serial.begin(115200); //mengatur serial monitor pada baudrate 115200

WiFi.begin(ssid, password); //Memulai inisialisasi WiFi
pinMode(buzzer,OUTPUT);
while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}

timeClient.begin(); //Memulai NTPClient
tm1637.init();
tm1637.set(7);
}

void loop() {
timeClient.update();
hh = timeClient.getHours(); //Jam
mm = timeClient.getMinutes(); //Menit
ss = timeClient.getSeconds(); //Detik
//Kode untuk mengatur alarm
if (hh == 9 & mm ==36 & ss == 00){ //jam 23, menit ke 25, detik 00
digitalWrite(buzzer,HIGH);
delay(10000);
digitalWrite(buzzer,LOW);
}
Serial.print(daysOfTheWeek[timeClient.getDay()]); //Menampilkan informasi hari pada serial monitor
Serial.print(", ");
Serial.print(hh); //mencetak jam pada serial monitor
Serial.print(":");
Serial.print(mm); //mencetak menit pada serial monitor
Serial.print(":");
Serial.println(ss); //mencetak detik pada serial monitor
//Serial.println(timeClient.getFormattedTime());
tm1637.point(POINT_OFF);
tm1637.display(0, hh / 10); // jam
tm1637.display(1, hh % 10);
tm1637.display(2, mm / 10); // menit
tm1637.display(3, mm % 10); //
delay(500);
tm1637.point(POINT_ON);
tm1637.display(0, hh / 10); // jam
tm1637.display(1, hh % 10);
tm1637.display(2, mm / 10); // menit
tm1637.display(3, mm % 10); //
delay(500);
}