#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

extern int tokens;

/**
 @brief                      получает число с клавиатуры

 @param [out]  pt            указатель на переменную которой присвоен ввод, в режиме 1 = NULL
 @param [out]  for_compare   строка для анализа в режиме 1, NULL в режиме 0
 @param [in]   mode          режим работы функции: 0 - в обычном режиме, 1 - в режиме теста
 @return                     ничего в режиме 0, в режиме 1 - вернет полученное число при корректном вводе, 0 при некорректном

 @note              при недопустимом вводе дает возможность повторного ввода, а в режиме теста нет
 */

double get_num(double *pt, int mode, const char *for_compare)
{
    if (mode == test)
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
            if (mode == classic)
            {
                ch = getchar();
                buffer[i] = (char)ch;
            }
            else
            {
                ch = *(for_compare+i);
                buffer[i] = (char)ch;
            }
        }

        if (buffer[0] == '\n')
        {
            if (mode == test)
            {
                return 0;
            }
            tokens += 3;
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
            if (mode == classic)
            {
                coeffs_read_success = true;
                continue;
            }
            return num;
        }
        buffer[i-1] = mem;

        if (*end != '\n')
        {
            if (mode == test)
            {
                return 0;
            }
            buffer[i-1] = '\0';
            tokens += 5;
            PRINT_COLOR(RED, "%s не является числовым вводом\n", buffer);
            continue;
        }
        if (mode == test)
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

    char phrase[MAX_PHRASE_SIZE] = {};
    bool read_successfully = false;
    int ch = '\0';

    while (!read_successfully)
    {
        my_assert(fgets(phrase, MAX_PHRASE_SIZE, stdin));

        if (phrase[0] != 'y' && phrase[0] != 'n')
        {
            phrase[strlen(phrase) - 1] = '\0';
            tokens += 9;
            PRINT_COLOR(RED, "%s не является допустимым вводом, введите y или n\n", phrase);
        }
        else
        {
            if (phrase[1] == '\n' || check_clear_buf(phrase + 1))
            {
                ch = phrase[0];
                read_successfully = true;
            }
            else
            {
                tokens += 9;
                phrase[strlen(phrase) - 1] = '\0';
                PRINT_COLOR(RED, "%s не является допустимым вводом, введите y или n\n", phrase);
            }
        }

    }

    return ch;
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