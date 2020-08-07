#include <Servo.h>
Servo servo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pickup_open_servo = 0;
int pickup_close_servo = 0;
int initial_distance = 0;
int picked_up = 0;

int dropoff = 1;
int servo_dropoff = 0;
int complete = 0;
int dropoff_start = 0;

int trigPin = 11 ;    // Trigger
int echoPin = 12;    // Echo
float duration, cm;

//Pulley motor
int IN1 = 5;       //control pin for first motor
int IN2 = 7;       //control pin for first motor
int EN_A = 6;      //Enable pin for first motor

//Vertical motor
int IN3 = 2;
int IN4 = 4;
int EN_B = 3;

int warning = 13;

void setup() {
  Serial.begin (9600);
  servo1.attach(A5);  // attaches the servo on pin 9 to the servo object
  pinMode (warning, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //audioVal_total = 0.0;
  //audioSense();
  if (picked_up == 0) {
    digitalWrite(warning, HIGH);
    delay(500);
    digitalWrite(warning, LOW);
    pickup_function();
  }

  else {
    digitalWrite(warning, HIGH);
    delay(500);
    digitalWrite(warning, LOW);
    dropoff_function();
  }
}

void dropoff_function() {
  ultrasonic_sense();
  //servo1.write(0);

  if (dropoff_start == 0) {
    initial_distance = cm;
    Serial.println(initial_distance);
    dropoff_start = 1;
  }
  
  if (servo_dropoff == 1 && cm >= initial_distance) {
    wind_stop();
    complete = 1;
  }
  
  if (dropoff == 1 && complete == 0) {
    if (cm > 12 && servo_dropoff == 0) {
      wind_down();
    }
  
    else if (cm <= 12 && servo_dropoff == 0) {
      wind_stop();
      delay(2000);
      servo1.write(0);
      
      servo_dropoff = 1;
    }
  
    else if (complete == 0) {
      wind_up();
      servo1.detach();
    }
  }
}

void pickup_function() {
  ultrasonic_sense();
  
  if (pickup_close_servo == 1 && cm >= initial_distance) {
    Serial.println("initiate movement");
    wind_stop();
    picked_up = 1;
  }

  //opening servo at top
  if (pickup_open_servo == 0) {
    servo1.write(0);
    initial_distance = cm;
    pickup_open_servo = 1;
    Serial.println();
    Serial.println(" INTIAL DISTANCE:");
    Serial.println(initial_distance);
  }
  
  if (picked_up == 0) {
    if (cm > 12 && pickup_close_servo == 0) {
      wind_down();
    }
  
    else if (cm <= 12 && pickup_close_servo == 0) {
      wind_stop();
      delay(2000);
      for (int angle = 0; angle < 130; angle++) {
        servo1.write(angle);
        delay(10);
      }
      pickup_close_servo = 1;
    }
  
    else if (picked_up == 0) {
      wind_up();
      //servo1.detach();
    }
  }
}

void ultrasonic_sense(){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehando
  //to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  //pinMode(echoPin, INPUT)
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.println(" cm");

  delay(250);
}


void wind_down() {
  Serial.println(initial_distance);
  Serial.print("wind down");
  analogWrite(EN_B, 50);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void wind_stop() {
  Serial.println(initial_distance);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, 0);
  Serial.print(cm);
  Serial.println(" cm");
  Serial.println("WIND STOP");
}

void wind_up() {
  Serial.println(initial_distance);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN_B, 150);
  Serial.print("WIND UP");
  Serial.println();
}
