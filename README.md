# ESP32 DHT22 MQTT Sensor

This Arduino sketch enables an ESP32 microcontroller board to connect a DHT22 temperature and humidity sensor and publish the data to an MQTT broker over a WiFi connection.

## Hardware Requirements
- ESP32 microcontroller board
- DHT22 temperature and humidity sensor
- Stable power supply for the ESP32 board

## Software Requirements
- Arduino IDE (or any compatible IDE)
- Libraries:
  - WiFi.h
  - PubSubClient.h
  - DHT.h
  - ArduinoJson.h

## Installation
1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries...**
3. Search for each of the required libraries mentioned above.
4. Click on the library name and then click the "Install" button.

## Wiring Instructions
- Connect the signal pin of the DHT22 sensor to pin 5 (DHT_PIN) on the ESP32 board.
- Connect the VCC pin of the DHT22 sensor to a 3.3V pin on the ESP32 board.
- Connect the GND pin of the DHT22 sensor to a GND pin on the ESP32 board.

## Configuration
- Modify the `ssid` and `password` variables in the code to match your WiFi network credentials.
- Set the `mqtt_server` variable to the IP address of your MQTT broker.

## Running the Code
1. Connect your ESP32 board to your computer via USB.
2. Open the Arduino IDE and load the provided sketch.
3. Verify that the correct board and port are selected in the Arduino IDE.
4. Click the "Upload" button to upload the sketch to the ESP32 board.
5. Open the serial monitor to view the output and ensure that the ESP32 successfully connects to the WiFi network and MQTT broker.

## Expected Behavior
- The ESP32 will connect to the specified WiFi network.
- It will then attempt to connect to the MQTT broker.
- Once connected, it will read temperature and humidity data from the DHT22 sensor at regular intervals.
- The data will be formatted into a JSON object and published to the MQTT broker under the topic `/data`.

## Troubleshooting
- If you encounter any issues, ensure that your hardware is wired correctly and that you have installed all the required libraries.
- Check the serial monitor for any error messages or debugging information.
- Verify that your MQTT broker is running and accessible from the ESP32's network.
