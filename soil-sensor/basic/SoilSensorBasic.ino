/**
 * Dry: 821 -> 824	
 * Wet: 490 -> 549
 * https://diyi0t.com/soil-moisture-sensor-tutorial-for-arduino-and-esp8266/
 */

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
