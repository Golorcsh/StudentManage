//
// Created by 10451 on 2022/5/22.
//

#ifndef STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
#define STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
#include "./mylabel.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class PagingWidget : public QWidget {
  Q_OBJECT
public:
  explicit PagingWidget(QWidget *parent = nullptr);
  void SetCurrentPage(int current_page);
  void SetPageSize(int page_size);
  void SetInfo(int nums, int total_page);

private:
  void Init();
signals:
  void PageChanged(int page_num);
  void NextPage();
  void PrevPage();
  void FirstPage();
  void LastPage();
  void PageSizeChanged(int page_size);

private slots:
  void InputPage();
  void ClickNext();
  void ClickPrev();
  void ClickFirst();
  void ClickLast();
  void InputPageSize();

private:
  // 分页按钮
  MyLabel *first_{};
  MyLabel *prev_{};
  MyLabel *next_{};
  MyLabel *last_{};
  QLabel *info_{};
  QLineEdit *input_page_{};
  QLabel *page_size_label_{};
  QLineEdit *input_page_size_{};
};

#endif // STUDENTMANAGE_SRC_PAGINGWIDGET_PAGINGWIDGET_H_
