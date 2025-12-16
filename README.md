# Hand Gesture For Motor Controls

## About
This is a program that detects hand movements where it also detects hand gestures, this can also be connected with an ESP32 if you have it at home. How it works is that motors via ESP32 + MQTT will move depending on the position of the index finger. You can what finger to keep track on in `/pyImaging/main.py`. to test out or play around with the program, you are must have the following [requirements](#Requirements) before setting up where you can follow the [guide](#Steps) below. 

## Setting Up

### Requirements:
- Python Version = 3.12.7
- MQTT Server
- PlaformIO Extension
- ESP32
- HW-095 Driver
- 5V DC Motor
- Servo Motor
- Power Supply
- Cables

### Steps:

Before starting, you must have the MQTT server on.

#### Run Python Imaging
1. Install Python Dependencies
2. Create python venv inside `/pyImaging`
3. Inside `/pyImaging/` create a `.env` and input:
```
    MQTT_BROKER = [Your MQTT Server IP]
    MQTT_PORT = [Your PORT]
```
4. activate `/venv`
5. run by using `python /pyImaging/main.py`

#### Running ESP32 Board
1. import `/GestureMotorControl` into PIO
2. open the project
3. create a `/lib/private` folder and `/lib/private/private.h/`
4. inside `/lib/private/private.h` input:
```
    #pragma once

    #define SSID "YOUR SSID"
    #define WIFIPW "YOUR WIFI PASSWORD"
    #define SERVERIP "MQTT SERVER IP"
    #define PORT [SERVER PORT]
```
5. Follow the [schematics](#Schematics).
6. connect your esp32 board
7. upload the project into your esp32
8. run the pyImaging program


## Schematics

### Servo Motor:

##### Servo Motor Connections
- Servo(Red) ===> ESP32(VCC) 
- Servo(Black) ===> ESP32(GND) 
- Servo(Yellow) ===> ESP32(P18) 


### DC Motor:

##### DC Motor Connections
- DC(Red) ===> Driver(Out1)
- DC(Red) ===> Driver(Out2)

##### Driver Connections
- Driver(IN1) ===> ESP32(P15) 
- Driver(IN2) ===> ESP32(P2)
- Driver(12V) ===> PowerSupply(+) 
- Driver(GND) ===> PowerSupply(-) 