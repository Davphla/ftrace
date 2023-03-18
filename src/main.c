/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#include "main.h"

static void get_flags(const int ac, char *const *av)
{
    int option;

    while ((option = getopt_long(ac, av, "h", long_options, NULL)) != EOF) {
        (option == 'h') ? usage(EXIT_SUCCESS) : usage(EXIT_ERROR);
    }
}

static void start(const int ac, char *const *av)
{
    get_flags(ac, av);
    main_ftrace(av);
}

int main(const int ac, char *const *av)
{
    if (ac < 2)
        return EXIT_ERROR;
    start(ac, av);
    if (g_exit_status)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
