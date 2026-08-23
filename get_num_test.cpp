#include "quadratic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *GET_NUM_DATA_FILE = "get_num_ref";
const char *GET_NUM_STRINGS_FILE = "get_num_strings";

/**
 @brief                     запускает несколько тестов run_get_num_test

 @param                     нет
 @return                    число успешных тестов
 */

int run_get_num_tests(void)
{

    FILE *fp_data = NULL, *fp_strings = NULL;
    my_assert(fp_data = fopen(GET_NUM_DATA_FILE, "r"));
    my_assert(fp_strings = fopen(GET_NUM_STRINGS_FILE, "r"));
    int test_num = 0;
    int not_error = 0;

    int sum_of_fails = 0;

    while (fscanf(fp_data, "%d %d", &test_num, &not_error) == 2)
    {
        sum_of_fails += run_get_num_test(not_error, test_num, fp_data, fp_strings);
    }

    my_assert(!fclose(fp_data));
    my_assert(!fclose(fp_strings));
    return sum_of_fails;
}

/**
 @brief                     запускает тесты функции get_num

 @param                     нет
 @return                    ничего
 */

void test_get_num(void)
{
    int sum_of_fails = 0;
    PRINT_COLOR(PURPLE, "Старт тестирования get_num. sum_of_fails = 0\n");

    sum_of_fails = run_get_num_tests();

    PRINT_COLOR(PURPLE, "Конец тестирования get_num. sum_of fails = %d\n", sum_of_fails);
    if (sum_of_fails == 0)
    {
        PRINT_COLOR(GREEN, "get_num работает идеально!\n\n");
    }
}

/**
 @brief                      проводит тест функции get_num_test

 @param [out]   fp_strings   указатель на файл с строками для обработки
 @param [out]   fp_strings   указатель на файл с кодировкой ввода
 @param [in]    not_error    1 - число считано успешно, 0 - неудачно
 @param [in]    test_num     указатель на строку, которую должна обработать функция
 @return                     0 - тест пройден, 1 - нет
 */

int run_get_num_test(int not_error, int test_num, FILE *fp_data, FILE *fp_strings)
{
    my_assert(fp_data);
    my_assert(fp_strings);

    char line[MAX_PHRASE_SIZE] = {};
    double ref_meaning = 0;
    double meaning = 0;

    if (not_error)
    {
        fscanf(fp_data, "%lf", &ref_meaning);
        fgets(line, INPUT_BUFFER_SIZE * 2, fp_strings);
        meaning = get_num(NULL, 1, line);
        if (!meanings_are_equal(meaning, ref_meaning))
        {
            PRINT_COLOR(EXTRA_RED, "%d Test FAILED: ref_meaning = %g\n"
                "           GOT:     meaning = %g\n\n", test_num, ref_meaning, meaning);
            return 1;
        }
    }
    else
    {
        meaning = get_num(NULL, 1, line);
        if (!is_zero(meaning))
        {
            PRINT_COLOR(EXTRA_RED, "%d Test FAILED: ref_meaning = %g\n"
                "           GOT:     meaning = %g\n\n", test_num, ref_meaning, meaning);
            return 1;
        }
    }

    return 0;
}