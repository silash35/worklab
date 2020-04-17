#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>

#define infrared 3

long eletro{0};
long mec{0};
long pgn{0};
long metal{0};

#define eletroLCDPin 0x46
#define mecLCDPin 0x45
#define pgnLCDPin 0x44
#define metalLCDPin 0x43

#define eletroLED 13
#define mecLED 12
#define pgnLED 11
#define metalLED 10

#define eletroButton 7
#define mecButton 6
#define pgnButton 5
#define metalButton 4

int selected{0};
int normalInfraValue{0};
long int time{0};

LiquidCrystal_I2C eletroLCD(eletroLCDPin, 16, 2);
LiquidCrystal_I2C mecLCD(mecLCDPin, 16, 2);
LiquidCrystal_I2C pgnLCD(pgnLCDPin, 16, 2);
LiquidCrystal_I2C metalLCD(metalLCDPin, 16, 2);

bool detect();
void EEPROMWriteLong(int address, long value);
long EEPROMReadLong(int address);

void setup(){

  normalInfraValue = analogRead(infrared);
  eletroLCD.begin(16, 2);
  mecLCD.begin(16, 2);
  pgnLCD.begin(16, 2);
  metalLCD.begin(16, 2);

  eletro = EEPROMReadLong(0);
  mec = EEPROMReadLong(10);
  pgn = EEPROMReadLong(20);
  metal = EEPROMReadLong(30);

}

void loop(){

  if(selected != 0){

    switch(selected){
      case 1:
        digitalWrite(eletroLED, HIGH);
        digitalWrite(mecLED, LOW);
        digitalWrite(pgnLED, LOW);
        digitalWrite(metalLED, LOW);
      break;
      case 2:
        digitalWrite(eletroLED, LOW);
        digitalWrite(mecLED, HIGH);
        digitalWrite(pgnLED, LOW);
        digitalWrite(metalLED, LOW);
      break;
      case 3:
        digitalWrite(eletroLED, LOW);
        digitalWrite(mecLED, LOW);
        digitalWrite(pgnLED, HIGH);
        digitalWrite(metalLED, LOW);
      break;
      case 4:
        digitalWrite(eletroLED, LOW);
        digitalWrite(mecLED, LOW);
        digitalWrite(pgnLED, LOW);
        digitalWrite(metalLED, HIGH);
      break;
      default:
        digitalWrite(eletroLED, LOW);
        digitalWrite(mecLED, LOW);
        digitalWrite(pgnLED, LOW);
        digitalWrite(metalLED, LOW);
      break;
    }

    if(!detect()){
      delay(1);
      time++;
      if(time > 20000){
        selected = 0;
        time = 0;
      }
    }else{
      switch(selected){
        case 1:
          eletro++;
          delay(1000);
        break;
        case 2:
          mec++;
          delay(1000);
        break;
        case 3:
          pgn++;
          delay(1000);
        break;
        case 4:
          metal++;
          delay(1000);
        break;
      }
    }

  }

  if(digitalRead(eletroButton) == HIGH){
    selected = 1;
    time = 0;
  }else if(digitalRead(mecButton) == HIGH){
    selected = 2;
    time = 0;
  }else if(digitalRead(pgnButton) == HIGH){
    selected = 3;
    time = 0;
  }else if(digitalRead(metalButton) == HIGH){
    selected = 4;
    time = 0;
  }

  eletroLCD.clear();
  mecLCD.clear();
  pgnLCD.clear();
  metalLCD.clear();

  eletroLCD.print(eletro);
  mecLCD.print(mec);
  pgnLCD.print(pgn);
  metalLCD.print(metal);

  EEPROMWriteLong(0, eletro);
  EEPROMWriteLong(10, mec);
  EEPROMWriteLong(20, pgn);
  EEPROMWriteLong(30, metal);

}

bool detect(){

  unsigned int diff = normalInfraValue - analogRead(infrared);

  if(diff > 50){
    return true;
  }else {
    return false;
  }
}

void EEPROMWriteLong(int address, long value) {
   byte four = (value & 0xFF);
   byte three = ((value >> 8) & 0xFF);
   byte two = ((value >> 16) & 0xFF);
   byte one = ((value >> 24) & 0xFF);

   EEPROM.write(address, four);
   EEPROM.write(address + 1, three);
   EEPROM.write(address + 2, two);
   EEPROM.write(address + 3, one);
}

long EEPROMReadLong(int address) {
   long four = EEPROM.read(address);
   long three = EEPROM.read(address + 1);
   long two = EEPROM.read(address + 2);
   long one = EEPROM.read(address + 3);

   return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

