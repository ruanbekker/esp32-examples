# Setup NodeMCU ESP32

### Install 

This is based for Windows, for Mac I had some issues, which can be resolved with [this](https://github.com/espressif/arduino-esp32/issues/4408) and install pyserial.

Install Arduino:
- https://www.arduino.cc/en/software

Download the drivers:
- https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

Create a directory:

```
C:\Users\Ruan\Documents\Arduino\hardware\espressif\esp32
```

Move the contents from https://github.com/espressif/arduino-esp32 to the folder created.

Run the `tools\get.exe` program

Open Arduino

Select File  -> Preferences -> Additional Boards URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` , then Tools -> Boards Manager -> Search ESP32 -> Install Ref: (https://www.youtube.com/watch?v=xPlN_Tk3VLQ)

Select Tools -> Boards -> ESP32 -> ESP32 Dev Module
       Tools -> Upload Speed -> 115200
       Tools -> Ports -> COM3

In the code section write:

```
#define led 2

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

```

Compile and upload with Ctrl + U, now the led should blink.

If you are outputting to console and want to view the console logs, Tools -> Serial Monitor. Make sure to set the baud rate the same as your upload speed

### Resources:
- https://www.youtube.com/watch?v=5IuZ-E8Tmhg
- https://www.youtube.com/watch?v=xPlN_Tk3VLQ (WiFi Setup)
- https://www.youtube.com/watch?v=5X06sF91ixE (ESP32 Projects for Beginners)
- https://www.youtube.com/watch?v=--Fj8QDlGuQ (More Examples)
- https://www.arduino.cc/en/software
- https://github.com/espressif/arduino-esp32
- https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
- https://www.youtube.com/watch?v=mJcxnaR08Dg
