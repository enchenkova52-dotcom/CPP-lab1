#pragma once

#include <queue>
#include <map>
#include <string>
#include "Email.h"
#include "Solution.h"

class Teacher {
private:
    std::queue<Email> emailQueue;
    std::map<std::string, int> results;

    bool compareSolutions(const Solution& s1, const Solution& s2) const;

public:
    void receiveEmail(const Email& email);
    void checkAllEmails();
    void publishGradeTable() const;
    void saveGradeTableToFile(const std::string& filename) const;
};