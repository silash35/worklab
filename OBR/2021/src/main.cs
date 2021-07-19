importar("seguirLinha")
importar("acharTriangulo")

/*
TODO:
  - Mudar o modo de reconhecer a area de resgate
  - Desenvolver a parte de pegar as bolinhas e colocar no triangulo
  - Implementar a função de desviar de objetos na pista
*/

void Main() {
  bc.TurnLedOn(255, 255, 255);

  bc.PrintConsole(0, "Seguindo Linha");
  while (bc.Distance(0)>25) {
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
