//
// Created by 10451 on 2022/5/12.
//

#ifndef STUDENTMANAGE_SRC_MAINWIDGET_H_
#define STUDENTMANAGE_SRC_MAINWIDGET_H_

#include "../Config/common.h"
#include "../EditStuMessBox/editstumessbox.h"
#include "../PagingWidget/pagingwidget.h"
#include "../Sql/msql.h"
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <fstream>
#include <set>

class MainWidget : public QWidget {
  Q_OBJECT
public:
  MainWidget();
  ~MainWidget() override;

private:
  void CalulateTotalPage();
  void AddStuBox();
  void ModifyStuBox(QStringList &list);
public slots:
  void FlushTable();
  void FlushTableFromPageNum(int current_page);
  void FirstPage();
  void PrevPage();
  void NextPage();
  void LastPage();
  void PageSizeChanged(int page_size);
  void FlushListWidget(int row);
  void DeleteStudent();
  void FindStuMess();
  void ChangeStuMessItem(QTableWidgetItem *item);
  void Export();
  void Import();

private:
  QGroupBox *CreateStuMess(int page_size);
  QGroupBox *CreateMenu();

private:
  // 分页参数
  int total_page_{};
  int current_page_{};
  int page_size_{};
  int total_num_{};
  // 主窗口学生面板
  QTableWidget *table_widget_{};
  PagingWidget *paging_widget_{};
  // 主窗口功能面板
  QListWidget *list_widget_{};
  // 主窗口添加、删除,导出按钮
  QPushButton *add_stu_button_{};
  QPushButton *del_stu_button_{};
  QPushButton *export_button_{};
  QPushButton *import_button_{};
  QLineEdit *find_stu_edit_{};

  EditStuMessBox *mess_box_{};

  M_Sql *sql_{};
};

#endif // STUDENTMANAGE_SRC_MAINWIDGET_H_
