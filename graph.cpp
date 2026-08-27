#include <stdio.h>
#include "quadratic.h"
#include <math.h>
#include <time.h>

/**
 @brief                  выводит график заданной функции

 @param [in]  a          коэффициент а
 @param [in]  b          коэффициент b
 @param [in]  c          коэффициент с

 @return                 количество непройденных тестов
 @note                   берет данные из файла "quadratic_references"
 */

void graphic(double a, double b, double c)
{
    struct timespec time = {.tv_sec = 0, .tv_nsec = 500000};

    char graph[SIZE][SIZE] = {};

    for (int i = 0; i < SIZE; i++)
    {
        graph[SIZE / 2][i] = '_';
    }
    for (int i = 0; i < SIZE; i++)
    {
        graph[i][SIZE / 2] = '|';
    }

    graph[SIZE / 2][SIZE - 1] = '\\';
    graph[SIZE / 2 + 1][SIZE - 1] = '/';
    graph[SIZE / 2 + 2][SIZE - 1] = 'x';

    graph[0][SIZE  / 2] = '/';
    graph[0][SIZE / 2 + 1] = '\\';
    graph[0][SIZE / 2 + 2] = 'y';
    // x in (-40, 40)
    double y_l = 1600 * a - 40 * b + c;
    double y_r = 1600 * a + 40 * b + c;

    double y_scale = (double)SIZE * 2 / fmax(fabs(y_l), fabs(y_r));
    for (int column = 0; column < SIZE; column++)
    {
        double x = (column - (double)SIZE / 2);

        double y = a * x * x + b * x + c;
        y *= y_scale;

        int row = SIZE / 2 - (int)y;

        if (row >= 0 && row < SIZE)
            graph[row][column] = '*';
    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j< SIZE; j++)
        {
            if (graph[i][j] != '|' && graph[i][j] != '_' && graph[i][j] != '*' && graph[i][j] != '\\' && graph[i][j] != '/' && graph[i][j] != 'x' && graph[i][j] != 'y')
            {
                nanosleep(&time, NULL);
                printf("%c", ' ');
            }
            else
            {
                nanosleep(&time, NULL);
                printf("%c", graph[i][j]);
            }
        }
        printf("\n");
    }
}