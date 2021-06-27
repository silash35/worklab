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
void Main() {
  PID pid = new PID();
  bc.TurnLedOn(255, 255, 255);

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