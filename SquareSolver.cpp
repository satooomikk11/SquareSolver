#include <stdio.h>
#include <math.h>
#include <ctype.h>


int sravn(double a, double b) 
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


int main() 
{
    double a = 1, b = 1, c = 1; // Коэффициенты
    double discriminant = 0, x1 = 0, x2 = 0;

    printf("Введите коэффициенты a, b и c: ");
    
    // Проверка корректности ввода
    int read_count = scanf("%lf %lf %lf", &a, &b, &c);
	if (read_count != 3) 
    {
		printf("Ошибка: нужно ввести три числа\n");
		return 1;
    }


    // Проверка NaN
    if (isnan(a) || isnan(b) || isnan(c))
    {
        printf("Ошибка: введено значение NaN\n");
        return 1;
    }

	// Проверка лишних символов
    int next_char;
    while ((next_char = getchar()) != '\n' && next_char != EOF)
    {
        if (!isspace(next_char)) // Проверка пробела
        {
        printf("Ошибка: после трёх чисел обнаружены лишние символы.\n");
            return 1;
        }
    }

    // Частные случаи
    if (sravn(a, 0) == 1) 
    {
    	if (sravn(b, 0) == 1) 
    	{
        	if (sravn(c, 0) == 1) 
        	{
       		 printf("Бесконечное кол-во корней\n");
      	  } 
      	  else 
      	  {
            	printf("Корней нет\n");
            }
        } 
        else 
        {
            x1 = -c / b;
        	printf("Единственный корень:\n"
      	  		  "x = %g\n", x1);;
        }
	} 
	else 
	{
    	discriminant = b * b - 4 * a * c;
 
		// Проверка дискриминанта
		if (discriminant > 0) 
		{
        	x1 = (-b - sqrt(discriminant)) / (2 * a);
        	x2 = (-b + sqrt(discriminant)) / (2 * a);
        	printf("Два действительных корня\n"
       			   "x1 = %g\n"
        			  "x2 = %g\n", x1, x2);
        } 
        else if (sravn(discriminant, 0) == 1) 
        {
        	x1 = -b / (2 * a);
        	printf("Один действительный корень:\n"
        			  "x = %g\n", x1);
        } 
        else 
        {
			printf("Корней нет\n");
        }
    }
		
    return 0;
}