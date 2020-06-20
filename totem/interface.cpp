#include "interface.h"
#include "./ui_interface.h"

interface::interface(QWidget *parent):QMainWindow(parent),ui(new Ui::interface){
  ui->setupUi(this);
}

interface::~interface(){
  delete ui;
}


void interface::on_botao_iniciar_clicked(){
  ui->pagina->setCurrentIndex(1);
  pontos = 0;
}
