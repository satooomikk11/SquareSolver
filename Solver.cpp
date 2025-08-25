#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <TXLib.h>

#include "Solver.h"
#include "Input.h"


// choosing type of solution
SolutionType solve_equation(struct Equation *eq)
    {
    assert(eq != NULL);
    if (are_doubles_equal(eq->a, 0))
        {
        eq->type = linear_equation_solver(eq);
        }
    else
        {
        eq->type = square_equation_solver(eq);
        }
    return eq->type;
    }


// solving linear equation
SolutionType linear_equation_solver(struct Equation *eq)
    {
    assert(eq != NULL);
    if (are_doubles_equal(eq->b, 0))
        {
        if (are_doubles_equal(eq->c, 0))
            {
            return INFINITE_SOLUTIONS;
            }
        else
            {
            return NO_SOLUTIONS;
            }
        }
    else
        {
        eq->x1 = -eq->c / eq->b;
        return SINGLE_SOLUTION;
        }
    }


// solving square equation
SolutionType square_equation_solver(struct Equation *eq)
    {
    assert(eq != NULL);
    assert(!are_doubles_equal(eq->a, 0));

    double discriminant = eq->b * eq->b - 4 * eq->a * eq->c;

    if (discriminant > 0)
        {
        eq->x1 = (-eq->b - sqrt(discriminant)) / (2 * eq->a);
        eq->x2 = (-eq->b + sqrt(discriminant)) / (2 * eq->a);
        return TWO_REAL_SOLUTIONS;
        }
    else if (are_doubles_equal(discriminant, 0))
        {
        eq->x1 = -eq->b / (2 * eq->a);
        return SINGLE_SOLUTION_D0;
        }
    else
        {
        return NO_SOLUTIONS;
        }
    }


// print all the solutions
SolutionResult solution_output(const struct Equation *eq)
    {
    assert(eq != NULL);
    switch(eq->type)
        {
        default:
            printf("Wrong solution_type!\n");
            return SOLUTION_INVALID_TYPE;

        case INFINITE_SOLUTIONS:
            printf("Infinite number of solutions.\n");
            break;

        case NO_SOLUTIONS:
            printf("There are no solutions.\n");
            break;

        case SINGLE_SOLUTION:
        case SINGLE_SOLUTION_D0:
            printf("The only solution:\n"
                   "x = %lg\n", eq->x1);
            break;

        case TWO_REAL_SOLUTIONS:
            printf("Two real solutions:\n"
                   "x1 = %lg\n"
                   "x2 = %lg\n", eq->x1, eq->x2);
            break;
        }

    return SOLUTION_SUCCESS;
    }
