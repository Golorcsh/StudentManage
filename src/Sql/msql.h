//
// Created by 10451 on 2022/5/15.
//

#ifndef STUMANAGE_SRC_SQL_MSQL_H_
#define STUMANAGE_SRC_SQL_MSQL_H_
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include<QFileInfo>
#include<vector>
#include "../Config/common.h"
#include "../Student/student.h"
class M_Sql {
 public:
  M_Sql();
  ~M_Sql();
  bool Insert(QStringList &list);
  bool Delete(QString &id);
  bool Update(QStringList &list);
  Student Select(int id);
  std::vector<Student> SelectAll();
 private:
  void Init();
  QSqlDatabase db;
  QSqlQuery *query_;
};

#endif //STUMANAGE_SRC_SQL_MSQL_H_
