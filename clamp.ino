#include <Servo.h>

Servo servo;
int angle;

void setup() {
    //connecting servo to 8
    servo.attach(8);
    servo.write(angle);
}

void loop() {
    // scan from 0 to 180 degrees, close servo
    for (angle = 10; angle < 180; angle++) {
        servo.write(angle);
        delay(15);
    }
    // now scan back from 180 to 0 degrees, open servo
    for (angle = 180; angle > 10; angle--) {
        servo.write(angle);
        delay(15);
    }
}
