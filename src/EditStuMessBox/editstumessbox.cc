//
// Created by 10451 on 2022/5/12.
//

#include "editstumessbox.h"

EditStuMessBox::EditStuMessBox(QWidget *parent, M_Sql *sql)
    : QDialog(parent), sql_(sql), isAdd_(true) {
  /*!
   *  垂直布局：主要布局，里面包含一个表单布局和水平布局
   *  表单布局：每行一个标签和一个输入框
   *  水平布局：放置按钮
   * */
  setWindowIcon(QIcon(":/img/qt_logo.png"));
  setFixedSize(400, 200);

  // 表单布局设置
  auto *Form = new QFormLayout();

  stu_name_ = new QLineEdit(this);
  stu_name_->setPlaceholderText("Please input name");

  stu_gender_ = new QLineEdit(this);
  stu_gender_->setPlaceholderText("Please input gender");

  stu_age_ = new QLineEdit(this);
  stu_age_->setPlaceholderText("Please input age");

  Form->addRow("Name", stu_name_);
  Form->addRow("Gender", stu_gender_);
  Form->addRow("Age", stu_age_);
  Form->setRowWrapPolicy(QFormLayout::WrapLongRows);

  // 水平布局设置
  auto *HBox = new QHBoxLayout();
  submit_ = new QPushButton("Submit");
  cancel_ = new QPushButton("Cancel");
  HBox->addWidget(submit_);
  HBox->addWidget(cancel_);

  // 主要布局设置,拉伸比例为4:1
  auto *VBox = new QVBoxLayout();
  VBox->addLayout(Form, 4);
  VBox->addLayout(HBox, 1);

  this->setLayout(VBox);

  // 信号与槽
  // 提交按钮,将输入信息保存到文件中
  connect(submit_, &QPushButton::clicked, this,
          &EditStuMessBox::SaveStuMessToDB);
  // 取消按钮,关闭窗口
  connect(cancel_, &QPushButton::clicked, this, &EditStuMessBox::close);
}

EditStuMessBox::~EditStuMessBox() {
  if (sql_) {
    delete sql_;
    sql_ = nullptr;
  }
}

/*!
 * \brief 将学生信息提交到数据库中
 */
void EditStuMessBox::SaveStuMessToDB() {
  if (stu_name_->text().isEmpty() || stu_age_->text().isEmpty() ||
      stu_gender_->text().isEmpty()) {
    QMessageBox::warning(this, "Warning", "Please input all information");
  } else {
    // 将学生信息插入数据库中
    QStringList string_list;
    string_list << stu_name_->text() << stu_gender_->text() << stu_age_->text();
    sql_->Insert(string_list);
    this->close();
    emit CloseBox();
  }
}
/*!
 * \brief 更新学生信息到数据库中
 */
void EditStuMessBox::UpDateStuMessToDB() {
  if (stu_name_->text().isEmpty() || stu_age_->text().isEmpty() ||
      stu_gender_->text().isEmpty()) {
    QMessageBox::warning(this, "Warning", "Please input all information");
  } else {
    // 将学生信息插入数据库中
    QStringList string_list;
    string_list << id_ << stu_name_->text() << stu_gender_->text()
                << stu_age_->text();
    sql_->Update(string_list);
    this->close();
    emit CloseBox();
  }
}

/*!
 * @brief 设置姓名
 * @param name
 */
void EditStuMessBox::SetStuName(const QString &name) {
  stu_name_->setText(name);
}

/*!
 * @brief 设置年龄
 * @param age
 */
void EditStuMessBox::SetStuAge(const QString &age) { stu_age_->setText(age); }

/*!
 * @brief 设置性别
 * @param age
 */
void EditStuMessBox::SetStuGender(const QString &gender) {
  stu_gender_->setText(gender);
}

/*!
 * @brief 设置id
 * @param age
 */
void EditStuMessBox::SetId(const QString &id) { id_ = id; }

/*!
 * @brief 切换为编辑模式，提交按钮信号槽设置为更新
 */
void EditStuMessBox::SetModifyMode() {
  disconnect(submit_, &QPushButton::clicked, nullptr, nullptr);
  connect(submit_, &QPushButton::clicked, this,
          &EditStuMessBox::UpDateStuMessToDB);
}
