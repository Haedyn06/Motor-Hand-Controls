#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* user = "Haykaykriz";   
const char* pw = "3MgaAnakKo.";    
const char* serverIP = "192.168.1.89";  
const int servPort = 1883;       

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);

  WiFi.begin(user, pw);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  client.setServer(serverIP, 1883);
  client.setCallback(callback);
  client.connect("ESP32Client");
  client.subscribe("esp32/sendDC");
  client.subscribe("esp32/sendServo");
}


void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Client")) delay(200);
    client.subscribe("esp32/sendDC");
    client.subscribe("esp32/sendServo");
  }
  client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) message += (char)payload[i];

  if (strcmp(topic, "esp32/pc") == 0) dcMotorOnMsg(msg);
  else if (strcmp(topic, "esp32/sendServo") == 0) servoMotorOnMsg(msg);
}
