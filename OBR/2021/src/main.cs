importar("seguirLinha")

void Main() {
  PID pid = new PID();
  bc.TurnLedOn(255, 255, 255);

  while (bc.Distance(0)>5) {
    seguirLinha();
  }

  while(true){
    // Código do resgate
  }
}
