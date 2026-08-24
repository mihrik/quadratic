#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


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
    char line[400];

    do
    {
        coeffs_initialization(&equation);

        equation.number_of_roots = root_count_and_solution(&equation);

        switch(equation.number_of_roots)
        {
            case          IMAGINARY: print_no_real_roots();
                            break;
            case       NO_SOLUTIONS: print_no_roots();
                            break;
            case       ONE_SOLUTION: sprintf(line, "x=%.3g", equation.x1);
                                     nice_output(line);
                            break;
            case      TWO_SOLUTIONS: sprintf(line, "x1=%.3g", equation.x1);
                                     nice_output(line);
                                     sprintf(line, "x2=%.3g", equation.x2);
                                     nice_output(line);
                            break;
            case INFINITY_SOLUTIONS: print_inf_roots();
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

 @param [out]  pt            указатель на переменную которой присвоен ввод, в режиме 1 = NULL
 @param [out]  for_compare   строка для анализа в режиме 1, NULL в режиме 0
 @param [in]   mode          режим работы функции: 0 - в обычном режиме, 1 - в режиме теста
 @return                     ничего в режиме 0, в режиме 1 - вернет полученное число при корректном вводе, 0 при некорректном

 @note              при недопустимом вводе дает возможность повторного ввода, а в режиме теста нет
 */

double get_num(double *pt, int mode, const char *for_compare)
{
    if (mode == 1)
    {
        my_assert(for_compare);
    }
    else
    {
        my_assert(pt);
    }

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
            if (mode == 0)
            {
                ch = getchar();
                buffer[i] = ch;
            }
            else
            {
                ch = *(for_compare+i);
                buffer[i] = ch;
            }
        }

        if (buffer[0] == '\n')
        {
            if (mode == 1)
            {
                return 0;
            }
            PRINT_COLOR(RED, "недопустимый формат ввода\n");
            continue;
        }
        if (mode == 0 && ch != '\n' && ch != EOF)
        {
            clear_buffer();
        }

        num = strtod(buffer, &end);
        mem = buffer[i-1];
        buffer[i-1] = '\0';
        is_spaces = check_clear_buf(end);

        if (is_spaces)
        {
            if (mode == 0)
            {
                coeffs_read_success = true;
                continue;
            }
            return num;
        }
        buffer[i-1] = mem;

        if (*end != '\n')
        {
            if (mode == 1)
            {
                return 0;
            }
            buffer[i-1] = '\0';
            PRINT_COLOR(RED, "%s не является числовым вводом\n", buffer);
            continue;
        }
        if (mode == 1)
        {
            return num;
        }
        coeffs_read_success = true;
    }


    *pt = num;
    return 1;
}

/**
 @brief             получает символ y или n с клавиатуры

 @param             нет
 @return            символ y или n

 @note              при недопустимом вводе дает возможность повторного ввода
 */
int get_option(void)
{
    printf(RED);
    print_continue_message();
    printf(RESET_COLOR);

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

    print_a();
    printf(">:");
    get_num(&ptr->a, 0, NULL);

    print_b();
    printf(">:");
    get_num(&ptr->b, 0, NULL);

    print_c();
    printf(">:");
    get_num(&ptr->c, 0, NULL);
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

/**
 @brief                      выводит классную картинку

 @param [out]   art_addres   адрес файла с картинкой
 @return                     ничего
 */

void print_ascii(FILE *art_addres, int times)
{
    char one_line[300];
    while(fgets(one_line, 300, art_addres))
    {
        printf("\033[%dC", times);
        fputs(one_line, stdout);
    }

    puts("\n");
}

/**
 @brief              печатает рандомную крутую картинку

 @param              нет
 @return             ничего
 */

void print_rand_ascii(void)
{
    srand((unsigned int) time(0));

    FILE *fp_art = NULL;
    my_assert(fp_art = fopen(ASCII_ARTS[rand() % (sizeof (ASCII_ARTS) / sizeof(ASCII_ARTS[0]))], "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

/**
 @brief              печатает афигенное приветствие

 @param              нет
 @return             ничего
 */

void print_greeting(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/greeting", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}



void nice_output(char *output)
{
    FILE *fp = NULL;
    my_assert(output);
    int i = 1;
    while(*output)
    {


        switch(*output)
        {
            case 'x':   {
                            my_assert(fp = fopen("symbols/x", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '-':   {
                            my_assert(fp = fopen("symbols/minus", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '.':   {
                            my_assert(fp = fopen("symbols/dot", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        };

            case '9':   {
                            my_assert(fp = fopen("symbols/9", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '8':   {
                            my_assert(fp = fopen("symbols/8", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '7':   {
                            my_assert(fp = fopen("symbols/7", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '6':   {
                            my_assert(fp = fopen("symbols/6", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '5':   {
                            my_assert(fp = fopen("symbols/5", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '4':   {
                            my_assert(fp = fopen("symbols/4", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '3':   {
                            my_assert(fp = fopen("symbols/3", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '2':   {
                            my_assert(fp = fopen("symbols/2", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '1':   {
                            my_assert(fp = fopen("symbols/1", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '0':   {
                            my_assert(fp = fopen("symbols/0", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case '=':   {
                            my_assert(fp = fopen("symbols/equal", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            case 'e':   {
                            my_assert(fp = fopen("symbols/e", "r"));
                            print_ascii(fp, i * 9);
                            printf("\033[8A");
                            break;
                        }

            default :   my_assert(0);
        }
        i++;
        output++;
    }
    puts("\n\n\n\n\n\n\n\n");
    my_assert(!fclose(fp));
}


void print_goodbye(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/goodbye", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_inf_roots(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/inf_roots", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_no_roots(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/no_roots", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_no_real_roots(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/no_real_roots", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_a(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/print_a", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_b(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/print_b", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_c(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/print_c", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

void print_continue_message(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/print_continue_message", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}