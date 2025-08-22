#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>


// Объявление enum
typedef enum {
    SOLUTION_SUCCESS = 0,
    SOLUTION_INVALID_TYPE = 1
} SolutionResult;

typedef enum {
    INFINITE_SOLUTIONS = 0,
    NO_SOLUTIONS = 1,
    SINGLE_SOLUTION = 2,
    TWO_REAL_SOLUTIONS = 3,
    SINGLE_SOLUTION_ALT = 4
} SolutionType;


// Объявление функций
int are_numbers_equal(double a, double b);
SolutionResult solution_output(SolutionType solution_type, double variables[]);
SolutionType linear_equation_solver(double b, double c, double variables[]);
SolutionType square_equation_solver(double variables[]);
int check_extra_chars(void);
int entering_coefficients_and_checking(double variables[]);
SolutionType coosing_solution_type(double variables[]);


int main()
{
    // Массив для хранения всех переменных: [a, b, c, x1, x2]
    double variables[5] = {0}; // Инициализируем все элементы нулями

    if (entering_coefficients_and_checking(variables) != 0)
    {
        printf("Программа завершена из-за ошибки ввода.\n");
        return 1;
    }

    SolutionType solution_type = coosing_solution_type(variables);

    solution_output(solution_type, variables);

    return 0;
}


int are_numbers_equal(double a, double b)
{
    if (fabs(a - b) > 0.000001)
    {
        return 0; // Числа не равны
    }
    else
    {
        return 1; // Числа равны
    }
}


SolutionType coosing_solution_type(double variables[])
{
    if (are_numbers_equal(variables[0], 0) == 1)
    {
        return linear_equation_solver(variables[1], variables[2], variables);
    }
    else
    {
        return square_equation_solver(variables);
    }
}


SolutionResult solution_output(SolutionType solution_type, double variables[])
{
    switch(solution_type)
    {
        default:
            printf("Неверный solution_type!\n");
            return SOLUTION_INVALID_TYPE;
            break;
        case INFINITE_SOLUTIONS:
            printf("Бесконечное кол-во корней\n");
            break;
        case NO_SOLUTIONS:
            printf("Корней нет\n");
            break;
        case SINGLE_SOLUTION:
        case SINGLE_SOLUTION_ALT:
            printf("Единственный корень:\n"
                      "x = %lg\n", variables[3]); // x1
            break;
        case TWO_REAL_SOLUTIONS:
            printf("Два действительных корня\n"
                      "x1 = %lg\n"
                      "x2 = %lg\n", variables[3], variables[4]); // x1, x2
            break;
    }
    return SOLUTION_SUCCESS;
}


SolutionType linear_equation_solver(double b, double c, double variables[])
{
    // variables[0] = a, variables[1] = b, variables[2] = c
    // variables[3] = x1, variables[4] = x2

    // Частные случаи
    if (are_numbers_equal(b, 0) == 1)
    {
        if (are_numbers_equal(c, 0) == 1)
        {
            return INFINITE_SOLUTIONS; // Бесконечное количество решений
        }
        else
        {
            return NO_SOLUTIONS; // Нет решений
        }
    }
    else
    {
        variables[3] = -c / b; // x1 = -c / b
        return SINGLE_SOLUTION; // Одно решение
    }
}


SolutionType square_equation_solver(double variables[])
{
    // variables[0] = a, variables[1] = b, variables[2] = c
    // variables[3] = x1, variables[4] = x2

    assert(are_numbers_equal(variables[0], 0) == 0); // Проверка что a ≠ 0

    double discriminant = 0;
    variables[3] = 0; // x1
    variables[4] = 0; // x2

    discriminant = variables[1] * variables[1] - 4 * variables[0] * variables[2];

    // Проверка дискриминанта
    if (discriminant > 0)
    {
        variables[3] = (-variables[1] - sqrt(discriminant)) / (2 * variables[0]); // x1
        variables[4] = (-variables[1] + sqrt(discriminant)) / (2 * variables[0]); // x2
        return TWO_REAL_SOLUTIONS; // Два решения
    }
    else if (are_numbers_equal(discriminant, 0) == 1)
    {
        variables[3] = -variables[1] / (2 * variables[0]); // x1
        return SINGLE_SOLUTION_ALT; // Одно решение (D = 0)
    }
    else
    {
        return NO_SOLUTIONS; // Нет решений
    }
}


int check_extra_chars(void)
{
    int next_char = 0;
    while ((next_char = getchar()) != '\n' && next_char != EOF)
    {
        if (!isspace(next_char)) // Проверка пробела
        {
            printf("Ошибка: после трёх чисел обнаружены лишние символы.\n");
            return 1;
        }
    }
    return 0;
}


int entering_coefficients_and_checking(double variables[])
{
    // variables[0] = a, variables[1] = b, variables[2] = c

    printf("Введите коэффициенты a, b и c: ");

    // Ввод и проверка чисел
    int read_count = scanf("%lf %lf %lf", &variables[0], &variables[1], &variables[2]);
    if (read_count != 3)
    {
        printf("Ошибка: нужно ввести три числа\n");
        return 1;
    }

    // Проверка NaN
    if (isnan((double) variables[0]) || isnan((double) variables[1]) || isnan((double) variables[2]))
    {
        printf("Ошибка: введено значение NaN\n");
        return 1;
    }

    // Проверка лишних символов
    return check_extra_chars();
}
