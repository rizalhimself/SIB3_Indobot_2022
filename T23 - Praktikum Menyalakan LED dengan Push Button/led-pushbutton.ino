const int pinLED = D2;
const int pinPB = D3;

void setup()
{
    pinMode(pinLED, OUTPUT);
    pinMode(pinPB, INPUT_PULLUP);
}
void loop()
{
    if (digitalRead(pinPB) == HIGH)
    {
        digitalWrite(pinLED, LOW);
    }
    else
    {
        digitalWrite(pinLED, HIGH);
    }
}