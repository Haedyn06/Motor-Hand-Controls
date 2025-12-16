import cv2, os
import mediapipe as mp
import paho.mqtt.client as mqtt
from utils.Finger import Finger
from utils.Gestures import handGesture
from dotenv import load_dotenv

load_dotenv()

MQTT_BROKER = os.getenv("MQTT_BROKER")
MQTT_PORT = int(os.getenv("MQTT_PORT", "1883"))

mp_hands = mp.solutions.hands
mp_draw  = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0) #Web Cam


client = mqtt.Client()
client.connect(MQTT_BROKER, MQTT_PORT, 60)


#Initiate Fingers
thumb = Finger("thumb", [1, 2, 3, 4])
index = Finger("index", [5, 6, 7, 8])
middle = Finger("middle", [9, 10, 11, 12])
ring = Finger("ring", [13, 14, 15, 16])
pinky = Finger("pinky", [17, 18, 19, 20])


def msgRec(client, userdata, msg):
    print(f"MQTT <- {msg.topic}: {msg.payload.decode()}")


def displayText(fr, txt, pos):
    cv2.putText(fr, str(txt), pos, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

client.on_message = msgRec
client.subscribe("pc/sendDC")
client.subscribe("pc/sendServo")
client.loop_start()

# Process Hands
with mp_hands.Hands(max_num_hands=1, min_detection_confidence=0.6, min_tracking_confidence=0.6) as hands:
    while True:
        ok, frame = cap.read()
        if not ok:
            break
        
        # Invert + Colors
        frame = cv2.flip(frame, 1)
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        res = hands.process(rgb)

        # Identify Finger Pos
        if res.multi_hand_landmarks:
            hand = res.multi_hand_landmarks[0]
            mp_draw.draw_landmarks(frame, hand, mp_hands.HAND_CONNECTIONS)

            finga = hand.landmark
            thumb.setFingerPos(finga, "tip")
            index.setFingerPos(finga, "tip")
            middle.setFingerPos(finga, "tip")
            ring.setFingerPos(finga, "tip")
            pinky.setFingerPos(finga, "tip")


        #Label
        displayText(frame, index, (350, 20))
        displayText(frame, handGesture(thumb, index, middle, ring, pinky), (20, 80))
        client.publish("esp32/sendDC", index.x) # For DC
        client.publish("esp32/sendServo", index.y) # For Servo
        
        frame = cv2.resize(frame, (960, 720))

        cv2.imshow("Hands", frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break


cap.release()
cv2.destroyAllWindows()