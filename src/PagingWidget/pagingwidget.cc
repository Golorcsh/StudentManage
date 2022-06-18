//
// Created by 10451 on 2022/5/22.
//

#include "pagingwidget.h"

PagingWidget::PagingWidget(QWidget *parent) : QWidget(parent) { Init(); }
/*!
 * @brief 初始化
 */
void PagingWidget::Init() {
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
  input_page_->setFixedSize(30, 20);
  input_page_->setAlignment(Qt::AlignCenter);

  info_ = new QLabel(this);
  info_->setFixedHeight(20);
  info_->setFixedWidth(100);
  info_->setAlignment(Qt::AlignCenter);
  info_->adjustSize();

  page_size_label_ = new QLabel(this);
  page_size_label_->setAlignment(Qt::AlignCenter);
  page_size_label_->setFixedHeight(20);
  page_size_label_->setText("PageSize:");

  input_page_size_ = new QLineEdit(this);
  input_page_size_->setFixedSize(30, 20);
  input_page_size_->setAlignment(Qt::AlignCenter);

  auto hb_layout1 = new QHBoxLayout();
  hb_layout1->addWidget(first_);
  hb_layout1->addWidget(prev_);
  hb_layout1->addWidget(input_page_);
  hb_layout1->addWidget(next_);
  hb_layout1->addWidget(last_);
  hb_layout1->setSpacing(0);
  hb_layout1->setAlignment(Qt::AlignCenter);
  auto hb_layout2 = new QHBoxLayout();
  hb_layout2->addWidget(page_size_label_);
  hb_layout2->addWidget(input_page_size_);
  hb_layout2->addWidget(info_);
  hb_layout2->setSpacing(0);
  hb_layout2->setAlignment(Qt::AlignCenter);
  auto main_layout = new QHBoxLayout();
  main_layout->addLayout(hb_layout1, 10);
  main_layout->addLayout(hb_layout2, 1);
  this->setLayout(main_layout);

  // 信号与槽
  connect(first_, &MyLabel::Clicked, this, &PagingWidget::ClickFirst);
  connect(last_, &MyLabel::Clicked, this, &PagingWidget::ClickLast);
  connect(prev_, &MyLabel::Clicked, this, &PagingWidget::ClickPrev);
  connect(next_, &MyLabel::Clicked, this, &PagingWidget::ClickNext);
  connect(input_page_, &QLineEdit::returnPressed, this,
          &PagingWidget::InputPage);
  connect(input_page_size_, &QLineEdit::returnPressed, this,
          &PagingWidget::InputPageSize);
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
  info_->setText(QString("%1P-%2S").arg(total_page).arg(nums));
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
void PagingWidget::ClickNext() { emit NextPage(); }
/**
 * @brief 发出上一页信号
 */
void PagingWidget::ClickPrev() { emit PrevPage(); }
/**
 * @brief 发出第一页信号
 */
void PagingWidget::ClickFirst() { emit FirstPage(); }
/**
 * @brief 发出最后一页信号
 */
void PagingWidget::ClickLast() { emit LastPage(); }
/*!
 * @brief 输入每页显示的记录数，发出信号
 */
void PagingWidget::InputPageSize() {
  auto page_size = input_page_size_->text().toInt();
  emit PageSizeChanged(page_size);
}
/*!
 * @brief 设置每页显示的记录数
 * @param page_size
 */
void PagingWidget::SetPageSize(int page_size) {
  input_page_size_->setText(QString::number(page_size));
}
