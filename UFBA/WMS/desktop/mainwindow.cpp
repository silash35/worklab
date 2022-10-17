#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QtConcurrent>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtWidgets>

bool MainWindow::findArduino() {
  // Conectar Porta Arduino
  arduino_is_available = false;
  arduino_port_name = "";
  arduino = new QSerialPort;

  foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
    if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
      arduino_port_name = serialPortInfo.portName();
      arduino_is_available = true;
    }
  }

  if (arduino_is_available) {
    // open and configure the serialport
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud115200);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
  }

  return arduino_is_available;
}

void MainWindow::check_arduino() {
  if (findArduino()) {
    ui->label->setText("Arduino conectado. Aguardando instruções...");
    ui->retry->hide();
    future.resume();
  } else {
    ui->label->setText("Nenhum Arduino encontrado");
    ui->retry->show();
    future.suspend();
  }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // future = QtConcurrent::run(loop);
}

MainWindow::~MainWindow() {
  arduino->close();
  future.cancel();
  delete ui;
}

void MainWindow::on_retry_clicked() { check_arduino(); }

void MainWindow::loop() {
  while (true) {
    QString serialText = arduino->readLine();
    qInfo() << "Teste AAAAAAAAA";
    qInfo() << serialText;
  }
}
