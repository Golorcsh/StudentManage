//
// Created by 10451 on 2022/5/22.
//
// 为label添加Clicked信号

#include "mylabel.h"
MyLabel::MyLabel(QWidget *parent) : QLabel(parent) {}
/*!
 * @brief 重写该函数，当鼠标点击label时，发送Clicked信号
 * @param event
 */
void MyLabel::mousePressEvent(QMouseEvent *event) { emit Clicked(); }
