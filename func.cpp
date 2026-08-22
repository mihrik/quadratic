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
    quadratic equation = {0, 0, 0, 0, 0, 0};
    int option = '\0';

    do
    {
        coeffs_initialization(&equation);

        equation.number_of_roots = root_count_and_solution(&equation);

        switch(equation.number_of_roots)
        {
            case          IMAGINARY: PRINT_COLOR(BLUE, "Уравнение не имеет действительных решений\n");
                            break;
            case       NO_SOLUTIONS: PRINT_COLOR(BLUE, "Уравнение не имеет никаких решений\n");
                            break;
            case       ONE_SOLUTION: PRINT_COLOR(BLUE, "Уравнение %gx^2%+gx%+g имеет единственный"
                            " корень x = %g\n", equation.a, equation.b, equation.c,
                              equation.x1);
                            break;
            case      TWO_SOLUTIONS: PRINT_COLOR(BLUE, "Уравнение %gx^2%+gx%+g имеет два"
                            " корня x = %g и x = %g\n", equation.a,
                             equation.b, equation.c, equation.x1, equation.x2);
                            break;
            case INFINITY_SOLUTIONS: PRINT_COLOR(BLUE, "Бесконечное количество решений\n");
                            break;
            default                : PRINT_COLOR(EXTRA_RED, "Ошибка\n");
                           return;
        }

        option = get_option();
        while (getchar() != '\n'); //function
    } while (option != 'n');
}

/**
 @brief             получает число с клавиатуры

 @param [out]  pt   указатель на переменную которой присвоен ввод
 @return            ничего

 @note              при недопустимом вводе дает возможность повторного ввода
 */

void get_num(double *pt)
{
    my_assert(pt);

    double num = 0;
    bool coeffs_read_success = false;

    while (!coeffs_read_success)
    {
        char buffer[INPUT_BUFFER_SIZE] = {};
        char *end = buffer;
        int ch = '\0';
        int i = 0;
        char mem = '\0';
        bool is_spaces = false;

        for ( ; i < INPUT_BUFFER_SIZE - 1 && ch != '\n' && ch != EOF; i++)
        {
            ch = getchar();
            buffer[i] = ch;
        }

        if (buffer[0] == '\n')
        {
            PRINT_COLOR(RED, "недопустимый формат ввода\n");
            continue;
        }

        if (ch != '\n')
        {
            clear_buffer();
        }

        num = strtod(buffer, &end);
        mem = buffer[i-1];
        buffer[i-1] = '\0';
        is_spaces = check_clear_buf(end);

        if (is_spaces)
        {
            coeffs_read_success = true;
            continue;
        }
        buffer[i-1] = mem;

        if (*end != '\n')
        {
            buffer[i-1] = '\0';
            PRINT_COLOR(RED, "%s не является числовым вводом\n", buffer);
            continue;
        }

        coeffs_read_success = true;
    }

    *pt = num;
}

/**
 @brief             получает символ y или n с клавиатуры

 @param             нет
 @return            символ y или n

 @note              при недопустимом вводе дает возможность повторного ввода
 */
int get_option(void)
{
    PRINT_COLOR(ORANGE, "Введите y, чтобы продолжить. n - в противном случае\n");
    int ch1 = getchar();
    while (ch1 != 'y' && ch1 != 'n')
    {
        PRINT_COLOR(RED, "Недопустимый ввод, введите y или n\n");
        clear_buffer();

        ch1 = getchar();
    }

    return ch1;
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
 @brief              инициализирует коэффициенты квадратного уравнения

 @param [out]  ptr   указатель на структуру которая требует инициализации
 @return             ничего

 @note               имеет оформленный ввод
 */

void coeffs_initialization(quadratic * ptr)
{
    my_assert(ptr);

    PRINT_COLOR(GREEN, "Введите a\n");
    printf(">:");
    get_num(&ptr->a);

    PRINT_COLOR(GREEN, "Введите b\n");
    printf(">:");
    get_num(&ptr->b);

    PRINT_COLOR(GREEN, "Введите c\n");
    printf(">:");
    get_num(&ptr->c);
}

/**
 @brief              очищает буфер от всех символов до '\n'

 @param              нет
 */

void clear_buffer(void)
{
    while (getchar() != '\n');
}

/**
 @brief                 проверяет является ли строка пробелами

 @param [out]  buffer   указатель на строку которая требует проверки
 @return                1 - является пробелами, 0 - не является
 */

int check_clear_buf(char *buffer)
{
    my_assert(buffer);

    bool all_space = true;
    while (*buffer && *buffer != '\n')
    {
        if (*buffer != ' ')
        {
            all_space = false;
            break;
        }
        buffer++;
    }
    return all_space;
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