int redPin = 6;
int greenPin = 9;
int bluePin = 5;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  while (!Serial.available()) {}
  analogWrite(redPin, int(Serial.read()));
  while (!Serial.available()) {}
  analogWrite(greenPin, int(Serial.read()));
  while (!Serial.available()) {}
  analogWrite(bluePin, int(Serial.read()));
}
