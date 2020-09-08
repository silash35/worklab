int normalInfraValue{0};

bool detectCap(){
  bool capDetected = false;
  long int timer{0};

  while(!capDetected && timer < 180000){
    unsigned int diff = normalInfraValue - analogRead(infraredPin);
    if(diff > 50){
      capDetected = true;
    }else {
      capDetected = false;
    }

    delay(1);
    ++timer;
  }
  return capDetected;
}

int getSelectedButton(){
  int selectedButton{0};

  while (selectedButton == 0){
    if(digitalRead(buttonPinEletro) == HIGH){
      selectedButton = 1;
    }else if(digitalRead(buttonPinMec) == HIGH){
      selectedButton = 2;
    }else if(digitalRead(buttonPinPgn) == HIGH){
      selectedButton = 3;
    }else if(digitalRead(buttonPinMetal) == HIGH){
      selectedButton = 4;
    }
    delay(1);
  }
  return selectedButton;
}