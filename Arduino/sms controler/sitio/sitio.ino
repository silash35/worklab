#include "bibliotecas/Sim800l.h"
#include "bomba.h"
#include "codes.h"
#include <SoftwareSerial.h>

#define TELEFONE_MESTRE "99999999999"

Sim800l sim800l;
String textSms, numberSms;

Bomba bomba1("Bomba 1", 1, A1);
Bomba bomba2("Bomba 2", 2, A2);
Bomba bomba3("Bomba 3", 3, A3);
Bomba bomba4("Bomba 4", 4, A4);
Bomba bomba5("Bomba 5", 5, A5);

void setup() {
  Serial.begin(9600);

  sim800l.begin();
  sim800l.delAllSms(); // Apaga SMS antigos
}

void loop() {

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
  if (textSms.indexOf(LB1) != -1) {
    bomba1.ligarBomba();
  }
  if (textSms.indexOf(LB2) != -1) {
    bomba2.ligarBomba();
  }
  if (textSms.indexOf(LB3) != -1) {
    bomba3.ligarBomba();
  }
  if (textSms.indexOf(LB4) != -1) {
    bomba4.ligarBomba();
  }
  if (textSms.indexOf(LB5) != -1) {
    bomba5.ligarBomba();
  }

  // Caso receba DBX, Desligar a bomba X
  if (textSms.indexOf(DB1) != -1) {
    bomba1.desligarBomba();
  }
  if (textSms.indexOf(DB2) != -1) {
    bomba2.desligarBomba();
  }
  if (textSms.indexOf(DB3) != -1) {
    bomba3.desligarBomba();
  }
  if (textSms.indexOf(DB4) != -1) {
    bomba4.desligarBomba();
  }
  if (textSms.indexOf(DB5) != -1) {
    bomba5.desligarBomba();
  }

  // Caso receba RSX, Ler os dados da bomba X
  if (textSms.indexOf(RS1) != -1) {
    sim800l.sendSms(TELEFONE_MESTRE, (char *)bomba1.getMessage().c_str());
  }
  if (textSms.indexOf(RS2) != -1) {
    sim800l.sendSms(TELEFONE_MESTRE, (char *)bomba2.getMessage().c_str());
  }
  if (textSms.indexOf(RS3) != -1) {
    sim800l.sendSms(TELEFONE_MESTRE, (char *)bomba3.getMessage().c_str());
  }
  if (textSms.indexOf(RS4) != -1) {
    sim800l.sendSms(TELEFONE_MESTRE, (char *)bomba4.getMessage().c_str());
  }
  if (textSms.indexOf(RS5) != -1) {
    sim800l.sendSms(TELEFONE_MESTRE, (char *)bomba5.getMessage().c_str());
  }

  // Apagar todas as mensagens da memoria
  sim800l.delAllSms();
}
