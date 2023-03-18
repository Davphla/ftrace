/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#include "syscall.h"
#include "opcodes.h"

void asm_syscall(user_regs regs, UNUSED const pid_t pid)
{
    if (regs->rax >= LEN(SYSCALL_TABLE))
        return;
    print_syscall(regs);
}
