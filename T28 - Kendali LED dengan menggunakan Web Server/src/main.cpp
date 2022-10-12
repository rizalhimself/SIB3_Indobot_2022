#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "vivo1820";
const char* password = "sinta123";
const int ledPin = D2;

const char index_on[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <title>Kendali LED dengan Web Server</title>
</head>
<style>
    header {
        background-color: slategray;
        padding: 30px;
        text-align: center;
    }

    h1 {
        color: blanchedalmond;
        font-size: larger;
    }

    h2 {
        font-size: large;
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

    .btnContainer {
        text-align: center;
    }

    footer {
        background-color: slategray;
        padding: 10px;
        text-align: center;
    }
</style>

<body>
    <header>
        <h1>Kendali LED dengan Web Server WeMos D1 R1</h1>
    </header>
    <br>
    <br>
    <section>
        <div class="btnContainer">
            <h2>Saklar LED Merah</h2>
            <form action="?" method="post">
                <label class="switch">
                    <input type="checkbox" name="switch_1" value="on" onchange="this.form.submit()">
                    <span class="slider round"></span>
                </label>
                <input type="hidden" name="switch_1" value="off" onchange="this.form.submit()">
            </form>
        </div>
    </section>
    <br>
    <br>
    <footer>
        <div class="textFooter">
            <b>Rizal Alfikri | SIB3_Wifi</b>
        </div>
    </footer>
</body>

</html>
)=====";

const char index_off[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <title>Kendali LED dengan Web Server</title>
</head>
<style>
    header {
        background-color: slategray;
        padding: 30px;
        text-align: center;
    }

    h1 {
        color: blanchedalmond;
        font-size: larger;
    }

    h2 {
        font-size: large;
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

    .btnContainer {
        text-align: center;
    }

    footer {
        background-color: slategray;
        padding: 10px;
        text-align: center;
    }
</style>

<body>
    <header>
        <h1>Kendali LED dengan Web Server WeMos D1 R1</h1>
    </header>
    <br>
    <br>
    <section>
        <div class="btnContainer">
            <h2>Saklar LED Merah</h2>
            <form action="?" method="post">
                <label class="switch">
                    <input type="checkbox" name="switch_1" value="off" onchange="this.form.submit()" checked>
                    <span class="slider round"></span>
                </label>
                <input type="hidden" name="switch_1" value="off" onchange="this.form.submit()">
            </form>
        </div>
    </section>
    <br>
    <br>
    <footer>
        <div class="textFooter">
            <b>Rizal Alfikri | SIB3_Wifi</b>
        </div>
    </footer>
</body>

</html>
)=====";

ESP8266WebServer server(80);

const int led = 0;

void returnFail(String msg){
  server.sendHeader("Connection","close");
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(500,"text/plain",msg+"\r\n");
}

void writeLED(int LEDon){
  if (LEDon == 1)
  {
    digitalWrite(ledPin, HIGH);
  } else if (LEDon == 0)
  {
    digitalWrite(ledPin, LOW);
  }  
}

void handleSubmit(){
  String LEDvalue;

  if (!server.hasArg("switch_1"))
  {
    return returnFail("BAD ARGS");
  }
  Serial.println(server.arg("switch_1"));
  LEDvalue = server.arg("switch_1");

  if (LEDvalue == "on")
  {
    writeLED(1);
    server.send(200,"text/html",index_off);
  } else if (LEDvalue == "off")
  {
    writeLED(0);
    server.send(200,"text/html",index_on);
  } else
  {
    returnFail("Bad LED Value");
  }
}

void handleRoot(){
  if (server.hasArg("switch_1"))
  {
    handleSubmit();
  } else
  {
    server.send(200,"text/html",index_on);
  }
}

void handle_on(){
  writeLED(1);
}

void handle_off(){
  writeLED(0);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Terkoneksi ke ");
  Serial.println(ssid);
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/led_on",handle_on);
  server.on("/led_off", handle_off);

  server.begin();
  Serial.println("ESP8266 HTTP Server Dimulai");
  
}

void loop() {
  server.handleClient();
}