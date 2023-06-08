#################################################################################
##Code to comunicate with the haptic device of the TFM of Mónica Ocaña Bastante##
## Pattern permitted: up, down, right, left, rotateR, rotateL                  ##
## Use free to comunicate with the device                                      ##
##You must install PyBluez o pybluez2                                          ##
#################################################################################


import bluetooth

host = "30:C6:F7:18:92:92"
 
#establish connection       
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)     
sock.connect((host, 1))


def vibrate(patternId,duration):
    message = 0
    patternID = patternID.lower()
    
    
    #codify pattern
    if(patternId == "up"):
        message = 1
    elif(patternId == "down"):
        message = 2
    elif(patternId == "right"):
        message = 3
    elif(patternId == "left"):
        message = 4
    elif(patternId == "rotater"):#rotate to the right
        message = 5
    elif(patternId == "rotatel"):#rotate to the left
        message = 6
    else:
        message = 0
    
    
    
    #only if pattern is valid
    if(message> 0):
        
        #codify duration
        if(duration <= 175):
            message  += 10
        elif(duration <= 275):
            message  += 20
        elif(duration <= 375):
            message  += 30
        elif(duration <= 475):
            message  += 40
        elif(duration <= 575):
            message  += 50
        elif(duration <= 675):
            message  += 60
        elif(duration <= 775):
            message  += 70
        elif(duration <= 875):
            message  += 80
        else:
            message  += 90
     
        #send the message 
        sock.send(str(message))