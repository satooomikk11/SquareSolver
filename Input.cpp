#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <TXLib.h>

#include "Input.h"
#include "doubles.h"
#include "define_colors.h"


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
    // MY_ASSERT(x != 0);  // я упал! сообщение об ошибке, функция откуда он вызвался, строку, имя файла
    // MY_ASSERT(x != 0, "x pointer is NULL!");
    // MY_ASSERT(x != 0, "x pointer is %p\n", x);

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
