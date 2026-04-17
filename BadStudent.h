#pragma once

#include "Student.h"

class BadStudent : public Student {
public:
    BadStudent(const std::string& name);
    Solution solve(const QuadraticEquation& eq) override;
};