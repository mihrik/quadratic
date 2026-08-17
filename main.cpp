#include <stdio.h>
#include <math.h>
#define EPS 1e-9
#define SQUARE(x) ((x) * (x))
#define ABS(x) (((x) > 0) ? (x) : -(x))
typedef struct quadratic_equation
{
    double a; // коэфф. перед x^2
    double b; // коэфф. перед x
    double c; // свободный член
} QE;

double eval_d(QE eq); //вычисляет дискриминант

int main(void)
{
    QE eq1;
    puts("Эта программа решает квадратное уравнение в действительных "
    "решениях");
    puts("Квадратное уравнение имеет вид ax^2 + bx + c");
    puts("Поочерёдно введите a, b, c (любой символ для выхода)");
    while (scanf("%lf %lf %lf", &eq1.a, &eq1.b, &eq1.c) == 3)
    {
        double d = eval_d(eq1);
        if (eq1.a < EPS) {
            puts("Не является квадратным уравнением");
        }
        else if (d < -EPS)
        {
            printf("Уравнение % .2fx^2 %+.2fx %+.2f не имеет"
            " действительных решений\n", eq1.a, eq1.b, eq1.c);
        }
        else if (ABS(d) <= EPS)
        {
            double x = -eq1.b / (2 * eq1.a);
            printf("Уравнение % .2fx^2 %+.2fx %+.2f имеет"
            " единственное решение: x = %.2f\n", eq1.a, eq1.b, eq1.c,
            x);
        }
        else
        {
            double x1 = (-eq1.b + sqrt(d)) / (2 * eq1.a);
            double x2 = (-eq1.b - sqrt(d)) / (2 * eq1.a);
            printf("Уравнение % .2fx^2 %+.2fx %+.2f имеет"
            " два решения: x1 = %.2f x2 = %.2f\n",
             eq1.a, eq1.b, eq1.c,x1, x2);
        }
        puts("Поочерёдно введите a, b, c (любой символ для выхода)");
    }

    return 0;
}

double eval_d(QE eq)
{
    return SQUARE(eq.b) - 4 * eq.a * eq.c;
}
