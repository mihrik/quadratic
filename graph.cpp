#include <stdio.h>
#include "quadratic.h"
#include <math.h>
#define SIZE 55 // even num

void graphic(double a, double b, double c)
{
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

    double y_scale = (SIZE / 2.0) / fmax(fabs(y_l), fabs(y_r));
    for (int column = 0; column < SIZE; column++)
    {
        double x = (double)(column - SIZE / 2);

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
                printf("%c", ' ');
            }
            else
            {
                printf("%c", graph[i][j]);
            }
        }
        printf("\n");
    }
}