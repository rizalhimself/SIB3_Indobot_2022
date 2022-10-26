#include <Arduino.h>
#include <Esp.h>

int bilA, bilB, hasil;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("===Program Perbandingan Bilangan===");
  Serial.println("Masukkan Bilangan A = ");
  while (Serial.available() == 0)
  {
    // waiting for the input
  }
  bilA = Serial.parseInt();
  Serial.print("Bilangan A adalah = ");
  Serial.println(bilA);
  delay(1000);

  Serial.println("Masukkan Bilangan B = ");
  while (Serial.available() == 0)
  {
    // waiting for the input
  }
  bilB = Serial.parseInt();
  Serial.print("Bilangan B adalah = ");
  Serial.println(bilB);
  delay(1000);

  Serial.println("===Pilihan program yang tersedia: ===");
  Serial.println("1. Perbandingan Bilangan A dan B");
  Serial.println("2. Bilangan Ganjil Genap");
  Serial.println("3. Restart Device");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Masukkan pilihan anda = ");

  while (Serial.available() == 0)
  {
    // dont do anything but run switch function
  }

  int pilihanMenu = Serial.parseInt();
  switch (pilihanMenu)
  {
  case 1:
    Serial.println("===Perbandingan bilangan A dan B===");
    if (bilA > bilB)
    {
      Serial.print(bilA);
      Serial.print(" lebih besar dari ");
      Serial.println(bilB);
    }
    else if (bilA < bilB)
    {
      Serial.print(bilA);
      Serial.print(" lebih kecil dari ");
      Serial.println(bilB);
    }
    else if (bilA == bilB)
    {
      Serial.println("Bilangan A sama dengan Bilangan B");
    }
    break;

  case 2:
    Serial.println("===Bilangan Ganjil atau Genap===");
    if (bilA % 2 == 0)
    {
      Serial.print(bilA);
      Serial.print(" adalah bilangan genap dan ");
    }
    else
    {
      Serial.print(bilA);
      Serial.print(" adalah bilangan ganjil dan ");
    }

    if (bilB % 2 == 0)
    {
      Serial.print(bilB);
      Serial.println(" adalah bilangan genap. ");
    }
    else
    {
      Serial.print(bilB);
      Serial.println(" adalah bilangan ganjil. ");
    }
    break;

  case 3:
    ESP.restart();
    break;

  default:
    break;
  }
}