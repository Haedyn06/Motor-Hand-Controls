#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <math.h>



//WIFI
const char* user = "Haykaykriz";   
const char* pw = "3MgaAnakKo.";    
const char* serverIP = "192.168.1.89";  
const int servPort = 1883;       

WiFiClient espClient;
PubSubClient client(espClient);

#define IN1 15
#define IN2 2
#define ENA 33

#define PWM_CH   0

int Speedmotor = 0;

void callback(char* topic, byte* payload, unsigned int length);
void motorDirection(bool forward);
void setSpeed(int speed);
bool getDirState(float x);
int xToSpeed(float x);

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  ledcSetup(PWM_CH, 1000, 8);
  ledcAttachPin(ENA, PWM_CH);

  WiFi.begin(user, pw);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  client.setServer(serverIP, servPort);
  client.setCallback(callback);

  if (client.connect("ESP32Client")) client.subscribe("esp32/pc");
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Client")) delay(200);
    client.subscribe("esp32/pc");
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) message += (char)payload[i];

  if (String(topic) == "esp32/pc") {
    float x = atof(message.c_str());
    motorDirection(getDirState(x));
    setSpeed(xToSpeed(x));
  }
}


void motorDirection(bool forward) {
  digitalWrite(IN1, forward ? HIGH : LOW);
  digitalWrite(IN2, forward ? LOW  : HIGH);
}

void setSpeed(int speed) {
  speed = constrain(speed, 0, 255);
  ledcWrite(PWM_CH, speed);
}

int xToSpeed(float x) {
  x = constrain(x, 0.0f, 1.0f);
  return (int)(((fabs(x - 0.5f)) / 0.5f) * 255.0f);
}

bool getDirState(float x) { return x >= 0.5f; }
