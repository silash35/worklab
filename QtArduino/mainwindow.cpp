#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

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
    arduino->open(QSerialPort::WriteOnly);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    arduino->write("off");
  } else {
    // give error message if not available
    QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
  }
}

MainWindow::~MainWindow() {
  arduino->close();
  delete ui;
}

void MainWindow::on_LedButton_clicked() {
  LedState = !LedState;

  if (LedState) {
    ui->LedButton->setText("DESLIGAR");
    arduino->write("on");
  } else {
    ui->LedButton->setText("LIGAR");
    arduino->write("off");
  }
}
