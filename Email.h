#pragma once

#include <string>
#include "QuadraticEquation.h"
#include "Solution.h"

struct Email {
    std::string studentName;
    QuadraticEquation equation;
    Solution studentSolution;

    Email(const std::string& name, const QuadraticEquation& eq, const Solution& sol);
};
