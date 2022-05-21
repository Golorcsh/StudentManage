//
// Created by 10451 on 2022/5/12.
//

#ifndef STUDENTMANAGE_SRC_MAINWIDGET_H_
#define STUDENTMANAGE_SRC_MAINWIDGET_H_

#include <QWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../EditStuMessBox/editstumessbox.h"
#include "../Config/common.h"
#include "../Sql/msql.h"

class MainWidget : public QWidget {
 Q_OBJECT
 public:
  MainWidget();
  ~MainWidget() override;
  void AddStuBox();
  void ModifyStuBox(QStringList &list);
 public slots:
  void FlushTable();
  void FlushListWidget(int row);
  void DeleteStudent();
  void FindStuMess();
  void ChangeStuMessItem(QTableWidgetItem *item);
  void ChangeStuMess(int row);

 private:
  QGroupBox *CreateStuMess();
  QGroupBox *CreateMenu();

 private:
  //主窗口学生面板
  QTableWidget *table_widget_{};
  //主窗口功能面板
  QListWidget *list_widget_{};
  //主窗口添加、删除、保存、修改学生按钮
  QPushButton *add_stu_button_{};
  QPushButton *del_stu_button_{};
  QLineEdit *find_stu_edit_{};

  EditStuMessBox *mess_box_{};

  M_Sql *sql_;
};

#endif //STUDENTMANAGE_SRC_MAINWIDGET_H_
