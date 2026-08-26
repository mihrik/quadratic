#define COLOR
#include <stdio.h>
#ifdef COLOR
    #include "colors.h"
#else
    #define RED ""
    #define GREEN ""
    #define EXTRA_GREEN ""
    #define BLUE ""
    #define RESET_COLOR ""
    #define PRINT_EXTRA_GREEN(...) printf(__VA_ARGS__)
    #define PRINT_RED(...) printf(__VA_ARGS__)
    #define PRINT_BLUE(...) printf(__VA_ARGS__)
    #define PRINT_GREEN(...) printf(__VA_ARGS__)
#endif
#define my_assert(x) \
    if (!(x)) \
    { \
        fprintf(stderr, "Не проходит проверку. Ошибка в %s:%d\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }

const double EPS = 1e-9;
const int INPUT_BUFFER_SIZE = 100;
const int MAX_PHRASE_SIZE = 200;

const char* const ASCII_ARTS[] = {"arts/shrek", "arts/mole", "arts/some_bird", "arts/squid", "arts/sponge_bob", "arts/teddy", "arts/old_car", "arts/vamp"};

typedef struct quadratic
{
    double a; // коэфф. перед x^2
    double b; // коэфф. перед x
    double c; // свободный член
    double x1; // первый корень
    double x2; // второй корень
    int number_of_roots; // число корней этого уравнения
} quadratic;

enum root_cases
{
    IMAGINARY = -1,
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    INFINITY_SOLUTIONS
};

enum modes
{
    classic = 0,
    test = 1
};

enum arg_values
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
// todo скрипты .sh .bush
