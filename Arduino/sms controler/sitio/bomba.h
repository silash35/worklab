class Bomba {
private:
  int pinBomba = 0;
  int pinSensor = 0;
  String nome = "";

  bool bombIsOn = false;

  int horarioParaDesligar = 0;
  int horarioParaLigar = 0;

public:
  Bomba(String n, int pb, int ps) {
    nome = n;

    pinBomba = pb;
    pinMode(pb, OUTPUT);
    pinSensor = ps;
  }

  void ligarBomba() {
    digitalWrite(pinBomba, HIGH);
    bombIsOn = true;
  }
  void desligarBomba() {
    digitalWrite(pinBomba, LOW);
    bombIsOn = false;
  }

  int getSensor() { return analogRead(pinSensor); }
  // bool isOn() { return bombIsOn; }

  String getMessage() {
    String message = "A bomba '" + nome + "' está ";
    message = message + bombIsOn ? "Funcionando" : "Desligada";
    message = message + "\n";
    message = message + "E seu sensor está detectando o seguinte valor" + getSensor();

    return message;
  }
};
