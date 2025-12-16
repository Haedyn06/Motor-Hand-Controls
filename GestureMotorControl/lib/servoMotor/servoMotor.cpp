#include <Arduino.h>
#include <ESP32Servo.h>
#include "servoMotor.h"

//Variables
Servo servo;
const int SERVO_PIN = 18;


// Method Declarations
void moveServo(float handPos);


// Executions
void servoMotorSetup() {
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);
}


// Methods
void servoGetMsg(String msg) {
  float handPos = atof(msg.c_str());
  moveServo(handPos);
}

void moveServo(float handPos) {
  handPos = max(0.0f, min(1.0f, handPos));
  float angle = handPos * 180.0f;
  servo.write((int)angle);
}

