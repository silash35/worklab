int normalInfraValue{0};

bool detectCap() {
  bool capDetected = false;
  long int timer{0};

  while (!capDetected && timer < 180000) {
    unsigned int diff = normalInfraValue - analogRead(INFRARED_PIN);
    if (diff > 50) {
      capDetected = true;
    } else {
      capDetected = false;
    }

    delay(1);
    ++timer;
  }
  return capDetected;
}

int getSelectedButton() {
  int selectedButton{0};

  while (selectedButton == 0) {
    if (digitalRead(BUTTON_PIN_ELETRO) == HIGH) {
      selectedButton = 1;
    } else if (digitalRead(BUTTON_PIN_MEC) == HIGH) {
      selectedButton = 2;
    } else if (digitalRead(BUTTON_PIN_PGN) == HIGH) {
      selectedButton = 3;
    } else if (digitalRead(BUTTON_PIN_METAL) == HIGH) {
      selectedButton = 4;
    }
    delay(1);
  }
  return selectedButton;
}