//definisikan Pin yang digunakan
const int LED1 = D5;
const int LED2 = D4;
const int LED3 = D3;

//buat array dari variabel Pin yang akan digunakan untuk perulangan
int ledPin[]={LED1,LED2,LED3};
//buat variabel untuk delay
int nDelay1 = 15000;
int nDelay2 = 3000;
int nDelay3 = 10000;

void setup() {
  Serial.begin(9600);
  //perulangan untuk menentukan pin menjadi output
  for(int i = 0; i < 3; i++){
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  //perulangan untuk menghidupmatikan led
  for(int i = 0; i < 3; i++){
    switch(i){
      case 0:
      digitalWrite(ledPin[i], HIGH);
      Serial.println("LED 1 Menyala");
      delay(nDelay1);
      break;
      case 1:
      digitalWrite(ledPin[i], HIGH);
      Serial.println("LED 2 Menyala");
      delay(nDelay2);
      break;
      case 2:
      digitalWrite(ledPin[i], HIGH);
      Serial.println("LED 3 Menyala");
      delay(nDelay3);
      break;
    }
    
    for(int j = 0; j < 3; j++){
      digitalWrite(ledPin[j], LOW);
    }
  }
}
