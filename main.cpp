#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int tokens = 0;
int graph_limit = 0;

int main(int argc, char *argv[])
{
    print_rand_ascii();
    print_greeting();


    char primary_str[8] = "";
    char *test_mode = primary_str;

    arg_analysis(&test_mode, argv, argc);

    if (strcmp(test_mode, "on") == 0)
    {
        big_test();
    }

    quadratic_solution();

    print_goodbye();
    return 0;
}
// TODO token usage
