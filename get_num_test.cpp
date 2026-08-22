#include "quadratic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *GET_NUM_RESULTS_FILE = "get_num_results";
const char *GET_NUM_DATA_FILE = "get_num_data";
const char *GET_NUM_STRINGS_FILE = "get_num_strings";

/**
 @brief                     аналог get_num из "quadratic.h", специально для корректной работы с тестами исключен цикл

 @param [out]   r_compare   указатель на строку, которую должна обработать функция
 @return                    обработанное число если корректный ввод, 0 - если нет

 @note                      при некорректном вводе сохраняет предупреждение о нем в файл GET_NUM_RESULTS_FILE
 */

double get_num_test(const char *for_compare)
{
    my_assert(for_compare);
    FILE *fp = NULL;
    my_assert(fp = fopen(GET_NUM_RESULTS_FILE, "w"));

    double num = 0;
    char buffer[INPUT_BUFFER_SIZE] = {};
    char *end = buffer;
    int ch = '\0';
    int i = 0;
    char mem = '\0';
    bool is_spaces = false;

    for ( ; i < INPUT_BUFFER_SIZE - 1 && ch != '\n' && ch != EOF; i++)
    {
        ch = *(for_compare+i);
        buffer[i] = ch;
    }

    if (buffer[0] == '\n')
    {
        fprintf(fp, "недопустимый формат ввода\n");
        my_assert(!fclose(fp));
        return 0;
    }

    num = strtod(buffer, &end);
    mem = buffer[i-1];
    buffer[i-1] = '\0';
    is_spaces = check_clear_buf(end);

    if (is_spaces)
    {
        my_assert(!fclose(fp));
        return num;
    }
    buffer[i-1] = mem;

    if (*end != '\n')
    {
        buffer[i-1] = '\0';
        fprintf(fp, "%s не является числовым вводом\n", buffer);
        my_assert(!fclose(fp));
        return 0;
    }
    return num;
}

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
    char line[MAX_PHRASE_SIZE] = {};
    char *ptr = NULL;
    double ref_meaning = 0;
    double meaning = 0;

    if (not_error)
    {
        fscanf(fp_data, "%lf", &ref_meaning);
        fgets(line, INPUT_BUFFER_SIZE * 2, fp_strings);
        meaning = get_num_test(line);
        if (!meanings_are_equal(meaning, ref_meaning))
        {
            PRINT_COLOR(EXTRA_RED, "%d Test FAILED: ref_meaning = %g\n"
                "          GOT: meaning = %g\n\n", test_num, ref_meaning, meaning);
            return 1;
        }
    }
    else
    {
        FILE *fp_results = NULL;
        my_assert(fp_results = fopen(GET_NUM_RESULTS_FILE, "r"));

        fgets(line, INPUT_BUFFER_SIZE, fp_strings);
        meaning = get_num_test(line);
        if ((ptr = strchr(line, '\n')) != NULL)
        {
            *ptr = '\0';
        }

        char current_line[MAX_PHRASE_SIZE] = {};

        fgets(current_line, MAX_PHRASE_SIZE, fp_results);
        strcat(line, " не является числовым вводом\n");
        if (strcmp(line, current_line) != 0)
        {
        PRINT_COLOR(EXTRA_RED, "%d Test FAILED: ref_line = %s\n"
            "          GOT: line     = %s\n\n", test_num, line, current_line);

        my_assert(!fclose(fp_results));
        return 1;
        }
        my_assert(!fclose(fp_results));

    }

    return 0;
}