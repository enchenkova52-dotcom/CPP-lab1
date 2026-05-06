#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "Constants.h"
#include "QuadraticEquation.h"
#include "GoodStudent.h"
#include "AverageStudent.h"
#include "BadStudent.h"
#include "Teacher.h"
#include "Email.h"

std::vector<QuadraticEquation> readEquationsFromFile(const std::string& filename) {
    std::vector<QuadraticEquation> equations;
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return equations;
    }

    double a, b, c;
    while (fin >> a >> b >> c) {
        if (std::fabs(a) < EPS) {
            std::cerr << "Пропущено уравнение: коэффициент a не должен быть 0\n";
            continue;
        }

        equations.emplace_back(a, b, c);
    }

    fin.close();
    return equations;
}

int main() {
    std::vector<QuadraticEquation> equations = readEquationsFromFile("equations.txt");

    if (equations.empty()) {
        std::cout << "Нет уравнений для обработки.\n";
        return 0;
    }

    GoodStudent ivan("Иван");
    AverageStudent maria("Мария", 0.7);
    AverageStudent oleg("Олег", 0.5);
    BadStudent petr("Петр");

    std::vector<Student*> students = { &ivan, &maria, &oleg, &petr };

    Teacher teacher;

    for (const auto& eq : equations) {
        for (Student* student : students) {
            Solution sol = student->solve(eq);
            Email email(student->getName(), eq, sol);
            teacher.receiveEmail(email);
        }
    }

    teacher.checkAllEmails();
    teacher.publishGradeTable();
    teacher.saveGradeTableToFile("results.txt");

    std::cout << "\nРезультаты сохранены в файл results.txt\n";

    return 0;
}
