#define COLOR
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
#define to_int(x) !(x)
const double EPS = 1e-9;
const int INPUT_BUFFER_SIZE = 50;

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
    off = 0,
    on = 1
};

double eval_discriminant(quadratic eq);
int root_count_and_solution(quadratic *object);
void quadratic_solution(void);
void get_num(double *pt);
int get_option(void);
void my_assert(int mode, int n, const char* file_name);
int isinf_or_isnan(double num);
int is_zero(double num);
void coeffs_initialization(quadratic * ptr);
void clear_buffer(void);
int check_clear_buf(char *buffer);