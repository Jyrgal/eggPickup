//FUNCTIONS
void move();
void brake();
float pickup_distance();

//clipping indicator variables
boolean clipping = 0;

//data storage variables
byte newData = 0;
byte prevData = 0;

//freq variables
unsigned int timer = 0;//counts period of wave
unsigned int period;
int frequency = 0;

//Motor Pins
int EN_A = 11;      //Enable pin for first motor
int IN1 = 9;       //control pin for first motor
int IN2 = 8;       //control pin for first motor
int IN3 = 7;        //control pin for second motor
int IN4 = 6;        //control pin for second motor
int EN_B = 10;      //Enable pin for second motor

//Initializing variables to store data
int motor_speed;
int motor_speed1;

//flag to see whether the motor has picked up
int flag_start = 0;

//values needed for ultrasonic sensor
int trigPin = 1;    // Trigger
int echoPin = 2;    // Echo
float duration, cm;

void setup(){

    Serial.begin(9600);

    //Initializing the motor pins as output
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(EN_B, OUTPUT);

    //Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // pinMode(13,OUTPUT);//led indicator pin

    cli();//diable interrupts

    //set up continuous sampling of analog pin 0

    //clear ADCSRA and ADCSRB registers
    ADCSRA = 0;
    ADCSRB = 0;

    ADMUX |= (1 << REFS0); //set reference voltage
    ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only

    ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
    ADCSRA |= (1 << ADATE); //enabble auto trigger
    ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
    ADCSRA |= (1 << ADEN); //enable ADC
    ADCSRA |= (1 << ADSC); //start ADC measurements

    sei();//enable interrupts
}

ISR(ADC_vect) {//when new ADC value ready

    prevData = newData;//store previous value
    newData = ADCH;//get value from A0
    if (prevData < 127 && newData >=127){//if increasing and crossing midpoint
      period = timer;//get period
      timer = 0;//reset timer
    }


    if (newData == 0 || newData == 1023){//if clipping
      PORTB |= B00100000;//set pin 13 high- turn on clipping indicator led
      clipping = 1;//currently clipping
    }

    timer++;//increment timer at rate of 38.5kHz
}

void loop(){
    if (clipping) {//if currently clipping
      PORTB &= B11011111;//turn off clippng indicator led
      clipping = 0;
    }

    frequency = 38462/period;//timer rate/period
    //print results
    //Serial.print(frequency);
    //Serial.println(" hz");
    int frequency_counter = 0;

    //testing if audio signal has been received
    if (frequency != 0) {
        frequency_counter = 1;
    }

    //enable motors, give speed
    analogWrite(EN_A, 100);
    analogWrite(EN_B, 100);

    //before body has reached pickup
    if (flag_start == 0 && frequency_counter == 0) {
        move();
    }

    //reached pickup zone
    else if (flag_start == 0 && frequency_counter == 1) {
        brake();

        //has reached starting point
        flag_start = 1;

        //calculate distance to the egg
        int distance = pickup_distance();

        //insert motor code to pickup
    }

    //has alreayd rached starting point, but no audio meaning its travelling between starting point & end
    else if (flag_start == 1 && frequency_counter == 0) {
        move();
    }

    //read starting point, and reached 2nd control module
    else if (flag_start == 1 && frequency_counter == 1) {
        brake();

        //calculate distance to the egg
        int distance = pickup_distance();

        //insert motor code to pickup

    }

  //delay(100);
}

void brake() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    analogWrite(EN_A, 0);
    analogWrite(EN_B, 0);
}

void move() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

float pickup_distance () {
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

    return cm;
}
