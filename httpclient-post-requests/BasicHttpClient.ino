/**
 * HTTP Client the makes POST Requests
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

void setup() {

    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("YOUR_SSID", "YOUR_PASSWD");
}

void loop() {

    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // payload
        String logJson = String("{\"message\": \"hello, world\"}");
        //Serial.println(logJson);

        // Submit POST Request to Flask Endpoint
        http.begin("http://192.168.0.10:5000/post"); 
        http.addHeader("Content-Type", "application/json");

        USE_SERIAL.print("Making a HTTP POST Request\n");
        int httpCode = http.POST(logJson);

        if(httpCode > 0) {

            USE_SERIAL.printf("POST Request Succeeded code: %d\n", httpCode);
            Serial.println();

            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                //USE_SERIAL.println(payload);
                USE_SERIAL.printf("Response: %s\n", payload.c_str());
            }
        } else {
            USE_SERIAL.printf("POST Request failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
