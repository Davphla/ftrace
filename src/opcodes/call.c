/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#include "opcodes.h"
#include <sys/ptrace.h>
#include <sys/wait.h>

void asm_call(user_regs regs, const pid_t pid)
{
    int signal = manage_signal(pid);
    unsigned long long value = regs->rip;

    if (ptrace(PTRACE_SINGLESTEP, pid, 0, signal) == -1)
        return;
    waitpid(pid, NULL, 0);
    ptrace(PTRACE_GETREGS, pid, 0, regs);
    printf("Entering function ");
    value = regs->rip;
    printf("func_%#llx@%s", value, "a.out");
    printf(" at %#llx\n", value);
    add_context(regs->rip);
}
