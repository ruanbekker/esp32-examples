// You can check on your device after a successful
// connection here: https://www.shiftr.io/try.
// MQTT by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// https://platformio.org/lib/show/617/MQTT

#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "your-ssid";
const char pass[] = "your-passwd";

WiFiClient net;
MQTTClient client;

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("Connected to WiFi");
  randomSeed(micros());
}

void connectToMQTT(){
  Serial.println("Connecting to MQTT Broker");
  client.begin("public.cloud.shiftr.io", net);

  while (!client.connect("arduino-client", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("MQTT Broker Connected");
}

void publishMessage(){
  client.publish("demo/esp-topic", "hello, world");
  Serial.println("Published to MQTT");
}

void setup(){
  Serial.begin(115200);
  connectToWiFi();
  connectToMQTT();
}

void loop() {
  publishMessage();
  client.loop();
  delay(1000);
}
