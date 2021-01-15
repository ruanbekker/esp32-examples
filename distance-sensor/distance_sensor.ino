#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <HCSR04.h> //ultrasonic distance sensor
#include "config.h"

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);
UltraSonicDistanceSensor distanceSensor(ULTRASONIC_PIN_TRIG, ULTRASONIC_PIN_ECHO);

void setupWiFi(){
  Serial.print("Connecting to '");
  Serial.print(WIFI_SSID);
  Serial.print("' ...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  randomSeed(micros());
}

void submitToStdout(unsigned long ts, long distance, int project_id, int project_version){
  String logJson = String("{\"timestamp\"") + ": " + ts + ", " + String("\"project_id\"") + ": " + project_id + ", " + String("\"project_version\"") + ": " + project_version + ", " + String("\"distance\"") + ": " + distance + String("}");
  Serial.println(logJson);
}

void setup(){
  Serial.begin(115200);
  setupWiFi();
  ntpClient.begin();
  String prj_name = "Distance sensor \n";
  Serial.print("Booting project: " + String(prj_name));
}

void loop(){
  if (WiFi.status() != WL_CONNECTED){
    WiFi.disconnect();
    yield();
    setupWiFi();
  }

  while (!ntpClient.update()){
    yield();
    ntpClient.forceUpdate();
  }

  unsigned long ts = ntpClient.getEpochTime();
  double distance = distanceSensor.measureDistanceCm();
  int project_id = PROJECT_ID;
  int project_version = VERSION;

  if (isnan(distance)){
    Serial.println(F("Failed to read from sensor!"));
    return;
  }

  yield();
  submitToStdout(ts, distance, project_id, project_version);

  delay(INTERVAL * 1000);
}
