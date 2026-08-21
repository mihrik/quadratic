#define RED "\033[91m"
#define GREEN "\033[92m"
#define BLUE "\033[94m"
#define EXTRA_GREEN "\033[32m"
#define RESET_COLOR "\033[0m"
#define PRINT_EXTRA_GREEN(...)       \
    printf(EXTRA_GREEN __VA_ARGS__); \
    printf(RESET_COLOR)
#define PRINT_RED(...)       \
    printf(RED __VA_ARGS__); \
    printf(RESET_COLOR)
#define PRINT_BLUE(...)       \
    printf(BLUE __VA_ARGS__); \
    printf(RESET_COLOR)
#define PRINT_GREEN(...)       \
    printf(GREEN __VA_ARGS__); \
    printf(RESET_COLOR)