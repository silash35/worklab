#define MAX 900

String getSerialResponse(String emptySerialString) {
  String serialResponse = emptySerialString;
  while (serialResponse == emptySerialString) {
    serialResponse = Serial.readString();
  }
  return serialResponse;
}

int stringToInt(String str) {
  for (int i = 0; i < str.length(); i++) {
    if (!isDigit(str[i])) {
      return 0;
    }
  }
  return str.toInt();
}

char intToLetter(int i) {
  char letter = 'a';

  if (i == 0) {
    letter = 'a';
  } else if (i == 1) {
    letter = 'b';
  } else if (i == 2) {
    letter = 'c';
  } else if (i == 3) {
    letter = 'd';
  } else if (i == 4) {
    letter = 'e';
  } else if (i == 5) {
    letter = 'g';
  } //...

  return letter;
}

void askMultiply(int x, int y) {
  Serial.print("Quanto é ");
  Serial.print(x);
  Serial.print(" X ");
  Serial.print(y);
  Serial.println(" ?");
}

int getButtonsResponse() {

  char userAnswer = '0';
  while (userAnswer == '0') {
    if (analogRead(A0) < MAX) {
      userAnswer = 'a';
    }

    if (analogRead(A1) < MAX) {
      userAnswer = 'b';
    }

    if (analogRead(A2) < MAX) {
      userAnswer = 'c';
    }

    if (analogRead(A3) < MAX) {
      userAnswer = 'd';
    }

    if (analogRead(A4) < MAX) {
      userAnswer = 'e';
    }

    if (analogRead(A5) < MAX) {
      userAnswer = 'q';
    }
  }
  return userAnswer;
}

int getRandomNumber(int min, int max) {
  delay(45);
  randomSeed(millis());
  return random(min, max + 1);
}