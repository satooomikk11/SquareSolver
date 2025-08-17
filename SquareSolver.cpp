#include <stdio.h>
#include <math.h>
#include <ctype.h>


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
        case 0: // Бесконечное количество решений
            printf("Бесконечное кол-во корней\n");
            break;
        case 1: // Нет решений
            printf("Корней нет\n");
            break;
        case 2: // Одно решение
            printf("Единственный корень:\n"
                      "x = %g\n", x1);
            break;
        case 3: // Два решения
            printf("Два действительных корня\n"
                      "x1 = %g\n"
                      "x2 = %g\n", x1, x2);
            break;
        case 4: // Одно решение (квадратное)
            printf("Один действительный корень:\n"
                      "x = %g\n", x1);
            break;
    }
}


int square_equation_solver(double a, double b, double c, double *x1, double *x2)
{
    double discriminant = 0;
    *x1 = 0;
    *x2 = 0;

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
    else 
    {
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
}


int check_extra_chars()
{
    int next_char;
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


int input_validator(double *a, double *b, double *c)
{
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


int main() 
{
    double a = 0, b = 0, c = 0; // Коэффициенты
    double x1 = 0, x2 = 0; // Корни
    
    if (input_validator(&a, &b, &c) != 0)
    {
        printf("Программа завершена из-за ошибки ввода.\n");
        return 1;
    }
    
    int solution_type = square_equation_solver(a, b, c, &x1, &x2);
    solution_output(solution_type, x1, x2);
    
    return 0;
}