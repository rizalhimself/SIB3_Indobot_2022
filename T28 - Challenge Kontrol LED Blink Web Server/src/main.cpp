#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "vivo1820";
const char *password = "sinta123";
const char *parameterInput_1 = "output";
const char *parameterInput_2 = "state";
const int pinLedBiru = D8;

int r = 0;
int blinkState = 0;

unsigned long waktuSebelum = 0;
const long interval = 5000;

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kontrol LED dengan Web Server</title>
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

    footer {
        background-color: slategray;
        padding: 10px;
    }

    p.sinyal {
        color: burlywood;
    }
</style>

<body>
    <header>
        <h1>Kontrol LED dengan WeMos D1 R1 Web Server</h1>
        <p class="sinyal">
            <i class="fas fa-signal"></i>
            <span class="sigalRSSI">Sinyal Perangkat </span>
            <span id="rssi">%RSSI%</span>
            <sup class="units">db</sup>
        </p>

    </header>
    <br>
    <br>
    %BUTTONPLACEHOLDER%
    <br>
    <br>
    <footer>
        <div class="textFooter">
            <b>Rizal Alfikri | SIB3_Wifi</b>
        </div>
    </footer>
</body>
<script>
    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("rssi").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/rssi", true);
        xhttp.send();
    }, 10000);

    function tonggleCheckbox(element) {
        var xhr = new XMLHttpRequest();
        if (element.checked) {
            xhr.open("GET", "/update?output=" + element.id + "&state=1", true);
        } else {
            xhr.open("GET", "/update?output=" + element.id + "&state=0", false);
        }
        xhr.send();
    }
</script>

</html>
)rawliteral";

String outputState(int output)
{
    if (digitalRead(output))
    {
        return "checked";
    }
    else
    {
        return "";
    }
}

String processor(const String &var)
{
    if (var == "BUTTONPLACEHOLDER")
    {
        String buttons = "";
        buttons += "<h4>Saklar LED Biru</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"tonggleCheckbox(this)\" id=\"0\" " + outputState(pinLedBiru) + "><span class=\"slider\"></span></label>";
        buttons += "<h4>Saklar Blink LED</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"tonggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    else if (var == "RSSI")
    {
        return String(r);
    }
    return String();
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(pinLedBiru, OUTPUT);
    digitalWrite(pinLedBiru, LOW);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("Mengoneksikan ke jaringan ");
        Serial.print(ssid);
        Serial.println(" ...");

    }
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html, processor); });

    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    String inputMessage1;
    String inputMessage2;
    if (request->hasParam(parameterInput_1)&& request->hasParam(parameterInput_2))
    {
      inputMessage1 = request->getParam(parameterInput_1)->value();
      inputMessage2 = request->getParam(parameterInput_2)->value();
      Serial.println(inputMessage1);
      Serial.println(inputMessage2);
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
      if (inputMessage1 == "2" && inputMessage2 == "0")
      {
        blinkState = 0;
      } else if (inputMessage1 == "2" && inputMessage2 == "1")
      {
        blinkState = 1;
      }
    }
    else
    {
      inputMessage1 = "Tidak ada perintah dikirim!";
      inputMessage2 = "Tidak ada perintah dikirim!";
    }
    Serial.print("Pin: ");
    Serial.print(inputMessage1);
    Serial.print("- Diset ke: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK"); });

    server.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (blinkState == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            digitalWrite(pinLedBiru, HIGH);
            delay(100);
            digitalWrite(pinLedBiru, LOW);
            delay(100);
        }
    }
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
        waktuSebelum = waktuMillis;
    }
}