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
