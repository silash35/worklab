#include "paciente.h"

Paciente::Paciente(){
  //GPIO init
  QFuture<void> future = QtConcurrent::run([=]() {
    getDados();
  });
}

void Paciente::zeraDados(){
  temperatura = 0;
  pressao = 0;
  saturacao = 0;
  pontosDePerguntas = 0;
}

void Paciente::getDados(){

  int tempera{0};
  int press{0};
  int satura{0};

  while(true){
    //GPIO getDados

    if(tempera > temperatura){
      temperatura = tempera;
    }
    if(press > pressao){
      temperatura = pressao;
    }
    if(satura > saturacao){
      saturacao = satura;
    }
  }
}

int Paciente::pontosTotal(){

  int ptemp = 0;
  if(temperatura > temperaturaMax){
    ptemp = 10;
  }

  int ppress = 0;
  if(pressao > pressaoMax or pressao < pressaoMin){
      ptemp = 10;
    }

  int psatura = 0;
  if(saturacao < saturacaoMin){
      psatura = 10;
  }

  return pontosDePerguntas + ptemp + ppress + psatura;
}

void Paciente::imprimir(){
  //GPIO imprimir
}
