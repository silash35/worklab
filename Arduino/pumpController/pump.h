#include <EEPROM.h>
#include <RTClib.h>

#define INFINITO UINT32_MAX

RTC_DS1307 RTC;

class Schedule {
public:
  uint8_t onHour = 0;
  uint8_t onMinute = 0;

  uint8_t offHour = 0;
  uint8_t offMinute = 0;

  Schedule(int onH = 24, int onM = 60, int offH = 24, int offM = 60) {
    onHour = onH;
    onMinute = onM;

    offHour = offH;
    offMinute = offM;
  }
};

class Pump {
private:
  int pin = 0;
  int eepromAddress = 0;
  String name = "";

  bool isOn = false;
  bool isLocked = false;

  Schedule schedule;

  uint32_t onTimer = INFINITO;
  uint32_t offTimer = INFINITO;

public:
  Pump(String name, int pin, int eepromAddress, Schedule schedule) {
    this->name = name;
    this->pin = pin;
    this->eepromAddress = eepromAddress;
    this->schedule = schedule;

    byte value = EEPROM.read(eepromAddress);
    isLocked = bitRead(value, 0);
    turnOff();
  }

  void turnOn() {
    if (!isLocked) {
      digitalWrite(pin, LOW);
      isOn = true;
    }
  }
  void turnOff() {
    digitalWrite(pin, HIGH);
    isOn = false;
  }

  void lock() {
    if (!isLocked) {
      isLocked = false;
      turnOff();

      int val = 0;
      EEPROM.update(eepromAddress, val);
    }
  }

  void unlock() {
    if (isLocked) {
      isLocked = false;

      int val = 0;
      val = bitSet(val, 0);
      EEPROM.update(eepromAddress, val);
    }
  }

  void setOnTimer(int min) { onTimer = RTC.now().unixtime() + min * 60; }
  void setOffTimer(int min) { offTimer = RTC.now().unixtime() + min * 60; }

  void checkSchedule() {
    DateTime now = RTC.now();

    // Verificar Timers
    if (now.unixtime() > onTimer) {
      turnOn();
      onTimer = INFINITO;
    }
    if (now.unixtime() > offTimer) {
      turnOff();
      offTimer = INFINITO;
    }

    // Verificar Horarios
    if (now.hour() == schedule.onHour && now.minute() == schedule.onMinute) {
      turnOn();
    }

    if (now.hour() == schedule.offHour && now.minute() == schedule.offMinute) {
      turnOff();
    }
  }

  String getMessage() {
    String message = "A bomba '" + name + "' está ";
    message = message + (isOn ? "Funcionando" : "Desligada");
    message = message + "\n";

    return message;
  }
};

void checkPumps(Pump pumps[]) {
  for (int i = 0; i < sizeof(pumps) / sizeof(pumps[0]); i++) {
    pumps[i].turnOff();
  }
  for (int i = 0; i < sizeof(pumps) / sizeof(pumps[0]); i++) {
    pumps[i].turnOn();
    delay(2000);

    if (analogRead(A0) > 3) {
      pumps[i].lock();
    }
    pumps[i].turnOff();
  }
}