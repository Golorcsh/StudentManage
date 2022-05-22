//
// Created by 10451 on 2022/5/22.
//

#include "pagingwidget.h"

PagingWidget::PagingWidget(QWidget *parent) : QWidget(parent) {
  Init();
}
/*!
 * @brief 初始化
 */
void PagingWidget::Init() {
  this->setFixedSize(300, 35);
  first_ = new MyLabel(this);
  last_ = new MyLabel(this);
  prev_ = new MyLabel(this);
  next_ = new MyLabel(this);
  first_->setFixedSize(20, 20);
  auto first_img = new QPixmap(":/icon/first.png");
  first_img->scaled(first_->size(), Qt::KeepAspectRatio);
  first_->setScaledContents(true);
  first_->setPixmap(*first_img);

  last_->setFixedSize(20, 20);
  auto last_img = new QPixmap(":/icon/last.png");
  last_img->scaled(last_->size(), Qt::KeepAspectRatio);
  last_->setScaledContents(true);
  last_->setPixmap(*last_img);

  prev_->setFixedSize(20, 20);
  auto prev_img = new QPixmap(":/icon/prev.png");
  prev_img->scaled(prev_->size(), Qt::KeepAspectRatio);
  prev_->setScaledContents(true);
  prev_->setPixmap(*prev_img);

  next_->setFixedSize(20, 20);
  auto next_img = new QPixmap(":/icon/next.png");
  next_img->scaled(next_->size(), Qt::KeepAspectRatio);
  next_->setScaledContents(true);
  next_->setPixmap(*next_img);

  input_page_ = new QLineEdit(this);
  input_page_->setFixedWidth(30);
  input_page_->setAlignment(Qt::AlignCenter);
  info_ = new QLabel(this);
  info_->setFixedHeight(20);

  auto HBLayout = new QHBoxLayout(this);
  HBLayout->setAlignment(Qt::AlignCenter);
  HBLayout->addWidget(first_);
  HBLayout->addWidget(prev_);
  HBLayout->addWidget(input_page_);
  HBLayout->addWidget(next_);
  HBLayout->addWidget(last_);
  HBLayout->addWidget(info_);
  HBLayout->setContentsMargins(0, 0, 0, 0);
  HBLayout->setSpacing(0);
  this->setLayout(HBLayout);

  //信号与槽
  connect(first_, &MyLabel::Clicked, this, &PagingWidget::ClickFirst);
  connect(last_, &MyLabel::Clicked, this, &PagingWidget::ClickLast);
  connect(prev_, &MyLabel::Clicked, this, &PagingWidget::ClickPrev);
  connect(next_, &MyLabel::Clicked, this, &PagingWidget::ClickNext);
  connect(input_page_, &QLineEdit::returnPressed, this, &PagingWidget::InputPage);
}
/**
 * @brief 设置显示的页数
 * @param current_page
 */
void PagingWidget::SetCurrentPage(int current_page) {
  input_page_->setText(QString::number(current_page + 1));
}
/**
 * @brief 设置总页数和总记录数
 * @param nums
 * @param total_page
 */
void PagingWidget::SetInfo(int nums, int total_page) {
  info_->setText(QString("共%1条记录，共%2页").arg(nums).arg(total_page));
}
/**
 * @brief 发出输入页码信号
 */
void PagingWidget::InputPage() {
  auto page_num = input_page_->text().toInt();
  emit PageChanged(page_num - 1);
}
/**
 * @brief 发出下一页信号
 */
void PagingWidget::ClickNext() {
  emit NextPage();
}
/**
 * @brief 发出上一页信号
 */
void PagingWidget::ClickPrev() {
  emit PrevPage();
}
/**
 * @brief 发出第一页信号
 */
void PagingWidget::ClickFirst() {
  emit FirstPage();
}
/**
 * @brief 发出最后一页信号
 */
void PagingWidget::ClickLast() {
  emit LastPage();
}