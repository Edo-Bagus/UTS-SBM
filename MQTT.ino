#include <WiFi.h>  
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
StaticJsonDocument<200> doc;

const int DHT_PIN = 5;  
const char* ssid = "iPhone"; ///  wifi ssid 
const char* password = "12345678";
const char* mqtt_server = "172.20.10.4";// server broker

DHT sensor_dht(DHT_PIN,DHT22);
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
float temp = 0;
float hum = 0;

void setup_wifi() { 
  delay(10);
  Serial.println();
  Serial.print("Wifi terkoneksi ke : ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi berhasil terkoneksi");
  Serial.print("Alamat IP : ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { 
    Serial.print((char)payload[i]);
  }}
  
void reconnect() { 
  while (!client.connected()) {
    Serial.print("Baru melakukan koneksi MQTT ...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }}
}
void setup() {   
  Serial.begin(115200);
  sensor_dht.begin();
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 2000) { //perintah publish data
    lastMsg = now;
    float temp = sensor_dht.readTemperature();
    float hum = sensor_dht.readHumidity();

    doc["Temperature"] = temp;
    doc["Humidity"] = hum;
    String jsonString;
    serializeJson(doc, jsonString);
    char charArray[jsonString.length() + 1]; // Add one for null terminator
    jsonString.toCharArray(charArray, jsonString.length() + 1);
    client.publish("/data", charArray);   // publish to topic /data

    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.println();
  }
}