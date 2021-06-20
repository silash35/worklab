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

    bc.PrintConsole(0, bc.ReturnColor(0));
    bc.PrintConsole(1, bc.ReturnColor(1));

    if(bc.ReturnColor(0) == "GREEN"){
      bc.MoveFrontal((float)100, (float)100);
      bc.Wait(1000);

      bc.MoveFrontal((float)-100, (float)100);
      bc.Wait(15000);
    }else if(bc.ReturnColor(1) == "GREEN"){
      bc.MoveFrontal((float)100, (float)100);
      bc.Wait(1000);

      bc.MoveFrontal((float)100, (float)-100);
      bc.Wait(15000);
    }
  }
}