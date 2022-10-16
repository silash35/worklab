#include "robot.hpp"
#include "utils.hpp"

#define BUTTON_PIN 2
int selectedMode{0};

void setup() {
  Serial.begin(9600);
  robot.begin();
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {

  int aux{0};

  if (selectedMode == 0) { // selection mode
    robot.stopAll();
    selectedMode = getselectedMode(BUTTON_PIN);

    Serial.print("Mode:");
    Serial.print(selectedMode);
    Serial.print("\n");
  }

  while (selectedMode == 1) { // sumo
    // This version of the code is limited by the small number of ultrasonic sensors.
    // The correct thing is to have 4 sensors, one on each side. And not just 1 in the front.
    int aux{0};
    if (digitalRead(RIGHT_INFRARED_PIN) == LOW) {
      robot.goBack();
      delay(1000);
      robot.turnRight();
      delay(1000);
    }
    if (digitalRead(LEFT_INFRARED_PIN) == LOW) {
      robot.goBack();
      delay(1000);
      robot.turnLeft();
      delay(1000);
    }
    robot.goForward(100, 100);
    if (readUltrasonicDistance(ULTRASONIC_PIN_TRIGGER, ULTRASONIC_PIN_ECHO) < 19000) {
      robot.goForward();
    }
    delay(10);
  }

  while (selectedMode == 2) { // line follower

    if (digitalRead(RIGHT_INFRARED_PIN) == HIGH && digitalRead(LEFT_INFRARED_PIN) == LOW) {
      robot.turnLeft();
    } else if (digitalRead(RIGHT_INFRARED_PIN) == LOW && digitalRead(LEFT_INFRARED_PIN) == HIGH) {
      robot.turnRight();
    } else {
      robot.goForward(50, 50);
    }
    delay(10);
  }

  while (selectedMode == 3) { // autonomous
    int frontDistance = readUltrasonicDistance(ULTRASONIC_PIN_TRIGGER, ULTRASONIC_PIN_ECHO);

    robot.ultraServo.write(180);
    delay(1000);
    int leftDistance = readUltrasonicDistance(ULTRASONIC_PIN_TRIGGER, ULTRASONIC_PIN_ECHO);

    robot.ultraServo.write(0);
    delay(1000);
    int rightDistance = readUltrasonicDistance(ULTRASONIC_PIN_TRIGGER, ULTRASONIC_PIN_ECHO);

    robot.ultraServo.write(90);
    delay(1000);

    if (frontDistance > leftDistance && frontDistance > rightDistance) {
      robot.goForward();
      while (readUltrasonicDistance(ULTRASONIC_PIN_TRIGGER, ULTRASONIC_PIN_ECHO) > 100) {
        delay(10);
      }
    }
    if (rightDistance > frontDistance && rightDistance > leftDistance) {
      robot.turnRight();
    }
    if (leftDistance > frontDistance && leftDistance > rightDistance) {
      robot.turnLeft();
    }
    delay(1000);
  }

  while (selectedMode == 4) { // remote Control
    char bluetoothValue = bluetooth.read();
    if (bluetoothValue == 'F') {
      robot.goForward();
    } else if (bluetoothValue == 'B') {
      robot.goBack();
    } else if (bluetoothValue == 'R') {
      robot.turnRight();
    } else if (bluetoothValue == 'L') {
      robot.turnLeft();
    } else if (bluetoothValue == 'S') {
      robot.brake();
    } else {
      robot.stopAll();
    }
  }

  selectedMode = 0;
}
