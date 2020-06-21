#include "interface.h"
#include "./ui_interface.h"

interface::interface(QWidget *parent):QMainWindow(parent),ui(new Ui::interface){
  ui->setupUi(this);
}

interface::~interface(){
  delete ui;
}


void interface::on_botao_iniciar_clicked(){
  ui->pagina->setCurrentIndex(5);
  paciente.zeraDados();  
}

void interface::on_med_clicked(){
  ui->pagina->setCurrentIndex(6);
  int pontosTotal = paciente.pontosTotal();

  pontosTotal = 9;

  if(pontosTotal <= 10){
    ui->result_result->setText("Azul");
    ui->result_result->setStyleSheet("color: white; border:10px solid black; background-color:blue;");
  }else if(pontosTotal <= 20){
    ui->result_result->setText("Verde");
    ui->result_result->setStyleSheet("color: white; border:10px solid black; background-color: green;");
  }else if(pontosTotal <= 30){
    ui->result_result->setText("Amarelo");
    ui->result_result->setStyleSheet("color: white; border:10px solid black; background-color: yellow;");
  }else if(pontosTotal <= 40){
    ui->result_result->setText("Laranja");
    ui->result_result->setStyleSheet("color: white; border:10px solid black; background-color: orange;");
  }else if (pontosTotal > 40){
    ui->result_result->setText("Vermelho");
    ui->result_result->setStyleSheet("color: white; border:10px solid black; background-color: red;");
  }else{
    //ERRO
    qDebug() << "Erro! Pontuação invalida:" << pontosTotal << '\n';
  }
}
