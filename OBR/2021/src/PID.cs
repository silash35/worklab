// Classe para calcular PID
// Eu não precisei do I nem do D então suas implementações foram deletadas

public class PID {
  // Constantes a serem calibrados
  double kP = 50;
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