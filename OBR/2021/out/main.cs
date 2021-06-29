// Classe para calcular PID
// Eu não precisei do I nem do D então suas implementações foram deletadas

public class PID {
  // Constantes a serem calibrados
  double kP = 10;
  double tolerancia = 4;

  // Outras variaveis

  public float calcular(double sensor1, double sensor2) {
    double erro = sensor1 - sensor2;

    double p = kP * erro;

    float saida = (float)(p);
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
    bc.PrintConsole(0, saida.ToString());
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

void Main() {
  PID pid = new PID();
  bc.TurnLedOn(255, 255, 255);

  while (true) {
    seguirLinha();
  }
}
