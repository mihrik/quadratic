#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


int main(int argc, char *argv[])
{
    print_rand_ascii();
    print_greeting();


    char primary_str[] = "";
    char *color_mode = primary_str;
    char *test_mode = primary_str;


    switch(argc)
    {
        case ONE_VALUE   :
            break;
        case TWO_VALUES  : color_mode = argv[1];
            break;
        case THREE_VALUES: color_mode = argv[1];
                           test_mode = argv[2];
            break;
        default          : puts("Превышено максимальное количество аргументов командной строки"
                            ". Их максимальное количество = 3");
            break;
    }

    if (strcmp(test_mode, "on") == 0)
    {
        big_test();
    }

    if (strcmp(color_mode, "-c") == 0)
    {
        ;
    }

    quadratic_solution();

    print_goodbye();
    return 0;
}

// todo sleep
// todo graphic
// polynomial solution
