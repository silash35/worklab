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

// Class to control a section of a container
class Section {
private:
  int pinTrigger = 0;
  int pinEcho = 0;

  bool alreadyWarned = false;

public:
  Section(int pt, int pe) {
    pinMode(pt, OUTPUT);
    pinMode(pe, INPUT);

    pinTrigger = pt;
    pinEcho = pe;
  }

  int getState() {
    /*
      0: Empty
      1: Half
      2: Full (And needs to notify the mat operator)
      3: Full (And the mat operator was already notified)
    */

    int distance = readUltrasonicDistance(pinTrigger, pinEcho);
    int percentage = map(distance, EMPTY_BOX_VALUE, FULL_BOX_VALUE, 0, 100);

    if (percentage >= MAX_BOX_PERCENTAGE) {
      if (alreadyWarned) {
        return 3;
      }
      alreadyWarned = true;
      return 2;
    } else if (percentage >= 50) {
      alreadyWarned = false;
      return 1;
    } else {
      alreadyWarned = false;
      return 0;
    }
  }
};