void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D2, HIGH);
  Serial.println("LED 1 Menyala");
  delay(1000);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  Serial.println("LED 2 Menyala");
  delay(1000);
  digitalWrite(D3, LOW);
}
