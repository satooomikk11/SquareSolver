#ifndef TESTS_H
#define TESTS_H

#include "Equation.h"

void swap_double(double *a, double *b);
void unittest_solvesquare_from_file(const char *filename);
void run_all_tests(TestData *test_data, int total_tests, int *passed_tests);
void print_test_result(const TestData *test, const Equation *result, bool passed, int test_num);
void unittest_solvesquare_from_file(const char *filename);
void unittest_solvesquare(void);

#endif // TESTS_H
