class Finger:    
    def __init__(self, fingerType, jointNum):
        self.x = 0
        self.y = 0
        self.z = 0

        self.finger = fingerType

        self.joints = {
            "mcp": jointNum[0], "pip": jointNum[1],
            "dip": jointNum[2], "tip": jointNum[3],
        }


    def setFingerPos(self, calc, joint):
        self.x = calc[self.joints[joint]].x
        self.y = calc[self.joints[joint]].y
        self.z = calc[self.joints[joint]].z


    def getFinger(self):
        return self.finger
    
    def getJoints(self):
        return self.joints
    
    def __str__(self):
        return f"{self.finger} = [X:{self.x:.2f}, Y:{self.y:.2f}, Z:{self.z:.2f}]"
    
