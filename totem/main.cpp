#include "interface.h"

#include <QApplication>

int main(int argc, char *argv[]){
  QApplication a(argc, argv);
  interface w;
  //w.showFullScreen();
  w.showMaximized();
  return a.exec();
}
