int IN1 = 2;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int EN_A = 3;      //Enable pin for first motor
int IN3 = 5;
int IN4 = 7;
int EN_B = 6;

void setup() {
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop() {
    analogWrite(EN_A, 100);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
//    analogWrite(EN_B, 220);
//////    digitalWrite(IN3, HIGH);
//////    digitalWrite(IN4, LOW);
////    delay(2000);
////    analogWrite(EN_A, 220);
////    digitalWrite(IN1, HIGH);
////    digitalWrite(IN2, LOW);
////    delay(2000);
//    
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, HIGH);

}
