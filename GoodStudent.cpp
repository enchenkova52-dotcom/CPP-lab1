#include "GoodStudent.h"

GoodStudent::GoodStudent(const std::string& name)
    : Student(name) {
}

Solution GoodStudent::solve(const QuadraticEquation& eq) {
    return eq.solveCorrectly();
}