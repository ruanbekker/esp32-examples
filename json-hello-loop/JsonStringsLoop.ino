// examples: https://arduinojson.org/v6/example/

#include <ArduinoJson.h>

void jsonString(){
  StaticJsonDocument<200> doc;
  doc["uptime"] = millis();

  serializeJson(doc, Serial);
  Serial.println();
  serializeJsonPretty(doc, Serial);
}

void setup(){
  Serial.begin(115200);
}

void loop() {
  jsonString();
  delay(1000);
}
