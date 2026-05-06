#include "QuadraticEquation.h"
#include "Constants.h"

#include <cmath>
#include <algorithm>

QuadraticEquation::QuadraticEquation(double a, double b, double c)
    : a(a), b(b), c(c) {
}

Solution QuadraticEquation::solveCorrectly() const {
    double d = b * b - 4 * a * c;

    if (d < -EPS) {
        return Solution(0, 0.0, 0.0);
    }
    else if (std::fabs(d) < EPS) {
        double x = -b / (2 * a);
        return Solution(1, x, x);
    }
    else {
        double sqrtD = std::sqrt(d);
        double x1 = (-b - sqrtD) / (2 * a);
        double x2 = (-b + sqrtD) / (2 * a);

        if (x1 > x2) {
            std::swap(x1, x2);
        }

        return Solution(2, x1, x2);
    }
}
