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
