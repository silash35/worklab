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