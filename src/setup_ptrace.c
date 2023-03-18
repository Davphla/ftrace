/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#include "ftrace.h"
#include <sys/ptrace.h>

pid_t setup_ptrace(char *const *av)
{
    pid_t pid = fork();

    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0);
        if (execvp(av[1], av + 1) == -1)
            FATAL("Non existing command");
    }
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);
    return pid;
}
