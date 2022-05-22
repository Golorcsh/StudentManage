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
  Student(QString id, QString name, QString age, QString gender);
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
