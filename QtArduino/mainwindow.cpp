#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_LedButton_clicked() {
  LedState = !LedState;

  if (LedState) {
    qDebug("LIGADO");
  } else {
    qDebug("DESLIGADO");
  }
}
