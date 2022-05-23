//
// Created by 10451 on 2022/5/12.
//

#include "student.h"

Student::Student(QString id, QString name, QString age, QString gender) :
    id_(std::move(id)), name_(std::move(name)), age_(std::move(age)), gender_(std::move(gender)) {

}
Student::Student(const Student &stu) {
  this->id_ = stu.id_;
  this->name_ = stu.name_;
  this->gender_ = stu.gender_;
  this->age_ = stu.age_;
}
Student &Student::operator=(const Student &stu) {
  if (this == &stu) {//防止自己赋值自己
    return *this;
  }
  this->id_ = stu.id_;
  this->name_ = stu.name_;
  this->gender_ = stu.gender_;
  this->age_ = stu.age_;
  return *this;
}
Student::Student(Student &&stu) noexcept {
  this->id_ = stu.id_;
  this->name_ = stu.name_;
  this->gender_ = stu.gender_;
  this->age_ = stu.age_;
  //注意
  //由于该函数没有指针参数，因此没有意义。复习
  //如果有指针参数，则需要将当前类的指针指向，参数类的指针，然后将参数类的指针置空
}
Student &Student::operator=(Student &&stu) noexcept {
  if (this == &stu) {//防止自己赋值自己
    return *this;
  }
  this->id_ = stu.id_;
  this->name_ = stu.name_;
  this->gender_ = stu.gender_;
  this->age_ = stu.age_;
  return *this;
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
     << student.age_.toStdString()
     << std::endl;
  return os;
}

std::string Student::GetInfo() {
  std::string
      str = id_.toStdString() + "," + name_.toStdString() + "," + gender_.toStdString() + "," + age_.toStdString();
  return str;
}