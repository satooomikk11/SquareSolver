#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <TXLib.h>

#define COLOR_RED   "\033[1;31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

#include "Input.h"

const double MIN_DIFF = 1e-10;


// comparing two doubles
int are_doubles_equal(double a, double b)
    {
    return fabs(a - b) < MIN_DIFF;
    }


// extra chars checking
int check_extra_chars(void)
    {
    int next_char = 0;
    while ((next_char = getchar()) != '\n' && next_char != EOF)
        {
        if (!isspace(next_char))
            {
            printf(COLOR_RED "Error: extra characters found after three numbers!\n" COLOR_RESET);
            return 1;
            }
        }
    return 0;
    }


// input checking
int entering_coefficients_and_checking(struct Equation *eq)
    {
    assert(eq != NULL);
    printf("Enter the coefficients a, b and c: ");

    int read_count = scanf("%lg %lg %lg", &eq->a, &eq->b, &eq->c);
    if (read_count != 3)
        {
        printf(COLOR_RED "Error: you need to enter three numbers!\n" COLOR_RESET);
        return 1;
        }

    // NaN checking
    if (isnan(eq->a) || isnan(eq->b) || isnan(eq->c))
        {
        printf(COLOR_RED "Error: the NaN value is entered!\n" COLOR_RESET);
        return 1;
        }

    return check_extra_chars();
    }
