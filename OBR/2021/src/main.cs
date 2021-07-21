importar("seguirLinha")
importar("acharTriangulo")

/*
TODO:
  - Desenvolver a parte de pegar as bolinhas e colocar no triangulo
*/

bool isOnRescueArea(){
  return (bc.Inclination()>300) && (bc.Distance(2)<40) && (bc.Distance(1)<40);
}

void Main() {
  bc.TurnLedOn(255, 255, 255);
  bc.ActuatorUp(8000);

  bc.PrintConsole(0, "Seguindo Linha");
  while (!isOnRescueArea()) {
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
