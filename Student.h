#pragma once

#include <string>
#include "QuadraticEquation.h"
#include "Solution.h"

class Student {
protected:
    std::string name;

public:
    Student(const std::string& name);
    virtual ~Student() = default;

    std::string getName() const;
    virtual Solution solve(const QuadraticEquation& eq) = 0;
};
