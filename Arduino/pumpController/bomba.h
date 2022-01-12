#include <RTClib.h>

#define INFINITO UINT32_MAX

RTC_DS1307 RTC;

class Schedule {
public:
  int onHour;
  int onMinute;

  int offHour;
  int offMinute;

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
    pinMode(pb, OUTPUT);
    pinSensor = ps;

    this->schedule = schedule;
  }

  void ligarBomba() {
    digitalWrite(pinBomba, HIGH);
    bombIsOn = true;
  }
  void desligarBomba() {
    digitalWrite(pinBomba, LOW);
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
    message = message + bombIsOn ? "Funcionando" : "Desligada";
    message = message + "\n";
    message = message + "E seu sensor está detectando o seguinte valor" + getSensor();

    return message;
  }
};
