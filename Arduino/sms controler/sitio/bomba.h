#include <RTClib.h>

#define INFINITO UINT32_MAX

RTC_DS1307 RTC;

class Bomba {
private:
  int pinBomba = 0;
  int pinSensor = 0;
  String nome = "";

  bool bombIsOn = false;

  uint32_t horarioParaDesligar = INFINITO;
  uint32_t horarioParaLigar = INFINITO;

public:
  Bomba(String n, int pb, int ps) {
    nome = n;

    pinBomba = pb;
    pinMode(pb, OUTPUT);
    pinSensor = ps;

    Serial.print("Achou o RTC:");
    Serial.println(RTC.begin());
  }

  void ligarBomba() {
    digitalWrite(pinBomba, HIGH);
    bombIsOn = true;
  }
  void desligarBomba() {
    digitalWrite(pinBomba, LOW);
    bombIsOn = false;
  }

  void agendarLigamento(int min) { horarioParaLigar = RTC.now().unixtime() + min * 60; }
  void agendarDesligamento(int min) { horarioParaDesligar = RTC.now().unixtime() + min * 60; }

  int getSensor() { return analogRead(pinSensor); }

  void verificarAgendamentos() {
    uint32_t now = RTC.now().unixtime();

    if (now > horarioParaLigar) {
      ligarBomba();
      horarioParaLigar = INFINITO;
    }
    if (now > horarioParaDesligar) {
      desligarBomba();
      horarioParaDesligar = INFINITO;
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
