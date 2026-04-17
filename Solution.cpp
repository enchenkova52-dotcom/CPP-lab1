#include "Solution.h"

Solution::Solution() : rootCount(0), x1(0.0), x2(0.0) {
}

Solution::Solution(int count, double r1, double r2)
    : rootCount(count), x1(r1), x2(r2) {
}