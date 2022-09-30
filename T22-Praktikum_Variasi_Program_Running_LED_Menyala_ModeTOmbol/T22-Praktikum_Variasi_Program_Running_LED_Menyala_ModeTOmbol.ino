//definisikan Pin yang digunakan
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int LED4 = D5;
const int PB1 = D6;

//buat array dari variabel Pin yang akan digunakan untuk perulangan
int ledPin[]={LED1,LED2,LED3,LED4};
//buat variabel untuk delay
int nDelay = 200;
//buat variabel untuk mode tombol
int statusTombol = 0;
int konter = 0;
int statusTerakhirTombol = 0;
//buat variabel untuk millis
unsigned long waktuSebelum = 0;
unsigned long interval = 1000;

void setup() {
  //inisialisasi PB1 Sebagai inputan PushButton
  pinMode(PB1, INPUT_PULLUP);
  //perulangan untuk menentukan pin menjadi output
  for(int i = 0; i < 4; i++){
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  //baca input tombol
  statusTombol = digitalRead(PB1);
  if (statusTombol != statusTerakhirTombol){
    if (statusTombol == HIGH){
      konter++;
    } else
    {
    }
    delay(nDelay);
  }
  statusTerakhirTombol = statusTombol;
  if (konter > 3){
    konter = 0;
  }
  //inisialisasi millis
  unsigned long waktuSekarang = millis();
  if(waktuSekarang - waktuSebelum >= interval){
    if (konter == 1)
    {
      //perulangan untuk menghidupmatikan led
      for(int i = 0; i < 4; i++){
          digitalWrite(ledPin[i], HIGH);
          delay(nDelay);
          digitalWrite(ledPin[i], LOW);
        }
      for(int i = 4; i >= 0; i--){
          digitalWrite(ledPin[i], HIGH);
          delay(nDelay);
          digitalWrite(ledPin[i], LOW);
        }
      delay(nDelay);
    } 
    else if (konter == 2)
    {
      //perulangan untuk menghidupmatikan led
      for(int i = 0; i < 4; i++)
      {
          digitalWrite(ledPin[i], HIGH);
          delay(nDelay);
      }
      for(int j = 0; j < 4; j++)
      {
        digitalWrite(ledPin[j], LOW);
        delay(nDelay);
      }
    }
    else if (konter == 3)
    {
      //buat variabel untuk pengacakan
      int acak = random(4);
      //perulangan untuk menghidupmatikan led
      digitalWrite(ledPin[acak], HIGH);
      delay(nDelay);
      digitalWrite(ledPin[acak], LOW);
    }
    waktuSebelum = waktuSekarang;
  }
}
