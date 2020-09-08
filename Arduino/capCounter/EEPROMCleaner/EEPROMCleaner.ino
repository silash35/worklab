#include <EEPROM.h>

void setup(){
  for (int nL = 0; nL < 1000; nL++) {
    EEPROM.write(nL, 0);
  }
}

void loop(){
}
