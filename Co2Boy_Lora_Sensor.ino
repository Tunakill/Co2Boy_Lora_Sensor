/*
     ______     ___      ____
    / ____/___ |__ \    / __ )____  __  __
   / /   / __ \__/ /   / __  / __ \/ / / /
  / /___/ /_/ / __/   / /_/ / /_/ / /_/ /
  \____/\____/____/  /_____/\____/\__, /
                                 /____/
                                 
  Lora Sensor - reads CO2, humidity and temperature from a SCD30 Sensor
  By: Co2 Boy on Make@Thon
  Date: 15.11.2020
*/


/*
 * Pinout 
 * heltec WiFi LoRa 32 (V2) -> SD30 Sensor
 * GND -> GND
 * 3V3 -> VDD
 * G21 -> Rx/SDA
 * G22 -> Tx/SCL
 * 
 * heltec WiFi LoRa 32 (V2) -> NeoPixel
 * GND -> GND
 * 5V -> VDD
 * G19 -> Data
 */

 /*
  -- Additional libraries -- 
  LoRa               https://github.com/sandeepmistry/arduino-LoRa
  ArduinoJson        https://arduinojson.org/?utm_source=meta&utm_medium=library.properties
  Adafruit_NeoPixel  https://github.com/adafruit/Adafruit_NeoPixel_ZeroDMA
 */
 
#include <Wire.h>

// Json paser
#include <ArduinoJson.h>

// Lora
#include <SPI.h>
#include <LoRa.h>

#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     14   // GPIO14 -- SX127x's RESET
#define DI00    26   // GPIO26 -- SX127x's IRQ(Interrupt Request)


// Sensor
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30
SCD30 airSensor;

// Wifi - to read MacAdress
#include <WiFi.h>

// Co2 ppm thresholds
#define CO2_THRESHOLD_LOW 600
#define CO2_THRESHOLD_MEDIUM 1000
#define CO2_THRESHOLD_HIGH 1500


int device_id; // Device ID created from first 3 Bytes of the Mac Adress

// -- Arduino setup --
void setup()
{
  Serial.begin(115200);
  Serial.println("\n\nCo2 Boy");
  Wire.begin();

  if (airSensor.begin() == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1);
  }

  // Sensor settings
  airSensor.setMeasurementInterval(30); //Change number of seconds between measurements: 2 to 1800 (30 minutes)
  airSensor.setAltitudeCompensation(35); //Set altitude of Cloppenburg in m
  airSensor.setAmbientPressure(1000); //Current ambient pressure in mBar
  airSensor.setTemperatureOffset(0); //set the temperature offset to 0°C



  // Set ESP32 SPI pinout
  SPI.begin(SCK, MISO, MOSI, SS);
  // Pins onboard LoRa Module
  LoRa.setPins(SS, RST, DI00);

  // Start LoRa Module
  if (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Get Devie ID
  byte wifi_mac[6]; // MacAdress Buffer
  WiFi.macAddress(wifi_mac); // Read Mac Adress into Buffer
  device_id = ((unsigned int) wifi_mac[2] << 16) | ((unsigned int) wifi_mac[1] << 8) | (unsigned int) wifi_mac[0]; // First 3 Byte from Mac Adress - Later translatet into Hex String

  setupSmiley();


  // TODO: Share the device id via a QR Code on the display
}

void loop()
{


  // Wait for new sensor measurement
  if (airSensor.dataAvailable())
  {
    // ----
    // TODO: Ampel
    // ----

    uint16_t co2 = airSensor.getCO2();
    float temperature = airSensor.getTemperature();
    float humidity = airSensor.getHumidity();

    if (co2 < CO2_THRESHOLD_MEDIUM) {
      // Okay - Grün - Smiley
      goodsmile();
    } else {
      // Nicht Okay
      badsmile();
      Serial.println("WARNING: Co2 Konzentration ist zu hoch");
    }


    // Read sensor an serialize data with arduinojson
    // https://arduinojson.org/v6/doc/serialization/
    StaticJsonDocument<JSON_OBJECT_SIZE(4)> doc;

    doc["device_id"] = device_id;      // Device ID
    doc["co2"] = co2;                  // Co2 Value
    doc["temperature"] = temperature;  // temperature value
    doc["humidity"] = humidity;        // humidity value

    char output[128]; // Buffer for JSON
    int json_length = measureJson(doc); // Get length of serialized data
    serializeJson(doc, output); // serialize with ArduinoJson


    // Debug output Json data
    Serial.println(json_length);
    Serial.println(output);

    // --
    // Encrypt or sign the package
    // --

    // Transmit LoRa package
    LoRa.beginPacket();
    LoRa.write((uint8_t *)output, json_length);
    LoRa.endPacket();

  }

  delay(10000);
}
