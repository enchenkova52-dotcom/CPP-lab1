#include "Teacher.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

bool Teacher::compareSolutions(const Solution& s1, const Solution& s2) const {
    if (s1.rootCount != s2.rootCount) {
        return false;
    }

    if (s1.rootCount == 0) {
        return true;
    }

    if (s1.rootCount == 1) {
        return std::fabs(s1.x1 - s2.x1) < EPS;
    }

    std::vector<double> roots1 = { s1.x1, s1.x2 };
    std::vector<double> roots2 = { s2.x1, s2.x2 };

    std::sort(roots1.begin(), roots1.end());
    std::sort(roots2.begin(), roots2.end());

    return std::fabs(roots1[0] - roots2[0]) < EPS &&
        std::fabs(roots1[1] - roots2[1]) < EPS;
}

void Teacher::receiveEmail(const Email& email) {
    emailQueue.push(email);
}

void Teacher::checkAllEmails() {
    while (!emailQueue.empty()) {
        Email email = emailQueue.front();
        emailQueue.pop();

        Solution correct = email.equation.solveCorrectly();

        if (compareSolutions(email.studentSolution, correct)) {
            results[email.studentName]++;
        }
    }
}

void Teacher::publishGradeTable() const {
    std::cout << "\n===== Таблица успеваемости =====\n";
    std::cout << std::left << std::setw(20) << "Студент" << std::setw(10) << "Верно" << "\n";
    std::cout << std::string(30, '-') << "\n";

    for (const auto& pair : results) {
        std::cout << std::left << std::setw(20) << pair.first << std::setw(10) << pair.second << "\n";
    }
}

void Teacher::saveGradeTableToFile(const std::string& filename) const {
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }

    fout << "===== Таблица успеваемости =====\n";
    fout << std::left << std::setw(20) << "Студент" << std::setw(10) << "Верно" << "\n";
    fout << std::string(30, '-') << "\n";

    for (const auto& pair : results) {
        fout << std::left << std::setw(20) << pair.first << std::setw(10) << pair.second << "\n";
    }

    fout.close();
}
