#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  void on_LedButton_clicked();

private:
  Ui::MainWindow *ui;
  bool LedState = false;

  QSerialPort *arduino;
  QString arduino_port_name;
  bool arduino_is_available;
};
#endif // MAINWINDOW_H
