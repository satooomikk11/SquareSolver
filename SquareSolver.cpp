#include <stdio.h>
#include <string.h>

#define COLOR_RED   "\033[1;31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

#include "Equation.h"
#include "Input.h"
#include "Solver.h"
#include "Tests.h"

int main(int argc, char *argv[])
    {
    Equation eq = {0, 0, 0, 0, 0, NO_SOLUTIONS};

    if (argc > 1)
        {
        if (strcmp(argv[1], "--self-check") == 0)
            {
            if (argc > 2)
                {
                // testing from another file
                unittest_solvesquare_from_file(argv[2]);
                }
            else
                {
                // testing from tests.txt
                unittest_solvesquare();
                }
            }
        else if (strcmp(argv[1], "--solve") == 0)
            {
            if (entering_coefficients_and_checking(&eq) != 0)
                {
                printf(COLOR_RED "The program is terminated due to an input error.\n" COLOR_RESET);
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
                   "--self-check [file]  performs self-tests (unit-tests)\n"
                   "--solve              solves quadratic equations\n"
                   "--help               shows this help message\n\n");
            }
        }
    else
        {
        unittest_solvesquare();

        if (entering_coefficients_and_checking(&eq) != 0)
            {
            printf(COLOR_RED "The program is terminated due to an input error.\n" COLOR_RESET);
            return 1;
            }

        solve_equation(&eq);
        solution_output(&eq);
        }

    return 0;
    }

