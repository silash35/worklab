float calcularPID(double sensor1, double sensor2) {
  // Somente o P foi nescessario. Por isso o código do I e D foi removido

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
  bc.PrintConsole(0, "Seguindo Linha");

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
  bc.PrintConsole(0, "Procurando triangulo");

  for(int i = 0; i<500; ++i){
    bc.MoveFrontal((float)800, (float)800);
    bc.wait(1);

    if(bc.Distance(0)<25){
      bc.MoveFrontalAngles(500, 90);
      i = 0;
    }

    if(bc.ReturnColor(0) == "BLACK" &&
       bc.ReturnColor(1) == "BLACK" &&
       bc.ReturnColor(2) == "BLACK" &&
       bc.ReturnColor(3) == "BLACK" ){
      i = 500;
    }
  }

  return bc.Compass();
}

void irAoTriangulo(float trianglePosition){
  bc.PrintConsole(0, "Indo Ao triangulo");

  while(!((bc.Compass() - trianglePosition) < 1 && (bc.Compass() - trianglePosition) > -1)){
    bc.MoveFrontalAngles(500, 1);
  }

  bc.MoveFrontal((float)800, (float)800);
  bc.wait(5000);
}

void colocarBolinhas() {
  bc.PrintConsole(0, "Colocando bolinhas");

  bc.ActuatorUp(2000);
  bc.MoveFrontal((float)800, (float)800);
  bc.wait(100);
  bc.OpenActuator();
  bc.MoveFrontal((float)-800, (float)-800);
  bc.wait(100);
  bc.ActuatorDown(2000);
  bc.CloseActuator();
}

void regatarBolinhas(){
  bc.ActuatorDown(9000);
  bc.CloseActuator();

  float trianglePosition = acharTriangulo();

  while(true){
    irAoTriangulo(trianglePosition);
    colocarBolinhas();

    bc.MoveFrontalAngles(500, bc.RandomLimits(40, 300));
    bc.MoveFrontal((float)800, (float)800);
    bc.Wait(2000);
  }
}

bool isOnRescueArea(){
  return (bc.Inclination()>300) && (bc.Distance(2)<40) && (bc.Distance(1)<40);
}

void Main() {
  bc.TurnLedOn(255, 255, 255);
  bc.ActuatorUp(8000);

  while (!isOnRescueArea()) {
    seguirLinha();
  }

  regatarBolinhas();
}
