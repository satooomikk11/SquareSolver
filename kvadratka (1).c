#include <stdio.h>
#include <math.h>

int leading_zeros(long double x) { /*кол-во нулей+4*/
    int count = 0;
    long double abs_x = fabsl(x);  /*Берём модуль*/
    /*Умножаем на 10, пока не получим цифру >=1 или число станет нулём*/
    while (abs_x < 1.0L && abs_x != 0.0L) {
        abs_x *= 10.0L;
        int digit = (int)abs_x;  /*Берём целую часть*/
        if (digit == 0) {
            count++;
        } else {
            break;  /*Встретили ненулевую цифру — останавливаемся*/
        }
    }

    return count+4;
}



int rounding(long double num) {
    long double ROUND;
    if (num>=1.0L) {
  printf("Округлённое значение: %.4Lf\n", num);
    } else {
     /*Округление и вывод*/
     long double multiplier = powl(10, leading_zeros(num));
     long double rounded = roundl(num * multiplier) /  multiplier;

        printf("Округлённое значение: %.*Lf\n", leading_zeros(num), rounded);
    }

    return 0;
}




int main() {
    long double x;
    printf("Введите число типа long double: ");
    scanf("%Lf", &x);
    
    printf(" %d\n", rounding(x));


    double a, b, c; /*коэффы*/
    double discriminant, x1, x2;

    printf("Введите коэффициенты a, b и c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
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
      printf("x = %5lf\n", x1);
     }
    } else {
     discriminant = b * b - 4 * a * c;
 
     if (discriminant > 0) {
         /*Два действ*/
         x1 = (-b - sqrt(discriminant)) / (2 * a);
         x2 = (-b + sqrt(discriminant)) / (2 * a);
         printf("Два действительных корня:\n");
         printf("x1 = %.5lf\n", x1);
         printf("x2 = %.5lf\n", x2);
     } else if (discriminant == 0) {
         /*Один*/
         x1 = -b / (2 * a);
         printf("Один действительный корень:\n");
         printf("x = %.5lf\n", x1);
     } else {
         /*Комплексные*/
         double real = -b / (2 * a);
         double imaginary = sqrt(-discriminant) / (2 * a);
         printf("Два комплексных корня:\n");
         printf("x1 = %.5lf - %.2lfi\n", real, imaginary);
         printf("x2 = %.5lf + %.2lfi\n", real, imaginary);
     }
    }

    return 0;
}