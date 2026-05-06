#pragma once

#include "Solution.h"

class QuadraticEquation {
private:
    double a;
    double b;
    double c;

public:
    QuadraticEquation(double a, double b, double c);

    Solution solveCorrectly() const;
};
