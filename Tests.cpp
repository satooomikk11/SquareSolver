#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_RED   "\033[1;31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

#include "Tests.h"
#include "Solver.h"
#include "Input.h"

const int MAX_LINE_LENGTH = 256;
const int MAX_DESCRIPTION_LENGTH = 100;
const char* TEST_FILENAME = "tests.txt";

// swap two doubles
void swap_double(double *a, double *b)
    {
    assert(a != NULL);
    assert(b != NULL);

    if (*a > *b)
        {
        double temp = *a;
        *a = *b;
        *b = temp;
        }
    }

// read test cases from file and put into a dynamic array
TestData* read_test_cases(const char *filename, int *test_count)
    {
    assert(filename != NULL);
    assert(test_count != NULL);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        {
        printf(COLOR_RED "Error: cannot open test file '%s'\n" COLOR_RESET, filename);
        *test_count = 0;
        return NULL;
        }

    // count - number of test cases
    char line[MAX_LINE_LENGTH] = {0};
    int count = 0;

    while (fgets(line, sizeof(line), file))
        {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
        int type = 0;
        char description[MAX_DESCRIPTION_LENGTH] = {0};

        int parsed = sscanf(line, "%lg %lg %lg %d %lg %lg %[^\n]",
                            &a, &b, &c, &type, &x1, &x2, description);

        if (parsed >= 6)
            count++;
        }

    // for second reading of the file
    rewind(file);

    // get memory for test cases
    TestData *test_data = (TestData*)malloc(count * sizeof(TestData));
    if (test_data == NULL)
        {
        printf(COLOR_RED "Error: memory allocation failed\n" COLOR_RESET);
        fclose(file);
        *test_count = 0;
        return NULL;
        }

    // read test data
    int index = 0;
    while (fgets(line, sizeof(line), file) && index < count)
        {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        TestData *current = &test_data[index];
        char description[MAX_DESCRIPTION_LENGTH] = {0};

        int parsed = sscanf(line, "%lg %lg %lg %d %lg %lg %[^\n]",
                          &current->a, &current->b, &current->c,
                          &current->expected_type,
                          &current->expected_x1, &current->expected_x2,
                          description);

        if (parsed >= 6)
            {
            if (parsed >= 7)
                strncpy(current->description, description, MAX_DESCRIPTION_LENGTH - 1);
            else
                strcpy(current->description, "");

            index++;
            }
        }

    fclose(file);
    *test_count = count;
    return test_data;
    }

// run single test case
bool run_test_case(const TestData *test, Equation *result)
    {
    assert(test != NULL);
    assert(result != NULL);

    // initialize equation
    result->a = test->a;
    result->b = test->b;
    result->c = test->c;
    result->x1 = 0.0;
    result->x2 = 0.0;

    // solve equation
    result->type = solve_equation(result);

    // check solution type
    if (test->expected_type != result->type)
        return false;

    // check solutions
    switch (test->expected_type)
        {
        case INFINITE_SOLUTIONS:
        case NO_SOLUTIONS:
            return true;

        case SINGLE_SOLUTION:
        case SINGLE_SOLUTION_D0:
            return are_doubles_equal(test->expected_x1, result->x1);

        case TWO_REAL_SOLUTIONS:
            {
            double res1 = result->x1;
            double res2 = result->x2;
            swap_double(&res1, &res2);

            double exp1 = test->expected_x1;
            double exp2 = test->expected_x2;
            swap_double(&exp1, &exp2);

            return are_doubles_equal(exp1, res1) && are_doubles_equal(exp2, res2);
            }

        default:
            return false;
        }
    }

// run all tests from array
void run_all_tests(TestData *test_data, int total_tests, int *passed_tests)
    {
    assert(test_data != NULL);
    assert(passed_tests != NULL);

    *passed_tests = 0;

    for (int i = 0; i < total_tests; i++)
        {
        Equation result;
        bool passed = run_test_case(&test_data[i], &result);

        print_test_result(&test_data[i], &result, passed, i + 1);

        if (passed)
            (*passed_tests)++;
        }
    }

// print result
void print_test_result(const TestData *test, const Equation *result, bool passed, int test_num)
    {
    assert(test != NULL);
    assert(result != NULL);
    printf("Test %d: %s - ", test_num, passed ? COLOR_GREEN "PASSED" COLOR_RESET : COLOR_RED "FAILED" COLOR_RESET);

    if (strlen(test->description) > 0)
        {
        printf("%s\n", test->description);
        }
    else
        {
        printf("a=%.lg, b=%.lg, c=%.lg\n", test->a, test->b, test->c);
        }

    if (!passed)
        {
        printf("  Expected: type=%d, roots=(%.lg, %.lg)\n",
               test->expected_type, test->expected_x1, test->expected_x2);

        printf("  Got:      type=%d, roots=(%.lg, %.lg)\n",
               result->type, result->x1, result->x2);
        }
    }

// run unit tests from file
void unittest_solvesquare_from_file(const char *filename)
    {
    assert(filename != NULL);

    printf("Running unit tests from file: %s\n\n", filename);

    int total_tests = 0;
    int passed_tests = 0;

    // read test data from file
    TestData *test_data = read_test_cases(filename, &total_tests);

    if (test_data == NULL || total_tests == 0)
        {
        printf("No valid test cases found or error reading file\n");
        free(test_data);
        return;
        }

    // run all tests
    run_all_tests(test_data, total_tests, &passed_tests);

    printf("\nResult: %d/%d tests passed from %s\n\n",
           passed_tests, total_tests, filename);

    free(test_data);
    }

void unittest_solvesquare(void)
    {
    unittest_solvesquare_from_file(TEST_FILENAME);
    }
