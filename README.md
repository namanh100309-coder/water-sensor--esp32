# water-sensor--esp32
An automatic system for measuring the temperature and TDS in the water
## Introduction
-Project **water-sensor--esp32** is a simple system which monitors the quality of water, uses microcontroller **ESP32** to measure **Water temperature** and **Total Dissolved Solids (TDS)**.
-The system uses sensor **DS18B20** to measure temperature with high accuracy and read the TDS data by Analog input of ESP32.
-The measured specifications will be displayed diẻctly on screen **OLED SSD1306 (128x64)**, help user can easily track on-site.
-In addition, ESP32 is also connected with Wifi in order to send temperature and TDS data to ThinkSpeak platform. 
-As a result, user can remote supervise these specifications of the water through the Internet by computers or phones.
-The system is suitble to apply for models including:
+ Managing the quality of water in daily life.
+ Tracking the water in fish tanks or aquaculture ponds.
+ Practical exercises, projects on IoT, and embedded systems.
-The project is designed for learning and research, helping learners become familiar with connecting sensors,displaying data, and building a basic IoT system based on the ESP32 platform.

## Operating principle
- After powering on, the ESP32 microcontroller will start up and perform the necessary hardware initialization and connection steps:
+ First, the ESP32 initiates I2C communication to control the SSD1306 OLED display, and simultaneously initializes the DS18B20 temperature sensor via the OneWire protocol.
+ Next, the ESP32 connects to the pre-configured WiFi network.
- During operation, the system follows this cycle:
+ The ESP32 requests the DS18B20 sensor to measure the water temperature and read the temperature value in degrees Celsius.
+ The TDS value is read via the analog pin of the ESP32.
+ The temperature and TDS values ​​are then displayed on the OLED screen for direct user observation.
+ Simultaneously, the data is sent to the ThingSpeak platform via WiFi connection for storage and remote monitoring.
* The measurement, display, and data transmission cycle is repeated at a defined time interval (15 seconds), ensuring stable system operation and continuously updated data.
Overall, the series of activities can be described as flows
Temperature and TDS sensor
        ↓
      ESP32
   (data processing)
        ↓
  OLED display on-site
        ↓
   WiFi → ThingSpeak

## System Image
### The realistic image of system
The image below illustrates the hardware model of a water quality monitoring system using ESP32, including a DS18B20 temperature sensor, a TDS sensor, and an OLED display.
         
