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
    bc.MoveFrontalAngles(100, 40);
  }else if(bc.ReturnColor(2) == "GREEN"){
    while(bc.ReturnColor(2) != "BLACK"){
      bc.MoveFrontal((float)80, (float)80);
    }
    bc.MoveFrontalAngles(100, -40);
  }

  // Detectar obstaculo na pista
  if(bc.Distance(0)<15){
    bc.MoveFrontalAngles(500, -90);
    bc.MoveFrontal((float)300, (float)300);
    bc.Wait(1000);

    bc.MoveFrontalAngles(500, 90);
    bc.MoveFrontal((float)300, (float)300);
    bc.Wait(2500);

    bc.MoveFrontalAngles(500, 90);
    bc.MoveFrontal((float)300, (float)300);
    bc.Wait(1000);

    bc.MoveFrontalAngles(500, -90);
    while(!bc.Touch(0)){
      bc.MoveFrontal((float)-300, (float)-300);
    }
  }
}
float acharTriangulo() {
  for(int i = 0; i<500; ++i){
    bc.MoveFrontal((float)800, (float)800);
    bc.wait(1);

    if(bc.Distance(0)<25){
      bc.MoveFrontalAngles(100, 90);
      i = 0;
    }
  }

  return bc.Compass();
}
/*
TODO:
  - Mudar o modo de reconhecer a area de resgate
  - Desenvolver a parte de pegar as bolinhas e colocar no triangulo
  - Implementar a função de desviar de objetos na pista
*/

void Main() {
  bc.TurnLedOn(255, 255, 255);
  bc.ActuatorUp(8000);

  bc.PrintConsole(0, "Seguindo Linha");
  while (true) {
    seguirLinha();
  }

  bc.PrintConsole(0, "Procurando triangulo");
  float trianglePosition = acharTriangulo();

  bc.CloseActuator();
  bc.ActuatorUp(1000);
  bc.OpenActuator();

  /*
  bc.PrintConsole(0, bc.ReturnColor(4).ToString());
  bc.PrintConsole(0, i.ToString());
  bc.PrintConsole(1, bc.Distance(0).ToString());
  bc.PrintConsole(0, "Procurando bolinhas");
  while(true){
    // Código do resgate
    bc.PrintConsole(1, trianglePosition.ToString());
    bc.MoveFrontal((float)-80, (float)-80);
  }
  */
}
