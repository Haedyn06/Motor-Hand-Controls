#include <Arduino.h>
#include <math.h>
#include "dcMotor.h"

// Variables
#define IN1 15
#define IN2 2
#define ENA 33
#define PWM_CH   0


// Method Declarations
void motorDirection(bool forward);
void setSpeed(int speed);
bool getDirState(float x);
int xToSpeed(float x);


// Executions
void dcMotorSetup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  ledcSetup(PWM_CH, 1000, 8);
  ledcAttachPin(ENA, PWM_CH);
}


// Methods
void dcGetMsg(String msg) {
  float x = atof(msg.c_str());
  motorDirection(getDirState(x));
  setSpeed(xToSpeed(x));
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
