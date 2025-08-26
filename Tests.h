#ifndef TESTS_H
#define TESTS_H

#include "Equation.h"

struct TestData
    {
    double a, b, c;
    int expected_type;
    double expected_x1, expected_x2;
    char description[100];
    };

void unittest_solvesquare_from_file(const char *filename);
void run_all_tests(TestData *test_data, int total_tests, int *passed_tests);
void print_test_result(const TestData *test, const Equation *result, bool passed, int test_num);
void unittest_solvesquare_from_file(const char *filename);
void unittest_solvesquare(void);

#endif // TESTS_H
