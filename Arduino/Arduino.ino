// Harry Beadle
// LED Color Match

// Original 19/09/15
// Last Updated 06/10/15

// Initalise the arrays, incuding the pin numbers.
// You should make these any PWM enabled pins on
// your brand of Arduino. This is set up for an
// Arduino mini.

int pinColor[3] = {6, 9, 5}; // {R, G, B}
int oldColor[3] = {0, 0, 0}; 
int newColor[3] = {0, 0, 0};
int colorDifferance[3];
int colorDifferanceSign[3];
int currentTime;
int initalTime;

void setup() {
  // Start the serial connection with the host
  Serial.begin(9600);
  // Setup the pinout
  for (int Channel = 0; Channel < 3; Channel++) {
    pinMode(pinColor[Channel], OUTPUT);
  }
  // Set the output to full red, then wait for first set of data
  // before continuing.
  digitalWrite(pinColor[0], 1);
  for (int Channel = 0; Channel < 3; Channel++) {
    while (!Serial.available()) {continue;}
    newColor[Channel] = Serial.read();
  }
  digitalWrite(pinColor[0], 0);
}

void loop() {
  // Begin fading the LEDs
  initalTime = millis();
  currentTime = millis() = initalTime;
  while (currentTime < 1000) {
    currentTime = millis() - initalTime;
    for (int Channel = 0; Channel < 3; Channel++) {
      analogWrite(pinColor[Channel], oldColor[Channel] + colorDifferanceSign[Channel] * map(currentTime, 0, 1000, 0, colorDifferance[Channel]));
    }
  }

  for (int Channel = 0; Channel <3; Channel++) {
    oldColor[Channel] = newColor[Channel]; // Save the current color as the old color for each channel.
  }

  // Get the new color from serial connection.
  for (int Channel = 0; Channel < 3; Channel++) {
    while (!Serial.available()) {continue;} // Wait for serial to be available.
    newColor[Channel] = Serial.read(); // Set the new color for the channel
    // Calculate the color diferance while waiting for next serial input
    colorDifferance[Channel] = newColor[Channel] - oldColor[Channel];
    (colorDifferance[Channel] > 0) ? colorDifferanceSign[Channel] = 1 : colorDifferanceSign[Channel] = -1;
    // Change the value of colorDifferance to always be positive for mapping.
    colorDifferance[Channel] = abs(colorDifferance[Channel]);
  }
}
