// https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
// The code generates a pseudo-random number and sends the generated number to the serial port.
long randNumber;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  randNumber = random(300);
  Serial.println(randNumber);
  delay(50);
}
