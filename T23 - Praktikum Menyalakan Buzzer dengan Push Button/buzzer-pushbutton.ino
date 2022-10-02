const int pinPB = D5;
const int pinLED = D3;
const int pinBZ = D4;

void setup()
{
    
    pinMode(pinPB, INPUT_PULLUP);
    pinMode(pinLED, OUTPUT);
    pinMode(pinBZ, OUTPUT);
}
void loop()
{
    int statusTombol = digitalRead(pinPB);
    if (statusTombol == HIGH)
    {
        digitalWrite(pinLED, LOW);
    }
    else
    {
        digitalWrite(pinLED, HIGH);
        tone(pinBZ, 500);
        delay(50);
        noTone(pinBZ);
    }
}