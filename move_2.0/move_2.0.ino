int motor1 = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motor1, 255);
}
