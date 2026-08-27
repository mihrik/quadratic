#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

int root_count_and_solution(quadratic *object)
{
    my_assert(object);
    my_assert(!isinf_or_isnan(object->a));
    my_assert(!isinf_or_isnan(object->b));
    my_assert(!isinf_or_isnan(object->c));

    if (is_zero(object->a))
    {
        if (is_zero(object->b))
        {
            if (is_zero(object->c))
            {
                return INFINITY_SOLUTIONS;
            }
            else
            {
                return NO_SOLUTIONS;
            }
        }
        else if (is_zero(object->c))
        {
            object->x1 = 0;
            return ONE_SOLUTION;
        }
        else
        {
            object->x1 = -object->c / object->b;
            return ONE_SOLUTION;
        }
    }
    else if (is_zero(object->b) && is_zero(object->c))
    {
        object->x1 = 0;
        return ONE_SOLUTION;
    }


    double d = eval_discriminant(*object);

    if (d < 0)
    {
        return IMAGINARY;
    }

    else if (is_zero(d))
    {
        object->x1 = -object->b / (2 * object->a);
        return ONE_SOLUTION;
    }

    else
    {
        object->x1 = (-object->b + sqrt(d)) / (2 * object->a);
        object->x2 = (-object->b - sqrt(d)) / (2 * object->a);
        return TWO_SOLUTIONS;
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
    int option = '\0';
    char line[LEN_OF_ANSWER] = {};

    do
    {
        show_solution(line);

        option = get_option();
        while (getchar() != '\n'); //function
    } while (option != 'n');
}

/**
 @brief             проверяет является ли число NaN или inf

 @param [in]  num   число для проверки
 @return            1 - является, 0 - нет
 */

int isinf_or_isnan(double num)
{
    if (isinf(num))
    {
        return 1;
    }
    return !is_zero(num-num);
}

/**
 @brief              проверяет число double на равенство нулю

 @param [in]   num   число для проверки
 @return             0 - не равно нулю, 1 - равно нулю
 */

int is_zero(double num)
{
    return fabs(num) < EPS;
}

/**
 @brief              проверяет равны ли корни уравнения

 @param [in]  x1     первое число
 @param [in]  x2     второе число
 @return             1 - равны, 0 - неравны

 @note               при получении обоих значений NAN выводит 1
 */

int meanings_are_equal(double x1, double x2)
{
    if (!isinf_or_isnan(x1) && !isinf_or_isnan(x2))
    {
        return is_zero(x1 - x2);
    }
    else if (isnan(x1) && isnan(x2))
    {
        return 1;
    }
    return 0;
}

/**
 @brief              сортирует два числа в порядке неубывания

 @param [out]  x1    указатель на первое число
 @param [out]  x2    указатель на второе число
 @return             ничего

 @note               если среди чисел есть NAN то сначала число потом NAN
 */

void sort_roots(double *x1, double *x2)
{
    my_assert(x1);
    my_assert(x2);

    if (!isnan(*x1) && !isnan(*x2))
    {
        double temp = *x2;
        if (*x1 > *x2)
        {
            *x2 = *x1;
            *x1 = temp;
        }
    }
    if (isnan(*x1) && !isnan(*x2))
    {
        *x1 = *x2;
        *x2 = NAN;
    }
}

/**
 @brief              запускает тесты quadratic_solution и get_num

 @param              нет
 @return             ничего
 */

void big_test(void)
{
    test_quadratic();
    test_get_num();
}

/**
 @brief              выводит визуальную составляющую решения уравнения

 @param [out] line   строка содержащая решение уравнения в строковом формате
 @return             ничего
 */

void show_solution(char *line)
{
    quadratic equation = {.a = 0, .b = 0, .c = 0, .x1 = 0, .x2 = 0, .number_of_roots = 0};

    coeffs_initialization(&equation);

    equation.number_of_roots = root_count_and_solution(&equation);

    graphic(equation.a, equation.b, equation.c);

    output(&equation, &line);
}

/**
 @brief                  выводит корни уравнения через ascii art

 @param [out]  solution  указатель на структуру квадратного уравнения
 @param [out]  console   указатель на строку содержащую решение в строковом формате
 @return                 ничего
 */

void output(quadratic *solution, char **console)
{
    switch(solution->number_of_roots)
    {
        case          IMAGINARY: print_no_real_roots();
                        break;
        case       NO_SOLUTIONS: print_no_roots();
                        break;
        case       ONE_SOLUTION: sprintf(*console, "x=%.3g", solution->x1);
                                 nice_output(*console);
                        break;
        case      TWO_SOLUTIONS: sprintf(*console, "x1=%.3g", solution->x1);
                                 nice_output(*console);
                                 sprintf(*console, "x2=%.3g", solution->x2);
                                 nice_output(*console);
                        break;
        case INFINITY_SOLUTIONS: print_inf_roots();
                        break;
        default                : PRINT_COLOR(EXTRA_RED, "Ошибка\n");
                        return;
        }
}