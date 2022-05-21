//
// Created by 10451 on 2022/5/12.
//

#include "student.h"

Student::Student(QString id, QString name, QString age, QString gender) :
    id_(std::move(id)), name_(std::move(name)), age_(std::move(age)), gender_(std::move(gender)) {

}

const QString &Student::GetId() const {
  return id_;
}
void Student::SetId(const QString &id) {
  id_ = id;
}
const QString &Student::GetName() const {
  return name_;
}
void Student::SetName(const QString &name) {
  name_ = name;
}
const QString &Student::GetGender() const {
  return gender_;
}
void Student::SetGender(const QString &gender) {
  gender_ = gender;
}
const QString &Student::GetAge() const {
  return age_;
}
void Student::SetAge(const QString &age) {
  age_ = age;
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
  os << "id_: " << student.id_.toStdString() << " name_: " << student.name_.toStdString() << " gender_: "
     << student.gender_.toStdString()
     << " age_: "
     << student.age_.toStdString();
  return os;
}

