#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFuture>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_retry_clicked();
  void check_arduino();

private:
  Ui::MainWindow *ui;
  bool findArduino();

  QSerialPort *arduino;
  QString arduino_port_name;
  bool arduino_is_available;

  QFuture<void> future;
  void loop();
};
#endif // MAINWINDOW_H
