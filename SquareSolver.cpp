#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <TXLib.h>


// Объявление фукций
int are_numbers_equal(double a, double b);
int solution_output(int solution_type, double x1, double x2);
int linear_equation_solver(double a, double b, double c, double *x);
int square_equation_solver(double a, double b, double c, double *x1, double *x2);
int check_extra_chars(void);
int entering_coefficients_and_checking(double *a, double *b, double *c);


int main()
{
    double a = 0, b = 0, c = 0; // Коэффициенты
    double x1 = 0, x2 = 0; // Корни

    if (entering_coefficients_and_checking(&a, &b, &c) != 0)
    {
        printf("Программа завершена из-за ошибки ввода.\n");
        return 1;
    }

    // Сначала пробуем решить как линейное уравнение
    int solution_type = linear_equation_solver(a, b, c, &x1);

    // Если linear_equation_solver вернул -1, значит это квадратное уравнение
    if (solution_type == -1)
    {
        solution_type = square_equation_solver(a, b, c, &x1, &x2);
    }

    solution_output(solution_type, x1, x2);

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


int solution_output(int solution_type, double x1, double x2)
{
    switch(solution_type)
    {
        default:
            printf("Неверный solution_type!\n");
            return 1;
            break;
        case 0:
            printf("Бесконечное кол-во корней\n");
            break;
        case 1:
            printf("Корней нет\n");
            break;
        case 2:
        case 4:
            printf("Единственный корень:\n"
                      "x = %lg\n", x1);
            break;
        case 3:
            printf("Два действительных корня\n"
                      "x1 = %lg\n"
                      "x2 = %lg\n", x1, x2);
            break;
    }
    return 0;
}


int linear_equation_solver(double a, double b, double c,
                           double *x1)
{
    assert(x1 != NULL);
    *x1 = 0;

    // Частные случаи
    if (are_numbers_equal(a, 0) == 1)
    {
        if (are_numbers_equal(b, 0) == 1)
        {
            if (are_numbers_equal(c, 0) == 1)
            {
                return 0; // Бесконечное количество решений
            }
            else
            {
                return 1; // Нет решений
            }
        }
        else
        {
            *x1 = -c / b;
            return 2; // Одно решение
        }
    }
    return -1;
}


int square_equation_solver(double a, double b, double c,
                           double *x1, double *x2)
{
    assert(are_numbers_equal(a, 0) == 0);
    assert(x1 != NULL);
    assert(x2 != NULL);

    double discriminant = 0;
    *x1 = 0;
    *x2 = 0;


    discriminant = b * b - 4 * a * c;

    // Проверка дискриминанта
    if (discriminant > 0)
    {
        *x1 = (-b - sqrt(discriminant)) / (2 * a);
        *x2 = (-b + sqrt(discriminant)) / (2 * a);
        return 3; // Два решения
    }
    else if (are_numbers_equal(discriminant, 0) == 1)
    {
        *x1 = -b / (2 * a);
        return 4; // Одно решение (D = 0)
    }
    else
    {
        return 1; // Нет решений
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


int entering_coefficients_and_checking(double *a, double *b, double *c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    printf("Введите коэффициенты a, b и c: ");

    // Ввод и проверка чисел
    int read_count = scanf("%lf %lf %lf", a, b, c);
    if (read_count != 3)
    {
        printf("Ошибка: нужно ввести три числа\n");
        return 1;
    }
    
    // Проверка NaN
    if (isnan(*a) || isnan(*b) || isnan(*c))
    {
        printf("Ошибка: введено значение NaN\n");
        return 1;
    }

    // Проверка лишних символов
    return check_extra_chars();
}
