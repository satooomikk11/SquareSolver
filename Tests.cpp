#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "Tests.h"
#include "Solver.h"
#include "Input.h"

// swap two doubles
void swap_double(double *a, double *b)
    {
    if (*a > *b)
        {
        double temp = *a;
        *a = *b;
        *b = temp;
        }
    }

 // todo magic numbers
 // todo dont forget asserts
 // todo initialize variables
 // todo split into functions (read testcases, test, print test results)

void unittest_solvesquare_from_file(const char *filename)
    {
    assert(filename != NULL);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        {
        printf("Error: cannot open test file '%s'\n", filename);
        return;
        }

    char line[256] = {0};
    int total_tests = 0;
    int passed_tests = 0;

    printf("Running unit tests from file: %s\n\n", filename);

    while (fgets(line, sizeof(line), file))
        {
        // Skip comments, ...
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r')
            continue;

        // Parsing str
        double a = 0, b = 0, c = 0, expected_x1 = 0, expected_x2 = 0;
        int expected_type;
        char description[100];

        int parsed = sscanf(line, "%lg %lg %lg %d %lg %lg %[^\n]",
                           &a, &b, &c, &expected_type, &expected_x1, &expected_x2, description);

        // Checking number of data
        if (parsed < 6)
            {
            printf("Skipping malformed test: %s", line);
            continue;
            }

        total_tests++;

        Equation eq = {a, b, c, 0.0, 0.0, NO_SOLUTIONS};
        eq.type = solve_equation(&eq);

        bool test_passed = false;

        // Checking type of solution
        if (expected_type != eq.type)
            {
            test_passed = false;
            }
        else
            {
            // Checking solutions
            switch (expected_type)
                {
                case INFINITE_SOLUTIONS:
                case NO_SOLUTIONS:
                    test_passed = true;
                    break;

                case SINGLE_SOLUTION:
                case SINGLE_SOLUTION_D0:
                    test_passed = are_doubles_equal(expected_x1, eq.x1);
                    break;

                case TWO_REAL_SOLUTIONS:
                    {
                    double res1 = eq.x1;
                    double res2 = eq.x2;
                    swap_double(&res1, &res2);

                    double exp1 = expected_x1;
                    double exp2 = expected_x2;
                    swap_double(&exp1, &exp2);

                    test_passed = are_doubles_equal(exp1, res1) &&
                                  are_doubles_equal(exp2, res2);
                    }
                    break;

                default:
                    test_passed = false;
                    break;
                }
            }

        if (test_passed)
            {
            printf("Test passed: ");
            passed_tests++;
            }
        else
            {
            printf("Test failed: ");
            }

        // Print information about test
        if (parsed >= 7)
            {
            printf("%s\n", description);
            }
        else
            {
            printf("a=%.lg, b=%.lg, c=%.lg\n", a, b, c);
            }

        if (!test_passed)
            {
            printf("  Expected: type=%d, roots=(%.lg, %.lg)\n",
                   expected_type, expected_x1, expected_x2);
            printf("  Got:      type=%d, roots=(%.lg, %.lg)\n",
                   eq.type, eq.x1, eq.x2);
            }
        }

    fclose(file);

    printf("\nResult: %d/%d tests passed from %s\n\n",
           passed_tests, total_tests, filename);
    }

void unittest_solvesquare(void)
    {
    // Testing from file
    unittest_solvesquare_from_file("tests.txt");
    }
