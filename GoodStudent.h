#pragma once

#include "Student.h"

class GoodStudent : public Student {
public:
    GoodStudent(const std::string& name);
    Solution solve(const QuadraticEquation& eq) override;
};
