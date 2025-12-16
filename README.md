# Hand Gesture For Motor Controls

## /pyImaging

### Requirements:
- Python 3.12.7

### Run:
`(venv) python pyImaging/main.py`

## /GestureMotorControl

### Requirements:
- ESP32
- HW-095 Driver
- 5V DC Motor
- Servo Motor
- Power Supply
- Cables

### Servo Motor Schematics:

##### Servo Motor Connections
- Servo(Red) ===> ESP32(VCC) 
- Servo(Black) ===> ESP32(GND) 
- Servo(Yellow) ===> ESP32(P18) 


### DC Motor Schematics:

##### DC Motor Connections
- DC(Red) ===> Driver(Out1)
- DC(Red) ===> Driver(Out2)

##### Driver Connections
- Driver(IN1) ===> ESP32(P15) 
- Driver(IN2) ===> ESP32(P2)
- Driver(12V) ===> PowerSupply(+) 
- Driver(GND) ===> PowerSupply(-) 