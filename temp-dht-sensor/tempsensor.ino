#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <DHT.h>
#include "config.h"

//NTP Client
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);

//DHT Sensor
DHT dht(DHTPIN, DHTTYPE);

void setupWiFi(){
    Serial.print("Connecting to WiFi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected");
    Serial.println("IP Address:");
    Serial.println(WiFi.localIP());
    randomSeed(micros());
}

void setup(){
    // Start the serial output at 115,200 baud
    Serial.begin(115200);
    setupWiFi();
    ntpClient.begin();
    dht.begin();
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

    float hum = dht.readHumidity();
    yield();

    float cels = dht.readTemperature();
    yield();

    if (isnan(hum) || isnan(cels)){
        Serial.println(F("Failed to read from DHT Sensor"));
        return;
    }

    float hic = dht.computeHeatIndex(cels, hum, false);
    yield();

    Serial.printf("Temperature: %f\n", cels);
    Serial.printf("Humidity: %f\n", hum);

    delay(60 * 1000);
}
