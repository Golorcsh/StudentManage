//
// Created by 10451 on 2022/5/12.
//

#include "mainwidget.h"
MainWidget::MainWidget() : sql_(new M_Sql) {
  /*!
   * 主界面为水平布局，左侧为left_table_box，右侧为right_table_box
   */
  setWindowIcon(QIcon(":/img/qt_logo.png"));
  setWindowTitle("Student Management System");
  this->resize(800, 600);

  auto *main_layout = new QHBoxLayout(this);

  //使用函数功能穿件左右两侧控件
  auto left_table_box = CreateStuMess(50);
  auto right_table_box = CreateMenu();

  //左右两侧控件加入主布局
  main_layout->addWidget(left_table_box, 3);
  main_layout->addWidget(right_table_box, 2);

}

MainWidget::~MainWidget() {
  if (sql_) {
    delete sql_;
    sql_ = nullptr;
  }
}
/**
 * 创建学生信息窗口,即左侧控件
 * @return
 */
QGroupBox *MainWidget::CreateStuMess(int page_size) {
  //设置分页参数
  this->page_size_ = page_size;
  this->current_page_ = 0;
  int total_page = sql_->GetTotalNum() / page_size_;
  this->total_page_ = total_page + (sql_->GetTotalNum() % page_size_ == 0 ? 0 : 1);

  auto box = new QGroupBox("Student Information");
  table_widget_ = new QTableWidget(box);
  table_widget_->setSelectionBehavior(QAbstractItemView::SelectRows);
  table_widget_->setColumnCount(4);
  //设置不可编辑
  table_widget_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_widget_->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Gender" << "Age");
  //分页控件
  paging_widget_ = new PagingWidget(box);
  paging_widget_->SetCurrentPage(current_page_);

  FlushTable();
  auto box_layout = new QVBoxLayout(box);
  auto table_layout = new QHBoxLayout(box);
  auto paging_layout = new QHBoxLayout(box);
  table_layout->addWidget(table_widget_);
  paging_layout->addWidget(paging_widget_);
  paging_layout->setAlignment(Qt::AlignCenter);
  box_layout->addLayout(table_layout);
  box_layout->addLayout(paging_layout);
  box->setLayout(box_layout);

  //信号槽连接
  //当用户点击表格中的某个单元格时，触发cellClicked信号，更新列表中学生信息
  connect(table_widget_, &QTableWidget::cellClicked, this, &MainWidget::FlushListWidget);
  //当用户更改表格中的某个单元格时，触发cellChanged信号，调用FlushListWidget函数,修改的同时更新
  connect(table_widget_, &QTableWidget::cellChanged, this, &MainWidget::FlushListWidget);
  //当用户双击表格中某一行时，触发cellDoubleClicked信号，调用ChangeStuMessItem函数
  connect(table_widget_, &QTableWidget::itemDoubleClicked, this, &MainWidget::ChangeStuMessItem);
  //当用户输入页码时，调用FlushTable函数
  connect(paging_widget_, &PagingWidget::PageChanged, this, &MainWidget::FlushTableFromPageNum);
  //当用户点击第一页是，触发FirstPage信号，调用FirstPage函数
  connect(paging_widget_, &PagingWidget::FirstPage, this, &MainWidget::FirstPage);
  //当用户点击最后一页是，触发LastPage信号，调用LastPage函数
  connect(paging_widget_, &PagingWidget::LastPage, this, &MainWidget::LastPage);
  //当用户点击上一页是，触发PrevPage信号，调用PrevPage函数
  connect(paging_widget_, &PagingWidget::PrevPage, this, &MainWidget::PrevPage);
  //当用户点击下一页是，触发NextPage信号，调用NextPage函数
  connect(paging_widget_, &PagingWidget::NextPage, this, &MainWidget::NextPage);

  return box;
}

/**
 * 创建功能面板窗口
 * @return
 */
QGroupBox *MainWidget::CreateMenu() {
  auto box = new QGroupBox("Student Details");
  //功能面板
  auto box_layout = new QVBoxLayout(box);
  list_widget_ = new QListWidget(box);
  //按钮控件
  auto Buts = new QGridLayout;
  add_stu_button_ = new QPushButton("Add", box);
  del_stu_button_ = new QPushButton("Delete", box);
  export_button_ = new QPushButton("Export", box);
  find_stu_edit_ = new QLineEdit(box);
  find_stu_edit_->setPlaceholderText("Please input student ID or Name");
  find_stu_edit_->setClearButtonEnabled(true);
  Buts->addWidget(add_stu_button_, 0, 0);
  Buts->addWidget(del_stu_button_, 0, 1);
  Buts->addWidget(find_stu_edit_, 1, 0, 1, 0);
  Buts->addWidget(export_button_, 2, 0, 1, 0);

  box_layout->addWidget(list_widget_, 2);
  box_layout->addLayout(Buts, 3);
  box->setLayout(box_layout);

  //信号槽连接
  //点击添加按钮时，执行AddStuBox函数
  connect(add_stu_button_, &QPushButton::clicked, this, &MainWidget::AddStuBox);
  //点击删除按钮时，执行DelStuFun函数
  connect(del_stu_button_, &QPushButton::clicked, this, &MainWidget::DeleteStudent);
  //当在查找框中输入学生姓名后，调用FindStuMess函数
  connect(find_stu_edit_, &QLineEdit::returnPressed, this, &MainWidget::FindStuMess);
  //当用户击导出按钮时，执行ExportStuMess函数
  connect(export_button_, &QPushButton::clicked, this, &MainWidget::Export);
  return box;
}
/**
 * \brief 点击add按钮后，创建添加学生信息子窗口
 */
void MainWidget::AddStuBox() {
  /*!
   * 点击添加按钮是，弹出添加信息子窗口
   */
  mess_box_ = new EditStuMessBox(this, sql_);
  mess_box_->setWindowTitle("Add Student");
  //当关闭窗口时，更新表格，同时清除列表中的学生信息
  connect(mess_box_, &EditStuMessBox::CloseBox, this, &MainWidget::FlushTable);
  connect(mess_box_, &EditStuMessBox::CloseBox, list_widget_, &QListWidget::clear);
  mess_box_->exec();
}

/*!
 * \brief 双击表格某一行，进入编辑学生信息界面
 */
void MainWidget::ModifyStuBox(QStringList &list) {
  mess_box_ = new EditStuMessBox(this, sql_);
  mess_box_->setWindowTitle("Modify Student");
  mess_box_->SetModifyMode();
  mess_box_->SetId(list[0]);
  mess_box_->SetStuName(list[1]);
  mess_box_->SetStuGender(list[2]);
  mess_box_->SetStuAge(list[3]);
  //当关闭窗口时，更新表格，同时清除列表中的学生信息
  connect(mess_box_, &EditStuMessBox::CloseBox, this, &MainWidget::FlushTable);
  connect(mess_box_, &EditStuMessBox::CloseBox, list_widget_, &QListWidget::clear);
  mess_box_->exec();
}

/*!
 * @brief 根据页码从数据库中获得数据，刷新学生表单
 */
void MainWidget::FlushTable() {
  CalulateTotalPage();
  //更新表格前，断开cellChange信号所关联的槽
  disconnect(table_widget_, &QTableWidget::cellChanged, nullptr, nullptr);
  auto Students = sql_->SelectPage(current_page_, page_size_);
  table_widget_->setRowCount(0);
  for (auto &stu: Students) {
    table_widget_->setRowCount(table_widget_->rowCount() + 1);
    int row = table_widget_->rowCount() - 1;
    table_widget_->setItem(row, 0, new QTableWidgetItem(stu.GetId()));
    table_widget_->setItem(row, 1, new QTableWidgetItem(stu.GetName()));
    table_widget_->setItem(row, 2, new QTableWidgetItem(stu.GetGender()));
    table_widget_->setItem(row, 3, new QTableWidgetItem(stu.GetAge()));
  }
  //更新表格后，重新设置信号槽
  connect(table_widget_, &QTableWidget::cellChanged, this, &MainWidget::ChangeStuMess);
  connect(table_widget_, &QTableWidget::cellChanged, this, &MainWidget::FlushListWidget);
}
/*!
 * @brief 根据输入页码从数据库中获得数据，刷新学生表单
 */
void MainWidget::FlushTableFromPageNum(int current_page) {
  //防止页码超出范围
  if (current_page == current_page_)
    return;
  if (current_page < 0)
    current_page = 0;
  if (current_page > total_page_)
    current_page = total_page_ - 1;
  //更新页码
  current_page_ = current_page;
  paging_widget_->SetCurrentPage(current_page_);
  FlushTable();
}
/*!
 * @brief 跳转到下一页
 */
void MainWidget::NextPage() {
  if (current_page_ < total_page_) {
    ++current_page_;
    paging_widget_->SetCurrentPage(current_page_);
    FlushTable();
  }
}
/*!
 * @brief 跳转到上一页
 */
void MainWidget::PrevPage() {
  if (current_page_ > 0) {
    --current_page_;
    paging_widget_->SetCurrentPage(current_page_);
    FlushTable();
  }
}
/*!
 * @brief 跳转到第一页
 */
void MainWidget::FirstPage() {
  current_page_ = 0;
  paging_widget_->SetCurrentPage(current_page_);
  FlushTable();
}
/*!
 * @brief 跳转到最后一页
 */
void MainWidget::LastPage() {
  current_page_ = total_page_ - 1;
  paging_widget_->SetCurrentPage(current_page_);
  FlushTable();
}
/**
 * 刷新功能列表
 * @param row
 */
void MainWidget::FlushListWidget(int row) {
  if (list_widget_->count() > 0) {
    list_widget_->item(0)->setText("ID:" + table_widget_->item(row, 0)->text());
    list_widget_->item(1)->setText("Name:" + table_widget_->item(row, 1)->text());
    list_widget_->item(2)->setText("Gender:" + table_widget_->item(row, 2)->text());
    list_widget_->item(3)->setText("Age:" + table_widget_->item(row, 3)->text());
  } else {
    list_widget_->addItem("ID:" + table_widget_->item(row, 0)->text());
    list_widget_->addItem("Name:" + table_widget_->item(row, 1)->text());
    list_widget_->addItem("Gender:" + table_widget_->item(row, 2)->text());
    list_widget_->addItem("Age:" + table_widget_->item(row, 3)->text());
  }
}

/*!
 * \brief 删除选中的学生，并且在数据库中删除
 */
void MainWidget::DeleteStudent() {
  QList<QTableWidgetItem *> items = table_widget_->selectedItems();
  if (!items.empty()) {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Delete", "Do you want to delete  student of [" +
        items.at(0)->text() + "] ?");
    if (result == QMessageBox::Yes) {
      auto id = items.at(0)->text();
      sql_->Delete(id);
      FlushTable();
      list_widget_->clear();
    }
  } else {
    QMessageBox::warning(this, "Warning", "Please select a student!");
  }
}
/**
 * 查询学生
 */
void MainWidget::FindStuMess() {
  QString input = find_stu_edit_->text();
  if (input.isEmpty()) {
    QMessageBox::warning(this, "Warning", "Please input a student id or name!");
    return;
  }
  qint32 count = table_widget_->rowCount();
  bool findSuccess = false;
  if (count > 0) {
    for (qint32 i = 0; i < count; i++) {
      auto id = table_widget_->item(i, 0)->text();
      auto name = table_widget_->item(i, 1)->text();
      if (id == input || name == input) {
        findSuccess = true;
        //设置选中表单，并且更新功能列表显示查询到的学生信息
        table_widget_->selectRow(i);
        FlushListWidget(i);
      }
    }
    if (!findSuccess) {
      QMessageBox::information(this, "Query Failure", "No student found!");
    }
  }
}

/*!
 * \brief 修改表格中学生信息，同时保存到数据库中
 * @param row
 */
void MainWidget::ChangeStuMess(int row) {
  //获得修改后的信息
  QStringList string_list;
  for (int i = 0; i < table_widget_->columnCount(); i++) {
    string_list << table_widget_->item(row, i)->text();
  }
  //更新数据库
  sql_->Update(string_list);
}
/*!
 * \brief 双击表格中学生形象，进入修改界面
 */
void MainWidget::ChangeStuMessItem(QTableWidgetItem *item) {
  //获得修改后的信息
  QStringList string_list;
  for (int i = 0; i < table_widget_->columnCount(); i++) {
    string_list << table_widget_->item(item->row(), i)->text();
  }
  ModifyStuBox(string_list);
}
/*!
 * \brief 导出CSV文件
 */
void MainWidget::Export() {
  //获得所有学生信息
  auto Students = sql_->SelectAll();
  std::ofstream outfile("student.csv", std::ios::out | std::ios::trunc);
  outfile << "ID,Name,Gender,Age" << std::endl;
  for (auto &student: Students) {
    outfile << student.GetInfo();
  }
  outfile.close();
  QMessageBox::information(this, "Success", "CSV file has been export!");
}
/*!
 * @brief 计算更新总页数
 */
void MainWidget::CalulateTotalPage() {
  int total_page = sql_->GetTotalNum() / page_size_ + (sql_->GetTotalNum() % page_size_ == 0 ? 0 : 1);
  //如果总页数改变，则更新总页数，并且将当前页更新为最后一页
  if (this->total_page_ != total_page) {
    this->total_page_ = total_page;
    current_page_ = total_page_ - 1;
    paging_widget_->SetCurrentPage(current_page_);
  }
  paging_widget_->SetInfo(sql_->GetTotalNum(), total_page_);
}