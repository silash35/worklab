#include <RTClib.h>

#define INFINITO UINT32_MAX

RTC_DS1307 RTC;

struct Time {
  int hour;
  int minutes;
};

class Bomba {
private:
  int pinBomba = 0;
  int pinSensor = 0;
  String nome = "";

  bool bombIsOn = false;

  Time horarioParaLigar = {.hour = 0, .minutes = 0};
  Time horarioParaDesligar = {.hour = 0, .minutes = 0};

  uint32_t timerParaLigar = INFINITO;
  uint32_t timerParaDesligar = INFINITO;

public:
  Bomba(String n, int pb, int ps, Time hpl, Time hpd) {
    nome = n;

    pinBomba = pb;
    pinMode(pb, OUTPUT);
    pinSensor = ps;

    horarioParaLigar = hpl;
    horarioParaDesligar = hpd;

    RTC.begin();
  }

  void ligarBomba() {
    digitalWrite(pinBomba, HIGH);
    bombIsOn = true;
  }
  void desligarBomba() {
    digitalWrite(pinBomba, LOW);
    bombIsOn = false;
  }

  void agendarLigamento(int min) { timerParaLigar = RTC.now().unixtime() + min * 60; }
  void agendarDesligamento(int min) { timerParaDesligar = RTC.now().unixtime() + min * 60; }

  int getSensor() { return analogRead(pinSensor); }

  void verificarAgendamentos() {
    DateTime now = RTC.now();

    // Verificar Timers
    if (now.unixtime() > timerParaLigar) {
      ligarBomba();
      timerParaLigar = INFINITO;
    }
    if (now.unixtime() > timerParaDesligar) {
      desligarBomba();
      timerParaDesligar = INFINITO;
    }

    // Verificar Horarios
    if (now.hour() == horarioParaLigar.hour && now.minute() == horarioParaLigar.minutes) {
      ligarBomba();
    }

    if (now.hour() == horarioParaDesligar.hour && now.minute() == horarioParaDesligar.minutes) {
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
