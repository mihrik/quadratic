#define COLOR
#include <stdio.h>
#ifdef COLOR
    #include "colors.h"
#else
    #define RED "\033[0m"
    #define EXTRA_RED "\033[0m"
    #define GREEN "\033[0m"
    #define ORANGE "\033[0m"
    #define BLUE "\033[0m"
    #define YELLOW "\033[0m"
    #define PURPLE "\033[0m"
    #define EXTRA_BLUE "\033[0m"
    #define LIGHT_BLUE "\033[0m"
    #define EXTRA_GREEN "\033[0m"
    #define RESET_COLOR "\033[0m"
    #define PRINT_COLOR(x, ...)       \
        printf(x __VA_ARGS__);
#endif
#define my_assert(x) \
    if (!(x)) \
    { \
        fprintf(stderr, "Не проходит проверку. Ошибка в %s:%d в условии: %s\n", __FILE__, __LINE__, #x); \
        exit(EXIT_FAILURE); \
    }

const double EPS = 1e-9; // погрешность сравнения чисел double
const int INPUT_BUFFER_SIZE = 100; // макс длина массива для пользовательского ввода
const int MAX_PHRASE_SIZE = 200; // макс длина массива для ввода с файла
const int LEN_OF_ANSWER = 400; // макс длина массива для хранения ответа
const int SIZE = 77; // нечетное число, задает размер выводимого графика
const int MAX_TOKENS = 10000; // максимальное количество токенов для программы
const int MAX_GRAPHS = 10000; // максимальное количество выведенных графиков за программу

const char* const ASCII_ARTS[] = {"arts/shrek", "arts/mole", "arts/some_bird", "arts/squid", "arts/sponge_bob", "arts/teddy", "arts/old_car", "arts/vamp"};
// массив названий файлов ascii art используемых в программе

typedef struct quadratic // инфо о квадратном уравнении
{
    double a; // коэфф. перед x^2
    double b; // коэфф. перед x
    double c; // свободный член
    double x1; // первый корень
    double x2; // второй корень
    int number_of_roots; // число корней этого уравнения
} quadratic;

enum root_cases // вариации решений квадратного уравнения
{
    IMAGINARY = -1,
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    INFINITY_SOLUTIONS
};

enum modes // для функции get_num
{
    classic = 0,
    test = 1
};

enum arg_values // для анализа количества аргументов командной строки
{
    ONE_VALUE = 1,
    TWO_VALUES,
    THREE_VALUES
};

double eval_discriminant(quadratic eq);
int root_count_and_solution(quadratic *object);
void quadratic_solution(void);
double get_num(double *pt, int mode, const char *for_compare);
int get_option(void);
int isinf_or_isnan(double num);
int is_zero(double num);
void coeffs_initialization(quadratic * ptr);
void clear_buffer(void);
int check_clear_buf(char *buffer);
int run_one_test(quadratic *ref, int test_num, char const name_of_file[]);
int meanings_are_equal(double x1, double x2);
void sort_roots(double *x1, double *x2);
int run_tests(void);
int one_get_num_test(char *line, int test_num);
int run_get_num_tests(void);
void test_quadratic(void);
void test_get_num(void);
void big_test(void);
int run_get_num_test(int not_error, int test_num, FILE *fp_strings, FILE *fp_data);
void print_ascii(FILE *art_addres, int times);
void print_rand_ascii(void);
void print_greeting(void);
void nice_output(char *output);
void beautiful_print(const char *line);
void print_goodbye(void);
void print_inf_roots(void);
void print_no_roots(void);
void print_no_real_roots(void);
void print_a(void);
void print_b(void);
void print_c(void);
void print_continue_message(void);
void print_phrase(const char* const file_name);
int read_file_coeffs(quadratic **quadratic_equation);
void graphic(double a, double b, double c);
int amount_of_tests(void);
void show_solution(char *line);
void output(quadratic *solution, char **console);
void arg_analysis(char **color_mode, char **test_mode, char *argv[], int argc);
void check_tokens(void);
void print_graph_message(void);
