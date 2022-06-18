//
// Created by 10451 on 2022/5/12.
//

#ifndef STUDENTMANAGE_SRC_EDITSTUMESSBOX_H_
#define STUDENTMANAGE_SRC_EDITSTUMESSBOX_H_
#include "../Config/common.h"
#include "../Sql//msql.h"
#include "../Student/student.h"
#include <QDataStream>
#include <QFile>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class EditStuMessBox : public QDialog {
  Q_OBJECT
public:
  explicit EditStuMessBox(QWidget *parent, M_Sql *sql);
  ~EditStuMessBox() override;

  [[nodiscard]] QString GetStuName() const;
  void SetStuName(const QString &name);
  [[nodiscard]] QString GetStuAge() const;
  void SetStuAge(const QString &age);
  [[nodiscard]] QString GetStuGender() const;
  void SetStuGender(const QString &gender);
  void SetId(const QString &id);
  void SetModifyMode();

signals:
  // 自定义信号,添加学生信息后，发送信号，更新主界面的表格
  void CloseBox();

public slots:
  // 自定义槽
  // 将新学生的信息写入到数据库中
  void SaveStuMessToDB();
  // 更新学生信息
  void UpDateStuMessToDB();

private:
  QLineEdit *stu_name_;
  QLineEdit *stu_age_;
  QLineEdit *stu_gender_;
  QPushButton *submit_;

private:
  QPushButton *cancel_;
  M_Sql *sql_;
  QString id_;
  bool isAdd_;
};
#endif // STUDENTMANAGE_SRC_EDITSTUMESSBOX_H_
