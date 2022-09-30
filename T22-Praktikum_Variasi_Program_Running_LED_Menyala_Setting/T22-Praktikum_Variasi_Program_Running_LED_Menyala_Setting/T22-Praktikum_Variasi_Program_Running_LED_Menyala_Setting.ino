//definisikan Pin yang digunakan
const int LED1 = D2;
const int LED2 = D3;
const int LED3 = D4;
const int LED4 = D5;

//buat array dari variabel Pin yang akan digunakan untuk perulangan
int ledPin[]={LED1,LED2,LED3,LED4};
int ledSetting[]={
  (1,0,1,0),
  (0,1,0,1),
  (1,1,1,1),
  (0,0,0,0)
  };
//buat variabel untuk delay
int nDelay = 1000;

void setup() {
  Serial.begin(9600);
  //perulangan untuk menentukan pin menjadi output
  for(int i = 0; i < 4; i++){
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  //perulangan untuk menghidupmatikan led
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if (ledSetting[i][j] == 0){
        Serial.println("LOW");
      } 
      else if (ledSetting[i][j] == 1){
        Serial.println("HIGH");
      }
  }
 }
}
