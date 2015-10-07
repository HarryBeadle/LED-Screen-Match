# LED Screen Match

A utility that allows you to match the colour of an RGB LED setup on an Arduino with the average colour of your screen. Currently the Python program uses `screencapture` and `PIL` to find the modal color on your screen, the data is then sent via a serial connection (can be USB or Bluetooth) to the Arduino, which then softly fades between the colors.

The idea is to light your room and extend the experiance of watching Movies or TV on your Mac

Requires a Mac with `PIL` installed.

## Setup and use

Send `Arduino/Arduino.ino` to the Arduino and plug it in via a USB serial or other serial connection.  
Start `Host/Colors.py` in the Terminal, follow the instructions to select your Arduino.

