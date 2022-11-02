/*
  Waste Monitoring System (WMS)
  Sistema de monitoramento de resíduos

  Trabalho de Introdução a Engenharia de controle e automação da Equipe 3.
  Instruções:
  1- Fazer o upload desse código para o Arduino
  2- Executar o daemon com o comando "pnpm start" na pasta ./daemon
*/

#include "container.hpp"

// Iniciar objeto container
Container container;

void setup() {
  // Iniciar porta serial
  Serial.begin(115200);
}

void loop() {
  // Realizar rotina de verificação do container
  container.verify();
}
