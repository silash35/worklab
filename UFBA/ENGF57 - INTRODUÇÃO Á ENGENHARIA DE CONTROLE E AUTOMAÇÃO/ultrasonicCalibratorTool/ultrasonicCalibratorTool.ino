// Ultrasonic Calibrator Tool
#define PIN_TRIGGER A0
#define PIN_ECHO A1

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return 0.01723 * pulseIn(echoPin, HIGH);
}

void setup() {
  // Iniciar porta serial
  Serial.begin(115200);

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  int distance = readUltrasonicDistance(PIN_TRIGGER, PIN_ECHO);

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm\n");

  delay(1000);
}