#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    big_test();

    PRINT_COLOR(EXTRA_GREEN, "Эта программа решает квадратное уравнение в действительных "
    "решениях\n");
    PRINT_COLOR(GREEN, "Квадратное уравнение имеет вид ax^2 + bx + c\n");
    quadratic_solution();

    PRINT_COLOR(GREEN, "Завершение программы\n");
    return 0;
}
