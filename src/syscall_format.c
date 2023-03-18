/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#include "syscall_format.h"
#include "ftrace.h"
#include <stdio.h>
#include <string.h>

static char *concat_args(fmt_type_t args[])
{
    char *str;
    size_t len = 0;
    size_t offset = 0;
    int nb_args = 0;

    for (int i = 1; i < NB_PARAMS && args[i]; i++, nb_args++) {
        len += strlen(args[i]);
    }
    len += nb_args * 2;
    str = calloc(len + 1, 1);
    for (int i = 1; i < nb_args + 1; i++) {
        strcpy(str + offset, args[i]);
        offset += strlen(args[i]);
        if (nb_args > 1 && i < nb_args) {
            strcpy(str + offset, ", ");
            offset += 2;
        }
    }
    str[len] = '\0';
    return str;
}

static void display_args(const register_offset_t *registers,
    const syscall_t table, fmt_type_t args[])
{
    for (int i = 0; i < table.nb_args + 1; i++) {
        if (asprintf(&args[i], "%#llx", registers[i]) == -1)
            FATAL("asprintf failed");
    }
}

void print_syscall(const struct user_regs_struct *regs)
{
    const syscall_t table = SYSCALL_TABLE[regs->rax];
    const register_offset_t registers[] = {regs->rax, regs->rdi, regs->rsi,
        regs->rdx, regs->r10, regs->r8, regs->r9};
    fmt_type_t args[NB_PARAMS] = {0};
    char *params_string;

    fprintf(stderr, "Syscall %s(", table.name);
    display_args(registers, table, args);
    params_string = concat_args(args);
    fprintf(stderr, "%s) = %s\n", params_string, *args[0] ? args[0] : "?");
    for (int i = 0; i < NB_PARAMS && args[i]; i++) {
        free(args[i]);
    }
}
