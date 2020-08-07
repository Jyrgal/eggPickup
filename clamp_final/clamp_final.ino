#include <Servo.h>

Servo servo1;
int angle;
int pickup = 0;
int dropoff = 0;
int IN1 = 2;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int EN_A = 3;      //Enable pin for first motor
int IN3 = 5;
int IN4 = 7;
int EN_B = 6;
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
int LED = 13;
float duration, cm;

void setup() {
    Serial.begin (9600);
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    //Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    pinMode(LED,OUTPUT);
}

void loop() {
    digitalWrite(LED, HIGH);
    analogWrite(EN_A, 100);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN_B, 100);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(1000);
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(1000);

    digitalWrite(LED, LOW);
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
    //pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

    Serial.print(cm);
    Serial.print(" cm");
    Serial.println();
    
    servo1.attach(A0);
    servo1.write(angle);
//    scan from 0 to 180 degrees, close servo
    if (pickup == 0) {
        for (angle == 10; angle < 180; angle++) {
            servo1.write(angle);
            delay(10);
        }
        pickup = 1;
    }

    delay (1000);
    if (dropoff == 0) {
        // now scan back from 180 to 0 degrees, open servo
        for (angle == 180; angle > 10; angle--) {
            servo1.write(angle);
            delay(10);
        }
        dropoff = 1;
    }

    servo1.detach();
}
