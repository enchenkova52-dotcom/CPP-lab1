#pragma once

#include "Student.h"
#include <random>

class AverageStudent : public Student {
private:
    double probabilityCorrect;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;

public:
    AverageStudent(const std::string& name, double prob = 0.6);
    Solution solve(const QuadraticEquation& eq) override;
};