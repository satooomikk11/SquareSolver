#ifndef EQUATION_H
#define EQUATION_H

enum SolutionResult
    {
    SOLUTION_SUCCESS = 0,
    SOLUTION_INVALID_TYPE = 1
    };

enum SolutionType
    {
    INFINITE_SOLUTIONS = 0,
    NO_SOLUTIONS = 1,
    SINGLE_SOLUTION = 2,
    TWO_REAL_SOLUTIONS = 3,
    SINGLE_SOLUTION_D0 = 4
    };

struct Equation
    {
    double a;
    double b;
    double c;
    double x1;
    double x2;
    SolutionType type;
    };

#endif // EQUATION_H
