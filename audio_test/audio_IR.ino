int soundSensor = 8;
int IR = 7;
boolean IRStatus = false;
boolean motorStatus = false;
int IN1 = 2;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int EN_A = 3;      //Enable pin for first motor

void setup() {
 pinMode(soundSensor,INPUT);
 pinMode(IR,OUTPUT);
 pinMode(EN_A, OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);

}

void loop() {

  int SensorData = digitalRead(soundSensor); 
  if(SensorData == 1){
    if( motorStatus == false){
        motorStatus = true;
        IRStatus = true;
        digitalWrite(IR, HIGH);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN_A, 200);
    }
    else{
        motorStatus = false;
        IRStatus = false;
        digitalWrite(IR, LOW);
        analogWrite(EN_A,0);
    }
  }
 }  
