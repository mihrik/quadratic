#include <math.h>
#include "quadratic.h"
#include <stdio.h>
#include <stdlib.h>

const char *QUADRATIC_TEST_FILE = "quadratic_references";
/**
 @brief                  запускает тест квадратного уравнения

 @param [out]  ref       указатель на структуру хранящую коэффициенты уравнения и его решения
 @param [in]  test_num
 @return                 1 - тест не пройден, 0 - пройден

 @note                   если коэффициенты являются inf или nan то избегает прерывания программы
 */

int run_one_test(quadratic *ref, int test_num)
{
    my_assert(ref);

    if (isinf_or_isnan(ref->a))
    {
        //PRINT_COLOR(EXTRA_RED, "%d Test FAILED: Коэффициент a не должен являться бесконечностью или nan\n", test_num);
        return 0;
    }

    if (isinf_or_isnan(ref->b))
    {
        //PRINT_COLOR(EXTRA_RED, "%d Коэффициент b не должен являться бесконечностью или nan\n", test_num);
        return 0;
    }

    if (isinf_or_isnan(ref->c))
    {
        //PRINT_COLOR(EXTRA_RED, "%d Коэффициент c не должен являться бесконечностью или nan\n", test_num);
        return 0;
    }

    quadratic equation = {0, 0, 0, 0, 0, 0};
    quadratic *get = &equation;

    get->a = ref->a;
    get->b = ref->b;
    get->c = ref->c;

    get->x1 = NAN, get->x2 = NAN;
    get->number_of_roots = root_count_and_solution(get);

    sort_roots(&(get->x1), &(get->x2));
    sort_roots(&(ref->x1), &(ref->x2));

    if (get->number_of_roots != ref->number_of_roots || !meanings_are_equal(get->x1, ref->x1) ||
        !meanings_are_equal(get->x2, ref->x2))
    {
        PRINT_COLOR(EXTRA_RED, "%d Test FAILED:               a = %6lg,     b = %6lg,     c = %6lg\n"
            "     EXPECTED: number_of_roots = %6d, x1ref = %6lg, x2ref = %6lg\n"
            "          GOT: number_of_roots = %6d,    x1 = %6lg,    x2 = %6lg\n\n",
            test_num, ref->a, ref->b, ref->c, ref->number_of_roots, ref->x1, ref->x2,
            get->number_of_roots, get->x1, get->x2);

        return 1;
    }

    return 0;
}

/**
 @brief                  запускает многократно функцию run_one_test

 @param                  нет

 @return                 количество непройденных тестов
 @note                   берет данные из файла "quadratic_references"
 */

int run_tests(void)
{
    FILE *fp = NULL;
    my_assert(fp = fopen(QUADRATIC_TEST_FILE, "r"));

    int test = 0;
    int sum_of_fails = 0;
    quadratic quadratic_equation = {0, 0, 0, 0, 0, NO_SOLUTIONS};

    while(fscanf(fp, "%d %lf %lf %lf %d", &test, &quadratic_equation.a, &quadratic_equation.b,
        &quadratic_equation.c, &quadratic_equation.number_of_roots) == 5)
    {
        switch(quadratic_equation.number_of_roots)
        {
            case          IMAGINARY: quadratic_equation.x1 = NAN;
                                     quadratic_equation.x2 = NAN;
                        break;
            case       NO_SOLUTIONS: quadratic_equation.x1 = NAN;
                                     quadratic_equation.x2 = NAN;
                        break;
            case       ONE_SOLUTION: fscanf(fp, "%lf", &quadratic_equation.x1);
                                     quadratic_equation.x2 = NAN;
                        break;
            case      TWO_SOLUTIONS: fscanf(fp, "%lf %lf", &quadratic_equation.x1, &quadratic_equation.x2);
                        break;
            case INFINITY_SOLUTIONS: quadratic_equation.x1 = NAN;
                                     quadratic_equation.x2 = NAN;
            default                :
                        break;
        }
        sum_of_fails += run_one_test(&quadratic_equation, test);
    }

    my_assert(!fclose(fp));

    return sum_of_fails;
}

/**
 @brief                  запускает тест функции solve_quadratic()

 @param                  нет

 @return                 нет
 */

void test_quadratic(void)
{
    int sum_of_fails = 0;
    PRINT_COLOR(PURPLE, "Старт тестирования quadratic_solution. sum_of_fails = 0\n");

    sum_of_fails = run_tests();

    PRINT_COLOR(PURPLE, "Конец тестирования quadratic_solution. sum_of fails = %d\n", sum_of_fails);
    if (sum_of_fails == 0)
    {
        PRINT_COLOR(GREEN, "quadratic_solution работает идеально!\n\n");
    }
}
