#include <Arduino.h>
#include <Esp.h>

int bilA, bilB, hasil;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("===Program Operator Aritmatika===");
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

  Serial.println("===Pilihan operasi aritmatika: ===");
  Serial.println("1. Penjumlahan");
  Serial.println("2. Pengurangan");
  Serial.println("3. Perkalian");
  Serial.println("4. Pembagian");
  Serial.println("5. Restart Device");
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
    Serial.println("===Penjumlahan bilangan A dan B===");
    hasil = bilA + bilB;
    Serial.print(bilA);
    Serial.print(" + ");
    Serial.print(bilB);
    Serial.print(" = ");
    Serial.println(hasil);
    break;

  case 2:
    Serial.println("===Pengurangan bilangan A dan B===");
    hasil = bilA - bilB;
    Serial.print(bilA);
    Serial.print(" - ");
    Serial.print(bilB);
    Serial.print(" = ");
    Serial.println(hasil);
    break;

  case 3:
    Serial.println("===Perkalian bilangan A dan B===");
    hasil = bilA * bilB;
    Serial.print(bilA);
    Serial.print(" x ");
    Serial.print(bilB);
    Serial.print(" = ");
    Serial.println(hasil);
    break;

  case 4:
    Serial.println("===Pembagian bilangan A dan B===");
    hasil = bilA / bilB;
    Serial.print(bilA);
    Serial.print(" : ");
    Serial.print(bilB);
    Serial.print(" = ");
    Serial.println(hasil);
    break;

  case 5:
    ESP.restart();
    break;

  default:
    break;
  }
}