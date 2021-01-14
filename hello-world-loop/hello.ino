// https://arduinogetstarted.com/tutorials/arduino-hello-world
// https://arduinogetstarted.com/reference/arduino-loop

void setup(){
  Serial.begin(115200);
  Serial.println("Booted");
}

void loop(){
  Serial.println("This is a loop");
  delay(1000);
}
