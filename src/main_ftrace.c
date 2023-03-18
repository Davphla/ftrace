/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#include "ftrace.h"
#include "utils/error.h"
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

int manage_signal(const int pid)
{
    siginfo_t sig;

    ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig);
    if (!(sig.si_signo & (SIGTRAP | 0x80))) {
        fprintf(stderr, "Received signal SIG%s\n", sigabbrev_np(sig.si_signo));
        return sig.si_signo;
    }
    return 0;
}

static bool ptrace_logic(const pid_t pid, struct user_regs_struct *regs)
{
    long opcode;
    int signal = manage_signal(pid);

    ptrace(PTRACE_GETREGS, pid, 0, regs);
    opcode = ptrace(PTRACE_PEEKDATA, pid, regs->rip, 0);
    if (errno != 0 && opcode == -1)
        return true;
    manage_opcode(opcode, pid, regs);
    if (ptrace(PTRACE_SINGLESTEP, pid, 0, signal) == -1) {
        if (errno == ESRCH)
            NOT_FATAL("Process exited");
        return true;
    }
    return false;
}

static void main_loop(const pid_t pid)
{
    struct user_regs_struct regs;
    int status = 0;

    waitpid(pid, &status, 0);
    while (!WIFEXITED(status)) {
        if (ptrace_logic(pid, &regs))
            break;
        waitpid(pid, &status, 0);
    }
    if (status != 0)
        FATAL("Command failed with status code %d", status);
    fprintf(stderr, "+++ exited with %d +++\n", WEXITSTATUS(status));
}

void main_ftrace(char *const *av)
{
    pid_t pid = setup_ptrace(av);

    main_loop(pid);
}
