#include "MainWidget/mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWidget mWidget;
  mWidget.show();
  return QApplication::exec();
}