const double EPS = 1e-9;
const int INPUT_BUFFER_SIZE = 50;

typedef struct quadratic
{
    double a; // коэфф. перед x^2
    double b; // коэфф. перед x
    double c; // свободный член
    double x1; // первый корень
    double x2; // второй корень
} quadratic;

enum root_cases
{
    IMAGINARY = -1,
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    INFINITY_SOLUTIONS
};

double eval_discriminant(quadratic eq);
int root_count(quadratic *object);
void quadratic_solution(void);
void get_num(double *pt);
char get_char(void);
