importar("seguirLinha")

void Main() {
  PID pid = new PID();
  bc.TurnLedOn(255, 255, 255);

  while (true) {
    seguirLinha();
  }
}
