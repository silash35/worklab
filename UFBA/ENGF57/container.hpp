#include "section.hpp"

#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_RED 7

class Container {
private:
  // Cada seção do container é um objeto separado.
  // Ao criar um Array de objetos, fica mais fácil iterar por seus elementos e modificar a
  // quantidade de seções conforme o necessário
  Section sections[3];

  // Variável que guarda a informação se os operadores já foram avisados sobre o status do container
  // como um todo
  bool alreadyWarned = false;

public:
  Container() : sections{Section(A0, A1), Section(A4, A5), Section(A2, A3)} {
    // Setar pins de LED como saída.
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
  }

  void verify() {
    bool containerEmpty = true;
    bool containerHalf = true;
    bool containerFull = true;

    bool callTruck = true;

    for (int i = 0; i < sizeof(sections) / sizeof(sections[0]); i++) {
      int state = sections[i].getState();
      delay(100);

      if (state == 2) {
        Serial.print("mat: Seção " + String(i) + " Cheia, por favor mude a esteira para outra\n");
      }

      if (state != 0) {
        containerEmpty = false;
      }

      if (state < 2) {
        containerFull = false;
      }
    }

    if (containerEmpty || containerFull) {
      containerHalf = false;
    }

    if (containerEmpty) {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);

      alreadyWarned = false;
    } else if (containerHalf) {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_RED, LOW);
    } else if (containerFull) {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, HIGH);

      if (!alreadyWarned) {
        Serial.print("mat: todas as seções estão cheias. Por favor desligue o fluxo de resíduo\n");
        Serial.print("truck: Container Cheio\n");
        alreadyWarned = true;
      }
    }
  }
};