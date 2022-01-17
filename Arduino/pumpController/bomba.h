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

class Bomba {
private:
  int pinBomba = 0;
  int pinSensor = 0;
  String nome = "";

  bool bombIsOn = false;

  Schedule schedule;

  uint32_t onTimer = INFINITO;
  uint32_t offTimer = INFINITO;

public:
  Bomba(String n, int pb, int ps, Schedule schedule) {
    nome = n;
    pinBomba = pb;
    pinSensor = ps;

    pinMode(pb, OUTPUT);
    desligarBomba();
    this->schedule = schedule;
  }

  void ligarBomba() {
    digitalWrite(pinBomba, LOW);
    bombIsOn = true;
  }
  void desligarBomba() {
    digitalWrite(pinBomba, HIGH);
    bombIsOn = false;
  }

  void setOnTimer(int min) { onTimer = RTC.now().unixtime() + min * 60; }
  void setOffTimer(int min) { offTimer = RTC.now().unixtime() + min * 60; }

  int getSensor() { return analogRead(pinSensor); }

  void verificarAgendamentos() {
    DateTime now = RTC.now();

    // Verificar Timers
    if (now.unixtime() > onTimer) {
      ligarBomba();
      onTimer = INFINITO;
    }
    if (now.unixtime() > offTimer) {
      desligarBomba();
      offTimer = INFINITO;
    }

    // Verificar Horarios
    if (now.hour() == schedule.onHour && now.minute() == schedule.onMinute) {
      ligarBomba();
    }

    if (now.hour() == schedule.offHour && now.minute() == schedule.offMinute) {
      desligarBomba();
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
