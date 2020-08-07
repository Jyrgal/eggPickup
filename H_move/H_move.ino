int soundSensor = A0;
//int LED = 4;
//boolean LEDStatus = false;
//boolean motorStatus = false;
//int IN1 = 2;       //control pin for first motor
//int IN2 = 4;       //control pin for first motor
//int EN_A = 3;      //Enable pin for first motor

void setup() {
    Serial.begin(9600);
//  pinMode(LED,OUTPUT);
//    pinMode(EN_A, OUTPUT);
//    pinMode(IN1, OUTPUT);
//    pinMode(IN2, OUTPUT);

}

void loop() {

  int SensorData = digitalRead(soundSensor); 
  Serial.println(SensorData);          // debug value
  
//  if(SensorData == 1){
//    if(motorStatus == false){
//        motorStatus=true;
//        digitalWrite(IN1, HIGH);
//        digitalWrite(IN2, LOW);
//        analogWrite(EN_A,200);
//    }
//    else{
//        motorStatus = false;
//        analogWrite(EN_A,0);
//    }
//  }

}  
