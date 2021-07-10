// Classe para calcular PID
// Eu não precisei do I nem do D então suas implementações foram deletadas

public class PID {
  // Constantes a serem calibrados
  double kP = 10;
  double tolerancia = 6;

  // Outras variaveis

  public float calcular(double sensor1, double sensor2) {
    double erro = sensor1 - sensor2;

    double p = kP * erro;

    float saida = (float)(p);
    bc.PrintConsole(1, erro.ToString());
    if (erro < tolerancia && erro > -tolerancia) {
      saida = 0;
    }
    return saida;
  }
}
PID pid = new PID();

void seguirLinha(){

  // Seguir Linha suavemente com PID
  float saida = pid.calcular(bc.Lightness(1),bc.Lightness(2));
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

void Main() {
  bc.TurnLedOn(255, 255, 255);

  bc.PrintConsole(0, "Seguindo Linha");
  while (bc.Distance(0)>25) {
    seguirLinha();
  }

  bc.PrintConsole(0, "Procurando triangulo");
  float trianglePosition = acharTriangulo();

  //bc.PrintConsole(0, bc.ReturnColor(4).ToString());
  //bc.PrintConsole(0, i.ToString());
  //bc.PrintConsole(1, bc.Distance(0).ToString());

  bc.PrintConsole(0, "Procurando bolinhas");
  while(true){
    // Código do resgate
    bc.PrintConsole(1, trianglePosition.ToString());
    bc.MoveFrontal((float)-80, (float)-80);
  }
}
