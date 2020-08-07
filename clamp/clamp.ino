#include <Servo.h>

Servo servo1;
int angle;
int pickup_open = 0;
int pickup_close = 0;
int dropoff_open = 0;
int dropoff_close = 0;

void setup() {
}

void loop() {
  servo_open();

  servo_close();
}

void servo_open() {
  servo1.attach(A5);
  servo1.write(angle);
    //    scan from 0 to 180 degrees, close servo
  for (angle == 10; angle < 180; angle++) {
    servo1.write(angle);
    delay(10);
  }
  servo1.detach();
}

void servo_close() {
  servo1.attach(A5);
  servo1.write(angle);
  for (angle == 180; angle > 10; angle--) {
            servo1.write(angle);
            delay(10);
        }
  servo1.detach();
}
