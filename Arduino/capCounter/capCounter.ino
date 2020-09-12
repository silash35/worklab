#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "pinout.hpp"
#include "utils.hpp"
#include "EEPROMhelper.hpp"

long scoreEletro{0};
long scoreMec{0};
long scorePgn{0};
long scoreMetal{0};

int selectedButton{0};

LiquidCrystal_I2C LCDEletro(LCD_PIN_ELETRO, 16, 2);
LiquidCrystal_I2C LCDMec(LCD_PIN_MEC, 16, 2);
LiquidCrystal_I2C LCDPgn(LCD_PIN_PGN, 16, 2);
LiquidCrystal_I2C LCDMetal(LCD_PIN_METAL, 16, 2);

void setup(){
  normalInfraValue = analogRead(INFRARED_PIN);

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

  digitalWrite(LED_PIN_ELETRO, LOW);
  digitalWrite(LED_PIN_MEC, LOW);
  digitalWrite(LED_PIN_PGN, LOW);
  digitalWrite(LED_PIN_METAL, LOW);

  selectedButton = getSelectedButton();
  if(selectedButton == 1){
    digitalWrite(LED_PIN_ELETRO, HIGH);
    if(detectCap()){
      ++scoreEletro;
    }
  }else if(selectedButton == 2){
    digitalWrite(LED_PIN_MEC, HIGH);
    if(detectCap()){
      ++scoreMec;
    }
  }else if(selectedButton == 3){
    digitalWrite(LED_PIN_PGN, HIGH);
    if(detectCap()){
      ++scorePgn;
    }
  }else if(selectedButton == 4){
    digitalWrite(LED_PIN_METAL, HIGH);
    if(detectCap()){
      ++scoreMetal;
    }
  }

  LCDEletro.clear();
  LCDMec.clear();
  LCDPgn.clear();
  LCDMetal.clear();

  LCDEletro.print(scoreEletro);
  LCDMec.print(scoreMec);
  LCDPgn.print(scorePgn);
  LCDMetal.print(scoreMetal);

  EEPROMWriteLong(0, scoreEletro);
  EEPROMWriteLong(10, scoreMec);
  EEPROMWriteLong(20, scorePgn);
  EEPROMWriteLong(30, scoreMetal);
}