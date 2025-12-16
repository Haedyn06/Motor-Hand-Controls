def handGesture(thumb, index, middle, ring, pinky):
    fingers = [thumb, index, middle, ring, pinky]
    midFing = False
    thumbUp = False
    peaceFing = False
    okayFing = False



    for i in fingers:
        if (i.finger != "middle" and i.finger != "thumb"):
            if ((i.y-middle.y) > 0.15):
                midFing = True
            else:
                midFing = False
        
        if (i.finger != "thumb"):
            if ((i.y-thumb.y) > 0.15):
                thumbUp = True
            else:
                thumbUp = False    

        if (i.finger != "index" and i.finger != "middle"):
            if (((i.y-middle.y) > 0.15) and ((i.y-index.y) > 0.15)):
                peaceFing = True
                midFing = False
            else:
                peaceFing = False

        if (i.finger != "index" and i.finger != "thumb"):
            if (((thumb.y-i.y) > 0.15) and ((index.y-i.y) > 0.15)):
                okayFing =True
            else:
                okayFing = False


    if (midFing):
        return "middlefinga"
    elif (thumbUp):
        return "thumbup"
    elif (peaceFing):
        return "peace"
    elif (okayFing):
        return "okayish"
    
    return "None"