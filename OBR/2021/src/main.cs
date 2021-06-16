importar("PID")

void Main() {
  PID pid = new PID();

  while (true) {
    float saida = pid.calcular(bc.Lightness(0),bc.Lightness(1));

    if (saida != 0) {
        bc.MoveFrontal(saida, -saida);
    }else {
      bc.MoveFrontal((float)80, (float)80);
    }
  }
}