#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <TXLib.h>

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
            printf("Error: extra characters found after three numbers!\n");
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
