#include "Email.h"

Email::Email(const std::string& name, const QuadraticEquation& eq, const Solution& sol)
    : studentName(name), equation(eq), studentSolution(sol) {
}
