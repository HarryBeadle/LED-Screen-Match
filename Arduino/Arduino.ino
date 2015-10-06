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
  Serial.begin(9600);
  for (int Channel = 0; Channel < 3; Channel++) {
    pinMode(pinColor[Channel], OUTPUT);
  }
}

void loop() {
  // Get the new color from serial connection.
  for (int Channel = 0; Channel < 3; Channel++) {
    while (!Serial.available()) {continue;} // Wait for serial to be available.
    newColor[Channel] = Serial.read(); // Set the new color for the channel
  }

  // Find the diferance between the colors, and whether they're positive or negative.
  for (int Channel = 0; Channel < 3; Channel++) {
    colorDifferance[Channel] = newColor[Channel] - oldColor[Channel];
    (colorDifferance[Channel] > 0) ? colorDifferanceSign[Channel] = 1 : colorDifferanceSign[Channel] = -1;
    // Change the value of colorDifferance to always be positive for mapping.
    colorDifferance[Channel] = abs(colorDifferance[Channel])
  }

  // Begin fading the LEDs
  initalTime = millis();
  do {
    currentTime = millis() - initalTime;
    for (int Channel = 0; Channel < 3; Channel++) {
      anologWrite(pinColor[Channel], oldColor[Channel] + colorDifferanceSign[Channel] * map(currentTime, 0, 1000, 0, colorDifferance[Channel]);
    }
  } while (currentTime < 1000) // Do that until a second has passed.

  for (int Channel = 0; Channel <3; Channel++) {
    oldColor[Channel] = newColor[Channel]; // Save the current color as the old color for each channel.
  }
}
