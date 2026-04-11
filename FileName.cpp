#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <cmath>
#include <iomanip>
#include <memory>
#include <random>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;


struct Solution {
    int rootCount;   
    double x1;
    double x2;

    Solution(int count = 0, double r1 = 0, double r2 = 0)
        : rootCount(count), x1(r1), x2(r2) {
    }
};


class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }

    Solution solveCorrectly() const {
        double d = b * b - 4 * a * c;

        if (d < -EPS) {
            return Solution(0, 0, 0);
        }
        else if (fabs(d) < EPS) {
            double x = -b / (2 * a);
            return Solution(1, x, x);
        }
        else {
            double sqrtD = sqrt(d);
            double x1 = (-b - sqrtD) / (2 * a);
            double x2 = (-b + sqrtD) / (2 * a);

            if (x1 > x2) {
                swap(x1, x2);
            }

            return Solution(2, x1, x2);
        }
    }

    string toString() const {
        return to_string(a) + "x^2 + " + to_string(b) + "x + " + to_string(c) + " = 0";
    }
};


struct Email {
    string studentName;
    QuadraticEquation equation;
    Solution studentSolution;

    Email(const string& name, const QuadraticEquation& eq, const Solution& sol)
        : studentName(name), equation(eq), studentSolution(sol) {
    }
};


class Student {
protected:
    string name;

public:
    Student(const string& name) : name(name) {}
    virtual ~Student() = default;

    string getName() const {
        return name;
    }

    virtual Solution solve(const QuadraticEquation& eq) = 0;
};


class GoodStudent : public Student {
public:
    GoodStudent(const string& name) : Student(name) {}

    Solution solve(const QuadraticEquation& eq) override {
        return eq.solveCorrectly();
    }
};


class AverageStudent : public Student {
private:
    double probabilityCorrect;
    mt19937 gen;
    uniform_real_distribution<> dist;

public:
    AverageStudent(const string& name, double prob = 0.6)
        : Student(name), probabilityCorrect(prob), dist(0.0, 1.0) {
        random_device rd;
        gen.seed(rd());
    }

    Solution solve(const QuadraticEquation& eq) override {
        double p = dist(gen);

        if (p <= probabilityCorrect) {
            return eq.solveCorrectly();
        }
        else {
            // ошибоч реш
            return Solution(1, 0, 0);
        }
    }
};


class BadStudent : public Student {
public:
    BadStudent(const string& name) : Student(name) {}

    Solution solve(const QuadraticEquation& eq) override {
        return Solution(1, 0, 0);
    }
};


class Teacher {
private:
    queue<Email> emailQueue;
    map<string, int> results;

    bool compareSolutions(const Solution& s1, const Solution& s2) const {
        if (s1.rootCount != s2.rootCount) {
            return false;
        }

        if (s1.rootCount == 0) {
            return true;
        }

        if (s1.rootCount == 1) {
            return fabs(s1.x1 - s2.x1) < EPS;
        }

        vector<double> roots1 = { s1.x1, s1.x2 };
        vector<double> roots2 = { s2.x1, s2.x2 };

        sort(roots1.begin(), roots1.end());
        sort(roots2.begin(), roots2.end());

        return fabs(roots1[0] - roots2[0]) < EPS &&
            fabs(roots1[1] - roots2[1]) < EPS;
    }

public:


        void receiveEmail(const Email& email) {
        emailQueue.push(email);
    }

    void checkAllEmails() {
        while (!emailQueue.empty()) {
            Email email = emailQueue.front();
            emailQueue.pop();

            Solution correct = email.equation.solveCorrectly();

            if (compareSolutions(email.studentSolution, correct)) {
                results[email.studentName]++;
            }
        }
    }

    void publishGradeTable() const {
        cout << "\n===== Таблица успеваемости =====\n";
        cout << left << setw(20) << "Студент" << setw(10) << "Верно" << "\n";
        cout << string(30, '-') << "\n";

        for (const auto& pair : results) {
            cout << left << setw(20) << pair.first << setw(10) << pair.second << "\n";
        }
    }

    void saveGradeTableToFile(const string& filename) const {
        ofstream fout(filename);

        if (!fout.is_open()) {
            cerr << "Ошибка: не удалось открыть файл для записи: " << filename << endl;
            return;
        }

        fout << "===== Таблица успеваемости =====\n";
        fout << left << setw(20) << "Студент" << setw(10) << "Верно" << "\n";
        fout << string(30, '-') << "\n";

        for (const auto& pair : results) {
            fout << left << setw(20) << pair.first << setw(10) << pair.second << "\n";
        }

        fout.close();
    }
};


vector<QuadraticEquation> readEquationsFromFile(const string& filename) {
    vector<QuadraticEquation> equations;
    ifstream fin(filename);

    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return equations;
    }

    double a, b, c;
    while (fin >> a >> b >> c) {
        if (fabs(a) < EPS) {
            cerr << "Пропущено уравнение: коэффициент a не должен быть 0\n";
            continue;
        }

        equations.emplace_back(a, b, c);
    }

    fin.close();
    return equations;
}


int main() {
    

    vector<QuadraticEquation> equations = readEquationsFromFile("equations.txt");

    if (equations.empty()) {
        cout << "Нет уравнений для обработки.\n";
        return 0;
    }

    vector<unique_ptr<Student>> students;
    students.push_back(make_unique<GoodStudent>("Иван"));
    students.push_back(make_unique<AverageStudent>("Мария", 0.7));
    students.push_back(make_unique<AverageStudent>("Олег", 0.5));
    students.push_back(make_unique<BadStudent>("Петр"));

    Teacher teacher;

    
    for (const auto& eq : equations) {
        for (const auto& student : students) {
            Solution sol = student->solve(eq);
            Email email(student->getName(), eq, sol);
            teacher.receiveEmail(email);
        }
    }

    
    teacher.checkAllEmails();

    
    teacher.publishGradeTable();

   
    teacher.saveGradeTableToFile("results.txt");
    cout << "\nРезультаты сохранены в файл results.txt\n";

    return 0;
}
