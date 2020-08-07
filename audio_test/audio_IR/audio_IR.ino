int soundSensor = 10;

int audioIn = A1;
float audioVal = 0;
float audioVal_total = 0;
int delta_t = 1;
int t = 100;
int count = t / delta_t;


void setup() {
  Serial.begin (9600);
  pinMode(soundSensor,INPUT);

}

void loop() {
  //Initialising values for audio sensor
  audioVal_total = 0.0;
  audioSense();
}  

void audioSense() {

  //loop for rms
  for (int i = 0; i < count; i++) {
    audioVal_total += delta_t * (analogRead(audioIn))^2;
    delay(delta_t);
  }

  audioVal = sqrt(audioVal_total / t);
  Serial.println(audioVal);

  //loop for audio sensor
  int SensorData = digitalRead(soundSensor); 
  Serial.println(SensorData);

  //measuring for pickup 2 eggs
  //pickup low frequency
  if(audioVal < 18 && SensorData == 1 && pickup_low == 0 && pickup_high == 0){
    pickup_low = 1;
    Serial.println("low");
    initial_distance = cm;
  }

  //pickup high frequency
  else if (audioVal > 18 && SensorData == 1 && pickup_low == 0 && pickup_high == 0) {
    pickup_high = 1;
    Serial.println("high");
    initial_distance = cm;
  }

  //dropoff all frequencies
  else if (SensorData == 1 && picked_up == 1) {
    dropoff_flag = 1;
    Serial.println("dropoff");
    initial_distance = cm;
  }
  
}
