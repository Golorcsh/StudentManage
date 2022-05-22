//
// Created by 10451 on 2022/5/22.
//

#ifndef STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
#define STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
#include <QWidget>
#include <QLabel>
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

#endif //STUDENTMANAGE_SRC_PAGINGWIDGET_MYLABEL_H_
