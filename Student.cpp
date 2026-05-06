#include "Student.h"

Student::Student(const std::string& name) : name(name) {
}

std::string Student::getName() const {
    return name;
}
