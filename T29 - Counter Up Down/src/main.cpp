#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 19
#define DIO 18
#define btIncreasePin 25
#define btDecreasePin 26

int value = 0;
int btIncreaseState = 0;
int btDecreaseState = 0;
TM1637Display display(CLK, DIO);

const uint8_t allOn[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t allOff[] = {0x00, 0x00, 0x00, 0x00};

void setup()
{
  // put your setup code here, to run once:
  pinMode(btIncreasePin, INPUT);
  pinMode(btDecreasePin, INPUT);
  display.setBrightness(7);
  display.setSegments(allOn);
  delay(1000);
  display.setSegments(allOff);
  delay(1000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  btDecreaseState = digitalRead(btDecreasePin);
  btIncreaseState = digitalRead(btIncreasePin);

  if (btIncreaseState == HIGH)
  {
    /* code */
    if (value == 9999)
    {
      value = 0;
    }
    else
    {
      value++;
    }
  }

  if (btDecreaseState == HIGH)
  {
    /* code */
    if (value == 0)
    {
      value = 9999;
    }
    else
    {
      value--;
    }
  }

  display.showNumberDec(value);
  delay(200);
}