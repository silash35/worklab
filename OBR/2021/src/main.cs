importar("PID")

void Main() {
  PID direitaPID = new PID(bc.Lightness(0));
  PID esquerdaPID = new PID(bc.Lightness(1));

  while (true) {
    double direitaS = bc.Lightness(0);
    double esquerdaS = bc.Lightness(1);

    float saida1 = direitaPID.calcular(direitaS);
    if (saida1 != 0) {
        bc.MoveFrontal(-saida1, saida1);
    }

    float saida2 = esquerdaPID.calcular(esquerdaS);
    if (saida2 != 0) {
      bc.MoveFrontal(saida2, -saida2);
    }

    if(saida1 == 0 && saida2 == 0) {
      bc.MoveFrontal((float)80, (float)80);
    }
  }
}