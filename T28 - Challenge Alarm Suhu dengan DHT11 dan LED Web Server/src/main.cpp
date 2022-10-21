#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char *ssid = "vivo1820";
const char *password = "sinta123";
const int pinLedM = D2;
const int pinLedK = D3;
const int pinLedH = D4;
const int pinLedB = D5;
const int pinDHT = D6;
const int pinBz = D7;
int pinLED[] = {pinLedM, pinLedK, pinLedH};

const char *parameter = "batasSuhu";
const char *parameter2 = "btState";

#define DHTTYPE DHT11

DHT dht(pinDHT, DHTTYPE);
AsyncWebServer server(80);

float t = 0.0;
float h = 0.0;
int r = 0;
int b = 0;
int swState = 0;

unsigned long waktuSebelum = 0;
const long interval = 5000;
unsigned long waktuSebelum2 = 0;
const long interval2 = 1000;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Monitoring Suhu dan Kelembapan Sensor DHT11</title>
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css"
        integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
</head>

<style>
    html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
    }

    header {
        background-color: slategray;
        padding: 30px;
    }

    h1 {
        color: #ffebcd;
        font-size: larger;
    }

    footer {
        background-color: slategray;
        padding: 10px;
    }

    p.sinyal {
        color: burlywood;
    }

        .switch {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
    }

    .switch input {
        display: none;
    }

    .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        -webkit-transition: .4s;
        transition: .4s;
    }

    .slider:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        -webkit-transition: .4s;
        transition: .4s;
    }

    input:checked+.slider {
        background-color: #2196F3;
    }

    input:focus+.slider {
        box-shadow: 0 0 1px #2196F3;
    }

    input:checked+.slider:before {
        -webkit-transform: translateX(26px);
        -ms-transform: translateX(26px);
        transform: translateX(26px);
    }

    .slider.round {
        border-radius: 34px;
    }

    .slider.round:before {
        border-radius: 50%;
    }


</style>

<body>
    <header>
        <h1>Monitoring Suhu dan Kelembapan Sensor DHT11 dengan Web Server WeMos D1 R1</h1>
        <p class="sinyal">
            <i class="fas fa-signal"></i>
            <span class="sigalRSSI">Sinyal Perangkat </span>
            <span id="rssi">%RSSI%</span>
            <sup class="units">db</sup>
        </p>
    </header>
    <br>
    <br>
    <p>
        <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
        <span class="dht-labels">Suhu </span>
        <span id="temperature">%TEMPERATURE%</span>
        <sup class="units">°C</sup>
    </p>
    <p>
        <i class="fas fa-bell" style="color: #059e8a"></i>
        <span class="alm-labels">Alarm Suhu </span>
        <span id="alm">%ALM%</span>
        <sup class="units">°C</sup>
    </p>
    <p>
        <i class="fas fa-tint" style="color:#00add6;"></i>
        <span class="dht-labels">Kelembapan </span>
        <span id="humidity">%HUMIDITY%</span>
        <sup class="units">&#x25</sup>
    </p>
    <br>
    %BUTTON%
    <form action="/get">
        <br>
        <b>Setting Alarm Suhu</b>
        <br>
        <br>
        <input type="text" name="batasSuhu">
        <sup class="units">°C</sup>
        <input id="button" type="submit" value="Submit" disabled>
    </form>
    <br>
    <br>
    <footer>
        <div class="textFooter">
            <b>Rizal Alfikri | SIB3_Wifi</b>
        </div>
    </footer>
</body>
<script>
    var interval = 5000;
    var suhu = 0;
    var bSuhu;
    const btSubmit = document.getElementById("button");
    const checkbox = document.getElementById("checkbox1");
    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("rssi").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/rssi", true);
        xhttp.send();
    }, interval);

    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = this.responseText;
                suhu = parseInt(this.responseText);
            }
        };
        xhttp.open("GET", "/temperature", true);
        xhttp.send();
    }, interval);

    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("humidity").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/humidity", true);
        xhttp.send();
    }, interval);

    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("alm").innerHTML = this.responseText;
                bSuhu = parseInt(this.responseText);
            }
        };
        xhttp.open("GET", "/alm", true);
        xhttp.send();
    }, interval);

    setInterval(function () {
        if (bSuhu != 0) {
          btSubmit.disabled = false;
          checkbox.checked = true;
        } else if (bSuhu == 0) {
          btSubmit.disabled = true;
          checkbox.checked = false;
        }
    }, interval);

    function tonggleButton() {
      var xhttp = new XMLHttpRequest();
        if (checkbox.checked) {
            btSubmit.disabled = false;
            xhttp.open("GET","/get?btState=1",true);
        } else {
            btSubmit.disabled = true;
            xhttp.open("GET","/get?btState=0",true);
            bSuhu = 0;
        }
        xhttp.send();
    }

</script>

</html>
)rawliteral";

String processor(const String &var)
{
  if (var == "RSSI")
  {
    return String(r);
  }
  else if (var == "TEMPERATURE")
  {
    return String(t);
  }
  else if (var == "HUMIDITY")
  {
    return String(h);
  }
  else if (var == "ALM")
  {
    return String(b);
  }
  else if (var == "BUTTON")
  {
    String tombol = "";
    tombol += "<h4>Saklar Alarm Suhu</h4><label class=\"switch\"><input id=\"checkbox1\" type=\"checkbox\" onchange=\"tonggleButton()\"><span class=\"slider\"round\"></span></label>";
    return tombol;
  }

  return String();
}

void loadingLedAnim()
{
  for (int k = 0; k < 3; k++)
  {
    for (int i = 0; i <= 2; i++)
    {
      digitalWrite(pinLED[i], HIGH);
      delay(400);
      digitalWrite(pinLED[i], LOW);
    }
  }
}

void setup()
{
  pinMode(pinLedM, OUTPUT);
  pinMode(pinLedH, OUTPUT);
  pinMode(pinLedK, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  pinMode(pinBz, OUTPUT);
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Mengoneksikan WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    loadingLedAnim();
    Serial.print("Mengoneksikan ke jaringan ");
    Serial.print(ssid);
    Serial.println(" ...");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
  server.on("/rssi", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(r).c_str()); });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(t).c_str()); });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(h).c_str()); });
  server.on("/alm", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(b).c_str()); });
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String inputMessage;
              String inputMessage2;
              if (request->hasParam(parameter))
              {
                inputMessage = request->getParam(parameter)->value();
                b = atoi(inputMessage.c_str());
              } else if (request->hasParam(parameter2))
              {
                inputMessage2 = request->getParam(parameter2)->value();
                swState = atoi(inputMessage2.c_str());
                if (swState == 0)
                {
                  b = 0;
                }
                
              }
              
              request->send_P(200, "text/html", index_html, processor); });

  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  unsigned long waktuMillis = millis();
  if (waktuMillis - waktuSebelum >= interval)
  {
    int newR = WiFi.RSSI();
    if (isnan(newR))
    {
      Serial.println("Gagal membaca kekuatan sinyal!");
    }
    else
    {
      r = newR;
      Serial.println(r);
    }

    float newT = dht.readTemperature();
    if (isnan(newT))
    {
      Serial.println("Gagal membaca suhu DHT Sensor!");
    }
    else
    {
      t = newT;
      Serial.println(t);
    }

    float newH = dht.readHumidity();
    if (isnan(newH))
    {
      Serial.println("Gagal membaca kelembapan DHT Sensor!");
    }
    else
    {
      h = newH;
      Serial.println(h);
    }

    waktuSebelum = waktuMillis;
  }
  unsigned long waktuMillis2 = millis();
  if (waktuMillis2 - waktuSebelum2 >= interval2)
  {
    waktuSebelum2 = waktuMillis2;
    if (r > -60)
    {
      digitalWrite(pinLedM, HIGH);
    }
    else
    {
      digitalWrite(pinLedM, LOW);
    }
    if (r >= -40)
    {
      digitalWrite(pinLedK, HIGH);
    }
    else
    {
      digitalWrite(pinLedK, LOW);
    }
    if (r >= -25)
    {
      digitalWrite(pinLedH, HIGH);
    }
    else
    {
      digitalWrite(pinLedH, LOW);
    }
  }
}