#include <stdio.h>
#include <math.h>

int main() {
    double a = 1, b = 1, c = 1; // Коэффициенты
    double discriminant = 0, x1 = 0, x2 = 0;

    printf("Введите коэффициенты a, b и c: ");
    
    // Проверка корректности ввода
    int read_count = scanf("%lf %lf %lf", &a, &b, &c);
    if (read_count != 3) {
        printf("Ошибка: введены некорректные данные. Требуются три числа.\n");
        return 1;
    }
    int next_char = getchar();
    if (next_char != '\n' && next_char != EOF) {
        printf("Ошибка: после трёх чисел обнаружены лишние символы.\n");
        return 1;
    }
    
    // Частные случаи
    if (a == 0) {
    	if (b == 0) {
        	if (c == 0) {
       		 printf("Бесконечное кол-во корней\n");
      	  } else {
            	printf("Корней нет\n");
            }
        } else {
            x1 = -c / b;
        	printf("Единствпнный корень:\n");
      	  printf("x = %E\n", x1);
        }
    } else {
    	discriminant = b * b - 4 * a * c;
 
		// Проверка дискриминанта
		if (discriminant > 0) {
        	x1 = (-b - sqrt(discriminant)) / (2 * a);
        	x2 = (-b + sqrt(discriminant)) / (2 * a);
        	printf("Два действительных корня:\n");
        	printf("x1 = %E\n", x1);
        	printf("x2 = %E\n", x2);
        } else if (discriminant == 0) {
        	x1 = -b / (2 * a);
        	printf("Один действительный корень:\n");
        	printf("x = %E\n", x1);
        } else {
			printf("Корней нет\n");
        }
    }
		
    return 0;
}