#ifndef PACIENTE_H
#define PACIENTE_H

#include<QtConcurrent/qtconcurrentrun.h>

#define temperaturaMax 37 //Temperatura maxima até ser considerada febre
#define pressaoMax 15 //Pressão maxima até ser considerada pressão alta
#define pressaoMin 10 //Pressão  minima até ser considerada pressão baixa
#define saturacaoMin 95 //Saturação Minima até ser considerrada saturação baixa

class Paciente{
public:

  int temperatura{0};
  int pressao{0};
  int saturacao{0};

  int pontosDePerguntas{0};

  Paciente();
  void zeraDados();
  void getDados();
  void imprimir();
  int pontosTotal();
};

#endif // PACIENTE_H
