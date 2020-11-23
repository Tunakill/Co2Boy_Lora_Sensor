# Co2 Boy

![Logo](image.png)

Lora Co2 Sensor based on Heltec WiFi LoRa 32 (V2) Bord and an SD30 Co2 Sensor.

This design was part of the [Make@thon](http://opto-cubes.de/?p=100) competition.

The Co2 Boy can be placed in multiple classrooms to alert if ventilation is required.

The measured data will be transmitted over Lora to a gateway which will transmit the data to a evaluation server.

## Setup

This project use the Heltec Lora 32 board with the Arduino IDE.

Follow this [heltec setup guide](https://heltec-automation-docs.readthedocs.io/en/latest/esp32+arduino/quick_start.html) to add the board  to your IDE.

Following library's are used:

- `Heltec ESP32` [HelTecAutomation/Heltec_ESP32](https://github.com/HelTecAutomation/Heltec_ESP32)

- `LoRa` [sandeepmistry/arduino-LoRa](https://github.com/sandeepmistry/arduino-LoRa) - *Manual installation*

- `SparkFun_SCD30_Arduino_Library` [sparkfun/SparkFun_SCD30_Arduino_Library](https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library)

- `ArduinoJson`  [ArduinoJson](https://arduinojson.org/?utm_source=meta&utm_medium=library.properties)

- `Adafruit_NeoPixel` [adafruit/Adafruit_NeoPixel_ZeroDMA)](https://github.com/adafruit/Adafruit_NeoPixel_ZeroDMA)

## Improvements

Duo to the time limits we were not able to implement all of the planed features.

At this point there is no measure to prevent spoofing. This can be prevented by adding cryptographic algorithms to encrypt or sign the payload. The public key could be used for the device ID instead of the mac address.

Currently the only method to get the device ID is by receiving the packets. The device ID can be shared by showing the ID as a QR code on the OLED display.
