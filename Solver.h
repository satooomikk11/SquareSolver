#ifndef SOLVER_H
#define SOLVER_H

#include "Equation.h"

SolutionType solve_equation(struct Equation *eq);
SolutionType linear_equation_solver(struct Equation *eq);
SolutionType square_equation_solver(struct Equation *eq);
SolutionResult solution_output(const struct Equation *eq);

#endif // SILVER_H
