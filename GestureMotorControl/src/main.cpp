#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "servoMotor.h"
#include "dcMotor.h"
#include "private.h"  

//Variables
WiFiClient espClient;
PubSubClient client(espClient);

enum MotorMode { DC, SERVO, BOTH };
const MotorMode motorMode = DC;

// Method Declaration
void callback(char* topic, byte* payload, unsigned int length);
void receiveTopics();

// Executions
void setup() {
  Serial.begin(115200);

  if (motorMode == DC) dcMotorSetup();
  else if (motorMode == SERVO) servoMotorSetup();
  else {
    dcMotorSetup();
    servoMotorSetup();
  }

  WiFi.begin(SSID, WIFIPW);
  while (WiFi.status() != WL_CONNECTED) delay(200);
  client.setServer(SERVERIP, PORT);

  client.setCallback(callback);
  client.connect("ESP32Client");
  receiveTopics();
  
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Client")) delay(200);
    receiveTopics();
  }
  client.loop();
}


// Methods
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  if (strcmp(topic, "esp32/sendDC") == 0) dcGetMsg(msg);
  else if (strcmp(topic, "esp32/sendServo") == 0) servoGetMsg(msg);
}

void receiveTopics() {
  if (motorMode == DC) client.subscribe("esp32/sendDC");
  else if (motorMode == SERVO) client.subscribe("esp32/sendServo");
  else {
    client.subscribe("esp32/sendDC");
    client.subscribe("esp32/sendServo");
  }
}