#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_RED 7

#define PIN_TRIG A1
#define PIN_ECHO A0

#define PIN_PIEZO 9

#define EMPTY_BOX_VALUE 335
#define FULL_BOX_VALUE 4
#define MAX_BOX_PERCENTAGE 90

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
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  Serial.begin(9600);
}

void loop() {
  int distance = readUltrasonicDistance(PIN_TRIG, PIN_ECHO);
  int porcentage = map(distance, EMPTY_BOX_VALUE, FULL_BOX_VALUE, 0, 100);

  if (porcentage >= MAX_BOX_PERCENTAGE) {
    tone(PIN_PIEZO, porcentage * porcentage);

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  } else if (porcentage >= 50) {
    noTone(PIN_PIEZO);

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    noTone(PIN_PIEZO);

    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }

  Serial.println(porcentage);
}