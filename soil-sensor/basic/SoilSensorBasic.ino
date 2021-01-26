#define SensorPin 4

void setup() {
  //start serial line for debugging
  Serial.begin(115200);
}

void loop(){
  float sensorValue = analogRead(SensorPin);
  // print sensor value
  Serial.println(sensorValue);
  // sleep for 5 seconds
  delay(5000);
}
