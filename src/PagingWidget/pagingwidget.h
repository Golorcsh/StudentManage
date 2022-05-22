//
// Created by 10451 on 2022/5/22.
//

#ifndef STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
#define STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "../Sql/msql.h"

class PagingWidget : public QWidget {
 Q_OBJECT
 public:
  explicit PagingWidget(QWidget *parent = nullptr);
 private:
  void Init();

 signals:
  void PageChange(int page);
  void NextPage();
  void PrevPage();
  void FirstPage();
  void LastPage();

 private:
  //分页按钮
  QLabel *first_{};
  QLabel *prev_{};
  QLabel *next_{};
  QLabel *last_{};
  QLineEdit *input_page_{};
};

#endif //STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
