//
// Created by 10451 on 2022/5/12.
//

#ifndef STUDENTMANAGE_SRC_STUDENT_H_
#define STUDENTMANAGE_SRC_STUDENT_H_
#include <QString>
#include <ostream>
class Student {
 public:
  Student() = default;
  //带参构造函数
  Student(QString id, QString name, QString age, QString gender);
  //拷贝构造
  Student(const Student &stu);
  //拷贝赋值
  Student &operator=(const Student &stu);
  //移动构造
  Student(Student &&stu) noexcept ;
  //移动赋值
  Student &operator=(Student &&stu) noexcept;
  //析构函数
  ~Student() = default;

  friend std::ostream &operator<<(std::ostream &os, const Student &student);

  [[nodiscard]] const QString &GetId() const;
  void SetId(const QString &id);
  [[nodiscard]] const QString &GetName() const;
  void SetName(const QString &name);
  [[nodiscard]] const QString &GetGender() const;
  void SetGender(const QString &gender);
  [[nodiscard]] const QString &GetAge() const;
  void SetAge(const QString &age);
  std::string GetInfo();
 private:
  QString id_;
  QString name_;
  QString gender_;
  QString age_;
};

#endif //STUDENTMANAGE_SRC_STUDENT_H_
