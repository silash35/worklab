#define EMPTY_BOX_VALUE 12
#define FULL_BOX_VALUE 2
#define MAX_BOX_PERCENTAGE 90

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return 0.01723 * pulseIn(echoPin, HIGH);
}

// Classe para gerenciar uma seção do container
class Section {
private:
  int pinTrigger = 0;
  int pinEcho = 0;

  // Variável que guarda a informação se os operadores já foram avisados sobre o status dessa seção
  // do container em especifico
  bool alreadyWarned = false;

public:
  Section(int pt, int pe) {
    pinMode(pt, OUTPUT);
    pinMode(pe, INPUT);

    pinTrigger = pt;
    pinEcho = pe;
  }

  // Ler estado atual da seção
  int getState() {
    /*
      0: Vazio
      1: Cheio pela metade
      2: Cheio (E precisa notificar o operador da esteira)
      3: Cheio (E o operador já foi notificado)
    */

    int distance = readUltrasonicDistance(pinTrigger, pinEcho);
    int percentage = map(distance, EMPTY_BOX_VALUE, FULL_BOX_VALUE, 0, 100);

    /*
      Serial.print("Porcentagem: ");
      Serial.print(percentage);
      Serial.print("\n");
    */

    if (percentage >= MAX_BOX_PERCENTAGE) {
      if (alreadyWarned) {
        return 3;
      }
      alreadyWarned = true;
      return 2;
    } else if (percentage >= 50) {
      alreadyWarned = false;
      return 1;
    } else {
      alreadyWarned = false;
      return 0;
    }
  }
};