#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    PRINT_EXTRA_GREEN("Эта программа решает квадратное уравнение в действительных "
    "решениях\n");
    PRINT_GREEN("Квадратное уравнение имеет вид ax^2 + bx + c\n");
    quadratic_solution();

    PRINT_GREEN("Завершение программы\n");
    return 0;
}
