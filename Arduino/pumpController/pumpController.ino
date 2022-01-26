#include "bomba.h"
#include "codes.h"

int commandIndex = 0;
int selectedBomb = 0;
String textSms = "";

Schedule defaultSchedule(12, 03, 12, 04);

Bomba bombas[] = {
    Bomba("Bomba 0", 8, A0, 1, defaultSchedule), Bomba("Bomba 1", 9, A0, 1, defaultSchedule),
    Bomba("Bomba 2", 10, A0, 1, defaultSchedule), Bomba("Bomba 3", 11, A0, 1, defaultSchedule)};

void setup() {
  Serial.begin(115200);

  RTC.begin();

  // Adjust RTC time
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.print("Horario do RTC: ");
  Serial.println(RTC.now().timestamp());
}

void loop() {

  // Verficar Agendamentos
  for (int i = 0; i < sizeof(bombas) / sizeof(bombas[0]); i++) {
    bombas[i].verificarAgendamentos();
  }

  textSms = Serial.readString();

  // Converter o texto para maiúsculas
  textSms.toUpperCase();

  if (textSms != "") {
    Serial.print("Comando: ");
    Serial.println(textSms);
  }

  // Caso receba LBX, Ligar a bomba X
  commandIndex = textSms.indexOf(LB);
  if (commandIndex != -1) {
    if (isDigit(textSms[commandIndex + 2])) {
      selectedBomb = textSms.substring(commandIndex + 2, commandIndex + 3).toInt();

      if (textSms[commandIndex + 3] != '-') {
        bombas[selectedBomb].ligarBomba();
      } else {
        int time = textSms.substring(commandIndex + 4, commandIndex + 8).toInt();
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
      selectedBomb = textSms.substring(commandIndex + 2, commandIndex + 3).toInt();

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
      selectedBomb = textSms.substring(commandIndex + 2, commandIndex + 3).toInt();
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
