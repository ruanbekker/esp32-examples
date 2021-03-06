/**
 * SoilSensor
 * https://diyi0t.com/soil-moisture-sensor-tutorial-for-arduino-and-esp8266/
 * https://gist.github.com/igrr/7f7e7973366fc01d6393
 * https://www.youtube.com/watch?v=pFQaFnqpOtQ&t=303s
 * https://wiki.dfrobot.com/Moisture_Sensor__SKU_SEN0114_
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "PubSubClient.h"

#define USE_SERIAL Serial
#define SensorPin 4

char* topic = "arduino";
char* server = "x.x.x.x";
char* wifi_ssid = "xx";
char* wifi_passwd = "xx";

WiFiMulti wifiMulti;
WiFiClient wifiClient;

void callback(char* topic, byte* payload, unsigned int length) {
}

PubSubClient client(host, 1883, callback, wifiClient);
void setup() {

  //start serial line for debugging
  Serial.begin(115200);
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  wifiMulti.addAP(wifi_ssid, wifi_passwd);
}

void loop(){

  if((wifiMulti.run() == WL_CONNECTED)) {
    float sensorValue = analogRead(SensorPin);

    // payload
    String payload = "{\"moisture_level\":" + String(sensorValue) + "}";

    // publish to mqtt broker
    Serial.println("publishing to mqtt broker");
    
    // once connected, auth, then publish
    if (client.connect("arduinoClient", "mqtt", "mqtt")) {
      client.publish(topic, (char*) payload.c_str());
    }
    
    // sleep for 5 seconds
    delay(5000);
  }
}
