#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "pinout.hpp"
#include "smallFunctions.hpp"
#include "EEPROMhelper.hpp"

long scoreEletro{0};
long scoreMec{0};
long scorePgn{0};
long scoreMetal{0};

int selectedButton{0};

LiquidCrystal_I2C LCDEletro(LCDPinEletro, 16, 2);
LiquidCrystal_I2C LCDMec(LCDPinMec, 16, 2);
LiquidCrystal_I2C LCDPgn(LCDPinPgn, 16, 2);
LiquidCrystal_I2C LCDMetal(LCDPinMetal, 16, 2);

void setup(){
  normalInfraValue = analogRead(infrared);

  LCDEletro.begin(16, 2);
  LCDMec.begin(16, 2);
  LCDPgn.begin(16, 2);
  LCDMetal.begin(16, 2);

  scoreEletro = EEPROMReadLong(0);
  scoreMec = EEPROMReadLong(10);
  scorePgn = EEPROMReadLong(20);
  scoreMetal = EEPROMReadLong(30);
}

void loop(){

  digitalWrite(LEDPinEletro, LOW);
  digitalWrite(LEDPinMec, LOW);
  digitalWrite(LEDPinPgn, LOW);
  digitalWrite(LEDPinMetal, LOW);

  selectedButton = getSelectedButton();
  if(selectedButton == 1){
    digitalWrite(LEDPinEletro, HIGH);
    if(detectCap()){
      ++scoreEletro;
    }
  }else if(selectedButton == 2){
    digitalWrite(LEDPinMec, HIGH);
    if(detectCap()){
      ++scoreMec;
    }
  }else if(selectedButton == 3){
    digitalWrite(LEDPinPgn, HIGH);
    if(detectCap()){
      ++scorePgn;
    }
  }else if(selectedButton == 4){
    digitalWrite(LEDPinMetal, HIGH);
    if(detectCap()){
      ++scoreMetal;
    }
  }

  eletroLCD.clear();
  mecLCD.clear();
  pgnLCD.clear();
  metalLCD.clear();

  eletroLCD.print(scoreEletro);
  mecLCD.print(scoreMec);
  pgnLCD.print(scorePgn);
  metalLCD.print(scoreMetal);

  EEPROMWriteLong(0, scoreEletro);
  EEPROMWriteLong(10, scoreMec);
  EEPROMWriteLong(20, scorePgn);
  EEPROMWriteLong(30, scoreMetal);
}