//definisikan Pin yang digunakan
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int LED4 = D5;

//buat array dari variabel Pin yang akan digunakan untuk perulangan
int ledPin[]={LED1,LED2,LED3,LED4};
//buat variabel untuk delay
int nDelay = 200;

void setup() {
  Serial.begin(9600);
  //perulangan untuk menentukan pin menjadi output
  for(int i = 0; i < 4; i++){
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  //buat variabel untuk pengacakan
  int acak = random(4);
  //perulangan untuk menghidupmatikan led
  Serial.print("Lampu Menyala: ");
  Serial.println(acak);
  digitalWrite(ledPin[acak], HIGH);
  delay(nDelay);
  digitalWrite(ledPin[acak], LOW);
}
