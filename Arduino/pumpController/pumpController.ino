#include "bomba.h"
#include "codes.h"

int commandIndex = 0;
int selectedBomb = 0;
String textSms = "";

Bomba bombas[] = {Bomba("Bomba 0", 13, A0, (12, 0, 13, 0)), Bomba("Bomba 1", 1, A1, (12, 0, 13, 0)),
                  Bomba("Bomba 2", 2, A2, (12, 0, 13, 0)), Bomba("Bomba 3", 3, A3, (12, 0, 13, 0)),
                  Bomba("Bomba 4", 4, A4, (12, 0, 13, 0))};

void setup() {
  Serial.begin(9600);

  // Adjust RTC time
  // RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {

  // Verficar Agendamentos
  for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
    bombas[i].verificarAgendamentos();
  }

  textSms = Serial.readString();

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
      Serial.println(bombas[selectedBomb].getMessage());
    } else {
      String message = "";
      for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
        message = message + "\n \n" + bombas[i].getMessage();
      }
      Serial.println(message);
    }
  }
}
