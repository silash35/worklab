#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class interface; }
QT_END_NAMESPACE

class interface : public QMainWindow
{
  Q_OBJECT

public:
  interface(QWidget *parent = nullptr);
  ~interface();

private slots:
  void on_botao_iniciar_clicked();

private:
  Ui::interface *ui;
  int pontos{0};
};
#endif // INTERFACE_H
