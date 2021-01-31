// You can check on your device after a successful
// connection here: https://www.shiftr.io/try.
// MQTT by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// https://platformio.org/lib/show/617/MQTT

#include <WiFi.h>
#include <MQTT.h>
#include <DHT.h>
#include <NTPClient.h>
#include <ArduinoJson.h>

#define DHTPIN 32
#define DHTTYPE DHT11

const char ssid[] = "your-ssid";
const char pass[] = "your-passwd";

WiFiClient net;
MQTTClient client;
DHT dht(DHTPIN, DHTTYPE);
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);

void connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("Connected to WiFi");
  Serial.println("Connecting to MQTT Broker");
  
  client.begin("public.cloud.shiftr.io", net);

  while (!client.connect("arduino-client", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("MQTT Broker Connected");
  randomSeed(micros());
}

void validateNtpUpdate(){
  while (!ntpClient.update()){
    yield();
    ntpClient.forceUpdate();
  }
}

void publishMessage(){
  unsigned long ts = ntpClient.getEpochTime();

  float cels = dht.readTemperature();
  yield();

  float hum = dht.readHumidity();
  yield();

  StaticJsonDocument<200> doc;
  doc["timestamp"] = ts;
  doc["temperature"] = cels;
  doc["humidity"] = hum;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish("demo/esp-topic", jsonBuffer);
  Serial.println("Published to MQTT");
}

void setup(){
  Serial.begin(115200);
  connect();
  ntpClient.begin();
  dht.begin();
}

void loop() {
  validateNtpUpdate();
  publishMessage();
  client.loop();
  delay(1000);
}
