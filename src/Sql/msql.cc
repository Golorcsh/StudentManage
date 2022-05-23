//
// Created by 10451 on 2022/5/15.
//

#include "msql.h"
M_Sql::M_Sql() {
  Init();
  total_num_ = SelectCount();
}

M_Sql::~M_Sql() {
  if (query_) {
    delete query_;
    query_ = nullptr;
  }
  db.close();
}
/*!
 * \brief 初始化数据库
 */
void M_Sql::Init() {
  QFileInfo file(dbname);
  if (!file.exists()) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    query_ = new QSqlQuery(db);
    if (!db.open()) {
      qDebug() << "open database failed";
      return;
    }
    QString create_table = ""
                           "CREATE TABLE IF NOT EXISTS student("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "name VARCHAR(20),"
                           "gender VARCHAR(20),"
                           "age INTEGER)";
    query_->exec(create_table);
    query_->clear();
  } else {
    if (!db.isOpen()) {
      if (db.contains(dbname)) {
        db = QSqlDatabase::database(dbname);
      } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
      }
      db.setDatabaseName(dbname);
      query_ = new QSqlQuery(db);
    }
  }
  db.close();
}
/*!
 * \brief 插入学生信息到数据库
 * \param list 学生信息
 * \return 是否插入成功
 */
bool M_Sql::Insert(QStringList &list) {
  if (list.size() != 3) {
    return false;
  }
  if (!db.open()) {
    qDebug() << "open database failed";
    return false;
  }
  auto insert_cmd =
      QString("INSERT INTO student(name,gender,age) VALUES('%1','%2','%3')").arg(list[0], list[1], list[2]);
  query_->exec("begin;");
  query_->exec(insert_cmd);
  query_->exec("commit;");
  bool isSuccess = query_->isActive();
  query_->clear();
  ++total_num_;
  return isSuccess;
}
/*!
 * \brief 插入学生信息到数据库
 * \param stu 学生信息
 * \return 是否插入成功
 */
bool M_Sql::Insert(Student &stu) {
  if (!db.open()) {
    qDebug() << "open database failed";
    return false;
  }
  auto insert_cmd =
      QString("INSERT INTO student(name,gender,age) VALUES('%1','%2','%3')").arg(stu.GetName(),
                                                                                 stu.GetGender(),
                                                                                 stu.GetAge());
  query_->exec("begin;");
  query_->exec(insert_cmd);
  query_->exec("commit;");
  bool isSuccess = query_->isActive();
  query_->clear();
  ++total_num_;
  return isSuccess;
}
/*!
 * \brief 通id删除学生数据
 * @param id
 * @return
 */
bool M_Sql::Delete(QString &id) {
  if (id.isEmpty()) {
    return false;
  }
  if (!db.open()) {
    qDebug() << "open database failed";
    return false;
  }
  auto delete_cmd = QString("DELETE FROM student WHERE id='%1'").arg(id);
  query_->exec("begin;");
  query_->exec(delete_cmd);
  query_->exec("commit;");
  bool isSuccess = query_->isActive();
  query_->clear();
  --total_num_;
  return isSuccess;
}
/*!
 * \brief 更新学生数据
 * @param id
 * @param list
 * @return
 */
bool M_Sql::Update(QStringList &list) {
  if (list.size() != 4) {
    return false;
  }
  if (!db.open()) {
    qDebug() << "open database failed";
    return false;
  }
  auto update_cmd =
      QString("UPDATE student SET name='%2',gender='%3',age='%4' where id='%1'").arg(list[0],
                                                                                     list[1],
                                                                                     list[2],
                                                                                     list[3]);
  query_->exec("begin;");
  query_->exec(update_cmd);
  query_->exec("commit;");
  bool isSuccess = query_->isActive();
  query_->clear();
  return isSuccess;
}
Student M_Sql::Select(int id) {
  if (!db.open()) {
    qDebug() << "open database failed";
    return {};
  }
  auto select_cmd =
      QString("select * from student where id='%1'").arg(id);
  query_->exec(select_cmd);
  while (query_->next()) {
    Student student;
    student.SetId(query_->value(0).toString());
    student.SetName(query_->value(1).toString());
    student.SetGender(query_->value(2).toString());
    student.SetAge(query_->value(3).toString());
    query_->clear();
    return student;
  }
  query_->clear();
  return {};
}
/*!
 * \brief 查询所有学生数据
 * @return
 */
std::vector<Student> M_Sql::SelectAll() {
  if (!db.open()) {
    qDebug() << "open database failed";
    return {};
  }
  auto select_cmd = QString("SELECT * FROM student");
  query_->exec(select_cmd);
  std::vector<Student> students;
  while (query_->next()) {
    Student student;
    student.SetId(query_->value(0).toString());
    student.SetName(query_->value(1).toString());
    student.SetGender(query_->value(2).toString());
    student.SetAge(query_->value(3).toString());
    students.emplace_back(student);
  }
  query_->clear();
  return students;
}
/*!
 * \brief 查询学生数据数量
 * @return
 */
int M_Sql::SelectCount() {
  if (!db.open()) {
    qDebug() << "open database failed";
    return 0;
  }
  auto select_cmd = QString("SELECT count(*) FROM student");
  query_->exec(select_cmd);
  int count = 0;
  while (query_->next()) {
    count = query_->value(0).toInt();
  }
  query_->clear();
  return count;
}
int M_Sql::GetTotalNum() const {
  return total_num_;
}
/*!
 * \brief 通过页码查询学生数据
 * @param page
 * @param page_size
 * @return
 */
std::vector<Student> M_Sql::SelectPage(int page, int page_size) {
  if (!db.open()) {
    qDebug() << "open database failed";
    return {};
  }
  auto select_cmd = QString("SELECT * FROM student LIMIT %1,%2").arg(page * page_size).arg(page_size);
  query_->exec(select_cmd);
  std::vector<Student> students;
  while (query_->next()) {
    Student student;
    student.SetId(query_->value(0).toString());
    student.SetName(query_->value(1).toString());
    student.SetGender(query_->value(2).toString());
    student.SetAge(query_->value(3).toString());
    students.emplace_back(student);
  }
  query_->clear();
  return students;
}
/*!
 * 查询当前id所在的位置
 * @param id
 * @return
 */
int M_Sql::SelectPosition(int id) {
  if (!db.open()) {
    qDebug() << "open database failed";
    return 0;
  }
  auto select_cmd = QString("SELECT count(*) FROM student where id<'%1'").arg(id);
  query_->exec(select_cmd);
  int count = -1;
  while (query_->next()) {
    count = query_->value(0).toInt();
  }
  query_->clear();
  return count;
}
