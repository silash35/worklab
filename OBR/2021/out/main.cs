// Classe para calcular PID

public class PID {
  // Constantes a serem calibrados
  double kP = 20;
  double kI = 1;
  double kD = 1;
  double tolerancia = 4;
  // Constantes a serem definidas automaticamente
  double objetivo = 0;
  // Outras variaveis
  public double t = 0;
  double somatoriaDosErros = 0;

  public PID(double obj){
    objetivo = obj;
  }

  public float calcular(double entrada) {
    double p = 0;
    double i = 0;
    double d = 0;

    double erro = objetivo - entrada;
    somatoriaDosErros = somatoriaDosErros + erro;
    t = t+1;

    p = kP * erro;
    i = kI * somatoriaDosErros * t;
    d = kD * 0;

    bc.PrintConsole(1, "T = " + t);
    float saida = (float)(p + i + d);
    if (erro < tolerancia) {
      somatoriaDosErros = 0;
      saida = 0;
      t = 0;
    }
    return saida;
  }
}
void Main() {
  PID direitaPID = new PID(bc.Lightness(0));
  PID esquerdaPID = new PID(bc.Lightness(1));

  while (true) {
    double direitaS = bc.Lightness(0);
    double esquerdaS = bc.Lightness(1);

    float saida1 = direitaPID.calcular(direitaS);
    if (saida1 != 0) {
        bc.MoveFrontal(-saida1, saida1);
    }

    float saida2 = esquerdaPID.calcular(esquerdaS);
    if (saida2 != 0) {
      bc.MoveFrontal(saida2, -saida2);
    }

    if(saida1 == 0 && saida2 == 0) {
      bc.MoveFrontal((float)80, (float)80);
    }
  }
}