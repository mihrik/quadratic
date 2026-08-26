#include <math.h>
#include "quadratic.h"
#include <stdio.h>
#include <stdlib.h>

static quadratic quadratic_tests[] =
{
        {.a = 0, .b = 0, .c = 67, .x1 = NAN, .x2 = NAN, .number_of_roots = NO_SOLUTIONS},
        {.a = 1, .b = 1, .c = 1, .x1 = NAN, .x2 = NAN, .number_of_roots = IMAGINARY},
        {.a = 17, .b = -34, .c = 17, .x1 = 1, .x2 = NAN, .number_of_roots = ONE_SOLUTION},
        {.a = 0, .b = 0, .c = 0, .x1 = NAN, .x2 = NAN, .number_of_roots = INFINITY_SOLUTIONS},
        {.a = 17, .b = -31, .c = 6, .x1 = 0.2201190578644, .x2 = 1.603410353900, .number_of_roots = TWO_SOLUTIONS},
        {.a = 23, .b = -12, .c = (double)36 / 23, .x1 = (double)6 / 23, .x2 = NAN, .number_of_roots = ONE_SOLUTION},
        {.a = -37, .b = 24, .c = (double)-144 / 37, .x1 = (double)12 / 37, .x2 = NAN, .number_of_roots = ONE_SOLUTION},
        {.a = 31, .b = 4, .c = -15, .x1 = -0.7631099299, .x2 = 0.6340776719, .number_of_roots = TWO_SOLUTIONS}
};

const char *QUADRATIC_TEST_FILE = "quadratic_references";
/**
 @brief                  запускает тест квадратного уравнения

 @param [out]  ref       указатель на структуру хранящую коэффициенты уравнения и его решения
 @param [in]  test_num
 @return                 1 - тест не пройден, 0 - пройден

 @note                   если коэффициенты являются inf или nan то избегает прерывания программы
 */

int run_one_test(quadratic *ref, int test_num, char const name_of_file[])
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
            "          GOT: number_of_roots = %6d,    x1 = %6lg,    x2 = %6lg\n"
            "        INPUT: %s\n\n", test_num, ref->a, ref->b, ref->c, ref->number_of_roots, ref->x1, ref->x2,
            get->number_of_roots, get->x1, get->x2, name_of_file);

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
    int sum_of_fails = 0;

    quadratic *quadratic_equations = NULL;
    int len = read_file_coeffs(&quadratic_equations);

    for (unsigned int test_num = 0; test_num < sizeof(quadratic_tests) / sizeof(quadratic); test_num++)
    {
        sum_of_fails += run_one_test(&quadratic_tests[test_num], (int)test_num + 1, "array_tests");
    }

    for (unsigned int test_num = 0; (int)test_num < len; test_num++)
    {
        sum_of_fails += run_one_test(quadratic_equations + test_num, (int)test_num + 1, "file_tests");
    }

    free(quadratic_equations);

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

/**
 @brief                  присваивает указатель на массив из структур с данными из файла

 @param [out]            указатель на указатель на массив который должен быть изменен

 @return                 количество считанных структур
 */

int read_file_coeffs(quadratic **quadratic_equation)
{
    FILE *fp = NULL;
    my_assert(fp = fopen(QUADRATIC_TEST_FILE, "r"));
    quadratic *quadratic_equations = (quadratic *) calloc(1, sizeof(quadratic));
    unsigned int i = 0;

    while(fscanf(fp, "%lf %lf %lf %d", &quadratic_equations[i].a, &quadratic_equations[i].b,
        &quadratic_equations[i].c, &quadratic_equations[i].number_of_roots) == 4)
    {

        switch(quadratic_equations[i].number_of_roots)
        {
            case          IMAGINARY:
            case       NO_SOLUTIONS:
            case INFINITY_SOLUTIONS: quadratic_equations[i].x1 = NAN;
                                     quadratic_equations[i].x2 = NAN;
                        break;
            case       ONE_SOLUTION: fscanf(fp, "%lf", &quadratic_equations[i].x1);
                                     quadratic_equations[i].x2 = NAN;
                        break;
            case      TWO_SOLUTIONS: fscanf(fp, "%lf %lf", &quadratic_equations[i].x1, &quadratic_equations[i].x2);
                        break;
            default:
                        break;

        }
        i++;
        quadratic_equations = (quadratic *)realloc(quadratic_equations, (i + 1) * sizeof(quadratic));
    }

    *quadratic_equation = quadratic_equations;
    my_assert(!fclose(fp));
    return (int)i;
}