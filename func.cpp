#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/**
 @brief             вычисляет дискриминант

 @param [in]   eq   структура содержащая коэффициенты квадратного уравнения

 @return            значение дискриминанта
 */

double eval_discriminant(quadratic eq)
{
    return eq.b * eq.b - 4 * eq.a * eq.c;
}

/**
 @brief                  в зависимости от введенных коэффициентов выдает количество корней уравнения

 @param [out]  object    указатель на структуру хранящую коэффициенты уравнения и его решения

 @return                 количество корней уравнения

 @note                   прерывает программу в случае неверной передачи object
 */

int root_count(quadratic *object)
{
    assert(object != NULL);
    assert(isfinite((object->a)));
    assert(isfinite(object->b));
    assert(isfinite(object->c));

    if (fabs(object->a) < EPS)
    {
        if (fabs(object->b) < EPS)
        {
            if (fabs(object->c) < EPS)
            {
                return 3;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            object->x1 = -object->c / object->b;
            return 1;
        }
    }

    double d = eval_discriminant(*object);

    if (d < 0)
    {
        return -1;
    }

    else if (fabs(d) < EPS)
    {
        object->x1 = -object->b / (2 * object->a);
        return 1;
    }

    else
    {
        object->x1 = (-object->b + sqrt(d)) / (2 * object->a);
        object->x2 = (-object->b - sqrt(d)) / (2 * object->a);
        return 2;
    }
}

/**
 @brief             выводит решение квадратного уравнения формата ax^2 + bx + c

 @param             нет

 @return            нет

 @note              в случае невосприимчивого программой ввода прекращает ее
 */

void quadratic_solution(void)
{
    quadratic equation = {0, 0, 0, 0, 0};
    char ch = '\0';

    do
    {
        puts("Введите a");
        printf(">:");
        get_num(&equation.a);

        puts("Введите b");
        printf(">:");
        get_num(&equation.b);

        puts("Введите c");
        printf(">:");
        get_num(&equation.c);

        int roots = root_count(&equation);

        switch(roots)
        {
            case IMAGINARY: puts("Уравнение не имеет действительных решений");
                     break;
            case NO_SOLUTIONS: puts("Уравнение не имеет никаких решений");
                    break;
            case ONE_SOLUTION: printf("Уравнение %gx^2%+gx%+g имеет единственный"
                            " корень x = %g\n", equation.a, equation.b, equation.c,
                             equation.x1);
                    break;
            case TWO_SOLUTIONS: printf("Уравнение %gx^2%+gx%+g имеет два"
                            " корня x = %g и x = %g\n", equation.a,
                             equation.b, equation.c, equation.x1, equation.x2);
                    break;
            case INFINITY_SOLUTIONS: puts("Бесконечное количество решений");
                    break;
            default: puts("Ошибка");
                     exit(EXIT_FAILURE);
        }

        ch = get_char();
        while (getchar() != '\n');
    } while (ch != 'n');
}

/**
 @brief             получает число с клавиатуры

 @param [out]  pt   указатель на переменную которой присвоен ввод
 @return            ничего

 @note              при недопустимом вводе дает возможность повторного ввода
 */

void get_num(double *pt)
{
    double num = 0;
    bool marker = false;

    while (!marker)
    {
        char buffer[INPUT_BUFFER_SIZE] = {};
        char *end = buffer;
        char ch = '\0';
        int i = 0;

        for ( ; i < INPUT_BUFFER_SIZE - 1 && ch != '\n'; i++)
        {
            ch = getchar();
            buffer[i] = ch;
        }

        if (ch != '\n')
        {
            while (getchar() != '\n');
        }
        num = strtod(buffer, &end);
        if (*end != '\n')
        {
            buffer[i-1] = '\0';
            printf("%s не является целочисленным вводом\n", buffer);
            continue;
        }

        marker = true;
    }

    *pt = num;
}

/**
 @brief             получает символ y или n с клавиатуры

 @param             нет
 @return            символ y или n

 @note              при недопустимом вводе дает возможность повторного ввода
 */

char get_char(void)
{
    char ch1;

    puts("Введите y, чтобы продолжить. n - в противном случае");
    ch1 = getchar();
    while (ch1 != 'y' && ch1 != 'n')
    {
        puts("Недопустимый ввод, введите y или n");
        while (getchar() != '\n');

        ch1 = getchar();
    }

    return ch1;
}
