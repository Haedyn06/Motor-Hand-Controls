#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

//WIFI
const char* user = "Haykaykriz";   
const char* pw = "3MgaAnakKo.";    
const char* serverIP = "192.168.1.89";  
const int servPort = 1883;       

WiFiClient espClient;
PubSubClient client(espClient);

Servo servo;
const int SERVO_PIN = 18;

void callback(char* topic, byte* payload, unsigned int length);
void moveServo(float handPos);

void setup() {
  Serial.begin(115200);
  delay(1000);


  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);


  WiFi.begin(user, pw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  client.setServer(serverIP, servPort);
  client.setCallback(callback);

  if (client.connect("ESP32Client")) client.subscribe("esp32/pc");
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Client")) delay(500);
    client.subscribe("esp32/pc");
  }
  client.loop();
}




void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on ");
  Serial.print(topic);
  Serial.print(": ");
  
  String message = "";
  for (int i = 0; i < length; i++) message += (char)payload[i];

  Serial.println(message);

  if (String(topic) == "esp32/pc") {
    float handPos = atof(message.c_str());
    moveServo(handPos);
  }
}

void moveServo(float handPos) {
  handPos = max(0.0f, min(1.0f, handPos));
  float angle = handPos * 180.0f;
  servo.write((int)angle);
}

