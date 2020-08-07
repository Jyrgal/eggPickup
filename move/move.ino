//Audio sensor pins
//audio key is whichever pin you put it in, probably digital
//int audio_sensor_pin = 1;

//flag for start position
//int flag_start = 0;

//FUNCTIONS
//void move();
//void brake();

//position read from audio sensor
// int position;

//Motor Pins
int IN1 = 7;       //control pin for first motor
int IN2 = 8;       //control pin for first motor
int EN_A = 9;      //Enable pin for first motor
//int IN3 = 4;        //control pin for second motor
//int IN4 = 3;        //control pin for second motor
//int EN_B = 2;      //Enable pin for second motor

void setup ( ) {
    //Serial.begin (9600); //Starting the serial communication at 9600 baud rate

//    //Initiailising sensor pins as input
//    pinMode(audio_sensor_pin, INPUT);

    //Initializing the motor pins as output
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
//    pinMode(IN3, OUTPUT);
//    pinMode(IN4, OUTPUT);
//    pinMode(EN_B, OUTPUT);
}

void loop () {
    //position = analogRead(audio_sensor_pin);
    //Serial.println (position);

    //enable motors, give speed

//    analogWrite(EN_B, 100);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN_A, 100);
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, HIGH);

//    // when the sensor detects an audio signal
//    if (position == HIGH && flag_start == 0) {
//        move();
//        //change variable to 1 to signal the system has started
//        flag_start = 1;
//    }
//
//    //sensor detects signal below threshold value, breaks
//    else if (position == LOW && flag_start == 1){
//        move();
//    }
//
//    else if (position == HIGH && flag_start == 1){
//        brake();
//    }
}
//
//void brake() {
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN2, LOW);
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, LOW);
//
//    analogWrite(EN_A, 0);
//    analogWrite(EN_B, 0);
//}

//void move() {
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN2, HIGH);
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, HIGH);
//}
