float calcularPID(double sensor1, double sensor2) {
  double kP = 10;
  double tolerancia = 6;

  double erro = sensor1 - sensor2;
  double p = kP * erro;

  float saida = (float)(p);
  bc.PrintConsole(1, erro.ToString());
  if (erro < tolerancia && erro > -tolerancia) {
    saida = 0;
  }
  return saida;
}

void seguirLinha(){

  // Seguir Linha com PID
  float saida = calcularPID(bc.Lightness(1),bc.Lightness(2));
  if (saida != 0) {
    bc.MoveFrontal(saida, -saida);
  }else {
    bc.MoveFrontal((float)80, (float)80);
  }

  // Detectar quadrados verdes e agir
  if(bc.ReturnColor(1) == "GREEN"){
    while(bc.ReturnColor(1) != "BLACK"){
      bc.MoveFrontal((float)80, (float)80);
    }
    bc.MoveFrontalAngles(100, 30);
  }else if(bc.ReturnColor(2) == "GREEN"){
    while(bc.ReturnColor(2) != "BLACK"){
      bc.MoveFrontal((float)80, (float)80);
    }
    bc.MoveFrontalAngles(100, -30);
  }

  // Detectar
  if(){

  }
}
