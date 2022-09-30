//definisikan Pin yang digunakan
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int LED4 = D5;

//buat array dari variabel Pin yang akan digunakan untuk perulangan
int ledPin[]={LED1,LED2,LED3,LED4};
//buat variabel untuk delay
int nDelay = 1000;

void setup() {
  //perulangan untuk menentukan pin menjadi output
  for(int i = 0; i < 4; i++){
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  //perulangan untuk menghidupmatikan led
  for(int i = 0; i < 4; i++){
      digitalWrite(ledPin[i], HIGH);
      delay(nDelay);
    }
  for(int j = 0; j < 4; j++){
    digitalWrite(ledPin[j], LOW);
    delay(nDelay);
  }
}
