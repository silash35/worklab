importar("PID")

void Main() {
  PID pid = new PID();
  bc.Draw();

  while (true) {

    // Seguir Linha
    float saida = pid.calcular(bc.Lightness(0),bc.Lightness(1));
    if (saida != 0) {
      bc.MoveFrontal(saida, -saida);
    }else {
      bc.MoveFrontal((float)80, (float)80);
    }

    bc.PrintConsole(0, bc.ReturnColor(0));
    bc.PrintConsole(1, bc.ReturnColor(1));

    // Detectar quadrados verdes e agir
    if(bc.ReturnColor(0) == "GREEN"){
      bc.MoveFrontalAngles(500, 45);
    }else if(bc.ReturnColor(1) == "GREEN"){
      bc.MoveFrontalAngles(500, -45);
    }
  }
}