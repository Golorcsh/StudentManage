//
// Created by 10451 on 2022/5/22.
//

#include "pagingwidget.h"

PagingWidget::PagingWidget(QWidget *parent) : QWidget(parent) {
  Init();
}
void PagingWidget::Init() {
  this->setFixedSize(200, 35);
  auto HBLayout = new QHBoxLayout(this);
  first_ = new QLabel(this);
  last_ = new QLabel(this);
  prev_ = new QLabel(this);
  next_ = new QLabel(this);
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
  HBLayout->addWidget(first_);
  HBLayout->addWidget(prev_);
  HBLayout->addWidget(input_page_);
  HBLayout->addWidget(next_);
  HBLayout->addWidget(last_);
  HBLayout->setContentsMargins(0, 0, 0, 0);
  HBLayout->setSpacing(0);
}