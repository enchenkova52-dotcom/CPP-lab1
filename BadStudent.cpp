#include "BadStudent.h"

BadStudent::BadStudent(const std::string& name)
    : Student(name) {
}

Solution BadStudent::solve(const QuadraticEquation& eq) {
    return Solution(1, 0.0, 0.0);
}