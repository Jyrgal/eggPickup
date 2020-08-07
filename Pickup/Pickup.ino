int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
float duration, cm;

int IN1 = 2;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int EN_A = 3;      //Enable pin for first motor

int pickup = 0;

#include <Servo.h>

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  if (cm > 40 && pickup == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN_A, 40);
  }
  
  else if (cm <= 40 && cm >= 20  && pickup == 0) {
    pickup = 1;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN_A, 0);
    Serial.print(cm);
    Serial.print(" cm WIND STOP");
    Serial.println();
    delay(5000);
  }

  else if (pickup == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN_A, 220);
    Serial.print(cm);
    Serial.print(" cm WIND UP");
    Serial.println();
  }
  delay(100);
}
