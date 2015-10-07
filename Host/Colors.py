#! /usr/env/python

# Harry Beadle
# RGB LED Screen Matching

from os import system
from time import time
from sys import argv, platform
from glob import glob

from PIL import Image
import serial

# Debugging Mode
DEBUG = True

# Welcome
print """
LED Screen Match
by Harry Beadle
"""

# Setup Serial
print "Please wait while we setup the Serial connection."
print "If prompted with any dialogs during this period please close them, unless they are for your Arduino."

# Setup the serial with selection of port from user
if platform.startswith('darwin'):
    ports = glob('/dev/tty.*')
    working_ports = []
    for port in ports:
        try:
            test_serial = serial.Serial(port)
            test_serial.close()
            working_ports.append(port)
        except (OSError, serial.SerialException):
            pass
    print "Found {} serial ports.\n".format(len(working_ports))
    print "Please select your Arduino from the list below:\nIf you are unsure of the port, check the bottom of the Arduino IDE."
    for i in range(len(working_ports)):
        print "Port", i + 1, working_ports[i]
    serial_port = working_ports[
        input("Type a port number between 1 and {}: ".format(len(working_ports))) - 1]
else:
    raise EnviromentError('Unsuported platform: {}'.format(platform.system()))
ser = serial.Serial(serial_port, 9600)
print "\nEverything was successful, you should now see your LED lit up.\nPress and hold ctrl+c to quit."

# Begin Program
while True:
    # Get the time at the start of the operation
    t1 = time()

    # Capture and open a screenshot
    system("screencapture -Cmxr screencapture.png")
    image = Image.open("screencapture.png")

    # Get every 100th pixel in a list
    w, h = image.size
    pixels = image.getcolors(w * h)[0::100]

    # Initalise the color value
    color = pixels[0]

    # Find the colour that occours the most in our sample
    for count, colour in pixels:
        if count > color[0]:
            color = (count, colour)

    # Remove count and alpha data
    color = color[1][0:3]

    # Wait until a second has passed
    while (time() - t1) < 1:
        pass

    # Send the data to the Arduino]
    if DEBUG: print (str(time()) + ":"),
    for channel in range(3):
        print str(color[channel]) + ", ",
        ser.write(chr(color[channel]))
    print ""