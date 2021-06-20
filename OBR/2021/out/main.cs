// Classe para calcular PID

public class PID {
  // Constantes a serem calibrados
  double kP = 10;
  double kI = 0;
  double kD = 0;
  double tolerancia = 4;

  // Outras variaveis
  double t = 0;
  double somatoriaDosErros = 0;

  public float calcular(double sensor1, double sensor2) {
    double erro = sensor1 - sensor2;
    somatoriaDosErros = somatoriaDosErros + erro;
    t = t+1;

    double p = kP * erro;
    double i = kI * somatoriaDosErros * t;
    double d = kD * 0;

    float saida = (float)(p + i + d);
    if (erro < tolerancia && erro > -tolerancia) {
      somatoriaDosErros = 0;
      saida = 0;
      t = 0;
    }
    return saida;
  }
}
void Main() {
  PID pid = new PID();

  while (true) {
    float saida = pid.calcular(bc.Lightness(0),bc.Lightness(1));

    if (saida != 0) {
      bc.MoveFrontal(saida, -saida);
    }else {
      bc.MoveFrontal((float)80, (float)80);
    }

    bc.PrintConsole(0, bc.ReturnColor(0));
    bc.PrintConsole(1, bc.ReturnColor(1));

    if(bc.ReturnColor(0) == "GREEN"){
      bc.MoveFrontal((float)100, (float)100);
      bc.Wait(1000);

      bc.MoveFrontal((float)-100, (float)100);
      bc.Wait(15000);
    }else if(bc.ReturnColor(1) == "GREEN"){
      bc.MoveFrontal((float)100, (float)100);
      bc.Wait(1000);

      bc.MoveFrontal((float)100, (float)-100);
      bc.Wait(15000);
    }
  }
}