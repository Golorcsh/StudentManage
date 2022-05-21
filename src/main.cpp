#include <QApplication>
#include<iostream>
#include "MainWidget/mainwidget.h"
#include "./sql/msql.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWidget mWidget;
  mWidget.show();
  return QApplication::exec();
}