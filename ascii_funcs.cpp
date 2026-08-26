#include "quadratic.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/**
 @brief                      выводит классную картинку

 @param [out]   art_addres   адрес файла с картинкой
 @return                     ничего
 */

void print_ascii(FILE *art_addres, int times)
{
    char one_line[300];
    while(fgets(one_line, 300, art_addres))
    {
        printf("\033[%dC", times);
        fputs(one_line, stdout);
    }

    puts("\n");
}

/**
 @brief              печатает рандомную крутую картинку

 @param              нет
 @return             ничего
 */

void print_rand_ascii(void)
{
    srand((unsigned int) time(0));

    FILE *fp_art = NULL;
    my_assert(fp_art = fopen(ASCII_ARTS[(unsigned long)rand() % (sizeof (ASCII_ARTS) / sizeof(ASCII_ARTS[0]))], "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

/**
 @brief              печатает афигенное приветствие

 @param              нет
 @return             ничего
 */

void print_greeting(void)
{
    FILE *fp_art = NULL;
    my_assert(fp_art = fopen("arts/greeting", "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

/**
 @brief                  делает вывод выражений типа 'x = 98.2' в виде ascii art символов

 @param [out]            указатель на выражение

 @return                 ничего
 */

void nice_output(char *output)
{
    FILE *fp = NULL;
    my_assert(output);
    int i = 1;
    while(*output)
    {

    char name_of_file[100] = "symbols/";

        switch(*output)
        {
        // TODO: fix after grandad lection
            case '-':   { strcat(name_of_file, "minus"); break; }
            case '.':   { strcat(name_of_file, "dot"  ); break; }
            case '=':   { strcat(name_of_file, "equal"); break; }
            case '+':   { strcat(name_of_file, "plus" ); break; }
            case 'x':
            case '9':
            case '8':
            case '7':
            case '6':
            case '5':
            case '4':
            case '3':
            case '2':
            case '1':
            case '0':
            case 'e':   {
                            name_of_file[8] = *output;
                            break;
                        }


            default :   my_assert(0);
        }
        my_assert(fp = fopen(name_of_file, "r"));
        print_ascii(fp, i * 9);
        printf("\033[8A");

        i++;
        output++;
    }
    puts("\n\n\n\n\n\n\n\n");
    my_assert(!fclose(fp));
}

/**
 @brief                  функция для вывода нужного ascii art

 @param [out]            название файла с рисунком

 @return                 нет
 */

void print_phrase(const char* const file_name)
{
    FILE *fp_art = NULL;
    char phrase[100] = "arts/";
    strcat(phrase, file_name);
    my_assert(fp_art = fopen(phrase, "r"));
    print_ascii(fp_art, 10);
    my_assert(!fclose(fp_art));
}

/**
 @brief                  функция для вывода прощального сообщения

 @param                  нет

 @return                 нет
 */

void print_goodbye(void)
{
    print_phrase("goodbye");
}

/**
 @brief                  функция для вывода сообщения о бесконечном количестве корней

 @param                  нет

 @return                 нет
 */

void print_inf_roots(void)
{
    print_phrase("inf_roots");
}

/**
 @brief                  функция для вывода сообщения об отсутствии корней

 @param                  нет

 @return                 нет
 */

void print_no_roots(void)
{
    print_phrase("no_roots");
}

/**
 @brief                  функция для вывода сообщения об отсутствии реальных корней

 @param                  нет

 @return                 нет
 */

void print_no_real_roots(void)
{
    print_phrase("no_real_roots");
}

/**
 @brief                  функция для вывода приглашения к вводу первого коэффициента
 @param                  нет

 @return                 нет
 */

void print_a(void)
{
    print_phrase("print_a");
}

/**
 @brief                  функция для вывода приглашения к вводу второго коэффициента
 @param                  нет

 @return                 нет
 */

void print_b(void)
{
    print_phrase("print_b");
}

/**
 @brief                  функция для вывода приглашения к вводу третьего коэффициента
 @param                  нет

 @return                 нет
 */

void print_c(void)
{
    print_phrase("print_c");
}


/**
 @brief                  функция для вывода сообщения о продолжении программы
 @param                  нет

 @return                 нет
 */
void print_continue_message(void)
{
    print_phrase("print_continue_message");
}