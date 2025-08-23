#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <TXLib.h>

#include "wtf.h"

const double MIN_DIFF = 1e-10;

// enum declaration
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


// EQUATION STRUCTURE
struct Equation
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    SolutionType type;
};


// function declaration
int are_doubles_equal(double a, double b);
void swap_double(double *a, double *b);

int check_extra_chars(void);
int entering_coefficients_and_checking(struct Equation *eq);

SolutionResult solution_output(const struct Equation *eq);
SolutionType solve_equation(struct Equation *eq);
SolutionType linear_equation_solver(struct Equation *eq);
SolutionType square_equation_solver(struct Equation *eq);

void unittest_solvesquare(void);


int main(int argc, char *argv[])
{
    Equation eq = {0, 0, 0, 0, 0, NO_SOLUTIONS}; // initialization

    if (argc != 1)
    {
        if (strcmp(argv[1], "--self-check") == 0)
        {
            unittest_solvesquare();
        }

        else if (strcmp(argv[1], "--solve") == 0)
        {
            if (entering_coefficients_and_checking(&eq) != 0)
            {
                printf("The program is terminated due to an input error.\n");
                return 1;
            }

            solve_equation(&eq);
            solution_output(&eq);
        }

        else if(strcmp(argv[1], "--help") == 0)
        {
            printf("BRIEF DESCRIPTION\n\n"
                   "the program solves quadratic equations\n\n\n"
                   "DETAILED DESCRIPTION\n\n"
                   "--self-check performs self-tests (unit-tests)\n"
                   "--solve solves quadratic equations\n\n");
        }
    }

    else
    {
        Equation eq = {0, 0, 0, 0, 0, NO_SOLUTIONS}; // initialization

        // UNITTESTING DED
        unittest_solvesquare();

        if (entering_coefficients_and_checking(&eq) != 0)
        {
            printf("The program is terminated due to an input error.\n");
            return 1;
        }

        solve_equation(&eq);
        solution_output(&eq);
    }

    return 0;
}


int are_doubles_equal(double a, double b)
{
    return fabs(a - b) < MIN_DIFF;
}


void swap_double(double *a, double *b)
{
    if (*a > *b) {
        double temp = *a;
        *a = *b;
        *b = temp;
    }
}


int check_extra_chars(void)
{
    int next_char = 0;
    while ((next_char = getchar()) != '\n' && next_char != EOF)
    {
        if (!isspace(next_char))
        {
            printf("Error: extra characters found after three numbers!\n");
            return 1;
        }
    }
    return 0;
}



int entering_coefficients_and_checking(struct Equation *eq)
{
    assert(eq != NULL);
    printf("Enter the coefficients a, b and c: ");

    int read_count = scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c);
    if (read_count != 3)
    {
        printf("Error: you need to enter three numbers!\n");
        return 1;
    }

    // NaN checking
    if (isnan(eq->a) || isnan(eq->b) || isnan(eq->c))
    {
        printf("Error: the NaN value is entered!\n");
        return 1;
    }

    return check_extra_chars();
}



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


// TESTING SOS SOS SOS
void unittest_solvesquare(void)
{
    struct TestCase // Structure for testing
    {
        double a, b, c;
        SolutionType expected_type;
        double expected_x1;
        double expected_x2;
        const char* description;
    };

    struct TestCase tests[] = {
        // 2 solutions
        {1, -3,  2, TWO_REAL_SOLUTIONS,  1.0, 2.0,  "Two solutions:  x*82 - 3x + 2 = 0"},
        {2,  5, -3, TWO_REAL_SOLUTIONS, -3.0, 0.5,  "Two solutions: 2x**2 + 5x - 3 = 0"},

        // 1 solution
        {1, -4, 4, SINGLE_SOLUTION_D0,  2.0,  2.0, "One solution:   x**2 - 4x + 4 = 0"},
        {4,  4, 1, SINGLE_SOLUTION_D0, -0.5, -0.5, "One solution:  4x**2 + 4x + 1 = 0"},

        // 0 solutions
        {1, 0, 1, NO_SOLUTIONS, 0, 0, "No solutions:   x**2 + 1 = 0"},
        {2, 2, 3, NO_SOLUTIONS, 0, 0, "No solutions:  2x**2 + 2x + 3 = 0"},

        // a = 0
        {0, 2, -4, SINGLE_SOLUTION,    2.0, 2.0, "Linear:        2x - 4 = 0"},
        {0, 0,  5, NO_SOLUTIONS,         0,   0, "No solutions:       5 = 0"},
        {0, 0,  0, INFINITE_SOLUTIONS,   0,   0, "Inf solutions:      0 = 0"},
        {0, 3,  0, SINGLE_SOLUTION,    0.0, 0.0, "Linear:        3x = 0"},

        // b, c = 0
        {1, 0, -4, TWO_REAL_SOLUTIONS, -2.0, 2.0, "b = 0:          x**2 - 4 = 0"},
        {1, 0,  0, SINGLE_SOLUTION_D0,  0.0, 0.0, "b = 0, c = 0:   x**2 = 0"}
    };

    // Sizeof - operator, size in bytes
    int total_tests = sizeof(tests) / sizeof(tests[0]); // Counting number of tests
    int passed_tests = 0;

    printf("Running unit tests for SolverSquare():\n\n");

    for (int i = 0; i < total_tests; i++)
    {
        // Always put new test in structure
        TestCase test = tests[i];
        // Ñoefficients
        Equation eq = {test.a, test.b, test.c};

        eq.type = solve_equation(&eq);

        bool test_passed = false;

        // Testing type of solution
        if (test.expected_type != eq.type)
        {
            test_passed = false;
        }
        else
        {
            // Testing solutions
            switch (test.expected_type)
            {
                default:
                    test_passed = false;
                    break;
                case INFINITE_SOLUTIONS:
                case NO_SOLUTIONS:
                    test_passed = true;
                    break;

                case SINGLE_SOLUTION:
                case SINGLE_SOLUTION_D0:
                    test_passed = are_doubles_equal(test.expected_x1, eq.x1);
                    break;

                case TWO_REAL_SOLUTIONS:
                    // Sorting for comparing the solutions
                    double res1 = eq.x1;
                    double res2 = eq.x2;
                    swap_double(&res1, &res2);

                    double exp1 = test.expected_x1;
                    double exp2 = test.expected_x2;
                    swap_double(&exp1, &exp2);

                    test_passed = are_doubles_equal(exp1, res1) &&
                                  are_doubles_equal(exp2, res2);
                    break;
            }
        }

        if (test_passed)
        {

        printf("Test passed: %s\n", test.description);
            passed_tests++;
        }
        else
        {
            printf("ERROR: SolverSquare(%.lg, %.lg, %.lg) ", test.a, test.b, test.c);
            printf("returned type %d, roots: x1=%.lg, x2=%.lg ", eq.type, eq.x1, eq.x2);
            printf("(expected type %d, roots: x1=%.lg, x2=%.lg)\n",
                   test.expected_type, test.expected_x1, test.expected_x2);
            printf("  Description: %s\n", test.description);
        }
    }

    printf("Result: %d/%d tests passed\n\n\n", passed_tests, total_tests);
}
