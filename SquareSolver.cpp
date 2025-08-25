#include <stdio.h>
#include <string.h>

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
                // Запуск тестов из указанного файла
                unittest_solvesquare_from_file(argv[2]);
                }
            else
                {
                // Запуск тестов из файла по умолчанию
                unittest_solvesquare();
                }
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
                   "--self-check [file]  performs self-tests (unit-tests)\n"
                   "--solve              solves quadratic equations\n"
                   "--help               shows this help message\n\n");
            }
        }
    else
        {
        // Режим по умолчанию: сначала тесты, потом решение
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

