int audioIn = A1;
float audioVal = 0;
float audioVal_total = 0;

int delta_t = 1;
int t = 100;
int count = t / delta_t;

int soundSensor = 10;

void setup() {
  Serial.begin (9600);
  pinMode(soundSensor,INPUT);
}

void loop() {
  audioSense();


} 

void audioSense() {
    audioVal_total = 0.0;

  for (int i = 0; i < count; i++) {
    audioVal_total += delta_t * (analogRead(audioIn))^2;
    delay(delta_t);
  }

  audioVal = sqrt(audioVal_total / t);
  Serial.println(audioVal);

  int SensorData = digitalRead(soundSensor); 
  Serial.println(SensorData);

  if (SensorData == 1) {
    //Serial.println("sound");
  }

  if(audioVal < 18 && SensorData == 1){
    Serial.println("LOW");
  }

  else if (audioVal > 18 && SensorData == 1) {
    Serial.println("HIGH");
  }
}
