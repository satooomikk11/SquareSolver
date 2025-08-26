#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Equation.h"
#include "Input.h"
#include "Solver.h"
#include "Tests.h"
#include "doubles.h"
#include "define_colors.h"


// ask again
int ask_to_run_again()
    {
    printf("\nDo you want to solve another equation? (Y/N): ");

    char response[10];
    if (fgets(response, sizeof(response), stdin) != NULL)
        {
        // check first char
        char first_char = toupper(response[0]);
        return (first_char == 'Y');
        }

    return 0; // if input not Y don't run again
    }


// solving
void solve_equation_loop()
    {
    Equation eq = {0, 0, 0, 0, 0, NO_SOLUTIONS};
    int input_result = entering_coefficients_and_checking(&eq);

    if (input_result != 0)
        {
        printf(COLOR_RED "The program is terminated due to an input error.\n" COLOR_RESET);
        }
    else
        {
        solve_equation(&eq);
        solution_output(&eq);
        }
    }


int main(int argc, char *argv[])
    {
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
            return 0;
            }
        else if (strcmp(argv[1], "--help") == 0)
            {
            printf("BRIEF DESCRIPTION\n\n"
                   "the program solves quadratic equations\n\n\n"
                   "DETAILED DESCRIPTION\n\n"
                   "--self-check [file]  performs self-tests (unit-tests)\n"
                   "--solve              solves quadratic equations\n"
                   "--help               shows this help message\n\n");
            return 0;
            }
        else if (strcmp(argv[1], "--solve") == 0)
            {
            // for running again
            while (ask_to_run_again())
                {
                solve_equation_loop();
                }

            return 0;
            }
        }

    unittest_solvesquare();

    while (ask_to_run_again())
        {
        solve_equation_loop();
        }

    return 0;
    }
