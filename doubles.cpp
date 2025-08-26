#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "doubles.h"

const double MIN_DIFF = 1e-10;

// comparing two doubles
int are_doubles_equal(double a, double b)
    {
    return fabs(a - b) < MIN_DIFF;
    }


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
