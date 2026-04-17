#include "Student.h"

Student::Student(const std::string& name) : name(name) {
}

Student::~Student() {
}

std::string Student::getName() const {
    return name;
}