#include "bibliotecas/Sim800l.h"
#include "bomba.h"
#include "codes.h"
#include <SoftwareSerial.h>

#define TELEFONE_MESTRE "99999999999"

Sim800l sim800l;
int commandIndex = 0;
int selectedBomb = 0;
String textSms = "";
String numberSms = "";

Bomba bombas[] = {Bomba("Bomba 0", 0, A0, (12, 0, 13, 0)), Bomba("Bomba 1", 1, A1, (12, 0, 13, 0)),
                  Bomba("Bomba 2", 2, A2, (12, 0, 13, 0)), Bomba("Bomba 3", 3, A3, (12, 0, 13, 0)),
                  Bomba("Bomba 4", 4, A4, (12, 0, 13, 0))};

void setup() {
  Serial.begin(9600);

  sim800l.begin();
  sim800l.delAllSms(); // Apaga SMS antigos
}

void loop() {

  // Verficar Agendamentos
  for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
    bombas[i].verificarAgendamentos();
  }

  // Ler SMS e executar comandos
  textSms = sim800l.readSms(1);

  // Realizar Verificações antes de prosseguir
  if (textSms.indexOf("OK") == -1) {
    return; // Sair do código caso não tenha recebido mensagens validas
  }
  if (sim800l.getNumberSms(1) != TELEFONE_MESTRE) {
    return; // Sair do código caso o SMS não venha de um numero conhecido
  }

  // Converter o texto para maiúsculas
  textSms.toUpperCase();

  // Caso receba LBX, Ligar a bomba X
  commandIndex = textSms.indexOf(LB);
  if (commandIndex != -1) {
    if (isDigit(textSms[commandIndex + 2])) {
      selectedBomb = textSms.substring(commandIndex + 2, 1).toInt();

      if (textSms[commandIndex + 3] != '-') {
        bombas[selectedBomb].ligarBomba();
      } else {
        int time = textSms.substring(commandIndex + 4, 4).toInt();
        bombas[selectedBomb].setOnTimer(time);
      }
    } else {
      for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
        bombas[i].ligarBomba();
      }
    }
  }

  // Caso receba DBX, Desligar a bomba X
  commandIndex = textSms.indexOf(DB);
  if (commandIndex != -1) {
    if (isDigit(textSms[commandIndex + 2])) {
      selectedBomb = textSms.substring(commandIndex + 2, 1).toInt();

      if (textSms[commandIndex + 3] != '-') {
        bombas[selectedBomb].desligarBomba();
      } else {
        int time = textSms.substring(commandIndex + 4, 4).toInt();
        bombas[selectedBomb].setOffTimer(time);
      }
    } else {
      for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
        bombas[i].desligarBomba();
      }
    }
  }

  // Caso receba RSX, Ler os dados da bomba X
  commandIndex = textSms.indexOf(RS);
  if (commandIndex != -1) {
    if (isDigit(textSms[commandIndex + 2])) {
      selectedBomb = textSms.substring(commandIndex + 2, 1).toInt();
      sim800l.sendSms(TELEFONE_MESTRE, bombas[selectedBomb].getMessage());
    } else {
      String message = "";
      for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
        message = message + "\n \n" + bombas[i].getMessage();
      }
      sim800l.sendSms(TELEFONE_MESTRE, message);
    }
  }

  // Apagar todas as mensagens da memoria
  sim800l.delAllSms();
}
