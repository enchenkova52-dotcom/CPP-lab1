#include "AverageStudent.h"

AverageStudent::AverageStudent(const std::string& name, double prob)
    : Student(name), probabilityCorrect(prob), dist(0.0, 1.0) {
    std::random_device rd;
    gen.seed(rd());
}

Solution AverageStudent::solve(const QuadraticEquation& eq) {
    double p = dist(gen);

    if (p <= probabilityCorrect) {
        return eq.solveCorrectly();
    }
    else {
        return Solution(1, 0.0, 0.0);
    }
}