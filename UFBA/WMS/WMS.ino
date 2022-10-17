#include "section.hpp"

#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_RED 7

Section sections[] = {Section(A1, A0)};
bool alreadyWarned = false;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  Serial.print("Testando 1 2 3\n");

  bool containerEmpty = true;
  bool containerHalf = true;
  bool containerFull = true;

  bool callTruck = true;

  for (int i = 0; i < sizeof(sections) / sizeof(sections[0]); i++) {
    int state = sections[i].getState();

    if (state == 2) {
      Serial.print("mat: Seção " + String(i) + " Cheia\n");
    }

    if (state != 0) {
      containerEmpty = false;
    }

    if (state < 2) {
      containerFull = false;
    }
  }

  if (containerEmpty || containerFull) {
    containerHalf = false;
  }

  if (containerEmpty) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

    alreadyWarned = false;
  } else if (containerHalf) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);

    alreadyWarned = false;
  } else if (containerFull) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);

    if (!alreadyWarned) {
      Serial.print("truck: Container Cheio\n");
      alreadyWarned = true;
    }
  }
}