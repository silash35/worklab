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
  int pinPump = 0;
  int pinSensor = 0;
  int eepromAddress = 0;
  String nome = "";

  bool bombIsOn = false;
  bool isLocked = false;

  Schedule schedule;

  uint32_t onTimer = INFINITO;
  uint32_t offTimer = INFINITO;

public:
  Pump(String n, int pb, int ps, int eepromAddress, Schedule schedule) {
    nome = n;
    pinPump = pb;
    pinSensor = ps;

    this->eepromAddress = eepromAddress;
    byte value = EEPROM.read(eepromAddress);
    isLocked = bitRead(value, 0);

    pinMode(pb, OUTPUT);
    turnOff();
    this->schedule = schedule;
  }

  void turnOn() {
    if (!isLocked) {
      digitalWrite(pinPump, LOW);
      bombIsOn = true;
    }
  }
  void turnOff() {
    digitalWrite(pinPump, HIGH);
    bombIsOn = false;
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

  int getSensor() { return analogRead(pinSensor); }

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
    String message = "A bomba '" + nome + "' está ";
    message = message + (bombIsOn ? "Funcionando" : "Desligada");
    message = message + "\n";
    message = message + "E seu sensor está detectando o seguinte valor " + getSensor();

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