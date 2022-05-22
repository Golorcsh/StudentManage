//
// Created by 10451 on 2022/5/22.
//
//为label添加Clicked信号

#include "mylabel.h"
MyLabel::MyLabel(QWidget *parent) : QLabel(parent) {

}
void MyLabel::mousePressEvent(QMouseEvent *event) {
  emit Clicked();
}

