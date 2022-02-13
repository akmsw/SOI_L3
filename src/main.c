/**
 * @file main.c
 * @author Bonino, Francisco Ignacio
 * @brief Programa principal del laboratorio 3 de Sistemas Operativos I.
 * @version 1.5.2
 * @since 2021-08-31
 */

// Librerías a utilizar.

#include "include/lab3_utilities.h"
#include "include/cjson_x.h"
#include <getopt.h>
#include <regex.h>

/**
 * @brief Función principal del programa. Se ofrecen
 *        distintas funcionalidades en base a los
 *        argumentos recibidos por parámetro.
 * 
 * @param argc Cantidad de argumentos recibidos.
 * @param argv Arreglo con los argumentos recibidos.
 * 
 * @returns Si el programa finalizó correctamente.
 */
int main(int argc, char **argv)
{
    int arg = 0;

    bool flag_s = false;
    bool flag_a = false;
    bool flag_d = false;
    bool flag_j = false;
    bool flag_h = false;

    fprintf(stdout, "----- LAB #3 - OPERATIVES SYSTEMS I -----\n\n");

    regex_t regex;

    if (regcomp(&regex, "[^jd]", 0) != 0)
    {
        fprintf(stderr, "ERROR [main.c]: REGEX problem. Program will suht down.\n");

        return EXIT_FAILURE;
    }

    if (argc == 1 || argc > 4)
    {
        fprintf(stderr, "ERROR [main.c]: This program must be executed with at least 1 (one) and\
                \n                no more than 3 (three) arguments.\
                \n                Run this with '-h' to view a list of accepted arguments.\n");
        return EXIT_FAILURE;
    }

    while ((arg = getopt(argc, argv, "-:hs::a::d::j")) != -1)
        switch (arg)
        {
            case 'h':
            {
                if (flag_h)
                {
                    fprintf(stderr, "ERROR [main.c]: Received '-h' argument more than once.\n");

                    return EXIT_FAILURE;
                }

                if (optarg != NULL)
                {
                    fprintf(stderr, "ERROR [main.c]: '-h' argument does not support additional parameters.\n");

                    return EXIT_FAILURE;
                }

                flag_h = true;

                break;
            }

            case 's':
            {
                if (flag_s)
                {
                    fprintf(stderr, "ERROR [main.c]: Received '-s' argument more than once.\n");

                    return EXIT_FAILURE;
                }

                if (optarg != NULL && (regexec(&regex, optarg, 0, NULL, 0) == 0))
                {
                    fprintf(stderr, "ERROR [main.c]: '-s' argument does not support other parameter than '-j', 'j', '-d' or 'd'.\n");

                    return EXIT_FAILURE;
                }

                if (arg_has_param(optarg, 'j'))
                    flag_j = true;

                if (arg_has_param(optarg, 'd'))
                    flag_d = true;

                flag_s = true;

                break;
            }

            case 'a':
            {
                if (flag_a)
                {
                    fprintf(stderr, "ERROR [main.c]: Received '-a' argument more than once.\n");

                    return EXIT_FAILURE;
                }

                if (optarg != NULL && (regexec(&regex, optarg, 0, NULL, 0) == 0))
                {
                    fprintf(stderr, "ERROR [main.c]: '-a' argument does not support other parameter than '-j', 'j', '-d' or 'd'.\n");

                    return EXIT_FAILURE;
                }

                if (arg_has_param(optarg, 'j'))
                    flag_j = true;

                if (arg_has_param(optarg, 'd'))
                    flag_d = true;

                flag_a = true;

                break;
            }

            case 'd':
            {
                if (flag_d)
                {
                    fprintf(stderr, "ERROR [main.c]: Received '-d' argument more than once.\n");

                    return EXIT_FAILURE;
                }

                if (optarg != NULL)
                {
                    fprintf(stderr, "ERROR [main.c]: '-d' argument does not support additional parameters.\n");

                    return EXIT_FAILURE;
                }

                flag_d = true;

                break;
            }

            case 'j':
            {
                if (flag_j)
                {
                    fprintf(stderr, "ERROR [main.c]: Received '-j' argument more than once.\n");

                    return EXIT_FAILURE;
                }

                if (optarg != NULL)
                {
                    fprintf(stderr, "ERROR [main.c]: '-j' argument does not support additional parameters.\n");

                    return EXIT_FAILURE;
                }

                flag_j = true;

                break;
            }

            case ':':
                fprintf(stderr, "ERROR [main.c]: Missing parameter for %c argument.\n", optopt);
                return EXIT_FAILURE;

            case 1:

            default:
                fprintf(stderr, "ERROR [main.c]: Received unknown/unsupported/unexpected argument.\n");
                return EXIT_FAILURE;
        }

    if (flag_h)
    {
        if (flag_a || flag_d || flag_j || flag_s)
        {
            fprintf(stderr, "ERROR [main.c]: Invalid arguments combination.\
                            \n                '-h' only displays the help menu.\
                            \n                It should not be combined with any other arguments.\n");

            return EXIT_FAILURE;
        }

        print_help();

        return EXIT_SUCCESS;
    }

    if (flag_s)
    {
        if (flag_a)
        {
            fprintf(stderr, "ERROR [main.c]: Invalid arguments combination.\n");

            return EXIT_FAILURE;
        }
        else if (flag_j)
            cjson_s();
        else
            excercise_1_L2();

        if (flag_d)
        {
            fsys_ex();

            return EXIT_SUCCESS;
        }

        return EXIT_SUCCESS;
    }

    if (flag_a)
    {
        if (flag_j)
            cjson_a("/proc/version");
        else
            excercise_2_L2("/proc/version");

        if (flag_d)
            fsys_ex();

        return EXIT_SUCCESS;
    }

    if (flag_d)
    {
        if (flag_j)
        {
            fprintf(stderr, "ERROR [main.c]: Invalid arguments combination.\
                            \n                '-d' argument uses by default the cJSON format to print its output.\n");

            return EXIT_FAILURE;
        }

        fsys_ex();

        return EXIT_SUCCESS;
    }

    if (flag_j)
    {
        fprintf(stderr, "ERROR [main.c]: Argument '-j' must be prefixed.\n");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}