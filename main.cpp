#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "quadratic.h"
#include <stdbool.h>

int main(void)
{
    puts("Эта программа решает квадратное уравнение в действительных "
    "решениях");
    puts("Квадратное уравнение имеет вид ax^2 + bx + c");
    quadratic_solution();

    puts("Завершение программы");
    return 0;
}
