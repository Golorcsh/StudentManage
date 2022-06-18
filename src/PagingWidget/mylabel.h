//
// Created by 10451 on 2022/5/22.
//
/*label没有点击信号，因此写一个带有Clicked信号的label控件*/

#ifndef STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
#define STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
#include <QLabel>
#include <QWidget>
class MyLabel : public QLabel {
  Q_OBJECT
public:
  explicit MyLabel(QWidget *parent = nullptr);
  ~MyLabel() override = default;
signals:
  void Clicked();

protected:
  void mousePressEvent(QMouseEvent *event) override;
};

#endif // STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
